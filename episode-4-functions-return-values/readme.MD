# Episode 4: Functions & Return Values

**Video:** _
> **This episode needs the board connected and flashed** - unlike
> episodes 1-3, the proof here is behavioral, not a build message. If
> you haven't wired up your STM32 + ST-Link yet, see the
> [Hardware setup section](../README.md#hardware-setup-read-this-first-if-youre-new-here)
> in the root README first.

## The idea
Every HAL function returns a `HAL_StatusTypeDef` - `HAL_OK` if it
worked, an error value if it didn't. That return value is the only
way the function has of telling you something went wrong. Ignore it,
and you'll never know - the program keeps running as if nothing
happened.

`try_something()` is a small stand-in for a real HAL function: it
succeeds for inputs 0-10, fails for anything above that, and reports
back via its return value either way.

## Try it yourself
1. Build and flash `main.c` as-is - the LED blinks normally. Looks
   completely fine, even though `try_something(20)` silently failed
   inside - the return value is called but never checked.
2. Change the call to actually check the result:
   ```c
   if (try_something(20) != HAL_OK)
   {
     BSP_LED_On();
     while (1) { }
   }
   ```
   Build and flash again. The LED goes solid on and stays there,
   instead of blinking - a failure that was completely invisible a
   moment ago is now impossible to miss.
3. Change the argument from `20` to `5` (a value `try_something`
   accepts) and flash once more - back to normal blinking, since this
   time it actually succeeded.

## Wiring

### Programming connection (STM32 ↔ ST-Link)
Same as every episode - see the root README's
[Hardware setup section](../README.md#hardware-setup-read-this-first-if-youre-new-here)
for the full table. Confirmed required for this board/tool combo:

| ST-Link pin | STM32 board pin |
|---|---|
| SWCLK (CLK) | CLK |
| SWDIO (DAT) | DAT |
| GND | GND |
| 3V3 | 3.3V |
| **RST** | **NRST** |

**NRST is required**, not optional - without it, upload fails with
`Unable to reset target`. See the root README for details.

### LED circuit (what this episode actually uses)
```
PA4 → 220Ω resistor → LED anode
LED cathode → GND (breadboard -ve rail)
```
This is the only circuit `main.c`/`bsp.c` in this episode reads or
writes. Nothing else needs to be connected for this episode's demo
to work.

### Optional: UART wiring (not used by this episode)
If you're also wiring ahead for a future UART/serial episode, this is
unrelated to episode 4 and safe to leave connected or disconnected -
it has no effect on this episode's behavior either way:

```
STM32 TX (board's own TX pin, per its silkscreen) → ST-Link RX
```
Direction matters: STM32 transmits, so its TX line goes to the
ST-Link's RX line, not the other way around. Confirmed working when
using the board's own printed `TX` pin - not confirmed on PA6, which
does not appear to be a documented USART pin on this chip family.

## Troubleshooting notes (from real testing)

- **Flashing succeeds but the LED does nothing at all**: check the
  `BOOT0` jumper is set to `GND`, not `VCC`. Wrong position boots
  into the chip's system bootloader instead of running your flashed
  code - upload still reports success either way, so this is easy to
  miss.
- **Upload fails with `Unable to reset target`**: NRST isn't wired.
  See the programming connection table above.
- **Flashing succeeds, behavior doesn't match what you expect**:
  double check your terminal is in the correct PlatformIO project
  folder (`stm32_in_plain_c`, not a different project) before
  running the upload command - the project name shown in the build
  log's `Dependency Graph` / board line confirms which project just
  got flashed.
