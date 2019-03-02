#pragma once

#include <cstdint>
#include <array>

namespace CharLCD
{
    /**
     * Backend for LCD using the WiringPi library, supports backlight control.
     */
    class LCDBackend
    {
    public:
        struct PinConfig
        {
            enum class PinType
            {
                wiringPi = 0, // GPIO pins numbered starting from 0 (see wiringpi docs)
                gpio = 1, // Broadcom SOC channel numbering
                board = 2 // Numbers corresponding to pin numbers on the RPi GPIO header
            } pinType;
            bool has4DataPins;
            bool hasBacklightPin;
            int backlight;
            int rs;
            int en;
            int d7;
            int d6;
            int d5;
            int d4;
            int d3;
            int d2;
            int d1;
            int d0;
        };

        LCDBackend(const PinConfig &pinConfig, int rows = 2, int cols = 16);
        LCDBackend(const LCDBackend &that) = delete;
        LCDBackend& operator=(const LCDBackend& that) = delete;

        LCDBackend(LCDBackend &&that);
        LCDBackend& operator=(LCDBackend&& that);

        int getRows() { return rows; }
        int getCols() { return cols; }

        /**
         * Turn the display (including the backlight) on or off.
         * @param on True for on, false for off.
         */
        void power(bool on);

        /**
         * Clear the LCD display.
         */
        void clear();

        /**
         * Set the cursor mode.
         * @param on Whether the cursor is displayed.
         * @param blink Whether the cursor should blink.
         */
        void cursor(bool on, bool blink);

        /**
         * Move the cursor position.
         * @param row Row for cursor, 0 is top.
         * @param col Column for cursor, 0 is left.
         */
        void moveCursor(int row, int col);

        /**
         * Write to display RAM to define a custom character bitmap.
         * @param index Location in character memory to write to, from 0 to 7.
         * @param data Array of bytes defining character rows; first is top row and lower bit is right-most column.
         */
        void defineChar(int index, std::array<uint8_t, 8> data);

        /**
         * Write a character to the display at the specified location.
         * @param data Character value, which can be ASCII value or from 0 to 7 to address custom characters in RAM.
         */
        void writeChar(uint8_t data);

    private:
        int lcdHandle;
        int backlightPin;
        int rows;
        int cols;
    };
}
