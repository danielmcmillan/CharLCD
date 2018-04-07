#include <chrono>
#include <thread>
#include "LCDBackend.h"
#include "LCDController.h"
#include "Symbols.h"

using namespace CharLCD;

static const int charWidth = 5;
static const int charHeight = 8;
static const std::chrono::milliseconds updateDelay = std::chrono::milliseconds(100);

struct Vector2
{
    int x;
    int y;
};

Vector2 operator+(const Vector2 &a, const Vector2 &b)
{
    return Vector2({a.x + b.x, a.y + b.y});
}

int main(void)
{
    LCDBackend lcd({LCDBackend::PinConfig::PinType::board,
        true, // 4 data pins
        true, // has backlight pin
        12,   // backlight
        21,   // rs
        19,   // en
        10,   // d7
        15,   // d6
        16,   // d5
        18,   // d4
        0,
        0,
        0,
        0});

    LCDController controller(std::move(lcd));

    const int width = charWidth * lcd.getCols();
    const int height = charHeight * lcd.getRows();
    Vector2 position = {0, 0};
    Vector2 velocity = {2, 1};

    while (true)
    {
        // Compute new location
        position = position + velocity;
        if (position.x < 0 || position.x >= width)
        {
            velocity.x *= -1;
            position.x += 2*velocity.x;
        }
        if (position.y < 0 || position.y >= height)
        {
            velocity.y *= -1;
            position.y += 2*velocity.y;
        }

        // Compute corresponding character
        int col = position.x / charWidth;
        int row = position.y / charHeight;
        // Compute location within character
        int x = position.x % charWidth;
        int y = position.y % charHeight;

        // Create symbol
        LCDController::Symbol symbol = {{
            0b00000,
            0b00000,
            0b00000,
            0b00000,
            0b00000,
            0b00000,
            0b00000,
            0b00000
        }};
        symbol[y] |= 1 << (charWidth - x - 1);

        // Update the screen
        controller.drawSymbol(symbol, {row, col});
        controller.update();
        controller.clear();
        std::this_thread::sleep_for(std::chrono::milliseconds(updateDelay));
    }

    return 0;
}
