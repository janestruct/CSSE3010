/** 
 **************************************************************
 * @file /home/csse3010/csse3010/mylib/iss/s4495585_hal_iss.c
 * @author Aina Jauhara - s4464952
 * @date 23/02/2020
 * @brief mylib iss file
 ***************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "board.h"
#include "stm32f4xx_hal.h"
#include "debug_printf.h"
#include "s4464952_hal_iss.h"
#include "s4464952_hal_pb.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define S4464952_HAL_ISS_SOURCE_1                   0
#define S4464952_HAL_ISS_SOURCE_2                   1
#define S4464952_HAL_ISS_SOURCE_3                   2
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/*Array stores event counter value*/
uint32_t iss_eventcounter_val[] = {0};

/*Array stores last timer value*/
uint32_t iss_lasttimer_val[] = {0};

/*Array stores delay timer value*/
uint32_t iss_delaytimer_val[] = {10};

/* Private function prototypes -----------------------------------------------*/
void s4464952_hal_iss_init(void);                                                                           //initialise iss counter
void s4464952_hal_iss_synchroniser(unsigned char signal_source_index);                                      //sync input signal
void s4464952_hal_iss_eventcounter_read(unsigned char signal_source_index);                                 //return specified event counter value
void s4464952_hal_iss_lasttimer_read(unsigned char signal_source_index);                                    //return specified last time value
void s4464952_hal_iss_eventcounter_reset(unsigned char signal_source_index);                                //reset specified event counter value
void s4464952_hal_iss_lasttimer_reset(unsigned char signal_source_index);                                   //reset specified last time value
void s4464952_hal_iss_delaytimer_ctrl(unsigned char signal_source_index,int delay_value);                   //set delat value for specified source



/**
 * @brief  initialise iss counter
 * @param  none
 * @retval None
 */
void s4464952_hal_iss_init(void){
	
}

/**
 * @brief  synchronise input signal
 * @param  signal source index
 * @retval None
 */
void s4464952_hal_iss_synchroniser(unsigned char signal_source_index){
	
    int button_press = s4464952_hal_pb_iss_isr() ;

	int last_timer = HAL_GetTick() ; 
	int interval = HAL_GetTick() - last_timer ; //determine the time interval between interrupt

	if (button_press = 1 ) {
	if (interval > 5000) {

		//if interval more than 50ms, interrupt valid
		signal_source_index = 1 ; 
		s4464952_hal_iss_eventcounter_read(signal_source_index);
	} 
	}

}

/**
 * @brief  return event counter value
 * @param  signal source index
 * @retval None
 */
void s4464952_hal_iss_eventcounter_read(unsigned char signal_source_index){
	
	

		if(signal_source_index == 0){

			iss_eventcounter_val[0] ++; 
			debug_printf("Event 1 Counter Value : %d\n\r",  iss_eventcounter_val[0]);	

			if (iss_eventcounter_val[0] > 9){
			
			s4464952_hal_iss_eventcounter_reset(signal_source_index);
			debug_printf("Event 1 Counter Value : %d\n\r",  iss_eventcounter_val[0]);

			}
		}else if(signal_source_index == 1){

			iss_eventcounter_val[1] ++; 
			debug_printf("Event 2 Counter Value : %d\n\r",  iss_eventcounter_val[1]);

			if (iss_eventcounter_val[1] > 9){
			
			s4464952_hal_iss_eventcounter_reset(signal_source_index);
			debug_printf("Event 2 Counter Value : %d\n\r",  iss_eventcounter_val[1]);
			
			}			

		}else if(signal_source_index == 2){

			iss_eventcounter_val[2] ++; 
			debug_printf("Event 3 Counter Value : %d\n\r",  iss_eventcounter_val[2]);

			if (iss_eventcounter_val[2] > 9){
			
			s4464952_hal_iss_eventcounter_reset(signal_source_index);
			debug_printf("Event 3 Counter Value : %d\n\r",  iss_eventcounter_val[2]);
			
			}
		}

		
}

/**
 * @brief  return last time value
 * @param  signal source index
 * @retval None
 */
void s4464952_hal_iss_lasttimer_read(unsigned char signal_source_index){
	
		
		if(signal_source_index == 0){

			iss_lasttimer_val[0] = HAL_GetTick() ; 
			debug_printf("Event 1 Last Time : %d\n\n", iss_lasttimer_val[0]);
			
		}else if(signal_source_index == 1){

			iss_lasttimer_val[1] = HAL_GetTick() ; 
			debug_printf("Event 1 Last Time : %d\n\n", iss_lasttimer_val[1]);

		}else if(signal_source_index == 2){

			iss_lasttimer_val[2] = HAL_GetTick() ; 
			debug_printf("Event 1 Last Time : %d\n\n", iss_lasttimer_val[2]);
		}


}

/**
 * @brief  reset event counter value
 * @param  signal source index
 * @retval None
 */
void s4464952_hal_iss_eventcounter_reset(unsigned char signal_source_index){
	
		if(signal_source_index == 0){

			iss_eventcounter_val[0] = 0 ; 
			
		}else if(signal_source_index == 1){

			iss_eventcounter_val[1] = 0 ; 

		}else if(signal_source_index == 2){

			iss_eventcounter_val[2] = 0 ; 
		}

}

/**
 * @brief  reset last time value
 * @param  signal source index
 * @retval None
 */
void s4464952_hal_iss_lasttimer_reset(unsigned char signal_source_index){

		if(signal_source_index == 0){

			iss_lasttimer_val[0] = 0; 
			
		}else if(signal_source_index == 1){

			iss_lasttimer_val[1] = 0 ; 

		}else if(signal_source_index == 2){

			iss_lasttimer_val[2] = 0 ; 
		}	

}

/**
 * @brief  set delay value
 * @param  signal source index, delay value
 * @retval None
 */
void s4464952_hal_iss_delaytimer_ctrl(unsigned char signal_source_index,int delay_value){
	

}


