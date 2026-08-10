# Episode 7: Pointers and &

**Video:** 

> This episode needs the board connected and flashed - the proof is
> a speed change you can see. See the
> [Hardware setup section](../README.md#hardware-setup-read-this-first-if-youre-new-here)
> in the root README if you haven't wired up yet.

## The idea
Passing a variable to a normal function hands the function a **copy**.
Anything the function does to that copy is lost the instant it
returns - the original variable back in `main` never changes.

```c
static void try_by_value(uint16_t x)
{
  x = 100; // only the copy changes
}
```

A pointer works differently - instead of a copy of the *value*, you
pass the variable's **address**: literally, where it lives in memory.
`&delay_ms` means "the address of delay_ms." The function can then use
`*x` ("go to that address") to reach through and change the real
variable:

```c
static void try_by_pointer(uint16_t *x)
{
  *x = 100; // changes the real variable, through its address
}
```

This is exactly why `HAL_ADC_Init(&hadc1)` uses `&` throughout this
series - HAL needs to actually modify your real `hadc1`, not a copy
that disappears the moment the function ends.

## Try it yourself
1. Build and flash `main.c` as-is.
2. Watch the LED: it blinks **slowly** for a few seconds first (500ms)
   - proof that `try_by_value` had no real effect on `delay_ms`. Then
   it switches to a **fast** blink and stays fast forever - proof that
   `try_by_pointer` genuinely changed `delay_ms` to 100.
3. Bonus - try removing the `&` from `try_by_pointer(&delay_ms);` so
   it reads `try_by_pointer(delay_ms);` and try to **build**. This
   fails - `try_by_pointer` expects an address (`uint16_t *`), not a
   plain value (`uint16_t`). The `&` isn't optional decoration; it's
   type-checked by the compiler.

## Wiring
Same single-LED setup as earlier episodes:
PA4 → 220Ω resistor → LED anode, LED cathode → GND.
