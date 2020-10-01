/** 
 *************************************************************
 * @file /home/csse3010/csse3010/mylib/atimer/s4464952_hal_atimer.h
 * @author Aina Jauhara - s4464952
 * @date 14/3/2020
 * @brief header file contains atimer functions used by s4464952_hal_atimer.c
 ***************************************************************
 * EXTERNAL FUNCTIONS 
 ***************************************************************
 * void s4464952_hal_atimer_init(void)                                                                           - initialise atimer
 * void s4464952_hal_atimer_timer_getms(void)                                                                    - return atimer counter value (ms)
 * void s4464952_hal_atimer_timer_reset(void)                                                                    - reset atimer counter value to zero
 * void s4464952_hal_atimer_timer_pause(void)                                                                    - pause atimer
 * void s4464952_hal_atimer_timer_resume(void)                                                                   - resume atimer 
 * void s4464952_hal_atimer_clkspeed_set(int frequency)                                                          - set atimer clock speed (hz)
 * void s4464952_hal_atimer_period_set(int period)                                                               - set atimer period (ms)
 * void s4464952_hal_atimer_init_pin(void)                                                                       - initialise atimer GPIO pin
 * #define S4464952_HAL_ATIMER_PIN         BRD_D0_PIN                                                            - default values set to D0 pin 
 * #define S4464952_HAL_ATIMER_PINPORT     BRD_D0_GPIO_PORT                                                      - default value set to D0 port
 * #define S4464952_HAL_ATIMER_PINCLK      __BRD_D0_GPIO_CLK()                                                   - default set to D0 clock
 * #define S4464952_HAL_ATIMER_PERIOD      1                                                                     - default set to 1ms
 * #define S4464952_HAL_ATIMER_CLKSPEED    50000                                                                 - default set to 50000Hz
 *************************************************************** 
 */

#ifndef S4464952_HAL_ATIMER_H
#define S4464952_HAL_ATIMER_H

GPIO_InitTypeDef GPIO_InitStructure;

void s4464952_hal_atimer_init(void);                                                                      // initialise atimer
int s4464952_hal_atimer_timer_getms(void);                                                               // return atimer counter value (ms)
void s4464952_hal_atimer_timer_reset(void);                                                               // reset atimer counter value to zero
void s4464952_hal_atimer_timer_pause(void);                                                               // pause atimer
void s4464952_hal_atimer_timer_resume(void);                                                              // resume atimer 
void s4464952_hal_atimer_clkspeed_set(int frequency);                                                     // set atimer clock speed (hz)
void s4464952_hal_atimer_period_set(int period);                                                          // set atimer period (ms)
void s4464952_hal_atimer_init_pin(void);                                                                  // initialise atimer GPIO pin

#ifndef S4464952_HAL_MYLIB_CONFIGURE_H


#define S4464952_HAL_ATIMER_PIN         BRD_D0_PIN                                                       // default values set to D10 pin 
#define S4464952_HAL_ATIMER_PINPORT     BRD_D0_GPIO_PORT                                                 // default value set to D10 port
#define S4464952_HAL_ATIMER_PINCLK      __BRD_D0_GPIO_CLK()                                              // default set to D10 clock
#define S4464952_HAL_ATIMER_PERIOD      1                                                                // default set to 2ms
#define S4464952_HAL_ATIMER_CLKSPEED    50000                                                            // default set to 25000Hz

#endif
#endif

