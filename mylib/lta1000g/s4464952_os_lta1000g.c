/** 
 *************************************************************
 * @file /home/csse3010/csse3010/mylib/lta1000g/s4464952_os_lta1000g.c
 * @author Aina Jauhara - s4464952
 * @date 26/4/2020
 * @brief mylib lta1000g os file
 ***************************************************************
*/

/* Includes ------------------------------------------------------------------*/
 #include "s4464952_os_lta1000g.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
struct dualTimerMsg{
    char type;
    unsigned char timerValue;
};
/* Private function prototypes -----------------------------------------------*/
extern void TaskTimerDisplay(void);
extern void s4464952_os_lta1000g_init(void);

/**
 * @brief task timer display
 * @param  none
 * @retval None
 */
 extern void TaskTimerDisplay(void){

    uint16_t left_value = 0;
	uint16_t right_value = 0;
	int shift_right = 0 ;
	int shift_left = 0 ;

	struct dualTimerMsg RecvMessage;

	s4464952QueueTimerDisplay = xQueueCreate(5, sizeof(RecvMessage));		/* create queue */

	/* call init function from hal */
	

	for (;;) {

		if (s4464952QueueTimerDisplay != NULL) {	/* Check if queue exists */

			/* Check for item received - block atmost for 10 ticks */
			if (xQueueReceive( s4464952QueueTimerDisplay, &RecvMessage, 10 )) {				
				
				if (RecvMessage.type == 'r'){
					right_value = RecvMessage.timerValue;
					
					if (right_value < 32) {
					shift_right = right_value ;
					s4464952_hal_lta1000g_write(shift_right);
					} 

					if (right_value > 31) {
					shift_right = right_value & 31 ;
					s4464952_hal_lta1000g_write(shift_right);
					}
				}
				if (RecvMessage.type == 'l'){
					left_value = RecvMessage.timerValue;
					shift_left = left_value << 5;
					s4464952_hal_lta1000g_write(shift_left);
				}
					s4464952_hal_lta1000g_write(shift_left|shift_right);
			}
		}	
	}
 }

 /**
 * @brief unitialise os lta1000g
 * @param  none
 * @retval None
 */
 extern void s4464952_os_lta1000g_init(void){

	 	xTaskCreate( (void *) &TaskTimerDisplay, (const signed char *) "RECV", TaskTimerDisplay_STACK_SIZE, NULL, TaskTimerDisplay_PRIORITY, NULL );
		s4464952_hal_lta1000g_init();	

 }