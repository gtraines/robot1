#include <Arduino.h>
#include "IRremoteInt.h"
#include "IRremote.h"

#ifndef IrReceiver_h
#define IrReceiver_h

class IrReceiver {
public:
    IrReceiver(int recvpin);
    ~IrReceiver();
    void enableIRIn();
    void blink13(int blinkflag);
    int decode(decode_results *results);
    void resume();
private:
    irparams_t irparams;
    int compare (unsigned int oldval,  unsigned int newval);
    long decodeHash (decode_results *results);
    long decodeSony(decode_results *results);
    int getRClevel(decode_results *results, int *offset, int *used, int t1);
};

#endif