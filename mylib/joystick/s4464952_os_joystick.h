/** 
 *************************************************************
 * @file /home/csse3010/csse3010/mylib/joystick/s4464952_os_joystick.h
 * @author Aina Jauhara - s4464952
 * @date 26/4/2020
 * @brief header file contains joystick os functions used by main.c
 ***************************************************************
 * EXTERNAL FUNCTIONS 
 ***************************************************************
 * extern void s4464952_os_joystick_init(void);                       - initialise gpio pin and ADC                                             
 *************************************************************** 
 */

 #ifndef S4464952_OS_JOYSTICK
 #define S4464952_OS_JOYSTICK

#include "board.h"
#include "processor_hal.h"
#include "debug_printf.h"
#include "s4464952_hal_joystick.h"
#include <string.h>

#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"

#define S4464952_OS_JOYSTICK_PRIORITY				( tskIDLE_PRIORITY + 3 )
#define S4464952_OS_JOYSTICK_STACK_SIZE			( configMINIMAL_STACK_SIZE * 4 )

SemaphoreHandle_t s4464952SemaphoreJoystickZ ;  /* Semaphore for signal z interrupt */
QueueHandle_t s4464952QueueJoystick;	

void s4464952_os_joystick_init(void);
void s4464952_os_joystick_task(void);
void joystick_operation(void);

#endif
 
