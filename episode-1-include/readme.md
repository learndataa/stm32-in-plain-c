# Episode 1: `#include`

**Video:** _(add link once published)_

## The idea
`#include` isn't magic — it copies the contents of another file into
this one, before the compiler does anything else. `stm32f0xx_hal.h`
defines things like `GPIO_InitTypeDef`, `HAL_GPIO_WritePin`, and
`GPIO_PIN_4`. Without the include, none of those words exist as far as
the compiler is concerned.

## Try it yourself
1. Build and flash `main.c` as-is — the onboard LED (PA4) should blink
   once per second.
2. Comment out the `#include "stm32f0xx_hal.h"` line and rebuild.
3. Read the errors — you'll see things like `unknown type name
   'GPIO_InitTypeDef'`. That's the proof: those names only exist
   because the include brought them in.
4. Uncomment the line, rebuild, confirm the LED blinks again.

## Wiring
Same single-LED setup as earlier Hardware Conversations episodes:
PA4 → 220Ω resistor → LED anode, LED cathode → GND.
