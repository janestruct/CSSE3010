/** 
 *************************************************************
 * @file /home/csse3010/csse3010/mylib/keypad/s4464952_hal_keypad.h
 * @author Aina Jauhara - s4464952
 * @date 03/04/2020
 * @brief header file contains keypad functions used by s4464952_hal_keypad.c
 ***************************************************************
 * EXTERNAL FUNCTIONS 
 ***************************************************************
 * void s4464952_hal_keypad_init(void);                   
 * void s4464952_hal_keypad_deinit(void);                  
 * void s4464952_hal_keypad_fsmprocessing(void);           
 * void keypad_gpio_init(void);                            
 * void keypad_writecol(int colval);                       
 * void keypad_readrow(void);                              
 * void s4464952_hal_keypad_read_status(void);            
 * void s4464952_hal_keypad_read_key(void);                
 * void s4464952_hal_keypad_read_ascii(void);                                                                                    - initialise atimer
 *************************************************************** 
 */


#ifndef S4464952_HAL_KEYPAD_H
#define S4464952_HAL_KEYPAD_H

#ifdef S4464952_MYLIB_CONFIGURE_INC
#include "s4464952_hal_mylib_configure.h"
#endif

void s4464952_hal_keypad_init(void);                    // Set the state of the keypadFSM to INIT state
void s4464952_hal_keypad_deinit(void);                  // Set the state of the keypadFSM to DEINIT state.
void s4464952_hal_keypad_fsmprocessing(void);           // Keypad FSM processing loop
void keypad_gpio_init(void);                            // Initalise all GPIO pins.
void keypad_writecol(int colval);
int keypad_readrow(void);                               // Internal function for reading a row
int s4464952_hal_keypad_read_status(void);             // Return the KeypadStatus variable
int s4464952_keypad_read_key();
char s4464952_hal_keypad_read_ascii();

GPIO_InitTypeDef GPIO_InitStructure;
TIM_HandleTypeDef TIM_Init;

#define s4464952_HAL_KEYPAD_COL1PIN         BRD_D5_PIN 
#define s4464952_HAL_KEYPAD_COL2PIN         BRD_D4_PIN
#define s4464952_HAL_KEYPAD_COL3PIN         BRD_D3_PIN
#define s4464952_HAL_KEYPAD_COL4PIN         BRD_D2_PIN

#define s4464952_HAL_KEYPAD_COL1PINPORT     BRD_D5_GPIO_PORT
#define s4464952_HAL_KEYPAD_COL2PINPORT     BRD_D4_GPIO_PORT
#define s4464952_HAL_KEYPAD_COL3PINPORT     BRD_D3_GPIO_PORT
#define s4464952_HAL_KEYPAD_COL4PINPORT     BRD_D2_GPIO_PORT

#define s4464952_HAL_KEYPAD_COL1PINCLK      __BRD_D5_GPIO_CLK()
#define s4464952_HAL_KEYPAD_COL2PINCLK      __BRD_D4_GPIO_CLK()
#define s4464952_HAL_KEYPAD_COL3PINCLK      __BRD_D3_GPIO_CLK()
#define s4464952_HAL_KEYPAD_COL4PINCLK      __BRD_D2_GPIO_CLK()

#define s4464952_HAL_KEYPAD_ROW1PIN         BRD_A4_PIN
#define s4464952_HAL_KEYPAD_ROW2PIN         BRD_D9_PIN
#define s4464952_HAL_KEYPAD_ROW3PIN         BRD_D8_PIN
#define s4464952_HAL_KEYPAD_ROW4PIN         BRD_D7_PIN

#define s4464952_HAL_KEYPAD_ROW1PINPORT     BRD_A4_GPIO_PORT
#define s4464952_HAL_KEYPAD_ROW2PINPORT     BRD_D9_GPIO_PORT
#define s4464952_HAL_KEYPAD_ROW3PINPORT     BRD_D8_GPIO_PORT
#define s4464952_HAL_KEYPAD_ROW4PINPORT     BRD_D7_GPIO_PORT

#define s4464952_HAL_KEYPAD_ROW1PINCLK      __BRD_A4_GPIO_CLK()
#define s4464952_HAL_KEYPAD_ROW2PINCLK      __BRD_D9_GPIO_CLK()
#define s4464952_HAL_KEYPAD_ROW3PINCLK      __BRD_D8_GPIO_CLK() 
#define s4464952_HAL_KEYPAD_ROW4PINCLK      __BRD_D7_GPIO_CLK() 

#endif

