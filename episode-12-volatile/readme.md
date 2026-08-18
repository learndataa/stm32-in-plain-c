# Episode 12: volatile — "Why the Compiler Deletes Code You Needed"

## The idea

Optimizing compilers work off an assumption: if nothing in the code you can see changes a variable, its value won't change — so the compiler can skip re-reading it, or even delete the check entirely. Most of the time that assumption is correct and the optimization is exactly what you want.

It's wrong when the variable can change from *outside* the code the compiler can see — for example, a hardware register, or a variable an interrupt handler updates. The compiler doesn't know about that. It just sees a variable nothing touches, and "helpfully" removes the re-check.

`volatile` turns that assumption off for a specific variable: "don't assume — actually re-read this every single time, no matter what."

This episode is **build-only**, and unlike previous episodes, the proof isn't a compile-time check — it's reading the actual assembly the compiler generates, with and without `volatile`, and seeing the difference with your own eyes.

## The code

See [`main.c`](./main.c). No `#include "bsp.h"` — no hardware step.

```c
uint8_t flag = 0;

void wait_for_flag(void) {
    while (flag == 0) {
    }
}
```

This is a classic embedded pattern: "sit here until something else sets `flag`." In real firmware, that "something else" is usually an interrupt handler running independently of `main()`.

## Try it yourself

**Hardware required?** No. Build-only — you'll be reading generated assembly, not flashing anything.

1. Build as-is (no `volatile` yet):
   ```
   pio run
   ```
   Then disassemble just this function. PlatformIO's ARM toolchain lives under your PlatformIO packages folder — find `arm-none-eabi-objdump` there (typically inside `~/.platformio/packages/toolchain-gccarmnoneeabi/bin/`), then run:
   ```
   arm-none-eabi-objdump -d .pio/build/disco_f051r8/firmware.elf | grep -A 10 "<wait_for_flag>:"
   ```
   **Expected result:** the function reads `flag` **once**, compares it, and — if it was zero — falls into a self-loop that jumps to itself forever *without ever reading memory again*. The compiler decided nothing could change `flag`, so it stopped checking.

2. Add `volatile` to the declaration:
   ```c
   volatile uint8_t flag = 0;
   ```
   Rebuild and disassemble the same function again.
   **Expected result:** the function now re-reads `flag` from memory on **every** loop iteration (a `load`, then a compare, then a branch back to the load) — the correct behavior for a variable that can change outside the compiler's view.

   *(This exact before/after was verified on a desktop compiler at `-Os` — the same optimization level PlatformIO's release build uses — and the reasoning is standard C language behavior, not architecture-specific, so the same pattern holds on the ARM output. Steps 1 and 2 above have you confirm it directly on your own ARM build.)*

3. Think about why this matters: if `flag` were actually being set by a real interrupt handler, the non-`volatile` version would **hang forever** — even though the hardware genuinely changed the value — because the compiled code simply never looks again.

## Wiring

None — this episode has no hardware step. See the [root README's Hardware Setup section](../README.md#hardware-setup) for standard SWD wiring used in flashing episodes.

---
Previous: [Episode 11 — static](../episode-11-static)
Next: [Episode 13 — Putting It All Together](../episode-13-putting-it-together) *(coming soon)*
