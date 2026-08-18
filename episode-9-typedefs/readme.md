# Episode 9: Typedefs — "Why ADC_HandleTypeDef Has Such a Long Name"

## The idea

If you've looked at STM32 HAL code, you've seen type names like `ADC_HandleTypeDef`, `GPIO_InitTypeDef`, or `UART_HandleTypeDef`. These aren't special kinds of structs, and `TypeDef` isn't a keyword — they're just regular structs that have been given a shorter name using `typedef`.

Without `typedef`, using a struct means writing `struct SomeName` every time you declare a variable:

```c
struct ADC_LikeHandle_tag thing;
```

With `typedef`, the struct gets a standalone name you can use on its own:

```c
ADC_LikeHandle thing;
```

Same struct. Same memory layout. Just a shorter name to type.

This episode is **build-only** — there's no LED, no hardware step. The whole concept is proven by the compiler: either your code compiles (the types are valid and equivalent), or it doesn't (you'll see exactly what breaks when the name doesn't exist).

## The code

See [`main.c`](./main.c).

Note: unlike previous episodes, this one does **not** `#include "bsp.h"`. There's no hardware to initialize, since this episode is proven entirely by the compiler — only `#include <stdint.h>` is needed for `uint8_t`.

```c
// The long way: a struct with no typedef.
struct ADC_LikeHandle_tag {
    uint8_t channel;
    uint8_t is_ready;
};

// The typedef way: same struct, but now "ADC_LikeHandle" is a type name
// on its own -- no "struct" keyword needed to use it.
typedef struct {
    uint8_t channel;
    uint8_t is_ready;
} ADC_LikeHandle;
```

The `_Static_assert` in `main()` checks, at compile time, that the typedef'd and non-typedef'd forms are truly the same size — proof they're the same underlying type, not two different ones.

## Try it yourself

**Hardware required?** No. This episode is build-only — you just need PlatformIO and a C compiler. No flashing, no ST-Link, no LED.

1. Open this folder in PlatformIO and run `pio run`.
   **Expected result:** `BUILD SUCCESS` — both `long_way` and `short_way` compile fine, proving they're valid, equivalent types.
2. In `main.c`, remove the `typedef` keyword so the struct becomes anonymous again, then run `pio run`.
   **Expected result:** a compiler error on the `ADC_LikeHandle short_way;` line — `ADC_LikeHandle` no longer exists, because that name only existed *because* of the typedef.
3. Put the `typedef` back, then add an extra field (e.g. `uint8_t reserved;`) to only one of the two struct definitions, and run `pio run` again.
   **Expected result:** the `_Static_assert` fails at compile time with the message `"typedef'd and non-typedef'd forms must be identical"` — the compiler catches the mismatch before you ever run the code.

## Wiring

None — this episode has no hardware step. If you'd like to review the standard SWD wiring used in flashing episodes, see the [root README's Hardware Setup section](../README.md#hardware-setup).

---
Previous: [Episode 8 — Enums / Named Constants](../episode-8-enums)
Next: [Episode 10 — Macros / #define](../episode-10-macros) *(coming soon)*
