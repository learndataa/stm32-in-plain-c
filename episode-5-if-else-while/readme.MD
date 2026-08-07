# Episode 5: The Loop That Never Ends (On Purpose)

**Video:** 

> This episode needs the board connected and flashed - the proof is
> behavioral. See the
> [Hardware setup section](../README.md#hardware-setup-read-this-first-if-youre-new-here)
> in the root README if you haven't wired up yet.

## The idea
`if/else` picks between two paths based on a condition - `blink_count
< 5` is either true or false, and only one branch runs.

`while(1)` loops forever, on purpose. In Python, a script finishes and
exits back to the operating system. Bare-metal C on a microcontroller
has no operating system underneath it waiting to receive a "return
value" from `main` - there's nothing for it to return *to*. So `main`
is never allowed to actually finish. `while(1)` is what keeps the
program alive and running, deliberately, permanently.

## Try it yourself
1. Build and flash `main.c` as-is.
2. Watch the LED: it blinks 5 times, then goes solid on and **stays
   there** - it doesn't turn off, and the program doesn't stop or
   restart. It's still running, still looping, just permanently
   landing on the `else` branch now that `blink_count` has stopped
   changing.
3. Change `blink_count < 5` to `blink_count < 10` and reflash - now it
   blinks 10 times before going solid, proving the `if` condition is
   genuinely controlling the branch, not just decorative.

## Why the outer `while(1)` can't be removed
If you deleted the outer `while(1)` and just let the `if/else` run
once inside `main`, the function would reach its closing brace and
try to return - like any other C function. But unlike a normal
function that returns to whatever called it, `main` on bare-metal
hardware has no operating system above it to return to. What actually
happens next depends on your specific startup code and toolchain -
this isn't something with one universal guaranteed behavior, which is
exactly why `while(1)` is used deliberately rather than left out.

## Wiring
Same single-LED setup as earlier episodes:
PA4 → 220Ω resistor → LED anode, LED cathode → GND.
