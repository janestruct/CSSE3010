/** 
 *************************************************************
 * @file /home/csse3010/csse3010/mylib/project/s4464952_CAG_keypad_mnemonic.h
 * @author Aina Jauhara - s4464952
 * @date 11/5/2020
 * @brief header file contains CAG keypad mnemonic os functions used by main.c
 ***************************************************************
 * EXTERNAL FUNCTIONS 
 ***************************************************************
 * extern void s4464952_CAG_keypad_mnemonic_init(void);
 * extern void s4464952_CAG_keypad_mnemonic_task(void);                                        
 *************************************************************** 
 */

 #ifndef S4464952_CAG_KEYPAD_MNEMONIC
 #define S4464952_CAG_KEYPAD_MNEMONIC

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

#define S4464952_CAG_KEYPAD_MNEMONIC_PRIORITY				( tskIDLE_PRIORITY + 3 )
#define S4464952_CAG_KEYPAD_MNEMONIC_STACK_SIZE			( configMINIMAL_STACK_SIZE * 2 )

extern void s4464952_CAG_keypad_mnemonic_init(void);
extern void s4464952_CAG_keypad_mnemonic_task(void);

#endif
 
