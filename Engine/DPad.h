#ifndef DPAD_H
#define DPAD_H

#include "PinNames.h"

class DPad {

    private:
        bool _left;
        bool _right;
        bool _up; 
        bool _down;

    public:
        DPad(PinName left, PinName right, PinName up, PinName down);
};

#endif