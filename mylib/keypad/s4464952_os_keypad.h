/** 
 *************************************************************
 * @file /home/csse3010/csse3010/mylib/keypad/s4464952_os_keypad.h
 * @author Aina Jauhara - s4464952
 * @date 11/5/2020
 * @brief header file contains keypad os functions used by main.c
 ***************************************************************
 * EXTERNAL FUNCTIONS 
 ***************************************************************
 * extern void s4464952_os_keypad_init(void);   
 * extern void s4464952_os_keypad_task(void);                                        
 *************************************************************** 
 */

 #ifndef S4464952_OS_KEYPAD
 #define S4464952_OS_KEYPAD

#include "board.h"
#include "processor_hal.h"
#include "debug_printf.h"
#include "s4464952_hal_keypad.h"
#include <string.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "event_groups.h"

#define S4464952_OS_KEYPAD_PRIORITY				( tskIDLE_PRIORITY + 3 )
#define S4464952_OS_KEYPAD_STACK_SIZE			( configMINIMAL_STACK_SIZE * 4 )

QueueHandle_t s4464952QueueKeypad;

extern void s4464952_os_keypad_init(void);
extern void s4464952_os_keypad_task(void);

#endif
 
