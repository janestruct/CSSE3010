/** 
 ***************************************************************
 * @file /home/csse3010/csse3010/stage2/s4464952_hal_mylib_configure.h
 * @author Aina Jauhara - s4464952
 * @date 23/2/2020
 * @brief configuration header file 
 ***************************************************************
 * EXTERNAL FUNCTIONS 
 ***************************************************************
 *************************************************************** 
 */

#ifndef S4464952_MYLIB_CONFIGURE_INC
#define S4464952_MYLIB_CONFIGURE_INC

#include "board.h"
#include "stm32f4xx_hal.h"

GPIO_InitTypeDef GPIO_InitStructure;
TIM_HandleTypeDef TIM_Init;
#define S4464952_HAL_KEYPAD_COL1PIN         BRD_D5_PIN 
#define S4464952_HAL_KEYPAD_COL2PIN         BRD_D4_PIN
#define S4464952_HAL_KEYPAD_COL3PIN         BRD_D3_PIN
#define S4464952_HAL_KEYPAD_COL4PIN         BRD_D2_PIN

#define S4464952_HAL_KEYPAD_COL1PINPORT     BRD_D5_GPIO_PORT
#define S4464952_HAL_KEYPAD_COL2PINPORT     BRD_D4_GPIO_PORT
#define S4464952_HAL_KEYPAD_COL3PINPORT     BRD_D3_GPIO_PORT
#define S4464952_HAL_KEYPAD_COL4PINPORT     BRD_D2_GPIO_PORT

#define S4464952_HAL_KEYPAD_COL1PINCLK      __BRD_D5_GPIO_CLK()
#define S4464952_HAL_KEYPAD_COL2PINCLK      __BRD_D4_GPIO_CLK()
#define S4464952_HAL_KEYPAD_COL3PINCLK      __BRD_D3_GPIO_CLK()
#define S4464952_HAL_KEYPAD_COL4PINCLK      __BRD_D2_GPIO_CLK()

#define S4464952_HAL_KEYPAD_ROW1PIN         BRD_A4_PIN
#define S4464952_HAL_KEYPAD_ROW2PIN         BRD_D9_PIN
#define S4464952_HAL_KEYPAD_ROW3PIN         BRD_D8_PIN
#define S4464952_HAL_KEYPAD_ROW4PIN         BRD_D7_PIN

#define S4464952_HAL_KEYPAD_ROW1PINPORT     BRD_A4_GPIO_PORT
#define S4464952_HAL_KEYPAD_ROW2PINPORT     BRD_D9_GPIO_PORT
#define S4464952_HAL_KEYPAD_ROW3PINPORT     BRD_D8_GPIO_PORT
#define S4464952_HAL_KEYPAD_ROW4PINPORT     BRD_D7_GPIO_PORT

#define S4464952_HAL_KEYPAD_ROW1PINCLK      __BRD_A4_GPIO_CLK()
#define S4464952_HAL_KEYPAD_ROW2PINCLK      __BRD_D9_GPIO_CLK()
#define S4464952_HAL_KEYPAD_ROW3PINCLK      __BRD_D8_GPIO_CLK() 
#define S4464952_HAL_KEYPAD_ROW4PINCLK      __BRD_D7_GPIO_CLK() 

#endif

