#include "LCDBackend.h"

using namespace CharLCD;

int main(void)
{
    LCDBackend lcd({
        LCDBackend::PinConfig::PinType::board,
        true, // 4 data pins
        true, // has backlight pin
        12, // backlight
        21, // rs
        19, // en
        10, // d7
        15, // d6
        16, // d5
        18, // d4
        0,
        0,
        0,
        0
    });

    lcd.clear();
    lcd.moveCursor(0, 8);
    lcd.writeChar('A');
    return 0;
}
