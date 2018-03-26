#include "LCDController.h"
#include <lcd.h>

namespace CharLCD
{
    LCDController::LCDController(LCDBackend lcd)
        : lcd(std::move(lcd)), numRows(lcd.getRows()), numCols(lcd.getCols())
    {
        state = {
            true,
            -1,
            -1,
            {},
            {}
        };
        state.displayChars.resize(numRows * numCols);
        displayBuffer.resize(numRows * numCols);

        this->lcd.power(true);
        this->lcd.clear();
    }

    void LCDController::power(bool on)
    {
        if (state.power != on)
        {
            state.power = on;
            lcd.power(on);
        }
    }

    void LCDController::drawString(const std::string &string, Location location, TextAlignment alignment)
    {
        if (location.row < 0 || location.row >= numRows)
        {
            return;
        }
        // Get range of columns to draw the string within
        int startCol = 0;
        switch (alignment)
        {
        case TextAlignment::left:
            startCol = location.col;
            break;
        case TextAlignment::right:
            startCol = location.col - (string.size() - 1);
            break;
        case TextAlignment::center:
            startCol = location.col - ((string.size() - 1) / 2);
            break;
        }
        // Write each character of the string to display buffer
        for (int i = 0; i < string.size(); ++i)
        {
            int col = i + startCol;
            // Check column is on the screen
            if (col < 0 || col >= numCols)
            {
                continue;
            }
            int index = indexForLocation({location.row, col});
            displayBuffer[index] = {false, string[i]};
        }
    }

    void LCDController::drawSymbol(const Symbol &symbol, Location location)
    {
        BufferChar bc = {true};
        bc.symbol = symbol;
        displayBuffer[indexForLocation(location)] = bc;
    }

    void LCDController::update()
    {
        for (int row = 0; row < numRows; ++row)
        {
            for (int col = 0; col < numCols; ++col)
            {
                int index = indexForLocation({row, col});
                lcd.moveCursor(row, col);
                uint8_t c = displayBuffer[index].rawChar;
                if (c == 0) c = ' ';
                lcd.writeChar(c);
            }
        }
    }

    unsigned LCDController::indexForLocation(Location location)
    {
        return location.row * numCols + location.col;
    }
}