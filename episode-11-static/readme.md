# Episode 11: static — "One Keyword, Two Different Meanings"

## The idea

`static` does two unrelated-seeming things in C, depending on *where* you use it:

**1. On a function or global variable (file scope):** `static` means "only visible inside this file." No other `.c` file in the project can call it — not even if they declare it themselves. It's how library code hides its internal helper functions from you, so you only see the ones meant to be public.

**2. On a variable inside a function (local scope):** `static` means "initialize this once, and keep its value between calls" — instead of the normal behavior, where a local variable is destroyed and recreated fresh every time the function runs.

This episode is **build-only**. The file-scope meaning is proven directly by the compiler and linker — the strongest, most literal kind of proof there is. The local-scope meaning needs to actually run and print something to observe, so it's demonstrated in a small optional bonus file you run on your own computer (not the STM32 board — see below).

## The code

See [`main.c`](./main.c). Like Episodes 9 and 10, this file does not `#include "bsp.h"` — no hardware step, just `#include <stdint.h>`.

```c
static uint8_t double_it(uint8_t x) {   // invisible outside this file
    return x * 2;
}

uint8_t quadruple_it(uint8_t x) {       // NOT static -- other files could call this
    return double_it(double_it(x));
}
```

`quadruple_it` can call `double_it` because they're in the same file. Nothing outside this file can.

## Try it yourself

**Hardware required?** No. Build-only for the main demo. One optional bonus step runs on your own computer, not the STM32 board.

1. Run `pio run`.
   **Expected result:** `BUILD SUCCESS` — `double_it` and `quadruple_it` both compile and link fine, since everything's called from within `main.c`.

2. **See `static` actually block the linker.** This repo includes [`helper.c`](./helper.c) — a second file that tries to call `double_it()` from outside `main.c`. It is *not* built by default. To try it:
   - Temporarily add `helper.c` to your build (e.g. adjust `build_src_filter` in `platformio.ini`, or build both files directly with a plain C compiler: `gcc main.c helper.c`).
   - Build again.
   **Expected result:** a **linker** error (not a compiler error) — something like `undefined reference to 'double_it'`. The code is syntactically fine; the function just doesn't exist as far as anything outside `main.c` is concerned. That's `static`'s file-scope meaning, proven directly.

3. **Bonus (local static, runs on your computer, not the STM32 board):** this project has no UART/hardware in this episode to print output with, so the local-static example lives in [`bonus_host_demo.c`](./bonus_host_demo.c) — plain, ordinary C you can compile and run directly on your own machine:
   ```
   gcc -o bonus_host_demo bonus_host_demo.c
   ./bonus_host_demo
   ```
   **Expected result:** prints `1`, `2`, `3` — proof the `static` local variable inside `next_id()` kept its value between calls, instead of resetting to `0` every time. This is standard C behavior, not STM32-specific, so it's identical on the target chip.

## Wiring

None — this episode has no hardware step. See the [root README's Hardware Setup section](../README.md#hardware-setup) for standard SWD wiring used in flashing episodes.

---
Previous: [Episode 10 — Macros / #define](../episode-10-macros)
Next: [Episode 12 — volatile](../episode-12-volatile) *(coming soon)*
