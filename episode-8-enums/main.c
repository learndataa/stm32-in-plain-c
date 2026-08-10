/*
 * STM32 in Plain C — Episode 8: Enums / Named Constants
 *
 * GPIO_PIN_4 isn't magic. It's not special syntax, and it's not a
 * keyword - it's just a name for a plain number, defined somewhere
 * inside a HAL header. Every GPIO_PIN_4 used since episode 2 has
 * secretly just been a number with a label on it.
 *
 * BlinkSpeed below is our own tiny enum - a list of named constants.
 * SPEED_SLOW isn't a special "speed type" - it IS the number 500,
 * nothing more.
 */

#include "bsp.h"

typedef enum
{
  SPEED_SLOW = 500,
  SPEED_FAST = 100,
} BlinkSpeed;

int main(void)
{
  BSP_Init();

  // Proof 1: GPIO_PIN_4 - the exact constant used since episode 2 to
  // wire up this very LED - really is just the number 0x0010.
  // Two quick flashes if this is true.
  if (GPIO_PIN_4 == 0x0010)
  {
    for (uint8_t i = 0; i < 4; i++)
    {
      BSP_LED_Toggle();
      HAL_Delay(100);
    }
  }

  // Proof 2: our own enum works the same way - SPEED_SLOW really IS
  // the number 500, nothing more.
  BlinkSpeed current_speed = SPEED_SLOW;

  while (1)
  {
    BSP_LED_Toggle();
    HAL_Delay(current_speed); // HAL_Delay takes a plain number - this IS one
  }
}
