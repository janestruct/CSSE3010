/**
  ******************************************************************************
  * @file    stage3/main.c
  * @author  Aina Jauhara - s4464952
  * @date    03/04/2020
  * @brief   Stage 3 main file
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/

#include "board.h"
#include "processor_hal.h"
#include "s4464952_hal_mylib_configure.h"
#include "s4464952_lib_hamming.h"
#include "s4464952_hal_keypad.h"
#include "debug_printf.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define IDLE_STATE 0
#define ENCODE_STATE 1
#define DECODE_STATE 2
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
  int HammingFsmCurrentstate = IDLE_STATE;
  int HammingFsmPreviousState = IDLE_STATE;
/* Private function prototypes -----------------------------------------------*/
void Hardware_init(void);
void s4464952_hal_hamming_fsmprocessing(void);


/**
  * @brief  Main program 
  * @param  None
  * @retval None
  */
int main(void)  {
   
 int time = 0;
Hardware_init();

	/* Main processing loop */
	while (1) {  
    
   
    if ((HAL_GetTick()- time) > 50){

        s4464952_hal_keypad_fsmprocessing();
        int x = s4464952_hal_keypad_read_status();
        int key = s4464952_keypad_read_key();
        debug_printf("current status : %d\n\r", x);
        debug_printf("key value : %d\n\r", key);
       
        time = HAL_GetTick();
    }
     
  }
}

/**
 * @brief  Cyclic executive fsm processing
 * @param  None
 * @retval None
 */
void s4464952_hal_hamming_fsmprocessing(void){



    switch(HammingFsmCurrentstate){

        case IDLE_STATE:
					HammingFsmPreviousState = IDLE_STATE;
          s4464952_hal_keypad_fsmprocessing();
          
          
        break;

        case ENCODE_STATE:
					HammingFsmPreviousState = ENCODE_STATE;
          debug_printf("ENCODE STATE\n\r");
          HammingFsmCurrentstate = IDLE_STATE ;
        break;

        case DECODE_STATE:
					HammingFsmPreviousState = DECODE_STATE;
          debug_printf("DECODE STATE\n\r");
					HammingFsmCurrentstate = IDLE_STATE;
        break;
    }
}


/**
  * @brief  Hardware initialize
  * @param  None
  * @retval None
  */
void Hardware_init(void) {

	BRD_init();							//Initalise Board
	keypad_gpio_init();

}

	
