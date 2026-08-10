/*
 * STM32 in Plain C — Episode 7: Pointers and &
 *
 * Passing a variable to a normal function hands it a COPY - anything
 * the function does to that copy is lost the moment it returns. A
 * pointer instead hands over the variable's ADDRESS (via &), so the
 * function can reach through it and change the real thing. This is
 * exactly why HAL_ADC_Init(&hadc1) uses & - HAL needs to modify your
 * real hadc1, not scribble on a copy that vanishes.
 *
 * This program proves the difference: try_by_value has no effect on
 * delay_ms, so the LED blinks slowly for a few seconds first. Then
 * try_by_pointer genuinely changes delay_ms, and the LED speeds up -
 * permanently, since delay_ms itself was actually changed.
 */

#include "bsp.h"

static void try_by_value(uint16_t x)
{
  x = 100; // only changes the local copy - lost when the function returns
}

static void try_by_pointer(uint16_t *x)
{
  *x = 100; // reaches through the address - changes the real variable
}

int main(void)
{
  BSP_Init();

  uint16_t delay_ms = 500;

  try_by_value(delay_ms); // passes a COPY of delay_ms - the real one is untouched

  // Slow blink for a few seconds - proves try_by_value had no effect
  for (uint8_t i = 0; i < 6; i++)
  {
    BSP_LED_Toggle();
    HAL_Delay(delay_ms);
  }

  try_by_pointer(&delay_ms); // passes the ADDRESS - the real delay_ms can be reached

  // Fast blink forever - delay_ms was genuinely changed to 100
  while (1)
  {
    BSP_LED_Toggle();
    HAL_Delay(delay_ms);
  }
}
