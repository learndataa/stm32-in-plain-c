/*
 * STM32 in Plain C — Episode 2: "int main(void)"
 *
 * Every C program needs exactly one function named exactly `main` -
 * that's the fixed entry point the toolchain looks for when it links
 * everything together. Rename it, and there's nothing left for the
 * program to start running from.
 *
 * `void` here means main takes no input arguments.
 * The curly braces `{ }` mark where the function's body begins and
 * ends - everything between them runs as part of main.
 */

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
