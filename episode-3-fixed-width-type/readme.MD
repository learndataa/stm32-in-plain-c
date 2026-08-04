# Episode 3: Fixed-Width Types

**Video:** _

## The idea
`uint8_t`, `uint16_t`, and `uint32_t` guarantee an exact number of
bits - 8, 16, and 32 respectively - unlike plain `int`, whose exact
size isn't guaranteed to be the same across every platform. Embedded
registers and HAL structs expect fields of a precise width, which is
why HAL code uses these types instead of plain `int`.

`uint8_t` holds values 0 to 255 - exactly 8 bits, nothing more. Unlike
a missing `#include` or a renamed `main`, going outside that range
doesn't stop the build. It compiles anyway, and the value silently
wraps to something else.

## Try it yourself
1. Build and flash `main.c` as-is - the onboard LED (PA4) should turn
   on briefly then blink once per second, same as before.
2. Change `uint8_t counter = 5;` to `uint8_t counter = 300;` and try
   to **build** - no flashing needed for this step.
3. Notice: it still builds. Look for a compiler warning instead of an
   error - something like `large integer implicitly truncated to
   unsigned type`. 300 doesn't fit in 8 bits, so what actually gets
   stored is 300 − 256 = 44, not 300.
4. Change it back to a value that fits (0-255), confirm the warning
   disappears.

## Wiring
Same single-LED setup as earlier episodes:
PA4 → 220Ω resistor → LED anode, LED cathode → GND.
