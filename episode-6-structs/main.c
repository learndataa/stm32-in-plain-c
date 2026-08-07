/*
 * STM32 in Plain C — Episode 6: Structs
 *
 * A struct bundles several related variables together under one
 * name, instead of keeping them as loose, separate values. Every
 * GPIO_InitTypeDef GPIO_InitStruct = {0}; used throughout this
 * series is a struct - this episode is where that finally gets
 * explained.
 *
 * WashingMachine below is our own small struct: one bundle holding
 * two related settings - how long to "wash" (LED on) and how long to
 * "spin" (LED off) - accessed together by name, the same way HAL
 * structs bundle related settings like Pin and Mode.
 */

#include "bsp.h"

typedef struct
{
  uint16_t wash_ms;
  uint16_t spin_ms;
} WashingMachine;

int main(void)
{
  BSP_Init();

  WashingMachine my_cycle = { .wash_ms = 200, .spin_ms = 800 };

  while (1)
  {
    BSP_LED_On();
    HAL_Delay(my_cycle.wash_ms);

    BSP_LED_Off();
    HAL_Delay(my_cycle.spin_ms);
  }
}
