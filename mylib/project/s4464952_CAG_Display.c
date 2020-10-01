/** 
 *************************************************************
 * @file /home/csse3010/csse3010/mylib/project/s4464952_CAG_Display.c
 * @author Aina Jauhara - s4464952
 * @date 11/5/2020
 * @brief mylib CAG Display os file
 ***************************************************************
*/

/* Includes ------------------------------------------------------------------*/
#include "s4464952_CAG_Display.h"
#include "board.h"
#include "debug_printf.h"
#include "processor_hal.h"

/* Private typedef -----------------------------------------------------------*/
EventGroupHandle_t display_EventGroup;				//Control display Event Group
/* Private define ------------------------------------------------------------*/
//cell colour bit for display
#define SET_CELL_BLACK  	1 << 0
#define SET_CELL_RED		  1 << 1
#define SET_CELL_GREEN  	1 << 2
#define SET_CELL_YELLOW		1 << 3
#define SET_CELL_BLUE		  1 << 4
#define SET_CELL_MAGENTA	1 << 5
#define SET_CELL_CYAN		  1 << 6
#define SET_CELL_WHITE		1 << 7
#define CTRL_EVENT	    	SET_CELL_BLACK | SET_CELL_RED | SET_CELL_GREEN | SET_CELL_YELLOW | SET_CELL_BLUE | SET_CELL_MAGENTA | SET_CELL_CYAN | SET_CELL_WHITE 

#define BLACK  		0
#define RED		  	1
#define GREEN  		2
#define YELLOW		3
#define BLUE		  4
#define MAGENTA		5
#define CYAN		  6
#define WHITE	 	  7

#define SCREEN_CLEAR()  debug_printf("\e[2J")
#define SCREEN_HOME()  debug_printf("\e[H")

#define FG_BLACK 		30
#define FG_RED			31
#define FG_GREEN		32
#define FG_YELLOW		33
#define FG_BLUE			34
#define FG_MAGENTA	35
#define FG_CYAN			36
#define FG_WHITE		37
#define BG_BLACK		40
#define BG_RED			41
#define BG_GREEN		42
#define BG_YELLOW		43
#define BG_BLUE			44
#define BG_MAGENTA	45
#define BG_CYAN			46
#define BG_WHITE		47

#define CELL_BLACK 		"\e[7;30;40m"
#define CELL_RED			"\e[7;31;41m"
#define CELL_GREEN		"\e[7;32;42m"
#define CELL_YELLOW		"\e[7;33;43m"
#define CELL_BLUE			"\e[7;34;44m"
#define CELL_MAGENTA	"\e[7;35;45m"
#define CELL_CYAN			"\e[7;36;46m"
#define CELL_WHITE 		"\e[7;37;47m"

#define SET_CELL_COLOUR(fg, bg) debug_printf("\e[7;%d;%dm",fg,bg)
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
int alive = 4;
struct JoystickMsg{
	int x;
 int y;
};
int grid[15][15];
char *colour_palatte[] = {CELL_BLACK, CELL_RED, CELL_GREEN, CELL_YELLOW, CELL_BLUE, CELL_MAGENTA, CELL_CYAN, CELL_WHITE};
/* Private function prototypes -----------------------------------------------*/
extern void s4464952_CAG_Display_init(void);
extern void s4464952_CAG_Display_task(void);
void print_stuff(void);
void draw_still_life(void);
void draw_oscillator(void);
void draw_glider(void);
int check_colour(int colour);

/**
  * @brief  Set cell state
  * @param  None
  * @retval None
  */
void set_grid(int x, int y){

		grid[x][y] = BLUE; 		
}

/**
  * @brief  Update grid
  * @param  None
  * @retval None
  */
void grid_update(void){
	
	SCREEN_CLEAR();
	SCREEN_HOME();
	
	for (int col = 0 ; col < 15; col++){
		for (int row = 0 ; row < 15; row++){
			debug_printf("%s  ",colour_palatte[grid[row][col]]);
		}
		debug_printf("\n\r");
	}
}

/**
  * @brief  Set cell state
  * @param  None
  * @retval None
  */
void set_colour(int colour){

		if(alive != colour){
			for (int col = 0 ; col < 15 ; col++){
				for (int row = 0 ; row < 15 ; row++){
					if(grid[row][col] != 0){
						alive = colour;
						grid[row][col] = alive ;
					}
				}
			}
			grid_update();
		}	
}

/**
  * @brief  CAG Display Task.
  * @param  None
  * @retval None
  */
extern void s4464952_CAG_Display_task(void){

	display_EventGroup = xEventGroupCreate();		//create event group
	EventBits_t displayBits;			//event bit for display

	for (;;) {
	/* Wait a maximum of 100ms for either bit 0 or bit 1 to be set within
	 the event group.  Clear the bits before exiting. */
    displayBits = xEventGroupWaitBits(display_EventGroup, CTRL_EVENT, pdTRUE, pdFALSE, 10);

	//check if event flag is set
    if ((displayBits & SET_CELL_BLACK) != 0) {

			portENTER_CRITICAL(); 
			set_colour(BLACK);
			portEXIT_CRITICAL();

			displayBits = xEventGroupClearBits(display_EventGroup, SET_CELL_BLACK);		//Clear event flag.
		}
		//check if event flag is set
    if ((displayBits & SET_CELL_RED) != 0) {		

			portENTER_CRITICAL(); 
			set_colour(RED);
			portEXIT_CRITICAL();

			displayBits = xEventGroupClearBits(display_EventGroup, SET_CELL_RED);			//Clear event flag.
		}
		//check if event flag is set
		if ((displayBits & SET_CELL_GREEN) != 0) { 		

			portENTER_CRITICAL(); 
			set_colour(GREEN);
			portEXIT_CRITICAL();

			displayBits = xEventGroupClearBits(display_EventGroup, SET_CELL_GREEN);		//Clear event flag.
		}
    //check if event flag is set
		if ((displayBits & SET_CELL_YELLOW) != 0) {

			portENTER_CRITICAL(); 
			set_colour(YELLOW);
			portEXIT_CRITICAL();

			displayBits = xEventGroupClearBits(display_EventGroup, SET_CELL_YELLOW);	//Clear event flag.
		}
    //check if event flag is set
		if ((displayBits & SET_CELL_BLUE) != 0) {

			portENTER_CRITICAL(); 
			set_colour(BLUE);
			portEXIT_CRITICAL();

			displayBits = xEventGroupClearBits(display_EventGroup, SET_CELL_BLUE);		//Clear event flag.
		}
    //check if event flag is set
		if ((displayBits & SET_CELL_MAGENTA) != 0) {

			portENTER_CRITICAL(); 
			set_colour(MAGENTA);
			portEXIT_CRITICAL();

			displayBits = xEventGroupClearBits(display_EventGroup, SET_CELL_MAGENTA);		//Clear event flag.
		}
    //check if event flag is set
		if ((displayBits & SET_CELL_CYAN) != 0) {

			portENTER_CRITICAL(); 
			set_colour(CYAN);
			portEXIT_CRITICAL();

			displayBits = xEventGroupClearBits(display_EventGroup, SET_CELL_CYAN);		//Clear event flag.
		}
    	//check if event flag is set
		if ((displayBits & SET_CELL_WHITE) != 0) {

			portENTER_CRITICAL();
			set_colour(WHITE); 
			portEXIT_CRITICAL();

			displayBits = xEventGroupClearBits(display_EventGroup, SET_CELL_WHITE);		//Clear event flag.
		}
		  vTaskDelay(100);
	}
}

/**
  * @brief  Initialise os CAG Display
  * @param  None
  * @retval None
  */
extern void s4464952_CAG_Display_init(void){

	xTaskCreate( (void *) &s4464952_CAG_Display_task, (const signed char *) "RECV", S4464952_CAG_DISPLAY_STACK_SIZE, NULL, S4464952_CAG_DISPLAY_PRIORITY, NULL );

}
