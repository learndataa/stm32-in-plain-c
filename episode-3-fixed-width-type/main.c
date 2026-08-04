/*
 * STM32 in Plain C — Episode 3: Fixed-Width Types
 *
 * uint8_t, uint16_t, uint32_t guarantee an EXACT number of bits,
 * unlike plain int/short/long, whose exact size can vary by platform.
 * That precision matters for embedded registers and HAL structs,
 * which expect fields of an exact width.
 *
 * uint8_t holds exactly 8 bits: values 0 to 255, nothing more. Unlike
 * a missing #include or a renamed main, going outside that range
 * doesn't stop the build - it just silently wraps to the wrong number
 * and compiles anyway.
 */

#include "bsp.h"

int main(void)
{
  BSP_Init();

  uint8_t counter = 5; // fits fine - uint8_t holds 0 to 255

  if (counter > 0)
  {
    BSP_LED_On();
  }

  while (1)
  {
    BSP_LED_Toggle();
    HAL_Delay(500);
  }
}
