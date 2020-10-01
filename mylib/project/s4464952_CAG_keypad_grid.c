/** 
 *************************************************************
 * @file /home/csse3010/csse3010/mylib/project/s4464952_CAG_keypad_grid.c
 * @author Aina Jauhara - s4464952
 * @date 11/5/2020
 * @brief mylib CAG keypad grid os file
 ***************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "s4464952_CAG_keypad_grid.h"
#include "board.h"
#include "debug_printf.h"
#include "processor_hal.h"
/* Private typedef -----------------------------------------------------------*/
TaskHandle_t xs4464952_cag_keypad_grid_handle = NULL;	//cag keypad handler
EventGroupHandle_t grid_EventGroup;			//Control simulator Event Group
EventGroupHandle_t simulator_EventGroup;			//Control simulator Event Group
/* Private define ------------------------------------------------------------*/
#define SET_1  	1 << 0
#define SET_2   1 << 1
#define SET_3 	1 << 2
#define SET_4   1 << 3
#define SET_5   1 << 4
#define SET_6  	1 << 5
#define SET_7   1 << 6
#define SET_8   1 << 7
#define SET_9   1 << 8
#define SET_0   1 << 9
#define SET_A 	1 << 10
#define SET_B   1 << 11
#define SET_C   1 << 12
#define SET_D  	1 << 13
#define SET_E   1 << 14
#define SET_F   1 << 15
#define KEYPAD_CTRL_EVENT	SET_1 | SET_2 | SET_3 | SET_4 | SET_5 | SET_6 | SET_7 | SET_8 | SET_9 | SET_0 | SET_A | SET_B | SET_C | SET_D | SET_E | SET_F 

#define CLEAR_GRID    1 << 5
#define START 		  1 << 6
#define STOP		  1 << 7

#define clear_bit 		0
#define start_bit		1
#define stop_bit		2
/* Private macro -------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
typedef struct caMessage{
  int type ;
  int cell_x;
  int cell_y;
} caMessage_t;
int bit ; 
int count0 ;
int countF ;
/* Private function prototypes -----------------------------------------------*/
extern void s4464952_CAG_keypad_grid_init(void);
extern void s4464952_CAG_keypad_grid_task(void);
void s4464952_os_lta1000g_init(void);
int check_subgrid(void);
void subgrid_x(void);
void subgrid_y(void);
void keypad_simulator_bit(void);
void s4464952_hal_lta1000g_write(unsigned short value);
int check_subgrid(void);


/**
  * @brief  CAG Joystick Task.
  * @param  None
  * @retval None
  */
extern void s4464952_CAG_keypad_grid_task(void){	

	EventBits_t gridBits;                 
	caMessage_t grid ; 

	/* Create Event Group */
	grid_EventGroup = xEventGroupCreate();
	s4464952QueueKeypad = xQueueCreate(10, sizeof(grid));		

	s4464952_os_keypad_init();
	s4464952_os_lta1000g_init();
	BRD_LEDRedToggle();
	
  for (;;) {

	check_subgrid();

 	/* Wait a maximum of 100ms for either bit 0 or bit 1 to be set within
       the event group.  Clear the bits before exiting. */
    gridBits = xEventGroupWaitBits(grid_EventGroup, KEYPAD_CTRL_EVENT, pdTRUE, pdFALSE, 10);

		//check if event flag is set
		if ((gridBits & SET_1 ) != 0) {
			
			grid.cell_x = 0 ;
			grid.cell_y = 0 ;

			if (s4464952QueueKeypad != NULL) {	/* Check if queue exists */

			/*Send message to the front of the queue - wait atmost 10 ticks */
				if( xQueueSendToFront(s4464952QueueKeypad, ( void * ) &grid, ( portTickType ) 10 ) != pdPASS ) {
				portENTER_CRITICAL();
				debug_printf("Failed to post the message, after 10 ticks.\n\r");
				portEXIT_CRITICAL();
				}
			}
			gridBits = xEventGroupClearBits(grid_EventGroup, SET_1 );		//Clear event flag.
	
		} if ((gridBits & SET_2 ) != 0) {
			
			
			grid.cell_x = 1 ;
			grid.cell_y = 0 ;

			if (s4464952QueueKeypad != NULL) {	/* Check if queue exists */

			/*Send message to the front of the queue - wait atmost 10 ticks */
				if( xQueueSendToFront(s4464952QueueKeypad, ( void * ) &grid, ( portTickType ) 10 ) != pdPASS ) {
				portENTER_CRITICAL();
				debug_printf("Failed to post the message, after 10 ticks.\n\r");
				portEXIT_CRITICAL();
				}
			}
			gridBits = xEventGroupClearBits(grid_EventGroup, SET_2 );		//Clear event flag.
	
		} if ((gridBits & SET_3 ) != 0) {

			grid.cell_x = 2 ;
			grid.cell_y = 0 ;

			if (s4464952QueueKeypad != NULL) {	/* Check if queue exists */

			/*Send message to the front of the queue - wait atmost 10 ticks */
				if( xQueueSendToFront(s4464952QueueKeypad, ( void * ) &grid, ( portTickType ) 10 ) != pdPASS ) {
				portENTER_CRITICAL();
				debug_printf("Failed to post the message, after 10 ticks.\n\r");
				portEXIT_CRITICAL();
				}
			}
			gridBits = xEventGroupClearBits(grid_EventGroup, SET_3 );		//Clear event flag.
	
		} if ((gridBits & SET_4 ) != 0) {

			grid.cell_x = 0 ;
			grid.cell_y = 1 ;
			
			if (s4464952QueueKeypad != NULL) {	/* Check if queue exists */

			/*Send message to the front of the queue - wait atmost 10 ticks */
				if( xQueueSendToFront(s4464952QueueKeypad, ( void * ) &grid, ( portTickType ) 10 ) != pdPASS ) {
				portENTER_CRITICAL();
				debug_printf("Failed to post the message, after 10 ticks.\n\r");
				portEXIT_CRITICAL();
				}
			}
			gridBits = xEventGroupClearBits(grid_EventGroup, SET_4 );		//Clear event flag.
		
		} if ((gridBits & SET_5 ) != 0) {

			grid.cell_x = 1 ;
			grid.cell_y = 1 ; 

			if (s4464952QueueKeypad != NULL) {	/* Check if queue exists */

			/*Send message to the front of the queue - wait atmost 10 ticks */
				if( xQueueSendToFront(s4464952QueueKeypad, ( void * ) &grid, ( portTickType ) 10 ) != pdPASS ) {
				portENTER_CRITICAL();
				debug_printf("Failed to post the message, after 10 ticks.\n\r");
				portEXIT_CRITICAL();
				}
			}
			gridBits = xEventGroupClearBits(grid_EventGroup, SET_5 );		//Clear event flag.
	
		} if ((gridBits & SET_6 ) != 0) {

			grid.cell_x = 2 ;
			grid.cell_y = 1 ;

			if (s4464952QueueKeypad != NULL) {	/* Check if queue exists */

			/*Send message to the front of the queue - wait atmost 10 ticks */
				if( xQueueSendToFront(s4464952QueueKeypad, ( void * ) &grid, ( portTickType ) 10 ) != pdPASS ) {
				portENTER_CRITICAL();
				debug_printf("Failed to post the message, after 10 ticks.\n\r");
				portEXIT_CRITICAL();
				}
			}
			gridBits = xEventGroupClearBits(grid_EventGroup, SET_6 );		//Clear event flag.
	
		} if ((gridBits & SET_7 ) != 0) {
			
			grid.cell_x = 0 ;
			grid.cell_y = 2 ;

			if (s4464952QueueKeypad != NULL) {	/* Check if queue exists */

			/*Send message to the front of the queue - wait atmost 10 ticks */
				if( xQueueSendToFront(s4464952QueueKeypad, ( void * ) &grid, ( portTickType ) 10 ) != pdPASS ) {
				portENTER_CRITICAL();
				debug_printf("Failed to post the message, after 10 ticks.\n\r");
				portEXIT_CRITICAL();
				}
			}
			gridBits = xEventGroupClearBits(grid_EventGroup, SET_7 );		//Clear event flag.
	
		} if ((gridBits & SET_8 ) != 0) {

			grid.cell_x = 1 ;
			grid.cell_y = 2 ;

			if (s4464952QueueKeypad != NULL) {	/* Check if queue exists */

			/*Send message to the front of the queue - wait atmost 10 ticks */
				if( xQueueSendToFront(s4464952QueueKeypad, ( void * ) &grid, ( portTickType ) 10 ) != pdPASS ) {
				portENTER_CRITICAL();
				debug_printf("Failed to post the message, after 10 ticks.\n\r");
				portEXIT_CRITICAL();
				}
			}
			gridBits = xEventGroupClearBits(grid_EventGroup, SET_8 );		//Clear event flag.
		
		} if ((gridBits & SET_9 ) != 0) {

			grid.cell_x = 2 ;
			grid.cell_y = 2 ;

			if (s4464952QueueKeypad != NULL) {	/* Check if queue exists */

			/*Send message to the front of the queue - wait atmost 10 ticks */
				if( xQueueSendToFront(s4464952QueueKeypad, ( void * ) &grid, ( portTickType ) 10 ) != pdPASS ) {
				portENTER_CRITICAL();
				//debug_printf("Failed to post the message, after 10 ticks.\n\r");
				portEXIT_CRITICAL();
				}
			}
			gridBits = xEventGroupClearBits(grid_EventGroup, SET_9 );		//Clear event flag.
	
		} if ((gridBits & SET_0 ) != 0) {

			portENTER_CRITICAL(); 
			subgrid_x();
			//debug_printf("Update cell at position 0 event\n\r");
			portEXIT_CRITICAL();
			gridBits = xEventGroupClearBits(grid_EventGroup, SET_0 );		//Clear event flag.
	
		} if ((gridBits & SET_A ) != 0) {

			portENTER_CRITICAL(); 
			//debug_printf("Update cell at position A event\n\r");
			bit = start_bit;
			keypad_simulator_bit();
			portEXIT_CRITICAL();
			gridBits = xEventGroupClearBits(grid_EventGroup, SET_A );		//Clear event flag.
	
		} if ((gridBits & SET_B ) != 0) {

			portENTER_CRITICAL(); 
			//debug_printf("Update cell at position B event\n\r");
			bit = stop_bit;
			keypad_simulator_bit();
			portEXIT_CRITICAL();
			gridBits = xEventGroupClearBits(grid_EventGroup, SET_B );		//Clear event flag.
		
		} if ((gridBits & SET_C ) != 0) {

			portENTER_CRITICAL(); 
			//debug_printf("Update cell at position C event\n\r");
			bit = clear_bit;
			keypad_simulator_bit();
			portEXIT_CRITICAL();
			gridBits = xEventGroupClearBits(grid_EventGroup, SET_C );		//Clear event flag.
	
		} if ((gridBits & SET_D ) != 0) {

			portENTER_CRITICAL(); 
			//debug_printf("Update cell at position D event\n\r");
			portEXIT_CRITICAL();
			gridBits = xEventGroupClearBits(grid_EventGroup, SET_D );		//Clear event flag.
	
		} if ((gridBits & SET_E ) != 0) {

			portENTER_CRITICAL(); 
			//debug_printf("Update cell at position E event\n\r");
			portEXIT_CRITICAL();
			gridBits = xEventGroupClearBits(grid_EventGroup, SET_E );		//Clear event flag.
	
		} if ((gridBits & SET_F ) != 0) {

			portENTER_CRITICAL(); 
			subgrid_y();
			//debug_printf("Update cell at position F event\n\r");
			portEXIT_CRITICAL();
			gridBits = xEventGroupClearBits(grid_EventGroup, SET_F );		//Clear event flag.
		}
    	/* Wait for 500ms */
		vTaskDelay(500);
      }
 }

/**
  * @brief  Set x subgrid location
  * @param  None
  * @retval None
  */
void subgrid_x(void){
			
	if (count0 < 4){
		count0++;
	}
	else 
	{
		count0 = 0;
	}
}

/**
  * @brief  Set y subgrid location
  * @param  None
  * @retval None
  */
void subgrid_y(void){
			
	if (countF < 4){
		countF++;
	}
	else 
	{
		countF = 0;
	}
}

/**
  * @brief  Check current subgrid location
  * @param  None
  * @retval None
  */
int check_subgrid(void){

	int grid_x = count0;
	int grid_y = countF;
	int subgrid = 0;

	if (grid_x == 0){
		if (grid_y == 0){
			subgrid = 1; 
			s4464952_hal_lta1000g_write(0x00);
		}
		if (grid_y == 1){
			subgrid = 6;
			s4464952_hal_lta1000g_write(0x01);
		}
		if (grid_y == 2){
			subgrid = 11; 
			s4464952_hal_lta1000g_write(0x02);
		}
		if (grid_y == 3){
			subgrid = 16; 
			s4464952_hal_lta1000g_write(0x03);
		}
		if (grid_y == 4){
			subgrid = 21; 
			s4464952_hal_lta1000g_write(0x04);
		}
	}
	if (grid_x == 1){
		if (grid_y == 0){
			subgrid = 2; 
			s4464952_hal_lta1000g_write(0x20);
		}
		if (grid_y == 1){
			subgrid = 7; 
			s4464952_hal_lta1000g_write(0x21);
		}
		if (grid_y == 2){
			subgrid = 12; 
			s4464952_hal_lta1000g_write(0x22);
		}
		if (grid_y == 3){
			subgrid = 17; 
			s4464952_hal_lta1000g_write(0x23);
		}
		if (grid_y == 4){
			subgrid = 22; 
			s4464952_hal_lta1000g_write(0x24);
		}
	}
	if (grid_x == 2){
		if (grid_y == 0){
			subgrid = 3; 
			s4464952_hal_lta1000g_write(0x40);
		}
		if (grid_y == 1){
			subgrid = 8; 
			s4464952_hal_lta1000g_write(0x41);
		}
		if (grid_y == 2){
			subgrid = 13; 
			s4464952_hal_lta1000g_write(0x42);
		}
		if (grid_y == 3){
			subgrid = 18; 
			s4464952_hal_lta1000g_write(0x43);
		}
		if (grid_y == 4){
			subgrid = 23; 
			s4464952_hal_lta1000g_write(0x44);
		}
	}
	if (grid_x == 3){
		if (grid_y == 0){
			subgrid = 4; 
			s4464952_hal_lta1000g_write(0x60);
		}
		if (grid_y == 1){
			subgrid = 9; 
			s4464952_hal_lta1000g_write(0x61);
		}
		if (grid_y == 2){
			subgrid = 14; 
			s4464952_hal_lta1000g_write(0x62);
		}
		if (grid_y == 3){
			subgrid = 19; 
			s4464952_hal_lta1000g_write(0x63);
		}
		if (grid_y == 4){
			subgrid = 24; 
			s4464952_hal_lta1000g_write(0x64);
		}
	}
	if (grid_x == 4){
		if (grid_y == 0){
			subgrid = 5; 
			s4464952_hal_lta1000g_write(0x80);
		}
		if (grid_y == 1){
			subgrid = 10; 
			s4464952_hal_lta1000g_write(0x81);
		}
		if (grid_y == 2){
			subgrid = 15; 
			s4464952_hal_lta1000g_write(0x82);
		}
		if (grid_y == 3){
			subgrid = 20; 
			s4464952_hal_lta1000g_write(0x83);
		}
		if (grid_y == 4){
			subgrid = 25; 
			s4464952_hal_lta1000g_write(0x84);
		}
	}
	return subgrid ;
}

/**
  * @brief  Set simulator bit
  * @param  None
  * @retval None
  */
void keypad_simulator_bit(void){
	
	  /* Create Event Group */
	simulator_EventGroup = xEventGroupCreate();

  	EventBits_t simulatorBits;

	if (bit == 0){

		simulatorBits = xEventGroupSetBits(simulator_EventGroup, CLEAR_GRID);
		portENTER_CRITICAL(); 
		//debug_printf("Setting clear grid Event Flag\n\r");
		portEXIT_CRITICAL();

	} else if (bit == 1){

		simulatorBits = xEventGroupSetBits(simulator_EventGroup, START);
		portENTER_CRITICAL(); 
		//debug_printf("Setting start simulation Event Flag\n\r");
		portEXIT_CRITICAL();

	} else if (bit == 2){

		simulatorBits = xEventGroupSetBits(simulator_EventGroup, STOP);
		portENTER_CRITICAL(); 
		//debug_printf("Setting stop simulation Event Flag\n\r");
		portEXIT_CRITICAL();

	}
}

/**
  * @brief  Initialise os CAG keypad grid
  * @param  None
  * @retval None
  */
extern void s4464952_CAG_keypad_grid_init(void){

	xTaskCreate( (void *) &s4464952_CAG_keypad_grid_task, (const signed char *) "RECV", S4464952_CAG_KEYPAD_GRID_STACK_SIZE, NULL, S4464952_CAG_KEYPAD_GRID_PRIORITY, NULL );
	
}
