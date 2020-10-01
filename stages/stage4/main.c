/**
  ******************************************************************************
  * @file    stage4/main.c
  * @author  Aina Jauhara - s4464952
  * @date  	 26/4/2020
  * @brief   main file for stage 4
  ******************************************************************************
  *
  */

/* Includes ------------------------------------------------------------------*/
#include "board.h"
#include "processor_hal.h"
#include "debug_printf.h"
#include "s4464952_os_lta1000g.h"
#include "s4464952_os_joystick.h"
#include <string.h>

/* Scheduler includes. */
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
int check ; 

struct dualTimerMsg{
  char type;
  unsigned char timerValue;
};
/* Private function prototypes -----------------------------------------------*/
void Hardware_init();
void ApplicationIdleHook( void ); /* The idle hook is used to blink the Blue 'Alive LED' every second */
void TaskTimerLeft( void );
void TaskTimerRight( void );
void push_status(void);

/* Task Priorities ------------------------------------------------------------*/
#define TaskTimerRight_PRIORITY					( tskIDLE_PRIORITY + 2 )
#define TaskTimerLeft_PRIORITY					( tskIDLE_PRIORITY + 2 )
/* Task Stack Allocations -----------------------------------------------------*/
#define TaskTimerLeft_STACK_SIZE				( configMINIMAL_STACK_SIZE * 2 )
#define TaskTimerRight_STACK_SIZE				( configMINIMAL_STACK_SIZE * 2 )


/**
  * @brief  Starts all the other tasks, then starts the scheduler.
  * @param  None
  * @retval None
  */
int main( void ) {

	BRD_init();
	s4464952_os_joystick_init();
	s4464952_os_lta1000g_init();
	Hardware_init();

	/* Start the task to flash the LED. */
 	xTaskCreate( (void *) &TaskTimerLeft, (const signed char *) "SEND", TaskTimerLeft_STACK_SIZE, NULL, TaskTimerLeft_PRIORITY, NULL );
	xTaskCreate( (void *) &TaskTimerRight, (const signed char *) "SEND", TaskTimerRight_STACK_SIZE, NULL, TaskTimerRight_PRIORITY, NULL );

	/* Start the scheduler.
	
	NOTE : Tasks run in system mode and the scheduler runs in Supervisor mode.
	The processor MUST be in supervisor mode when vTaskStartScheduler is
	called.  The demo applications included in the FreeRTOS.org download switch
	to supervisor mode prior to main being called.  If you are not using one of
	these demo application projects then ensure Supervisor mode is used here. */

	vTaskStartScheduler();

	/* We should never get here as control is now taken by the scheduler. */
  	return 0;
}

/**
  * @brief  Check current z signal.
  * @param  None
  * @retval None
  */
void push_status(void){
	check = current_timer();
	debug_printf("current mode : %d\n\r",check);
}

/**
  * @brief  Left Timer Task.
  * @param  None
  * @retval None
  */
void TaskTimerLeft( void ) {

	BRD_LEDBlueOff();
	
	struct dualTimerMsg LeftMessage; 
	
	/*specify message type */
	LeftMessage.type = 'l';
	LeftMessage.timerValue = 0;

	for (;;) {

		if (s4464952QueueTimerDisplay != NULL) {	/* Check if queue exists */

			/*Send message to the front of the queue - wait atmost 10 ticks */
			if( xQueueSendToFront(s4464952QueueTimerDisplay, ( void * ) &LeftMessage, ( portTickType ) 10 ) != pdPASS ) {

				debug_printf("Failed to post the message, after 10 ticks.\n\r");

			}
		}
    
		if (check == 0){
		/* Toggle Blue LED */
   		BRD_LEDBlueToggle();

		portENTER_CRITICAL();
		debug_printf("Left timer task counter\n\r");
		portEXIT_CRITICAL();

		LeftMessage.timerValue++;		/* update timer value */
	
		/*delay timer for 1000ms*/
		vTaskDelay(1000);
		}
	}
}

/**
  * @brief  Right Timer Task.
  * @param  None
  * @retval None
  */
void TaskTimerRight( void ) {

	BRD_LEDRedOff();
	struct dualTimerMsg RightMessage; 

	/*specify message type */
	RightMessage.type = 'r';
	RightMessage.timerValue = 0;

	for (;;) {

		if (s4464952QueueTimerDisplay != NULL) {	/* Check if queue exists */

			/*Send message to the front of the queue - wait atmost 10 ticks */
			if( xQueueSendToFront(s4464952QueueTimerDisplay, ( void * ) &RightMessage, ( portTickType ) 10 ) != pdPASS ) {

				debug_printf("Failed to post the message, after 10 ticks.\n\r");

			}
		}

		if (check == 1){
			/* Toggle Blue LED */
      		BRD_LEDRedToggle();
	
			portENTER_CRITICAL();
			debug_printf("Right timer task counter\n\r");
			portEXIT_CRITICAL();
	
			RightMessage.timerValue++;		/* update timer value */
	
		/*delay timer for 1000ms*/
		vTaskDelay(100);
		}
	}
}


/**
 * @brief  Send semaphore for interrupt
 * @param  GPIO Pin
 * @retval None
 */
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin){

		BaseType_t xHigherPriorityTaskWoken;
		
		if(GPIO_Pin == BRD_A3_PIN){
			xHigherPriorityTaskWoken = pdFALSE;
		
   	if (s4464952SemaphoreJoystickZ != NULL) {

            xSemaphoreGiveFromISR(s4464952SemaphoreJoystickZ,&xHigherPriorityTaskWoken);
    }

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
  * @brief  Hardware Initialisation.
  * @param  None
  * @retval None
  */
void Hardware_init( void ) {
	
	portDISABLE_INTERRUPTS();	//Disable interrupts

	BRD_LEDInit();				//Initialise Blue LED
	BRD_LEDBlueOff();				//Turn off Blue LED
	BRD_LEDRedOff();				//Turn off Blue LED

	portENABLE_INTERRUPTS();	//Enable interrupts
}

/**
  * @brief  Application Tick Task.
  * @param  None
  * @retval None
  */
void vApplicationTickHook( void ) {

	BRD_LEDBlueOff();
	BRD_LEDRedOff();
}

/**
  * @brief  Idle Application Task
  * @param  None
  * @retval None
  */
void vApplicationIdleHook( void ) {
	static portTickType xLastTx = 0;

	BRD_LEDBlueOff();
	BRD_LEDRedOff();

	for (;;) {

		/* The idle hook simply prints the idle tick count, every second */
		if ((xTaskGetTickCount() - xLastTx ) > (1000 / portTICK_RATE_MS)) {

			xLastTx = xTaskGetTickCount();

			portENTER_CRITICAL();
			debug_printf("IDLE Tick %d\n", xLastTx);
			portEXIT_CRITICAL();

			/* Blink Alive LED */
			BRD_LEDBlueToggle();
			BRD_LEDRedToggle();
		}
	}
}

/**
  * @brief  vApplicationStackOverflowHook
  * @param  Task Handler and Task Name
  * @retval None
  */
void vApplicationStackOverflowHook( xTaskHandle pxTask, signed char *pcTaskName ) {
	/* This function will get called if a task overflows its stack.   If the
	parameters are corrupt then inspect pxCurrentTCB to find which was the
	offending task. */

	BRD_LEDBlueOff();
	( void ) pxTask;
	( void ) pcTaskName;

	for( ;; );
}
