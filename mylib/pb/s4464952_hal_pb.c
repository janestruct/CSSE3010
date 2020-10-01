/** 
 **************************************************************
 * @file /home/csse3010/csse3010/mylib/pb/s4495585_hal_pb.c
 * @author Aina Jauhara - s4464952
 * @date 23/02/2020
 * @brief mylib pb file
 ***************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "board.h"
#include "stm32f4xx_hal.h"
#include "debug_printf.h"
#include "s4464952_hal_pb.h"
#include "s4464952_hal_iss.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void s4464952_hal_pb_on_init(void);             //enable pb source
int s4464952_hal_pb_on_isr(void);              //pb isr
void s4464952_hal_pb_on_deinit(void);           //disable iss pin source
void s4464952_hal_pb_iss_init(void);            //enable iss pin source
int s4464952_hal_pb_iss_isr(void);             //iss pin source isr
void s4464952_hal_pb_iss_deinit(void);          //disable pb source

/**
 * @brief  initialise pb
 * @param  none
 * @retval None
 */
void s4464952_hal_pb_on_init(void){
	
  GPIO_InitTypeDef GPIO_InitStructure;

	BRD_USER_BUTTON_GPIO_CLK_ENABLE();

	GPIO_InitStructure.Mode = GPIO_MODE_IT_RISING;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	GPIO_InitStructure.Pin  = BRD_USER_BUTTON_PIN;
	HAL_GPIO_Init(BRD_USER_BUTTON_GPIO_PORT, &GPIO_InitStructure);

	HAL_NVIC_SetPriority(BRD_USER_BUTTON_EXTI_IRQn, 10, 0);
	HAL_NVIC_EnableIRQ(BRD_USER_BUTTON_EXTI_IRQn);

}

/**
 * @brief  pushbutton isr
 * @param  none
 * @retval None
 */
int s4464952_hal_pb_on_isr(void){

	int signal_on = 0 ;
	int event_occur = 0 ;
	s4464952_hal_iss_eventcounter_read(signal_on) ;

	if (signal_on = 1){

		event_occur ++ ;
		return event_occur ;

	} else {

		event_occur = 0 ;
		return event_occur ;
	}


}



/**
 * @brief  disable iss pin source
 * @param  none
 * @retval None
 */
void s4464952_hal_pb_on_deinit(void){
	

}

/**
 * @brief  enable iss pin source
 * @param  none
 * @retval None
 */
void s4464952_hal_pb_iss_init(void){
	
   	GPIO_InitTypeDef GPIO_InitStructure;

	__BRD_A0_GPIO_CLK();

	GPIO_InitStructure.Pin = BRD_A0_PIN;
	GPIO_InitStructure.Mode = GPIO_MODE_ANALOG;
	GPIO_InitStructure.Pull = GPIO_NOPULL;

	HAL_GPIO_Init(BRD_A0_GPIO_PORT, &GPIO_InitStructure);

}

/**
 * @brief  iss pin source isr
 * @param  none
 * @retval None
 */
int s4464952_hal_pb_iss_isr(void){
	
	uint16_t GPIO_Pin = GPIO_PIN_13 ; 
	int button = 0 ;
	
	if (GPIO_Pin == GPIO_PIN_13){
		
		button = 1;
		return button ;
		
  }

}

/**
 * @brief  disable pb
 * @param  none
 * @retval None
 */
void s4464952_hal_pb_iss_deinit(void){
	

}
