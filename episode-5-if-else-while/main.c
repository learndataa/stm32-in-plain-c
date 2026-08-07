/*
 * STM32 in Plain C — Episode 5: The Loop That Never Ends (On Purpose)
 *
 * if/else picks between two paths based on a condition. while(1)
 * loops forever, on purpose - there's no operating system underneath
 * this program waiting to receive a "return value" from main, so
 * main is never allowed to actually finish. while(1) is what keeps
 * it running, deliberately, forever.
 *
 * This program blinks 5 times, then switches to the else branch and
 * stays there - solid on, forever. blinks_done only increments once
 * per COMPLETED on-off cycle, not per toggle - a toggle alone flips
 * the state, but two toggles (on, then off) make one visible blink.
 */

#include "bsp.h"

int main(void)
{
  BSP_Init();

  uint8_t blinks_done = 0;
  uint8_t led_is_on = 0;

  while (1)
  {
    if (blinks_done < 5)
    {
      if (led_is_on)
      {
        BSP_LED_Off();
        led_is_on = 0;
        blinks_done++; // one full on-off cycle just completed
      }
      else
      {
        BSP_LED_On();
        led_is_on = 1;
      }
    }
    else
    {
      BSP_LED_On(); // done blinking - stays here, solid, forever
    }

    HAL_Delay(500);
  }
}
