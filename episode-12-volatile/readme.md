# Episode 12: volatile — "Why the Compiler Deletes Code You Needed"

## The idea

Think of this like telling someone: "Stand by the front door, and don't come back inside until the doorbell rings."

That's what our code says: sit in a loop, and don't leave, until a variable called `flag` changes from 0 to 1.

Here's the problem. An optimizing compiler works off an assumption: *if nothing in the code it can see changes a variable, that variable's value won't change* — so it can skip re-checking it, or even delete the re-check entirely. Most of the time, that assumption is correct, and it's a genuinely useful optimization.

But it's *wrong* when the variable can change from **outside** the code the compiler is looking at — like a hardware button being pressed, or a value an interrupt handler updates while your main code is doing something else. The compiler doesn't know that's possible. It just sees a variable nothing *nearby* touches, and "helpfully" removes the re-check — like a person standing at the door, glancing once, and then freezing there, never looking again, even though the mailman could still ring the bell any second.

`volatile` is you telling the compiler: "No — trust me, this can change from somewhere you can't see. Don't ever assume it won't. Check it again. Every single time."

This episode is **build-only**. Unlike previous episodes, the proof here isn't a compile-time check — it's reading the actual instructions the compiler generated, with and without `volatile`, and seeing the literal difference. You do not need to know assembly language to follow this — every line is explained in plain terms below.

## The code

See [`main.c`](./main.c). No `#include "bsp.h"` — no hardware step.

```c
uint8_t flag = 0;

void wait_for_flag(void) {
    while (flag == 0) {
    }
}
```

In real firmware, `flag` would usually get set by an interrupt handler — a separate piece of code that can run at any moment, completely independent of `wait_for_flag()`.

## Try it yourself

**Hardware required?** No. Build-only — you'll be reading generated instructions, not flashing anything.

### Step 1 — Build as-is (no `volatile` yet)

```
pio run
```

### Step 2 — Find your `objdump` tool

This is bundled inside PlatformIO's ARM toolchain, not something you install separately. On macOS/Linux it's typically at:

```
~/.platformio/packages/toolchain-gccarmnoneeabi/arm-none-eabi/bin/objdump
```

(Note: no `.exe` extension on Mac/Linux — Finder can make it *look* like there should be one, but there isn't. On Windows it will be `objdump.exe`.)

If that path doesn't exist on your machine, find the real one with:
```
find ~/.platformio/packages/toolchain-gccarmnoneeabi -iname "*objdump*"
```

### Step 3 — Disassemble the function

```
~/.platformio/packages/toolchain-gccarmnoneeabi/arm-none-eabi/bin/objdump -d .pio/build/disco_f051r8/firmware.elf | grep -A 10 "<wait_for_flag>:"
```

**Expected output** (yours should match this closely — line addresses may shift slightly depending on toolchain version, but the *shape* will be identical):

```
08000108 <wait_for_flag>:
 8000108:       4b02            ldr     r3, [pc, #8]
 800010a:       781b            ldrb    r3, [r3, #0]
 800010c:       2b00            cmp     r3, #0
 800010e:       d100            bne.n   8000112 <wait_for_flag+0xa>
 8000110:       e7fe            b.n     8000110 <wait_for_flag+0x8>
 8000112:       4770            bx      lr
```

**What each line actually means, in plain terms — no assembly knowledge needed:**

| Line | What it's doing |
|---|---|
| `8000108` | Bookkeeping — the compiler figuring out *where in memory* `flag` lives. Not part of the actual check. |
| `800010a` + `800010c` | **"Check the doorbell — once."** This reads the value of `flag`, then compares it to 0. |
| `800010e` | **"If it rang, leave."** If `flag` wasn't 0, jump down to the exit (line `8000112`). |
| `8000110` | **"Stuck here. Forever."** Look closely: this line's own address (`8000110`) and the address it jumps to (`8000110`) are the *same number*. It points at itself. Once execution lands here, it never leaves, and — critically — it never goes back and reads `flag` again. |
| `8000112` | The actual exit point of the function, if it's ever reached. |

So: the compiler reads `flag` exactly **once**. If it's already nonzero, fine, it moves on. But if `flag` is still 0, the code gets stuck at `8000110` — spinning in place, staring at nothing, never checking `flag` again. Even if a real interrupt handler changes `flag` to 1 a moment later, this compiled code will never notice, because it's not looking anymore.

### Step 4 — Add `volatile`

```c
volatile uint8_t flag = 0;
```

Rebuild (`pio run`) and run the **exact same** objdump command again.

**Expected result:** instead of one read followed by a frozen self-loop, you'll see a repeating pattern — read `flag`, compare, and loop back around to *read it again* — every single pass through the loop. That's the correct behavior: the code keeps actually checking, instead of deciding once and freezing.

*(This before/after pattern was verified on a desktop compiler at `-Os` — the same optimization level PlatformIO's release build uses for this chip — and the underlying reasoning is standard C language behavior, not specific to any one processor. The steps above have you confirm it directly on your own ARM build, which is the real proof that matters.)*

### Step 5 — Why this matters

If `flag` were genuinely being set by a real interrupt handler, the non-`volatile` version would **hang forever** — even though the hardware truly changed the value — because the compiled code simply stopped looking. `volatile` is what keeps the code honestly checking, every time, the way you actually meant it to.

## Wiring

None — this episode has no hardware step. See the [root README's Hardware Setup section](../README.md#hardware-setup) for standard SWD wiring used in flashing episodes.

---
Previous: [Episode 11 — static](../episode-11-static)
Next: [Episode 13 — Putting It All Together](../episode-13-putting-it-together) *(coming soon)*
