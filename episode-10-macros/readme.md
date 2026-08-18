# Episode 10: Macros / #define — "Why SQUARE(2+3) Isn't 25"

## The idea

A macro is not a function. Before your code is even compiled, a separate step called the **preprocessor** runs through your source and does a plain text swap — wherever it sees the macro name, it substitutes the macro's literal text, word for word, no math involved.

That's easy to forget, and it can bite you:

```c
#define UNSAFE_SQUARE(x) x*x
```

Calling `UNSAFE_SQUARE(2+3)` doesn't compute `(2+3)*(2+3)`. The preprocessor swaps `x` for the literal text `2+3`, so what actually reaches the compiler is:

```c
2+3*2+3
```

Following normal order of operations, that's `2 + 6 + 3 = 11` — not the `25` you probably expected.

The fix is to parenthesize the argument, and the whole expression:

```c
#define SAFE_SQUARE(x) ((x)*(x))
```

Now `SAFE_SQUARE(2+3)` expands to `((2+3)*(2+3))`, which correctly evaluates to `25`.

This episode is **build-only** — no LED, no hardware. The compiler itself proves both results, before the program would ever run.

## The code

See [`main.c`](./main.c).

Like Episode 9, this file does not `#include "bsp.h"` — there's no hardware step, so only `#include <stdint.h>` is needed.

```c
#define UNSAFE_SQUARE(x) x*x
#define SAFE_SQUARE(x)   ((x)*(x))
```

The `_Static_assert` calls check both expansions at compile time — no runtime, no printing, no hardware required.

## Try it yourself

**Hardware required?** No. Build-only — just PlatformIO and a C compiler.

1. Run `pio run`.
   **Expected result:** `BUILD SUCCESS` — both `_Static_assert` checks pass, confirming `UNSAFE_SQUARE(2+3) == 11` and `SAFE_SQUARE(2+3) == 25`.
2. See the raw substitution yourself. From this folder, run:
   ```
   gcc -E main.c | tail -20
   ```
   (This uses your computer's C preprocessor just to *show* the expansion — it won't build the STM32 target.)
   **Expected result:** you'll see the literal expanded text `2+3*2+3` and `((2+3)*(2+3))` in place of the macro calls — proof the swap really is just text substitution.
3. Change `UNSAFE_SQUARE`'s `_Static_assert` to check for `25` instead of `11`, then run `pio run` again.
   **Expected result:** a compile-time assertion failure — the compiler catching, before your code ever runs, that the macro didn't do what you assumed.

## Wiring

None — this episode has no hardware step. See the [root README's Hardware Setup section](../README.md#hardware-setup) for standard SWD wiring used in flashing episodes.

---
Previous: [Episode 9 — Typedefs](../episode-9-typedefs)
Next: [Episode 11 — static](../episode-11-static) *(coming soon)*
