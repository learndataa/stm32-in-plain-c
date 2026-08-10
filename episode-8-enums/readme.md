# Episode 8: Enums / Named Constants

**Video:** _(add link once published)_

> This episode needs the board connected and flashed - the proof is
> a flash pattern plus a speed change you can see. See the
> [Hardware setup section](../README.md#hardware-setup-read-this-first-if-youre-new-here)
> in the root README if you haven't wired up yet.

## The idea
`GPIO_PIN_4` isn't magic, and it isn't special syntax - it's just a
name for a plain number, defined once inside a HAL header file. Every
`GPIO_PIN_4` used since episode 2 has secretly just been a number
wearing a label the whole time.

```c
typedef enum
{
  SPEED_SLOW = 500,
  SPEED_FAST = 100,
} BlinkSpeed;
```

`SPEED_SLOW` isn't a special "speed" thing - it **is** the number
500. `SPEED_FAST` **is** 100. An enum is just a list of named
constants; the name exists purely to make the code readable to a
human, and gets replaced with the plain number underneath.

Named constants aren't unique to enums either - HAL pin names like
`GPIO_PIN_4` work the same way, defined as constants tied to a
specific bit position (each pin corresponds to one bit in a hardware
register - `GPIO_PIN_4` selects bit 4). Different mechanism under the
hood than our `BlinkSpeed` enum, same underlying idea: a name
standing in for a number.

![Simplified STM32 chip outline with pins on four sides](./docs/stm32-simplified-pins.png)

This is a simplified illustration, not the real pinout - it shows 6
example pins per side to stay legible. In reality, the STM32F051C8T6
is a 48-pin LQFP48 package: **12 real pins per side, 48 total**. See
the actual datasheet for the exact, full pin order.

## Try it yourself
1. Build and flash `main.c` as-is.
2. Watch the LED: two quick flashes first - proof that
   `GPIO_PIN_4 == 0x0010` is literally true, the exact constant
   you've been using since episode 2 to wire up this very LED. Then
   a slow, steady blink - because `HAL_Delay(current_speed)` is
   really just `HAL_Delay(500)` underneath the `SPEED_SLOW` name.
3. Change `BlinkSpeed current_speed = SPEED_SLOW;` to
   `SPEED_FAST` and reflash - the blink speeds up, because the name
   changed which plain number gets used, nothing more.

## Wiring
Same single-LED setup as earlier episodes:
PA4 → 220Ω resistor → LED anode, LED cathode → GND.
