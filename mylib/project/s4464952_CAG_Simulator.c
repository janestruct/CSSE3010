/** 
 *************************************************************
 * @file /home/csse3010/csse3010/mylib/project/s4464952_CAG_Simulator.c
 * @author Aina Jauhara - s4464952
 * @date 11/5/2020
 * @brief mylib CAG Simulator os file
 ***************************************************************
*/

/* Includes ------------------------------------------------------------------*/
 #include "s4464952_CAG_Simulator.h"
 #include <stdbool.h>
/* Private typedef -----------------------------------------------------------*/
TaskHandle_t xs4464952_cag_simulator_handle = NULL;
EventGroupHandle_t simulator_EventGroup;			//Control simulator Event Group
typedef struct caMessage{
  int type ;
  int cell_x;
  int cell_y;
} caMessage_t;
caMessage_t gridMessage;
/* Private define ------------------------------------------------------------*/
#define UPDATE_500MS  1 << 0
#define UPDATE_1S     1 << 1
#define UPDATE_2S     1 << 2
#define UPDATE_5S     1 << 3
#define UPDATE_10S    1 << 4
#define CLEAR_GRID    1 << 5
#define START 				1 << 6
#define STOP					1 << 7
#define CTRL_EVENT		UPDATE_500MS | UPDATE_1S | UPDATE_2S | UPDATE_5S | UPDATE_10S | CLEAR_GRID | START | STOP


#define GRIDWIDTH 		15
#define GRIDHEIGHT 		15
#define DEAD				 	0
#define ALIVE					1
#define BLUE					4

#define CELL_BLACK 		"\e[7;30;40m"
#define CELL_RED			"\e[7;31;41m"
#define CELL_GREEN		"\e[7;32;42m"
#define CELL_YELLOW		"\e[7;33;43m"
#define CELL_BLUE			"\e[7;34;44m"
#define CELL_MAGENTA	"\e[7;35;45m"
#define CELL_CYAN			"\e[7;36;46m"
#define CELL_WHITE 		"\e[7;37;47m"

#define SCREEN_CLEAR()   debug_printf("\e[2J")
#define SCREEN_HOME() 	 debug_printf("\e[H")

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
int grid[15][15];
int prevGrid[15][15];
char *cell_colour_palatte[] = {CELL_BLACK, CELL_RED, CELL_GREEN, CELL_YELLOW, CELL_BLUE, CELL_MAGENTA, CELL_CYAN, CELL_WHITE};
/* Private function prototypes -----------------------------------------------*/
extern void s4464952_CAG_Simulator_init(void);
extern void s4464952_CAG_Simulator_task(void);
void s4464952_os_lta1000g_init(void);
void s4464952_hal_lta1000g_write(unsigned short value);
void set_subgrid(int subgrid, int x, int y);
void grid_update(void);
void set_grid(int x, int y);
int check_subgrid(void);

/**
  * @brief  Initialise grid
  * @param  None
  * @retval None
  */
void init_grid(void){
	
	SCREEN_CLEAR();
	SCREEN_HOME();

	for (int col = 0 ; col < 15; col++){
		for (int row = 0 ; row < 15; row++){
			grid[row][col] = DEAD ;
			debug_printf("%s  ", cell_colour_palatte[grid[row][col]]);
		}	
		debug_printf("\n\r");
	}
}

/**
  * @brief  Game simulation
  * @param  None
  * @retval None
  */
void game_iteration(void){

	for (int j = 0 ; j < 15; j++){
		for (int i = 0 ; i < 15; i++){
			prevGrid[i][j] = grid[i][j];
		}
	}
	
	for (int i = 0 ; i < 15; i++){
		for (int j = 0 ; j < 15; j++){
			
			int neighbourCount = 0 ;
			int highestNeighbourState = 0 ;

				for (int ii = i-1 ; ii <= i+1 ; ii++){
					for (int jj = j-1 ; jj <= j+1 ; jj++){
						if(((ii>=0)&&(ii<15))&&((jj>=0)&&(jj<15))){
							if(!((ii==i)&&(jj==j))){
								if(prevGrid[ii][jj]!=DEAD){
										neighbourCount++;
										highestNeighbourState = prevGrid[ii][jj];
								}
							}
						}
					}
				}
			
			if (prevGrid[i][j] > highestNeighbourState){
				
				highestNeighbourState = prevGrid[i][j];
				
			}
			if (prevGrid[i][j] == DEAD){
				if (neighbourCount == 3){
					grid[i][j] = highestNeighbourState;
				}
			}
			if (prevGrid[i][j] != DEAD){
				if (neighbourCount < 2 || neighbourCount > 3){
					grid[i][j] = DEAD;
				}
				if (neighbourCount == 2 || neighbourCount == 3){
					grid[i][j] = highestNeighbourState;
				}
			}
	}
	}
	grid_update();
}

/**
  * @brief  CAG Simulator Task.
  * @param  None
  * @retval None
  */
extern void s4464952_CAG_Simulator_task(void){
	
	int check = 0;
	int delay = 2000 ;
	/* Create Event Group */
	simulator_EventGroup = xEventGroupCreate();
  EventBits_t simulatorBits;                      

	s4464952_os_lta1000g_init();
	init_grid();	
	
	for (;;) {			
		if (check == 1){
			game_iteration();
			s4464952_hal_lta1000g_write(0x200);

		} else if (check == 0) { 
			//grid_update();
		}

 			
			 /* Wait a maximum of 100ms for either bit 0 or bit 1 to be set within the event group.  Clear the bits before exiting. */
    	simulatorBits = xEventGroupWaitBits(simulator_EventGroup, CTRL_EVENT, pdTRUE, pdFALSE, 10);

		//check if event flag is set
		if ((simulatorBits & UPDATE_500MS) != 0) {

			portENTER_CRITICAL(); 
			//debug_printf("Update time every 500ms event\n\r");
			delay = 500 ;
			portEXIT_CRITICAL();
			simulatorBits = xEventGroupClearBits(simulator_EventGroup, UPDATE_500MS);		//Clear event flag.
		
		}
    //check if event flag is set
		if ((simulatorBits & UPDATE_1S) != 0) {

			portENTER_CRITICAL(); 
			//debug_printf("Update time every 1s event\n\r");
			delay = 1000 ;
			portEXIT_CRITICAL();
			simulatorBits = xEventGroupClearBits(simulator_EventGroup, UPDATE_1S);		//Clear event flag.
		
		}
		    //check if event flag is set
		if ((simulatorBits & UPDATE_2S) != 0) {

			portENTER_CRITICAL(); 
			//debug_printf("Update time every 2s event\n\r");
			delay = 2000 ;
			portEXIT_CRITICAL();
			simulatorBits = xEventGroupClearBits(simulator_EventGroup, UPDATE_2S);		//Clear event flag.
		
		}
    //check if event flag is set
		if ((simulatorBits & UPDATE_5S) != 0) {

			portENTER_CRITICAL(); 
			//debug_printf("Update time every 5s event\n\r");
			delay = 5000 ;
			portEXIT_CRITICAL();
			simulatorBits = xEventGroupClearBits(simulator_EventGroup, UPDATE_5S);		//Clear event flag.
		
		}
    //check if event flag is set
		if ((simulatorBits & UPDATE_10S) != 0) {

			portENTER_CRITICAL(); 
			//debug_printf("Update time every 10s event\n\r");
			delay = 10000 ;
			portEXIT_CRITICAL();
			simulatorBits = xEventGroupClearBits(simulator_EventGroup, UPDATE_10S);		//Clear event flag.
		
		}    
    //check if event flag is set
    if ((simulatorBits & CLEAR_GRID) != 0) {    

			portENTER_CRITICAL(); 
			//debug_printf("Update clear grid event\n\r");
			init_grid();
			portEXIT_CRITICAL();
			simulatorBits = xEventGroupClearBits(simulator_EventGroup, CLEAR_GRID);		//Clear event flag.
		}
		    //check if event flag is set
    if ((simulatorBits & START) != 0) {    
			
			check = 1;
			portENTER_CRITICAL(); 
			//debug_printf("Update start simulation event\n\r");
			//debug_printf("Start simulation check : %d\n\r",check);
			portEXIT_CRITICAL();
			simulatorBits = xEventGroupClearBits(simulator_EventGroup, START);		//Clear event flag.
		}
		    //check if event flag is set
    if ((simulatorBits & STOP) != 0) {    

			check = 0 ;
			portENTER_CRITICAL(); 
			//debug_printf("Update stop simulation event\n\r");
			//debug_printf("Start simulation check : %d\n\r",check);
			portEXIT_CRITICAL();
			simulatorBits = xEventGroupClearBits(simulator_EventGroup, STOP);		//Clear event flag.
		}

		if (s4464952QueueKeypad != NULL) {

			// Check for item received - block atmost for 10 ticks 
			if (xQueueReceive( s4464952QueueKeypad, &gridMessage, 10 )) {

			portENTER_CRITICAL(); 
			int	x = gridMessage.cell_x;
			int	y = gridMessage.cell_y;
			int subgrid =  check_subgrid();

			//debug_printf("X check : %d\n\r",x);
			//debug_printf("Y simulation check : %d\n\r",y);
			//debug_printf("Subgrid simulation check : %d\n\r",subgrid);
			set_subgrid(subgrid,x,y);
			grid_update();
			portEXIT_CRITICAL();
    	}
		} 
		vTaskDelay(delay);
	}
}

/**
  * @brief  Set subgrid
  * @param  None
  * @retval None
  */
void set_subgrid(int grid, int x, int y){

	int set_x = 0 ;
	int set_y = 0 ;
	int subgrid = grid;

	if (subgrid == 1){
			if (x == 0){
				if (y == 0){
					 set_x = 0 ;
					 set_y = 0 ;
				}
				if (y == 1){
					 set_x = 0;		
					 set_y = 1 ;
				}
				if (y == 2){
					 set_x = 0 ;
					 set_y = 2 ;	
				}
			}
			if (x == 1){
				if (y == 0){
					 set_x = 1 ;
					 set_y = 0 ;
				}
				if (y == 1){
					 set_x = 1;		
					 set_y = 1 ;
				}
				if (y == 2){
					 set_x = 1 ;
					 set_y = 2 ;	
				}
			}
			if (x == 2){
				if (y == 0){
					 set_x = 2 ;
					 set_y = 0 ;
				}
				if (y == 1){
					 set_x = 2;		
					 set_y = 1 ;
				}
				if (y == 2){
					 set_x = 2 ;
					 set_y = 2 ;	
				}
			}
		}
		if (subgrid == 2){
			if (x == 0){
				if (y == 0){
					 set_x = 3 ;
					 set_y = 0 ;
				}
				if (y == 1){
					 set_x = 3 ;		
					 set_y = 1 ;
				}
				if (y == 2){
					 set_x = 3 ;
					 set_y = 2 ;	
				}
			}
			if (x == 1){
				if (y == 0){
					 set_x = 4 ;
					 set_y = 0 ;
				}
				if (y == 1){
					 set_x = 4;		
					 set_y = 1;
				}
				if (y == 2){
					 set_x = 4;
					 set_y = 2;	
				}
			}
			if (x == 2){
				if (y == 0){
					 set_x = 5 ;
					 set_y = 0 ;
				}
				if (y == 1){
					 set_x = 5;		
					 set_y = 1;
				}
				if (y == 2){
					 set_x = 5;
					 set_y = 2;	
				}
			}
		}
		if (subgrid == 3){
			if (x == 0){
				if (y == 0){
					 set_x = 6 ;
					 set_y = 0 ;
				}
				if (y == 1){
					 set_x = 6;		
					 set_y = 1 ;
				}
				if (y == 2){
					 set_x = 6 ;
					 set_y = 2 ;	
				}
			}
			if (x == 1){
				if (y == 0){
					 set_x = 7 ;
					 set_y = 0 ;
				}
				if (y == 1){
					 set_x = 7;		
					 set_y = 1 ;
				}
				if (y == 2){
					 set_x = 7 ;
					 set_y = 2 ;	
				}
			}
			if (x == 2){
				if (y == 0){
					 set_x = 8 ;
					 set_y = 0 ;
				}
				if (y == 1){
					 set_x = 8;		
					 set_y = 1 ;
				}
				if (y == 2){
					 set_x = 8 ;
					 set_y = 2 ;	
				}
			}
		}
		if (subgrid == 4){
			if (x == 0){
				if (y == 0){
					 set_x = 9 ;
					 set_y = 0 ;
				}
				if (y == 1){
					 set_x = 9;		
					 set_y = 1 ;
				}
				if (y == 2){
					 set_x = 9 ;
					 set_y = 2 ;	
				}
			}
			if (x == 1){
				if (y == 0){
					 set_x = 10 ;
					 set_y = 0 ;
				}
				if (y == 1){
					 set_x = 10;		
					 set_y = 1 ;
				}
				if (y == 2){
					 set_x = 10 ;
					 set_y = 2 ;	
				}
			}
			if (x == 2){
				if (y == 0){
					 set_x = 11 ;
					 set_y = 0 ;
				}
				if (y == 1){
					 set_x = 11;		
					 set_y = 1 ;
				}
				if (y == 2){
					 set_x = 11;
					 set_y = 2 ;	
				}
			}
		}
		if (subgrid == 5){
			if (x == 0){
				if (y == 0){
					 set_x = 12;
					 set_y = 0 ;
				}
				if (y == 1){
					 set_x = 12;		
					 set_y = 1 ;
				}
				if (y == 2){
					 set_x = 12;
					 set_y = 2 ;	
				}
			}
			if (x == 1){
				if (y == 0){
					 set_x = 13;
					 set_y = 0 ;
				}
				if (y == 1){
					 set_x = 13;		
					 set_y = 1 ;
				}
				if (y == 2){
					 set_x = 13;
					 set_y = 2 ;	
				}
			}
			if (x == 2){
				if (y == 0){
					 set_x = 14;
					 set_y = 0 ;
				}
				if (y == 1){
					 set_x = 14;		
					 set_y = 1 ;
				}
				if (y == 2){
					 set_x = 14;
					 set_y = 2 ;	
				}
			}
		}
			if (subgrid == 6){
			if (x == 0){
				if (y == 0){
					 set_x = 0 ;
					 set_y = 3 ;
				}
				if (y == 1){
					 set_x = 0;		
					 set_y = 4 ;
				}
				if (y == 2){
					 set_x = 0 ;
					 set_y = 5 ;	
				}
			}
			if (x == 1){
				if (y == 0){
					 set_x = 1 ;
					 set_y = 3 ;
				}
				if (y == 1){
					 set_x = 1;		
					 set_y = 4 ;
				}
				if (y == 2){
					 set_x = 1 ;
					 set_y = 5 ;	
				}
			}
			if (x == 2){
				if (y == 0){
					 set_x = 2 ;
					 set_y = 3 ;
				}
				if (y == 1){
					 set_x = 2;		
					 set_y = 4 ;
				}
				if (y == 2){
					 set_x = 2 ;
					 set_y = 5 ;	
				}
			}
		}
		if (subgrid == 7){
			if (x == 0){
				if (y == 0){
					 set_x = 3 ;
					 set_y = 3 ;
				}
				if (y == 1){
					 set_x = 3 ;		
					 set_y = 4 ;
				}
				if (y == 2){
					 set_x = 3 ;
					 set_y = 5 ;	
				}
			}
			if (x == 1){
				if (y == 0){
					 set_x = 4 ;
					 set_y = 3 ;
				}
				if (y == 1){
					 set_x = 4;		
					 set_y = 4;
				}
				if (y == 2){
					 set_x = 4;
					 set_y = 5;	
				}
			}
			if (x == 2){
				if (y == 0){
					 set_x = 5 ;
					 set_y = 3 ;
				}
				if (y == 1){
					 set_x = 5;		
					 set_y = 4;
				}
				if (y == 2){
					 set_x = 5;
					 set_y = 5;	
				}
			}
		}
		if (subgrid == 8){
			if (x == 0){
				if (y == 0){
					 set_x = 6 ;
					 set_y = 3 ;
				}
				if (y == 1){
					 set_x = 6;		
					 set_y = 4 ;
				}
				if (y == 2){
					 set_x = 6 ;
					 set_y = 5 ;	
				}
			}
			if (x == 1){
				if (y == 0){
					 set_x = 7 ;
					 set_y = 3 ;
				}
				if (y == 1){
					 set_x = 7;		
					 set_y = 4 ;
				}
				if (y == 2){
					 set_x = 7 ;
					 set_y = 5 ;	
				}
			}
			if (x == 2){
				if (y == 0){
					 set_x = 8 ;
					 set_y = 3 ;
				}
				if (y == 1){
					 set_x = 8;		
					 set_y = 4 ;
				}
				if (y == 2){
					 set_x = 8 ;
					 set_y = 5 ;	
				}
			}
		}
		if (subgrid == 9){
			if (x == 0){
				if (y == 0){
					 set_x = 9 ;
					 set_y = 3 ;
				}
				if (y == 1){
					 set_x = 9;		
					 set_y = 4 ;
				}
				if (y == 2){
					 set_x = 9 ;
					 set_y = 5 ;	
				}
			}
			if (x == 1){
				if (y == 0){
					 set_x = 10 ;
					 set_y = 3 ;
				}
				if (y == 1){
					 set_x = 10;		
					 set_y = 4 ;
				}
				if (y == 2){
					 set_x = 10 ;
					 set_y = 5 ;	
				}
			}
			if (x == 2){
				if (y == 0){
					 set_x = 11 ;
					 set_y = 3 ;
				}
				if (y == 1){
					 set_x = 11;		
					 set_y = 4 ;
				}
				if (y == 2){
					 set_x = 11;
					 set_y = 5 ;	
				}
			}
		}
		if (subgrid == 10){
			if (x == 0){
				if (y == 0){
					 set_x = 12;
					 set_y = 3 ;
				}
				if (y == 1){
					 set_x = 12;		
					 set_y = 4 ;
				}
				if (y == 2){
					 set_x = 12;
					 set_y = 5 ;	
				}
			}
			if (x == 1){
				if (y == 0){
					 set_x = 13;
					 set_y = 3 ;
				}
				if (y == 1){
					 set_x = 13;		
					 set_y = 4 ;
				}
				if (y == 2){
					 set_x = 13;
					 set_y = 5 ;	
				}
			}
			if (x == 2){
				if (y == 0){
					 set_x = 14;
					 set_y = 3 ;
				}
				if (y == 1){
					 set_x = 14;		
					 set_y = 4 ;
				}
				if (y == 2){
					 set_x = 14;
					 set_y = 5 ;	
				}
			}
		}
			if (subgrid == 11){
			if (x == 0){
				if (y == 0){
					 set_x = 0 ;
					 set_y = 6 ;
				}
				if (y == 1){
					 set_x = 0;		
					 set_y = 7 ;
				}
				if (y == 2){
					 set_x = 0 ;
					 set_y = 8 ;	
				}
			}
			if (x == 1){
				if (y == 0){
					 set_x = 1 ;
					 set_y = 6 ;
				}
				if (y == 1){
					 set_x = 1;		
					 set_y = 7 ;
				}
				if (y == 2){
					 set_x = 1 ;
					 set_y = 8 ;	
				}
			}
			if (x == 2){
				if (y == 0){
					 set_x = 2 ;
					 set_y = 6 ;
				}
				if (y == 1){
					 set_x = 2;		
					 set_y = 7 ;
				}
				if (y == 2){
					 set_x = 2 ;
					 set_y = 8 ;	
				}
			}
		}
		if (subgrid == 12){
			if (x == 0){
				if (y == 0){
					 set_x = 3 ;
					 set_y = 6 ;
				}
				if (y == 1){
					 set_x = 3 ;		
					 set_y = 7 ;
				}
				if (y == 2){
					 set_x = 3 ;
					 set_y = 8 ;	
				}
			}
			if (x == 1){
				if (y == 0){
					 set_x = 4 ;
					 set_y = 6 ;
				}
				if (y == 1){
					 set_x = 4;		
					 set_y = 7;
				}
				if (y == 2){
					 set_x = 4;
					 set_y = 8;	
				}
			}
			if (x == 2){
				if (y == 0){
					 set_x = 5 ;
					 set_y = 6 ;
				}
				if (y == 1){
					 set_x = 5;		
					 set_y = 7;
				}
				if (y == 2){
					 set_x = 5;
					 set_y = 8;	
				}
			}
		}
		if (subgrid == 13){
			if (x == 0){
				if (y == 0){
					 set_x = 6 ;
					 set_y = 6 ;
				}
				if (y == 1){
					 set_x = 6;		
					 set_y = 7 ;
				}
				if (y == 2){
					 set_x = 6 ;
					 set_y = 8 ;	
				}
			}
			if (x == 1){
				if (y == 0){
					 set_x = 7 ;
					 set_y = 6 ;
				}
				if (y == 1){
					 set_x = 7;		
					 set_y = 7 ;
				}
				if (y == 2){
					 set_x = 7 ;
					 set_y = 8 ;	
				}
			}
			if (x == 2){
				if (y == 0){
					 set_x = 8 ;
					 set_y = 6 ;
				}
				if (y == 1){
					 set_x = 8;		
					 set_y = 7 ;
				}
				if (y == 2){
					 set_x = 8 ;
					 set_y = 8 ;	
				}
			}
		}
		if (subgrid == 14){
			if (x == 0){
				if (y == 0){
					 set_x = 9 ;
					 set_y = 6 ;
				}
				if (y == 1){
					 set_x = 9;		
					 set_y = 7 ;
				}
				if (y == 2){
					 set_x = 9 ;
					 set_y = 8 ;	
				}
			}
			if (x == 1){
				if (y == 0){
					 set_x = 10 ;
					 set_y = 6 ;
				}
				if (y == 1){
					 set_x = 10;		
					 set_y = 7 ;
				}
				if (y == 2){
					 set_x = 10 ;
					 set_y = 8 ;	
				}
			}
			if (x == 2){
				if (y == 0){
					 set_x = 11 ;
					 set_y = 6 ;
				}
				if (y == 1){
					 set_x = 11;		
					 set_y = 7 ;
				}
				if (y == 2){
					 set_x = 11;
					 set_y = 8 ;	
				}
			}
		}
		if (subgrid == 15){
			if (x == 0){
				if (y == 0){
					 set_x = 12;
					 set_y = 6 ;
				}
				if (y == 1){
					 set_x = 12;		
					 set_y = 7 ;
				}
				if (y == 2){
					 set_x = 12;
					 set_y = 8 ;	
				}
			}
			if (x == 1){
				if (y == 0){
					 set_x = 13;
					 set_y = 6 ;
				}
				if (y == 1){
					 set_x = 13;		
					 set_y = 7 ;
				}
				if (y == 2){
					 set_x = 13;
					 set_y = 8 ;	
				}
			}
			if (x == 2){
				if (y == 0){
					 set_x = 14;
					 set_y = 6 ;
				}
				if (y == 1){
					 set_x = 14;		
					 set_y = 7 ;
				}
				if (y == 2){
					 set_x = 14;
					 set_y = 8 ;	
				}
			}
		}
			if (subgrid == 16){
			if (x == 0){
				if (y == 0){
					 set_x = 0 ;
					 set_y = 9 ;
				}
				if (y == 1){
					 set_x = 0;		
					 set_y = 10 ;
				}
				if (y == 2){
					 set_x = 0 ;
					 set_y = 11 ;	
				}
			}
			if (x == 1){
				if (y == 0){
					 set_x = 1 ;
					 set_y = 9 ;
				}
				if (y == 1){
					 set_x = 1;		
					 set_y = 10 ;
				}
				if (y == 2){
					 set_x = 1 ;
					 set_y = 11 ;	
				}
			}
			if (x == 2){
				if (y == 0){
					 set_x = 2 ;
					 set_y = 9 ;
				}
				if (y == 1){
					 set_x = 2;		
					 set_y = 10 ;
				}
				if (y == 2){
					 set_x = 2 ;
					 set_y = 11 ;	
				}
			}
		}
		if (subgrid == 17){
			if (x == 0){
				if (y == 0){
					 set_x = 3 ;
					 set_y = 9 ;
				}
				if (y == 1){
					 set_x = 3 ;		
					 set_y = 10 ;
				}
				if (y == 2){
					 set_x = 3 ;
					 set_y = 11 ;	
				}
			}
			if (x == 1){
				if (y == 0){
					 set_x = 4 ;
					 set_y = 9 ;
				}
				if (y == 1){
					 set_x = 4;		
					 set_y = 10;
				}
				if (y == 2){
					 set_x = 4;
					 set_y = 11;	
				}
			}
			if (x == 2){
				if (y == 0){
					 set_x = 5 ;
					 set_y = 9 ;
				}
				if (y == 1){
					 set_x = 5;		
					 set_y = 10;
				}
				if (y == 2){
					 set_x = 5;
					 set_y = 11;	
				}
			}
		}
		if (subgrid == 18){
			if (x == 0){
				if (y == 0){
					 set_x = 6 ;
					 set_y = 9 ;
				}
				if (y == 1){
					 set_x = 6;		
					 set_y = 10 ;
				}
				if (y == 2){
					 set_x = 6 ;
					 set_y = 11 ;	
				}
			}
			if (x == 1){
				if (y == 0){
					 set_x = 7 ;
					 set_y = 9 ;
				}
				if (y == 1){
					 set_x = 7;		
					 set_y = 10 ;
				}
				if (y == 2){
					 set_x = 7 ;
					 set_y = 11 ;	
				}
			}
			if (x == 2){
				if (y == 0){
					 set_x = 8 ;
					 set_y = 9 ;
				}
				if (y == 1){
					 set_x = 8;		
					 set_y = 10 ;
				}
				if (y == 2){
					 set_x = 8 ;
					 set_y = 11 ;	
				}
			}
		}
		if (subgrid == 19){
			if (x == 0){
				if (y == 0){
					 set_x = 9 ;
					 set_y = 9 ;
				}
				if (y == 1){
					 set_x = 9;		
					 set_y = 10 ;
				}
				if (y == 2){
					 set_x = 9 ;
					 set_y = 11 ;	
				}
			}
			if (x == 1){
				if (y == 0){
					 set_x = 10 ;
					 set_y = 9 ;
				}
				if (y == 1){
					 set_x = 10;		
					 set_y = 10 ;
				}
				if (y == 2){
					 set_x = 10 ;
					 set_y = 11 ;	
				}
			}
			if (x == 2){
				if (y == 0){
					 set_x = 11 ;
					 set_y = 9 ;
				}
				if (y == 1){
					 set_x = 11;		
					 set_y = 10 ;
				}
				if (y == 2){
					 set_x = 11;
					 set_y = 11 ;	
				}
			}
		}
		if (subgrid == 20){
			if (x == 0){
				if (y == 0){
					 set_x = 12;
					 set_y = 9 ;
				}
				if (y == 1){
					 set_x = 12;		
					 set_y = 10 ;
				}
				if (y == 2){
					 set_x = 12;
					 set_y = 11 ;	
				}
			}
			if (x == 1){
				if (y == 0){
					 set_x = 13;
					 set_y = 9 ;
				}
				if (y == 1){
					 set_x = 13;		
					 set_y = 10 ;
				}
				if (y == 2){
					 set_x = 13;
					 set_y = 11 ;	
				}
			}
			if (x == 2){
				if (y == 0){
					 set_x = 14;
					 set_y = 9 ;
				}
				if (y == 1){
					 set_x = 14;		
					 set_y = 10 ;
				}
				if (y == 2){
					 set_x = 14;
					 set_y = 11 ;	
				}
			}
		}
			if (subgrid == 21){
			if (x == 0){
				if (y == 0){
					 set_x = 0 ;
					 set_y = 12 ;
				}
				if (y == 1){
					 set_x = 0;		
					 set_y = 13 ;
				}
				if (y == 2){
					 set_x = 0 ;
					 set_y = 14 ;	
				}
			}
			if (x == 1){
				if (y == 0){
					 set_x = 1 ;
					 set_y = 12 ;
				}
				if (y == 1){
					 set_x = 1;		
					 set_y = 13 ;
				}
				if (y == 2){
					 set_x = 1 ;
					 set_y = 14 ;	
				}
			}
			if (x == 2){
				if (y == 0){
					 set_x = 2 ;
					 set_y = 12 ;
				}
				if (y == 1){
					 set_x = 2;		
					 set_y = 13 ;
				}
				if (y == 2){
					 set_x = 2 ;
					 set_y = 14 ;	
				}
			}
		}
		if (subgrid == 22){
			if (x == 0){
				if (y == 0){
					 set_x = 3 ;
					 set_y = 12 ;
				}
				if (y == 1){
					 set_x = 3 ;		
					 set_y = 13 ;
				}
				if (y == 2){
					 set_x = 3 ;
					 set_y = 14 ;	
				}
			}
			if (x == 1){
				if (y == 0){
					 set_x = 4 ;
					 set_y = 12 ;
				}
				if (y == 1){
					 set_x = 4;		
					 set_y = 13;
				}
				if (y == 2){
					 set_x = 4;
					 set_y = 14;	
				}
			}
			if (x == 2){
				if (y == 0){
					 set_x = 5 ;
					 set_y = 12 ;
				}
				if (y == 1){
					 set_x = 5;		
					 set_y = 13;
				}
				if (y == 2){
					 set_x = 5;
					 set_y = 14;	
				}
			}
		}
		if (subgrid == 23){
			if (x == 0){
				if (y == 0){
					 set_x = 6 ;
					 set_y = 12 ;
				}
				if (y == 1){
					 set_x = 6;		
					 set_y = 13 ;
				}
				if (y == 2){
					 set_x = 6 ;
					 set_y = 14 ;	
				}
			}
			if (x == 1){
				if (y == 0){
					 set_x = 7 ;
					 set_y = 12 ;
				}
				if (y == 1){
					 set_x = 7;		
					 set_y = 13 ;
				}
				if (y == 2){
					 set_x = 7 ;
					 set_y = 14 ;	
				}
			}
			if (x == 2){
				if (y == 0){
					 set_x = 8 ;
					 set_y = 12 ;
				}
				if (y == 1){
					 set_x = 8;		
					 set_y = 13 ;
				}
				if (y == 2){
					 set_x = 8 ;
					 set_y = 14 ;	
				}
			}
		}
		if (subgrid == 24){
			if (x == 0){
				if (y == 0){
					 set_x = 9 ;
					 set_y = 12 ;
				}
				if (y == 1){
					 set_x = 9;		
					 set_y = 13 ;
				}
				if (y == 2){
					 set_x = 9 ;
					 set_y = 14 ;	
				}
			}
			if (x == 1){
				if (y == 0){
					 set_x = 10 ;
					 set_y = 12 ;
				}
				if (y == 1){
					 set_x = 10;		
					 set_y = 13 ;
				}
				if (y == 2){
					 set_x = 10 ;
					 set_y = 14 ;	
				}
			}
			if (x == 2){
				if (y == 0){
					 set_x = 11 ;
					 set_y = 12 ;
				}
				if (y == 1){
					 set_x = 11;		
					 set_y = 13 ;
				}
				if (y == 2){
					 set_x = 11;
					 set_y = 14 ;	
				}
			}
		}
		if (subgrid == 25){
			if (x == 0){
				if (y == 0){
					 set_x = 12;
					 set_y = 12 ;
				}
				if (y == 1){
					 set_x = 12;		
					 set_y = 13 ;
				}
				if (y == 2){
					 set_x = 12;
					 set_y = 14 ;	
				}
			}
			if (x == 1){
				if (y == 0){
					 set_x = 13;
					 set_y = 12 ;
				}
				if (y == 1){
					 set_x = 13;		
					 set_y = 13 ;
				}
				if (y == 2){
					 set_x = 13;
					 set_y = 14 ;	
				}
			}
			if (x == 2){
				if (y == 0){
					 set_x = 14;
					 set_y = 12 ;
				}
				if (y == 1){
					 set_x = 14;		
					 set_y = 13 ;
				}
				if (y == 2){
					 set_x = 14;
					 set_y = 14 ;	
				}
			}
		}
		set_grid(set_x, set_y);
}


/**
  * @brief  Initialise os CAG Simulator
  * @param  None
  * @retval None
  */
extern void s4464952_CAG_Simulator_init(void){

	xTaskCreate( (void *) &s4464952_CAG_Simulator_task, (const signed char *) "CAG_SIMULATOR", S4464952_CAG_SIMULATOR_STACK_SIZE, NULL, S4464952_CAG_SIMULATOR_PRIORITY, &xs4464952_cag_simulator_handle);
	
}

/**
  * @brief  Deinitialise os CAG Simulator
  * @param  None
  * @retval None
  */
extern void s4464952_CAG_Simulator_deinit(void){

	vTaskDelete(xs4464952_cag_simulator_handle);
	
}
