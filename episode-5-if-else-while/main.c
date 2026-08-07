/*
 * STM32 in Plain C — Episode 5: The Loop That Never Ends (On Purpose)
 *
 * if/else picks between two paths based on a condition. while(1)
 * loops forever, on purpose - there's no operating system underneath
 * this program waiting to receive a "return value" from main, so
 * main is never allowed to actually finish. while(1) is what keeps
 * it running, deliberately, forever.
 *
 * This program counts 5 blinks, then switches to the else branch and
 * stays there - solid on, forever. The program never stops running.
 * It just keeps re-checking a condition that's now permanently false.
 */

#include "bsp.h"

int main(void)
{
  BSP_Init();

  uint8_t blink_count = 0;

  while (1)
  {
    if (blink_count < 5)
    {
      BSP_LED_Toggle();
      blink_count++;
    }
    else
    {
      BSP_LED_On(); // done counting - stays here, solid, forever
    }

    HAL_Delay(500);
  }
}
