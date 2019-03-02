Library that provides a C++ interface for an LCD display controlled by a HD44780, using wiringpi for Raspberry Pi for hardware functions.

Provides LCDBackend with basic low-level support for LCD functions, and LCDController that provides a higher-level interface and buffers display data.

## Building

```
cmake <root of repository>
make
```

## Usage

```
#include "LCDBackend.h"
#include "LCDController.h"
...
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
// Write text to the display buffer
controller.drawString("Hello world", {0, 7}, LCDController::TextAlignment::center);
// Write the buffered contents to the display's memory
controller.update();
...
```

Custom symbols are supported, and LCDController manages their storage in display memory automatically (see `bounce.cpp` for example usage). Some predefined symbols are provided in `Symbols.h`.

## TODO

* Support brightness control of the backlight using hardware PWM
* Add support for drawing basic primitives to LCDController
* Improve efficiency by reordering custom symbols to reduce the number of writes required
* Support alternate LCDBackend implementations
