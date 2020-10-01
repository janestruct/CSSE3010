/** 
 *************************************************************
 * @file /home/csse3010/csse3010/mylib/lta1000g/s4464952_os_lta1000g.h
 * @author Aina Jauhara - s4464952
 * @date 26/4/2020
 * @brief header file contains joystick os functions used by main.c
 ***************************************************************
 * EXTERNAL FUNCTIONS 
 ***************************************************************
 * extern void TaskTimerDisplay(void);                      - display task function                                           
 *************************************************************** 
 */

 #ifndef S4464952_OS_LTA1000G
 #define S4464952_OS_LTA1000G

#include "board.h"
#include "processor_hal.h"
#include "debug_printf.h"
#include "s4464952_hal_lta1000g.h"
#include <string.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#define TaskTimerDisplay_PRIORITY				( tskIDLE_PRIORITY + 3 )
#define TaskTimerDisplay_STACK_SIZE			( configMINIMAL_STACK_SIZE * 2 )

QueueHandle_t s4464952QueueTimerDisplay;	

extern void s4464952_os_lta1000g_init(void);
extern void TaskTimerDisplay(void);

#endif
 
