/** 
 *************************************************************
 * @file /home/csse3010/csse3010/mylib/project/s4464952_CAG_Display.h
 * @author Aina Jauhara - s4464952
 * @date 11/5/2020
 * @brief header file contains CAG Display os functions used by main.c
 ***************************************************************
 * EXTERNAL FUNCTIONS 
 ***************************************************************
 * extern void s4464952_CAG_Display_init(void);
 * extern void s4464952_CAG_Display_task(void);                                         
 *************************************************************** 
 */

 #ifndef S4464952_CAG_DISPLAY
 #define S4464952_CAG_DISPLAY

#include "board.h"
#include "processor_hal.h"
#include "debug_printf.h"
#include "s4464952_os_joystick.h"
#include <string.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"

#define S4464952_CAG_DISPLAY_PRIORITY				( tskIDLE_PRIORITY + 3 )
#define S4464952_CAG_DISPLAY_STACK_SIZE			    ( configMINIMAL_STACK_SIZE * 4 )

extern void s4464952_CAG_Display_init(void);
extern void s4464952_CAG_Display_task(void);

#endif
 
