/**
  ******************************************************************************
  * @file    stage1/main.c
  * @author  Aina Jauhara - s4464952
  * @date    23/2/2020
  * @brief   Stage 1 main file
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "board.h"
#include "stm32f4xx_hal.h"
#include "debug_printf.h"
#include "s4464952_hal_lta1000g.h"
#include "s4464952_hal_pb.h"
#include "s4464952_hal_iss.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
unsigned int LEFT_TO_RIGHT = 0 ;
unsigned int RIGHT_TO_LEFT = 1 ;
int direction = 0;
/* Private function prototypes -----------------------------------------------*/
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin);
void EXTI15_10_IRQHandler(void);
void Hardware_init(void);


/**
  * @brief  Main program - makes a MPD with LED bar
  * @param  None
  * @retval None
  */
int main(void)  {

	Hardware_init();

	unsigned int led_value = 0x0003;  

	/* Main processing loop */
	while (1) {
		
		s4464952_hal_lta1000g_write(led_value);
		debug_printf("led value: 0x%.4x\n\r", led_value);
		s4464952_hal_pb_on_isr(); 
	
		

		/*direction change to right*/
		if(direction == 0){

			led_value = led_value << 1; //shifting LED light value to left by 1 place
			debug_printf("going right\n\r");
		
			if(led_value > 0x0300){
			led_value = 0x0003;				//reset LED value to 0x0003 once reach boundary
			}
		/*direction change to left*/
		}else if(direction == 1){

			led_value = led_value >> 1; //shifting LED light value to right by 1 place
			debug_printf("going left\n\r");

			if(led_value < 0x0003){
			led_value = 0x0300;
			}
		}
		
		
		HAL_Delay(1000);		
	}
}


/**
  * @brief  Hardware initialize
  * @param  None
  * @retval None
  */
void Hardware_init(void) {

	BRD_init();							//Initalise Board
	s4464952_hal_lta1000g_init();		//Initalise LED
	s4464952_hal_pb_on_init();			//Initialise pushbutton
	s4464952_hal_pb_iss_init();			//Initialise pushbutton

}

	

/**
  * @brief  Set direction
  * @param  GPIO pin 
  * @retval None
  */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){

	static int press_count = 1;

	if (GPIO_Pin == GPIO_PIN_13){
		debug_printf("button pressed");
		
		/*XOR on the press count*/
		press_count = press_count ^ 1;
		/*if count value is 0*/
		if(press_count == 0){
			direction = RIGHT_TO_LEFT;
		
		/*if count value is 1*/
		}else if(press_count == 1){
			direction = LEFT_TO_RIGHT;
	  }
  }
}



//Override default mapping of this handler to Default_Handler
void EXTI15_10_IRQHandler(void){

	HAL_GPIO_EXTI_IRQHandler(BRD_USER_BUTTON_PIN);
}
