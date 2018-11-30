#ifndef IR_RECEIVER__H
#define IR_RECEIVER__H

#include <Arduino.h>
#include "IrInterruptConfig.h"
#include "IrParams.h"
#include "IRremote.h"

class IrReceiver {
public:
    IrReceiver(int recvpin);
    ~IrReceiver();
    void enableIRIn();
    void blink13(int blinkflag);
    int decode(decode_results *results);
    void resume();
    static IrParams_t irParams;
private:
    int compare (unsigned int oldval,  unsigned int newval);
    long decodeHash (decode_results *results);
    long decodeSony(decode_results *results);
    int getRClevel(decode_results *results, int *offset, int *used, int t1);
};

#endif // IR_RECEIVER__H