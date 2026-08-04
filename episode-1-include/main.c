/*
 * STM32 in Plain C — Episode 1: "#include"
 *
 * #include copies another file's contents into this one before the
 * compiler does anything else. "stm32f0xx_hal.h" defines HAL_Delay
 * and every other HAL_ name used below - remove the line and none of
 * those names exist anymore, as far as the compiler is concerned.
 */

#include "stm32f0xx_hal.h"
#include "bsp.h"

int main(void)
{
  BSP_Init();

  while (1)
  {
    BSP_LED_Toggle();
    HAL_Delay(500);
  }
}
