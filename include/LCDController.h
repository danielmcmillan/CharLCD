#pragma once

#include <cstdint>
#include <array>
#include <vector>
#include "LCDBackend.h"

namespace CharLCD
{
    /**
     * High-level controller for a character LCD.
     * Changes are made to a separate buffer which is written to the display when calling update.
     * Custom character memory is managed automatically.
     */
    class LCDController
    {
        // Store current state of the display
        // - raw characters and symbols on the screen
        // - symbols currently in memory
        // - control state

        // No need to support enabling different modes (e.g. showing cursor or whatever) not the purpose of this
    public:
        /**
         * Alignment to control drawing text to the screen.
         */
        enum class TextAlignment
        {
            left = 0,
            center = 1,
            right = 2
        };

        /**
         * Character location on the display.
         */
        struct Location
        {
            int row;
            int col;
        };

        /**
         * Data for a custom symbol.
         * Array of bytes defining rows for the symbol bitmap.
         * First row is top row and lower bit is right-most column.
         */
        using Symbol = std::array<uint8_t, 8>;

        LCDController(LCDBackend lcd);

        /**
         * Turn the display on or off.
         * @param on Whether the display should be on.
         */
        void power(bool on);

        /**
         * Draw a string to the display buffer.
         * @param string String containing ASCII characters.
         * @param location Character location on the display {row, col}
         * @param alignment Control location of text relative to the given location.
         */
        void drawString(const std::string &string, Location location, TextAlignment alignment = TextAlignment::left);

        /**
         * Draw a symbol to the display buffer.
         * @param symbol Bitmap for the symbol.
         * @param location Character location on the display {row, col}
         */
        void drawSymbol(const Symbol &symbol, Location location);

        /**
         * Clear the display buffer.
         */
        void clear();

        /**
         * Write the current display buffer to the display.
         */
        void update();

    private:
        struct DisplayState
        {
            bool power;
            int cursorCol;
            int cursorRow;
            std::vector<uint8_t> displayChars;
            std::array<Symbol, 8> customChars;
        };

        // Char for display buffer. Either raw character, or custom bitmap.
        struct BufferChar
        {
            bool custom;
            union {
                uint8_t rawChar;
                Symbol symbol;
            };
        };

        // BufferChar representing an empty spot
        static const BufferChar emptyChar;

        // Get the index for character at given location
        unsigned indexForLocation(Location location);

        // Update the state of the display with the given characters and custom symbols.
        // customChars must be no longer than 8
        void writeToDisplay(const std::vector<uint8_t> &displayChars, const std::vector<Symbol> &customChars);

        LCDBackend lcd;
        int numRows;
        int numCols;
        // The data that has been committed to the display
        DisplayState state;
        // Characters/symbols buffered for display on next update
        std::vector<BufferChar> displayBuffer;
    };
}
