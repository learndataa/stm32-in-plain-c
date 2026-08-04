# Episode 2: `int main(void)`

**Video:** 

## The idea
Every C program needs exactly one function named exactly `main`. It's
not a convention or a suggestion - it's the fixed name the toolchain's
linker looks for as the program's entry point. `void` means main takes
no input arguments. The curly braces `{ }` mark the start and end of
everything that runs inside it.

## Try it yourself
1. Build and flash `main.c` as-is - the onboard LED (PA4) should blink
   once per second.
2. Rename `main` to something else (e.g. `run`) and try to **build**
   - no flashing needed, this fails at the link step.
3. Read the error - something like `undefined reference to 'main'`.
   That's the proof: the toolchain was specifically looking for that
   exact name.
4. Rename it back to `main`, build again to confirm it succeeds, then
   flash to confirm the LED blinks again.

## Wiring
Same single-LED setup as earlier episodes:
PA4 → 220Ω resistor → LED anode, LED cathode → GND.
