#include <Arduino.h>
#include <avr/portpins.h>
#include <avr/interrupt.h>
#include <avr/io.h>
#include <CppList.h>
#include "IrInterruptConfig.h"
#include "IrParams.h"
#include "IrReceiver.h"
#include "boarddefs.h"
#include "IrRxBase.h"

IrParams_t IrReceiver::irParams = IrParams_t();
IrReceiver::IrReceiver(int recvpin){

    irParams.recvpin = (uint8_t)recvpin;
    irParams.blinkflag = 0;
    irParams.rawlen = 0;
    irParams.rcvstate = STATE_IDLE;
}

IrReceiver::~IrReceiver() {
}

void IrReceiver::enableIRIn() {
  // setup pulse clock timer interrupt
  TCCR2A = 0;  // normal mode

  //Prescale /8 (16M/8 = 0.5 microseconds per tick)
  // Therefore, the timer interval can range from 0.5 to 128 microseconds
  // depending on the reset value (255 to 0)
  cbi(TCCR2B,CS22);
  sbi(TCCR2B,CS21);
  cbi(TCCR2B,CS20);

  //Timer2 Overflow Interrupt Enable
  sbi(TIMSK2,TOIE2);

  RESET_TIMER2;

  sei();  // enable interrupts

  // initialize state machine variables
  irParams.rcvstate = STATE_IDLE;
  irParams.rawlen = 0;

  // set pin modes
  pinMode(irParams.recvpin, INPUT);
}

// enable/disable blinking of pin 13 on IR processing
void IrReceiver::blink13(int blinkflag)
{
  irParams.blinkflag = (uint8_t)blinkflag;
}

// TIMER2 interrupt code to collect raw data.
// Widths of alternating SPACE, MARK are recorded in rawbuf.
// Recorded in ticks of 50 microseconds.
// rawlen counts the number of entries recorded so far.
// First entry is the SPACE between transmissions.
// As soon as a SPACE gets long, ready is set, state switches to IDLE, timing of SPACE continues.
// As soon as first MARK arrives, gap width is recorded, ready is cleared, and new logging starts

void ProcessOneIRParam() {

    IrRxBase::processSignalsIn(IrReceiver::irParams);
}

void IrReceiver::resume() {
  irParams.rcvstate = STATE_IDLE;
  irParams.rawlen = 0;
}

//+=============================================================================
// hashdecode - decode an arbitrary IR code.
// Instead of decoding using a standard encoding scheme
// (e.g. Sony, NEC, RC5), the code is hashed to a 32-bit value.
//
// The algorithm: look at the sequence of MARK signals, and see if each one
// is shorter (0), the same length (1), or longer (2) than the previous.
// Do the same with the SPACE signals.  Hash the resulting sequence of 0's,
// 1's, and 2's to a 32-bit value.  This will give a unique value for each
// different code (probably), for most code systems.
//
// http://arcfn.com/2010/01/using-arbitrary-remotes-with-arduino.html
//
// Compare two tick values, returning 0 if newval is shorter,
// 1 if newval is equal, and 2 if newval is longer
// Use a tolerance of 20%
//
int  IrReceiver::compare (unsigned int oldval,  unsigned int newval)
{
    if      (newval < oldval * .8)  return 0 ;
    else if (oldval < newval * .8)  return 2 ;
    else                            return 1 ;
}

// Decodes the received IR message
// Returns 0 if no data ready, 1 if data ready.
// Results of decoding are stored in results
int IrReceiver::decode(decode_results *results) {
	  results->rawbuf = irParams.rawbuf;
	  results->rawlen = irParams.rawlen;
	  if (irParams.rcvstate != STATE_STOP) {
	    return ERR;
	  }
	// decodeHash returns a hash on any input.
	// Thus, it needs to be last in the list.
	// If you add any decodes, add them before this.
	if (decodeHash(results))  return true ;

	// Throw away and start over
	resume();
	return false;

  // Throw away and start over
  resume();
  return ERR;
}
//+=============================================================================
// Use FNV hash algorithm: http://isthe.com/chongo/tech/comp/fnv/#FNV-param
// Converts the raw code values into a 32-bit hash code.
// Hopefully this code is unique for each button.
// This isn't a "real" decoding, just an arbitrary value.
//
#define FNV_PRIME_32 16777619
#define FNV_BASIS_32 2166136261

long IrReceiver::decodeHash (decode_results *results)
{
	long  hash = FNV_BASIS_32;

	// Require at least 6 samples to prevent triggering on noise
	if (results->rawlen < 6)  return false ;

	for (int i = 1;  (i + 2) < results->rawlen;  i++) {
		int value =  compare(results->rawbuf[i], results->rawbuf[i+2]);
		// Add value into the hash
		hash = (hash * FNV_PRIME_32) ^ value;
	}

	results->value       = hash;
	results->bits        = 32;
	results->decode_type = UNKNOWN;

	return true;
}

long IrReceiver::decodeSony(decode_results *results) {
  long data = 0;
  if (irParams.rawlen < 2 * SONY_BITS + 2) {
    return ERR;
  }
  int offset = 1; // Skip first space
  // Initial mark
  if (!MATCH_MARK(results->rawbuf[offset], SONY_HDR_MARK)) {
    return ERR;
  }
  offset++;

  while (offset + 1 < irParams.rawlen) {
    if (!MATCH_SPACE(results->rawbuf[offset], SONY_HDR_SPACE)) {
      break;
    }
    offset++;
    if (MATCH_MARK(results->rawbuf[offset], SONY_ONE_MARK)) {
      data = (data << 1) | 1;
    } 
    else if (MATCH_MARK(results->rawbuf[offset], SONY_ZERO_MARK)) {
      data <<= 1;
    } 
    else {
      return ERR;
    }
    offset++;
  }

  // Success
  results->bits = (offset - 1) / 2;
  if (results->bits < 12) {
    results->bits = 0;
    return ERR;
  }
  results->value = data;
  results->decode_type = SONY;
  return DECODED;
}

// Gets one undecoded level at a time from the raw buffer.
// The RC5/6 decoding is easier if the data is broken into time intervals.
// E.g. if the buffer has MARK for 2 time intervals and SPACE for 1,
// successive calls to getRClevel will return MARK, MARK, SPACE.
// offset and used are updated to keep track of the current position.
// t1 is the time interval for a single bit in microseconds.
// Returns -1 for error (measured time interval is not a multiple of t1).
int IrReceiver::getRClevel(decode_results *results, int *offset, int *used, int t1) {
  if (*offset >= results->rawlen) {
    // After end of recorded buffer, assume SPACE.
    return SPACE;
  }
  int width = results->rawbuf[*offset];
  int val = ((*offset) % 2) ? MARK : SPACE;
  int correction = (val == MARK) ? MARK_EXCESS : - MARK_EXCESS;

  int avail;
  if (MATCH(width, t1 + correction)) {
    avail = 1;
  } 
  else if (MATCH(width, 2*t1 + correction)) {
    avail = 2;
  } 
  else if (MATCH(width, 3*t1 + correction)) {
    avail = 3;
  } 
  else {
    return -1;
  }

  (*used)++;
  if (*used >= avail) {
    *used = 0;
    (*offset)++;
  }
#ifdef DEBUG
  if (val == MARK) {
    Serial.println("MARK");
  } 
  else {
    Serial.println("SPACE");
  }
#endif
  return val;   
}