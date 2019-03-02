#pragma once

#include "LCDController.h"

namespace CharLCD::Symbols
{
    namespace Media
    {
        extern const LCDController::Symbol play;
        extern const LCDController::Symbol pause;
        extern const LCDController::Symbol previous;
        extern const LCDController::Symbol next;
        extern const LCDController::Symbol stop;
    }

    namespace Arrows
    {
        extern const LCDController::Symbol left;
        extern const LCDController::Symbol right;
        extern const LCDController::Symbol up;
        extern const LCDController::Symbol down;
    }

    namespace Units
    {
        extern const LCDController::Symbol degrees;
        extern const LCDController::Symbol degreesC;
    }
}
