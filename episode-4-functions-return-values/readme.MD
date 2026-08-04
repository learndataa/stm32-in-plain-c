# Episode 4: Functions & Return Values

**Video:** 

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
Same single-LED setup as earlier episodes:
PA4 → 220Ω resistor → LED anode, LED cathode → GND.
