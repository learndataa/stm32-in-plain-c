/*
 * STM32 in Plain C — Episode 4: Functions & Return Values
 *
 * Every HAL_ function returns a HAL_StatusTypeDef - HAL_OK if it
 * worked, HAL_ERROR (or similar) if it didn't. That return value is
 * the function's only way of telling you something went wrong. If
 * you never look at it, you'll never know.
 *
 * try_something() below is a tiny stand-in for how every real HAL_
 * function behaves: it does something, then reports back whether it
 * worked.
 */

#include "bsp.h"

static HAL_StatusTypeDef try_something(uint8_t input)
{
  if (input > 10)
  {
    return HAL_ERROR; // couldn't do it
  }
  return HAL_OK; // worked fine
}

int main(void)
{
  BSP_Init();

  if (try_something(2) != HAL_OK)
  {
    BSP_LED_On();
    while (1) { }
  }
  while (1)
  {
    BSP_LED_Toggle();
    HAL_Delay(500);
  }
}
