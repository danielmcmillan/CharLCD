#include "LCDController.h"
#include <algorithm>
#include <iterator>
#include <cassert>
#include <lcd.h>

namespace CharLCD
{
    const LCDController::BufferChar LCDController::emptyChar = {false, {' '}};

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
        state.displayChars.resize(numRows * numCols, ' ');
        displayBuffer.resize(numRows * numCols, emptyChar);

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

    void LCDController::clear()
    {
        std::fill(displayBuffer.begin(), displayBuffer.end(), emptyChar);
    }

    void LCDController::update()
    {
        // New screen character data
        std::vector<uint8_t> displayChars(displayBuffer.size());
        std::vector<Symbol> customChars;

        for (int i = 0; i < displayBuffer.size(); ++i)
        {
            const BufferChar &bufferChar = displayBuffer[i];
            if (bufferChar.custom)
            {
                // For symbol, need to reference a custom character
                std::vector<Symbol>::iterator it = std::find(customChars.begin(), customChars.end(), bufferChar.symbol);
                if (it != customChars.end())
                {
                    // Symbol already exists in customChars
                    displayChars[i] = std::distance(customChars.begin(), it);
                }
                else if (customChars.size() < 8)
                {
                    // Add new symbol
                    displayChars[i] = customChars.size();
                    customChars.push_back(bufferChar.symbol);
                }
                else
                {
                    // No room for the symbol
                    displayChars[i] = ' ';
                }
            }
            else
            {
                // Store normal characters directly
                displayChars[i] = bufferChar.rawChar;
            }
        }

        writeToDisplay(displayChars, customChars);
    }

    unsigned LCDController::indexForLocation(Location location)
    {
        return location.row * numCols + location.col;
    }

    void LCDController::writeToDisplay(const std::vector<uint8_t> &displayChars, const std::vector<Symbol> &customChars)
    {
        assert(customChars.size() <= 8);
        // Write the custom characters
        for (int i = 0; i < customChars.size(); ++i)
        {
            if (customChars[i] != state.customChars[i])
            {
                lcd.defineChar(i, customChars[i]);
                state.customChars[i] = customChars[i];
            }
        }
        // Write the screen contents
        for (int row = 0; row < numRows; ++row)
        {
            for (int col = 0; col < numCols; ++col)
            {
                int index = indexForLocation({row, col});
                // Check whether an update is needed at this location
                if (displayChars[index] != state.displayChars[index])
                {
                    // Check whether the cursor needs to be moved
                    if (state.cursorCol != col || state.cursorRow != row)
                    {
                        lcd.moveCursor(row, col);
                    }
                    lcd.writeChar(displayChars[index]);
                    // Cursor moves to the right after writing
                    state.cursorCol = col + 1;
                    state.cursorRow = row;
                }
            }
        }
        state.displayChars = displayChars;
    }
}
