#include "Symbols.h"

namespace CharLCD::Symbols
{
namespace Media
{
    const LCDController::Symbol play = {{
        0b00000,
        0b01000,
        0b01100,
        0b01110,
        0b01100,
        0b01000,
        0b00000,
        0b00000,
    }};
    const LCDController::Symbol pause = {{
        0b00000,
        0b11011,
        0b11011,
        0b11011,
        0b11011,
        0b11011,
        0b00000,
        0b00000,
    }};
    const LCDController::Symbol previous = {{
        0b00000,
        0b10001,
        0b10011,
        0b10111,
        0b10011,
        0b10001,
        0b00000,
        0b00000,
    }};
    const LCDController::Symbol next = {{
        0b00000,
        0b10100,
        0b10110,
        0b10111,
        0b10110,
        0b10100,
        0b00000,
        0b00000,
    }};
    const LCDController::Symbol stop = {{
        0b00000,
        0b11111,
        0b11111,
        0b11111,
        0b11111,
        0b11111,
        0b00000,
        0b00000,
    }};
}

namespace Arrows
{
    const LCDController::Symbol left = {{
        0b00000,
        0b00100,
        0b01000,
        0b11111,
        0b01000,
        0b00100,
        0b00000,
        0b00000,
    }};
    const LCDController::Symbol right = {{
        0b00000,
        0b00100,
        0b00010,
        0b11111,
        0b00010,
        0b00100,
        0b00000,
        0b00000,
    }};
    const LCDController::Symbol up = {{
        0b00000,
        0b00100,
        0b01110,
        0b10101,
        0b00100,
        0b00100,
        0b00000,
        0b00000,
    }};
    const LCDController::Symbol down = {{
        0b00000,
        0b00000,
        0b00100,
        0b00100,
        0b10101,
        0b01110,
        0b00100,
        0b00000,
    }};
}

namespace Units
{
    const LCDController::Symbol degrees = {{
        0b01100,
        0b01100,
        0b00000,
        0b00000,
        0b00000,
        0b00000,
        0b00000,
        0b00000,
    }};
    const LCDController::Symbol degreesC = {{
        0b11000,
        0b11000,
        0b00011,
        0b00100,
        0b00100,
        0b00100,
        0b00011,
        0b00000,
    }};
}
}