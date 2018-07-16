
#ifndef DECODE_RESULTS__H
#define DECODE_RESULTS__H

// Results returned from the decoder
class decode_results {
public:
    int decode_type; // NEC, SONY, RC5, UNKNOWN
    unsigned long value; // Decoded value
    int bits; // Number of bits in decoded value
    volatile unsigned int *rawbuf; // Raw intervals in .5 us ticks
    int rawlen; // Number of records in rawbuf.
};

#endif // decode_results