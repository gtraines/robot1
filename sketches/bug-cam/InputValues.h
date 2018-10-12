#ifndef INPUTVALUES_H
#define INPUTVALUES_H

class InputValues
{
public:
    InputValues();
    ~InputValues();
    Buttons buttons;
    HatInputs rightHat;
    HatInputs leftHat;
};

class Buttons {
public:
    int R1;
    int R2;
    int L1;
    int L2;
};

class DirectionalPad {
    int Up;
    int Down;
    int Left;
    int Right;
}
struct HatInputs {
    float X;
    float Y;
}
#endif // INPUTVALUES_H
