/*
 * Shared board support for STM32 in Plain C.
 *
 * Handles the setup every episode needs (clock config, LED pin setup)
 * so each episode's main.c can stay focused on just the concept it's
 * teaching, instead of repeating the same boilerplate every time.
 *
 * Board: STM32F051C8T6
 * LED:   PA4 -> 220ohm resistor -> LED anode, LED cathode -> GND
 */

#ifndef BSP_H
#define BSP_H

#include "stm32f0xx_hal.h"

void BSP_Init(void);       // HAL_Init + clock config + LED pin setup
void BSP_LED_On(void);
void BSP_LED_Off(void);
void BSP_LED_Toggle(void);

#endif
