/** 
 *************************************************************
 * @file /home/csse3010/csse3010/mylib/keypad/s4464952_os_keypad.c
 * @author Aina Jauhara - s4464952
 * @date 11/5/2020
 * @brief mylib keypad os file
 ***************************************************************
*/

/* Includes ------------------------------------------------------------------*/
 #include "s4464952_os_keypad.h"
/* Private typedef -----------------------------------------------------------*/
EventGroupHandle_t grid_EventGroup;			//Control simulator Event Group
/* Private define ------------------------------------------------------------*/
//all event bit mapped to the keypad
#define SET_1  	1 << 0
#define SET_2		1 << 1
#define SET_3 	1 << 2
#define SET_4		1 << 3
#define SET_5	  1 << 4
#define SET_6  	1 << 5
#define SET_7		1 << 6
#define SET_8		1 << 7
#define SET_9		1 << 8
#define SET_0		1 << 9
#define SET_A 	1 << 10
#define SET_B		1 << 11
#define SET_C	  1 << 12
#define SET_D  	1 << 13
#define SET_E		1 << 14
#define SET_F		1 << 15
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
int key_x; 		//set x value for key press
int key_y;		//set y value for key press
/* Private function prototypes -----------------------------------------------*/
extern void s4464952_os_keypad_init(void);
extern void s4464952_os_keypad_task(void);
void keypad_operation(void);
void press_led(void);

/**
  * @brief  Keypad Task.
  * @param  None
  * @retval None
  */
extern void s4464952_os_keypad_task(void){

  /* Create Event Group */
	grid_EventGroup = xEventGroupCreate();

	EventBits_t gridBits;

  for (;;) {

      s4464952_hal_keypad_fsmprocessing();
      int stat =  s4464952_keypad_read_key();
			press_led();

   if (stat == 1){

    	/* Set event */
		  gridBits = xEventGroupSetBits(grid_EventGroup, SET_1);
			portENTER_CRITICAL(); 
			//debug_printf("Setting cell at position 1 Event Flag\n\r");
			portEXIT_CRITICAL();

  } else if (stat == 2){

    	/* Set event */
		  gridBits = xEventGroupSetBits(grid_EventGroup, SET_4);
			portENTER_CRITICAL(); 
			//debug_printf("Setting cell at position 4 Event Flag\n\r");
			portEXIT_CRITICAL();

  } else if (stat == 3){

    	/* Set event */
		  gridBits = xEventGroupSetBits(grid_EventGroup, SET_7);
			portENTER_CRITICAL(); 
			//debug_printf("Setting cell at position 7 Event Flag\n\r");
			portEXIT_CRITICAL();

  } else if (stat == 4){

    	/* Set event */
		  gridBits = xEventGroupSetBits(grid_EventGroup, SET_0);
			portENTER_CRITICAL(); 
			//debug_printf("Setting cell at position 0 Event Flag\n\r");
			portEXIT_CRITICAL();

  } else if (stat == 5){

    	/* Set event */
		  gridBits = xEventGroupSetBits(grid_EventGroup, SET_2);
			portENTER_CRITICAL(); 
			//debug_printf("Setting cell at position 2 Event Flag\n\r");
			portEXIT_CRITICAL();

  } else if (stat == 6){

    	/* Set event */
		  gridBits = xEventGroupSetBits(grid_EventGroup, SET_5);
			portENTER_CRITICAL(); 
			//debug_printf("Setting cell at position 5 Event Flag\n\r");
			portEXIT_CRITICAL();

  } else if (stat == 7){

    	/* Set event */
		  gridBits = xEventGroupSetBits(grid_EventGroup, SET_8);
			portENTER_CRITICAL(); 
			//debug_printf("Setting cell at position 8 Event Flag\n\r");
			portEXIT_CRITICAL();

  } else if (stat == 8){

    	/* Set event */
		  gridBits = xEventGroupSetBits(grid_EventGroup, SET_F);
			portENTER_CRITICAL(); 
			//debug_printf("Setting cell at position F Event Flag\n\r");
			portEXIT_CRITICAL();

  } else if (stat == 9){

    	/* Set event */
		  gridBits = xEventGroupSetBits(grid_EventGroup, SET_3);
			portENTER_CRITICAL(); 
			//debug_printf("Setting cell at position 3 Event Flag\n\r");
			portEXIT_CRITICAL();

  } else if (stat == 10){

    	/* Set event */
		  gridBits = xEventGroupSetBits(grid_EventGroup, SET_6);
			portENTER_CRITICAL(); 
			//debug_printf("Setting cell at position 6 Event Flag\n\r");
			portEXIT_CRITICAL();

  } else if (stat == 11){

    	/* Set event */
		  gridBits = xEventGroupSetBits(grid_EventGroup, SET_9);
			portENTER_CRITICAL(); 
			//debug_printf("Setting cell at position 9 Event Flag\n\r");
			portEXIT_CRITICAL();

  } else if (stat == 12){

			portENTER_CRITICAL(); 
			//debug_printf("Setting cell at position E Event Flag\n\r");
			portEXIT_CRITICAL();

  } else if (stat == 13){

      /* Set event */
		  gridBits = xEventGroupSetBits(grid_EventGroup, SET_A);
			portENTER_CRITICAL(); 
			//debug_printf("Setting cell at position A Event Flag\n\r");
			portEXIT_CRITICAL();

  }else if (stat == 14){

      /* Set event */
		  gridBits = xEventGroupSetBits(grid_EventGroup, SET_B);
			portENTER_CRITICAL(); 
			//debug_printf("Setting cell at position B Event Flag\n\r");
			portEXIT_CRITICAL();

  }else if (stat == 15){

    	/* Set event */
		  gridBits = xEventGroupSetBits(grid_EventGroup, SET_C);
			portENTER_CRITICAL(); 
			//debug_printf("Setting cell at position C Event Flag\n\r");
			portEXIT_CRITICAL();

  } else if (stat == 16){

    	/* Set event */
		  gridBits = xEventGroupSetBits(grid_EventGroup, SET_D);
			portENTER_CRITICAL(); 
			//debug_printf("Setting cell at position D Event Flag\n\r");
			portEXIT_CRITICAL();
  } 
	/* Wait for 500ms */
  vTaskDelay(500);
	}
}


/**
  * @brief  Set keypad green led 
  * @param  None
  * @retval None
  */

void press_led(void){

	BRD_LEDGreenOff();

	int press = s4464952_hal_keypad_read_status();		 

	if (press == 1){
				/* Toggle LED */
				BRD_LEDGreenToggle();
  }
	else 
	{
			BRD_LEDGreenOff();
	}
}

/**
  * @brief  Initialise os keypad
  * @param  None
  * @retval None
  */
extern void s4464952_os_keypad_init(void){

	xTaskCreate( (void *) &s4464952_os_keypad_task, (const signed char *) "RECV", S4464952_OS_KEYPAD_STACK_SIZE, NULL, S4464952_OS_KEYPAD_PRIORITY, NULL );
  
	keypad_gpio_init();
  s4464952_hal_keypad_init();

}
