# Episode 1: `#include`

**Video:** _(add link once published)_

## The idea
`#include` isn't magic — it copies the contents of another file into
this one, before the compiler does anything else. `stm32f0xx_hal.h`
defines things like `HAL_Delay` and everything else prefixed `HAL_`.
Without the include, none of those names exist as far as the compiler
is concerned.

This example uses the project's shared `bsp.h`/`bsp.c` (see the
repo root README) for setup, so `main.c` stays focused on just this
episode's concept.

## Try it yourself
1. Build and flash `main.c` as-is — the onboard LED (PA4) should blink
   once per second.
2. Comment out the `#include "stm32f0xx_hal.h"` line and try to
   **build** (compile) — no flashing needed for this step, since the
   failure happens before a binary is even produced.
3. Read the build errors — `HAL_Delay` and `HAL_Init` (called inside
   `BSP_Init`) will be reported as undefined. That's the proof: those
   names only exist because the include brought them in.
4. Uncomment the line, build again to confirm it succeeds, then flash
   to confirm the LED blinks again.

## Wiring
Same single-LED setup as earlier Hardware Conversations episodes:
PA4 → 220Ω resistor → LED anode, LED cathode → GND.
