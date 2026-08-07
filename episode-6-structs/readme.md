# Episode 6: Structs

**Video:** 

> This episode needs the board connected and flashed - the proof is
> a rhythm you can see. See the
> [Hardware setup section](../README.md#hardware-setup-read-this-first-if-youre-new-here)
> in the root README if you haven't wired up yet.

## The idea
A struct bundles several related variables together under one name,
instead of keeping them as loose, disconnected values. `wash_ms` and
`spin_ms` both describe the same thing - one washing cycle - so they
belong together as one unit, not as two unrelated numbers floating
around separately.

```c
typedef struct
{
  uint16_t wash_ms;
  uint16_t spin_ms;
} WashingMachine;
```

- `struct { ... }` defines the bundle - two named slots.
- `typedef ... WashingMachine;` gives that bundle a short, reusable
  name, so you don't have to write out `struct { ... }` in full every
  time you want one.

This is the same pattern behind every `GPIO_InitTypeDef` you've seen
in this series - `WashingMachine` is our own tiny version of exactly
that idea, easier to inspect since we wrote it ourselves.

To actually use one, create a real variable from the blueprint and
fill in its fields:
```c
WashingMachine my_cycle = { .wash_ms = 200, .spin_ms = 800 };
```
`my_cycle.wash_ms` and `my_cycle.spin_ms` - dot notation, same as
`GPIO_InitStruct.Pin` from earlier episodes.

**If you know Python:** this maps directly onto a class or dataclass,
not a set - a struct is named and ordered, a set is neither:
```python
from dataclasses import dataclass

@dataclass
class WashingMachine:
    wash_ms: int
    spin_ms: int

my_cycle = WashingMachine(200, 800)
my_cycle.wash_ms   # same dot notation as the C version
```

## Try it yourself
1. Build and flash `main.c` as-is. The LED does a quick flash, mostly
   off - 200ms on, 800ms off, repeating.
2. Swap the two values: `{ .wash_ms = 800, .spin_ms = 200 }`, reflash.
   The rhythm flips - now mostly on, quick off. Both numbers changed
   together, as one unit, because they live in the same struct.
3. Try changing just one field on its own (e.g. `wash_ms` only) - this
   works too, since each field is still individually addressable by
   name, even though they travel together as one variable.

## Wiring
Same single-LED setup as earlier episodes:
PA4 → 220Ω resistor → LED anode, LED cathode → GND.
