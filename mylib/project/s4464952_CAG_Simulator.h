/** 
 *************************************************************
 * @file /home/csse3010/csse3010/mylib/project/s4464952_CAG_Simulator.h
 * @author Aina Jauhara - s4464952
 * @date 11/5/2020
 * @brief header file contains CAG Simulator os functions used by main.c
 ***************************************************************
 * EXTERNAL FUNCTIONS 
 ***************************************************************
 * extern void s4464952_CAG_Simulator_init(void);
 * extern void s4464952_CAG_Simulator_task(void);                                        
 *************************************************************** 
 */

 #ifndef S4464952_CAG_SIMULATOR
 #define S4464952_CAG_SIMULATOR

#include "board.h"
#include "processor_hal.h"
#include "debug_printf.h"
#include "s4464952_CAG_keypad_grid.h"
#include <string.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"

QueueHandle_t s4464952QueueSimulator;

#define S4464952_CAG_SIMULATOR_PRIORITY				( tskIDLE_PRIORITY + 3 )
#define S4464952_CAG_SIMULATOR_STACK_SIZE			( configMINIMAL_STACK_SIZE * 4 )

extern void s4464952_CAG_Simulator_init(void);
extern void s4464952_CAG_Simulator_task(void);

#endif
 
