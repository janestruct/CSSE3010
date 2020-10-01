/** 
 *************************************************************
 * @file /home/csse3010/csse3010/mylib/pwm/s4464952_hal_pwm.h
 * @author Aina Jauhara - s4464952
 * @date 14/3/2020
 * @brief header file contains pwm functions used by s4464952_hal_pwm.c
 ***************************************************************
 * EXTERNAL FUNCTIONS 
 ***************************************************************
 * void s4464952_hal_pwm_init(void);                                                                          // initialise and start pwm (s)
 * void pwm_dutycycle_get(int DC);                                                                             // get duty cycle
 * void pwm_dutycycle_set(int DC, int VALUE);                                                                  // set duty cycle to value
 *************************************************************** 
 */

#ifndef S4464952_HAL_PWM_H
#define S4464952_HAL_PWM_H

GPIO_InitTypeDef GPIO_InitStructure;

void s4464952_hal_pwm_init(void);                                                                           // initialise and start pwm (s)
void pwm_dutycycle_get(int DC);                                                                             // get duty cycle
void pwm_dutycycle_set(int DC, int VALUE);                                                                  // set duty cycle to value

                                     
#define S4464952_HAL_PWM_DC_GET()                  pwm_dutycycle_get(0)                                     // return current duty cycle
#define S4464952_HAL_PWM_DC_SET(VALUE)             pwm_dutycycle_set(0,VALUE)                               // set duty cycle to duty

#ifndef S4464952_HAL_MYLIB_CONFIGURE_H

#define S4464952_HAL_PWM_CLOCKFREQ          100                                                            // default set to 100
#define S4464952_HAL_PWM_PULSEPERIOD        100                                                            // default set to 100
#define S4464952_HAL_PWM_PERIOD             100                                                            // default set to 100
#define S4464952_HAL_PWM_CHANNEL            0                                                              // default set to 0
#define S4464952_HAL_PWM_TIMER              0                                                              // default set to 0
#define S4464952_HAL_PWM_TIMER_CLK()        0                                                              // default set to 0
#define S4464952_HAL_PWM_TIMER_HANDLER      0                                                              // default set to 0
#define S4464952_HAL_PWM_PIN                BRD_D0_PIN                                                     // default values set to D10 pin 
#define S4464952_HAL_PWM_PINGPIOPORT        BRD_D0_GPIO_PORT                                               // default value set to D10 port
#define S4464952_HAL_PWM_PINGPIOAF          0                                                              // default set to 0
#define S4464952_HAL_PWM_PINCLK             0                                                              // default set to 0
#define S4464952_HAL_PWM_PINCLKSPEED        0                                                              // default set to 0


#endif
#endif


