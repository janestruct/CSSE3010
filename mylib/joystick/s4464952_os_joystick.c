/** 
 *************************************************************
 * @file /home/csse3010/csse3010/mylib/joystick/s4464952_os_joystick.c
 * @author Aina Jauhara - s4464952
 * @date 26/4/2020
 * @brief mylib joystick os file
 ***************************************************************
*/

/* Includes ------------------------------------------------------------------*/
 #include "s4464952_os_joystick.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
struct JoystickMsg{ 
	int x;							//x position of joystick
 	int y;							//y position of joystick	
};
int x_state = 0 ; 		//set x position of joystick
int y_state = 0 ; 		//set y position of joystick
int check = 0; 				//check key press
/* Private function prototypes -----------------------------------------------*/
extern void s4464952_os_joystick_init(void);
extern void s4464952_os_joystick_task(void);
void joystick_operation_x(void);
void joystick_operation_y(void);

/**
  * @brief  Joystick Task.
  * @param  None
  * @retval None
	*/
extern void s4464952_os_joystick_task(void){

		s4464952_hal_joystick_init();

		struct JoystickMsg SendMessage;

		s4464952QueueJoystick = xQueueCreate(10, sizeof(SendMessage));		/* Create queue of length 10 Message items */

	for (;;) {
			
			joystick_operation_x();
			joystick_operation_y();

			SendMessage.x = x_state;
			SendMessage.y = y_state;

		if (s4464952QueueJoystick != NULL) {	/* Check if queue exists */

			/*Send message to the front of the queue - wait atmost 10 ticks */
			if( xQueueSendToFront(s4464952QueueJoystick, ( void * ) &SendMessage, ( portTickType ) 10 ) != pdPASS ) {
				portENTER_CRITICAL();
				//debug_printf("Failed to post the message, after 10 ticks.\n\r");
				portEXIT_CRITICAL();
			}
		}
		/* Wait for 1000ms */
		vTaskDelay(500);
	}	
}

/**
  * @brief  Joystick signal x operation
  * @param  None
  * @retval None
	*/
void joystick_operation_x(void){

	int x_value = S4464952_HAL_JOYSTICK_X_READ() ;

	if (x_value < 10)
	{
			x_state = 0 ; 
	}	
	else if (10 < x_value && x_value < 1000)
	{
			x_state = 1 ; 
	}
	else if (1000 < x_value && x_value < 1500)
	{
			x_state = 2 ; 
	}
	else if (1500 < x_value && x_value < 2000)
	{
			x_state = 3 ; 
	}
	else if (2000 < x_value && x_value < 2100)
	{
			x_state = 4 ; 
	}
	else if (2500 < x_value && x_value < 3000)
	{
			x_state = 5 ; 
	}
	else if (3000 < x_value && x_value < 4090)
	{
			x_state = 6 ; 
	}
	else if (4090 < x_value)
	{
			x_state = 7 ; 
	}
 }

/**
  * @brief  Joystick signal y operation
  * @param  None
  * @retval None
	*/
void joystick_operation_y(void){

	int y_value = S4464952_HAL_JOYSTICK_Y_READ() ;

	if (y_value < 10){
			y_state = 0 ; 
	}	
	else if (10 < y_value && y_value < 1990){
			y_state = 1 ; 
	}
	else if (1990 < y_value && y_value < 2000){
			y_state = 2 ; 
	}
	else if (2000 < y_value && y_value < 3000){
			y_state = 3 ; 
	}
	else if (3000 < y_value && y_value < 4090){
			y_state = 4 ; 
	}
	else if (4090 < y_value){
			y_state = 5 ; 
	}
 }

/**
 * @brief EXTI line detection callback
 * @param GPIO_Pin: Specifies the pins connected EXTI line
 * @retval None
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
	BaseType_t xHigherPriorityTaskWoken;

	if(GPIO_Pin == BRD_A3_PIN)
	{
		/* Is it time for another Task() to run? */
		xHigherPriorityTaskWoken = pdFALSE;
		
   	if (s4464952SemaphoreJoystickZ != NULL) {/* Check if semaphore exists */

            xSemaphoreGiveFromISR(s4464952SemaphoreJoystickZ,&xHigherPriorityTaskWoken);		/* Give Joystick Z Semaphore from ISR*/
    }
		/* Perform context switching, if required. */
    portYIELD_FROM_ISR(xHigherPriorityTaskWoken);
	}
}

/**
 * @brief  Joystick interrupt handler
 * @param  none
 * @retval None
 */
void EXTI3_IRQHandler() {

    HAL_GPIO_EXTI_IRQHandler(BRD_A3_PIN);

}


/**
  * @brief  Initialise os joystick
  * @param  None
  * @retval None
  */
void s4464952_os_joystick_init(void){

	xTaskCreate( (void *) &s4464952_os_joystick_task, (const signed char *) "RECV", S4464952_OS_JOYSTICK_STACK_SIZE, NULL, S4464952_OS_JOYSTICK_PRIORITY, NULL );

	s4464952SemaphoreJoystickZ = xSemaphoreCreateBinary();

}

