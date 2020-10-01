/** 
 *************************************************************
 * @file /home/csse3010/csse3010/mylib/project/s4464952_CAG_Joystick.c
 * @author Aina Jauhara - s4464952
 * @date 11/5/2020
 * @brief mylib CAG Joystick os file
 ***************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "s4464952_CAG_Joystick.h"
#include "board.h"
#include "debug_printf.h"
#include "processor_hal.h"
/* Private typedef -----------------------------------------------------------*/
TaskHandle_t xs4464952_cag_joystick_handle = NULL;	//cag joystick handler
EventGroupHandle_t simulator_EventGroup;			//Control simulator Event Group
EventGroupHandle_t display_EventGroup;				//Control display Event Group
/* Private define ------------------------------------------------------------*/
//update time bit for simulator
#define UPDATE_500MS  1 << 0
#define UPDATE_1S     1 << 1
#define UPDATE_2S     1 << 2
#define UPDATE_5S     1 << 3
#define UPDATE_10S    1 << 4
#define CLEAR_GRID    1 << 5

//cell colour bit for display
#define SET_CELL_BLACK  	1 << 0
#define SET_CELL_RED			1 << 1
#define SET_CELL_GREEN  	1 << 2
#define SET_CELL_YELLOW		1 << 3
#define SET_CELL_BLUE			1 << 4
#define SET_CELL_MAGENTA	1 << 5
#define SET_CELL_CYAN			1 << 6
#define SET_CELL_WHITE		1 << 7

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
struct JoystickMsg{
	int x;
 int y;
};
struct JoystickMsg RecvMessage;
int z_signal = 0;
/* Private function prototypes -----------------------------------------------*/
extern void s4464952_CAG_Joystick_init(void);
extern void s4464952_CAG_Joystick_task(void);
void set_simulator_x_bit(void);
void set_simulator_y_bit(void);
void set_simulator_z_bit(void);

/**
  * @brief  CAG Joystick Task.
  * @param  None
  * @retval None
  */
extern void s4464952_CAG_Joystick_task(void){

    s4464952_os_joystick_init();
	
			/* Create Event Group */
			simulator_EventGroup = xEventGroupCreate();
			display_EventGroup = xEventGroupCreate();

	for (;;) {
      
		if (s4464952SemaphoreJoystickZ  != NULL) {	/* Check if semaphore exists */
			/* See if we can obtain the LED semaphore. If the semaphore is not available
          	 wait 10 ticks to see if it becomes free. */
			if ( xSemaphoreTake(s4464952SemaphoreJoystickZ , 10 ) == pdTRUE ) {
			
					portENTER_CRITICAL();
          z_signal = 1;
				//	debug_printf("Clear screen\n\r");
					portEXIT_CRITICAL();
			}
		}			
		if (s4464952QueueJoystick != NULL) {
			// Check for item received - block atmost for 10 ticks 
			if (xQueueReceive( s4464952QueueJoystick, &RecvMessage, 10 )) {
				// display received item 
				portENTER_CRITICAL();	
        set_simulator_x_bit();
				set_simulator_y_bit();
				set_simulator_z_bit();
				portEXIT_CRITICAL();
        	}
		} 
  	/* Wait for 1000ms */
		vTaskDelay(3000);
      }
 }

/**
  * @brief  Set simulator x bit
  * @param  None
  * @retval None
  */
void set_simulator_x_bit(void){

  EventBits_t displayBits;

  int x_signal =  RecvMessage.x;
  
  if (x_signal == 0) {	//check signal x value	

			/* Set event */
			displayBits = xEventGroupSetBits(display_EventGroup, SET_CELL_BLACK);

			portENTER_CRITICAL(); 
			//debug_printf("Setting set cell black Event Flag\n\r");
			portEXIT_CRITICAL();

		} else if (x_signal == 1) {	//check signal x value	

			/* Set event */
			displayBits = xEventGroupSetBits(display_EventGroup, SET_CELL_RED);

			portENTER_CRITICAL(); 
			//debug_printf("Setting set cell red Event Flag\n\r");
			portEXIT_CRITICAL();

		}else if (x_signal == 2) {	//check signal x value	

			/* Set event */
			displayBits = xEventGroupSetBits(display_EventGroup, SET_CELL_GREEN);

			portENTER_CRITICAL();
			//debug_printf("Setting set cell green Event Flag\n\r");
			portEXIT_CRITICAL();

		} else if (x_signal == 3) {	//check signal x value	

			/* Set event */
			displayBits = xEventGroupSetBits(display_EventGroup, SET_CELL_YELLOW);

			portENTER_CRITICAL(); 
			//debug_printf("Setting set cell yellow Event Flag\n\r");
			portEXIT_CRITICAL();

    } else if (x_signal == 4) {	//check signal x value	

			/* Set event */
			displayBits = xEventGroupSetBits(display_EventGroup, SET_CELL_BLUE);

			portENTER_CRITICAL();
			//debug_printf("Setting set cell blue Event Flag\n\r");
			portEXIT_CRITICAL();

		} else if (x_signal == 5) {	//check signal x value	

			/* Set event */
			displayBits = xEventGroupSetBits(display_EventGroup, SET_CELL_MAGENTA);

			portENTER_CRITICAL(); 
			//debug_printf("Setting set cell magenta Event Flag\n\r");
			portEXIT_CRITICAL();
		
    } else if (x_signal == 6) {	//check signal x value	

			/* Set event */
			displayBits = xEventGroupSetBits(display_EventGroup, SET_CELL_CYAN);

			portENTER_CRITICAL();
			//debug_printf("Setting set cell cyan Event Flag\n\r");
			portEXIT_CRITICAL();

		} else if (x_signal == 7) {	//check signal x value	

			/* Set event */
			displayBits = xEventGroupSetBits(display_EventGroup, SET_CELL_WHITE);

			portENTER_CRITICAL(); 
			//debug_printf("Setting set cell white Event Flag\n\r");
			portEXIT_CRITICAL();

		}
}

/**
  * @brief  Set simulator y bit
  * @param  None
  * @retval None
  */
void set_simulator_y_bit(void){

	EventBits_t simulatorBits;

  int y_signal =  RecvMessage.y;

	if (y_signal == 0) {	//check signal y value	
			
			/* Set event */
			simulatorBits = xEventGroupSetBits(simulator_EventGroup, UPDATE_500MS);

			portENTER_CRITICAL(); 
			//debug_printf("Setting update time every 500ms Event Flag\n\r");
			portEXIT_CRITICAL();

		} else if (y_signal == 1) {	//check signal y value	

			/* Set event */
			simulatorBits = xEventGroupSetBits(simulator_EventGroup, UPDATE_1S);

			portENTER_CRITICAL(); 
			//debug_printf("Setting update time every 1s Event Flag\n\r");
			portEXIT_CRITICAL();

		}else if (y_signal == 2) {	//check signal y value	

			/* Set event */
			simulatorBits = xEventGroupSetBits(simulator_EventGroup, UPDATE_2S);

			portENTER_CRITICAL();
			//debug_printf("Setting update time every 2s Event Flag\n\r");
			portEXIT_CRITICAL();

		} else if (y_signal == 3) {	//check signal y value	

			/* Set event */
			simulatorBits = xEventGroupSetBits(simulator_EventGroup, UPDATE_5S);

			portENTER_CRITICAL(); 
			//debug_printf("Setting update time every 5s Event Flag\n\r");
			portEXIT_CRITICAL();

		} else if (y_signal == 4) {	//check signal y value	

			/* Set event */
			simulatorBits = xEventGroupSetBits(simulator_EventGroup, UPDATE_10S);

			portENTER_CRITICAL(); 
			//debug_printf("Setting update time every 10s Event Flag\n\r");
			portEXIT_CRITICAL();
		}
}

/**
  * @brief  Set simulator z bit
  * @param  None
  * @retval None
  */
void set_simulator_z_bit(void){

	EventBits_t simulatorBits;
    
    if (z_signal == 1) {	

			/* Set event */
			simulatorBits = xEventGroupSetBits(simulator_EventGroup, CLEAR_GRID);

			portENTER_CRITICAL(); 
			//debug_printf("Setting clear grid Event Flag\n\r");
      z_signal = 0 ;
			portEXIT_CRITICAL();
		}
}

/**
  * @brief  Initialise os CAG Joystick
  * @param  None
  * @retval None
  */
extern void s4464952_CAG_Joystick_init(void){

	xTaskCreate( (void *) &s4464952_CAG_Joystick_task, (const signed char *) "CAG_JOYSTICK", S4464952_CAG_JOYSTICK_STACK_SIZE, NULL, S4464952_CAG_JOYSTICK_PRIORITY, &xs4464952_cag_joystick_handle);

}

/**
  * @brief  Deinitialise os CAG Joystick
  * @param  None
  * @retval None
*/  
extern void s4464952_CAG_Joystick_deinit(void){

	vTaskDelete(xs4464952_cag_joystick_handle);
	
}
