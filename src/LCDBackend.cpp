#include "LCDBackend.h"
#include <wiringPi.h>
#include <lcd.h>

namespace CharLCD
{
    LCDBackend::LCDBackend(const PinConfig &pinConfig, int rows, int cols) : rows(rows), cols(cols)
    {
        // Setup WiringPi with pin number type specified in pinConfig
        switch (pinConfig.pinType)
        {
        case PinConfig::PinType::wiringPi:
            wiringPiSetup();
        case PinConfig::PinType::gpio:
            wiringPiSetupGpio();
        case PinConfig::PinType::board:
            wiringPiSetupPhys();
        }

        // Initialise WiringPi LCD library
        if (pinConfig.has4DataPins)
        {
            // Wiring PI data pin numbers are wrong when set to 4 pins
            lcdHandle = lcdInit(rows, cols, 4, pinConfig.rs, pinConfig.en, pinConfig.d4, pinConfig.d5, pinConfig.d6, pinConfig.d7, 0, 0, 0, 0);
        }
        else
        {
            lcdHandle = lcdInit(rows, cols, 8, pinConfig.rs, pinConfig.en, pinConfig.d0, pinConfig.d1, pinConfig.d2,
                pinConfig.d3, pinConfig.d4, pinConfig.d5, pinConfig.d6, pinConfig.d7);
        }

        // Initialise backlight pin if specified
        if (pinConfig.hasBacklightPin)
        {
            backlightPin = pinConfig.backlight;
            pinMode(backlightPin, OUTPUT);
            // Defaults to display on
            digitalWrite(backlightPin, true);
        }
        else
        {
            backlightPin = -1;
        }
    }

    LCDBackend::LCDBackend(LCDBackend &&that)
    {
        lcdHandle = that.lcdHandle;
        backlightPin = that.backlightPin;
        rows = that.rows;
        cols = that.cols;

        that.lcdHandle = -1;
        that.backlightPin = -1;
    }

    LCDBackend& LCDBackend::operator=(LCDBackend&& that)
    {
        lcdHandle = that.lcdHandle;
        backlightPin = that.backlightPin;
        rows = that.rows;
        cols = that.cols;

        that.lcdHandle = -1;
        that.backlightPin = -1;
        return *this;
    }

    void LCDBackend::power(bool on)
    {
        lcdDisplay(lcdHandle, on);
        if (backlightPin >= 0)
        {
            digitalWrite(backlightPin, on);
        }
    }

    void LCDBackend::clear()
    {
        lcdClear(lcdHandle);
    }

    void LCDBackend::cursor(bool on, bool blink)
    {
        lcdCursor(lcdHandle, on);
        lcdCursorBlink(lcdHandle, blink);
    }

    void LCDBackend::moveCursor(int row, int col)
    {
        lcdPosition(lcdHandle, col, row);
    }

    void LCDBackend::defineChar(int index, std::array<uint8_t, 8> data)
    {
        lcdCharDef(lcdHandle, index, data.data());
    }

    void LCDBackend::writeChar(uint8_t data)
    {
        lcdPutchar(lcdHandle, data);
    }
}
