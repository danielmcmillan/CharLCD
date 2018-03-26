#include "LCDBackend.h"
#include "LCDController.h"

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

    LCDController controller(std::move(lcd));
    controller.drawString("Hello world!", {1, 8}, LCDController::TextAlignment::center);
    controller.update();
    return 0;
}
