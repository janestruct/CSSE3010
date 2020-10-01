/** 
 *************************************************************
 * @file /home/csse3010/csse3010/mylib/project/s4464952_CAG_keypad_mnemonic.c
 * @author Aina Jauhara - s4464952
 * @date 11/5/2020
 * @brief mylib CAG keypad mnemonic os file
 ***************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "s4464952_CAG_keypad_mnemonic.h"
/* Private typedef -----------------------------------------------------------*/
TaskHandle_t xs4464952_cag_keypad_mnemonic_handle = NULL; //cag keypad handler
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
extern void s4464952_CAG_keypad_mnemonic_init(void);
extern void s4464952_CAG_keypad_mnemonic_task(void);

/**
  * @brief  CAG keypad mnemonic Task.
  * @param  None
  * @retval None
  */

extern void s4464952_CAG_keypad_mnemonic_task(void){
}

/**
  * @brief  Initialise os CAG mnemonic grid
  * @param  None
  * @retval None
  */
extern void s4464952_CAG_keypad_mnemonic_init(void){

	xTaskCreate( (void *) &s4464952_CAG_keypad_mnemonic_task, (const signed char *) "RECV", S4464952_CAG_KEYPAD_MNEMONIC_STACK_SIZE, NULL, S4464952_CAG_KEYPAD_MNEMONIC_PRIORITY, NULL );
	
}
