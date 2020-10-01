/** 
 ***************************************************************
 * @file /home/csse3010/csse3010/stage2/s4464952_hal_mylib_configure.h
 * @author Aina Jauhara - s4464952
 * @date 23/2/2020
 * @brief configuration header file 
 ***************************************************************
 * EXTERNAL FUNCTIONS 
 ***************************************************************
 *************************************************************** 
 */


#ifdef S4464952_HAL_ATIMER_CONFIG_H


GPIO_InitTypeDef GPIO_InitStructure;
TIM_HandleTypeDef TIM_Init;


#define S4464952_HAL_ATIMER_PIN         BRD_D10_PIN                                                           // default values set to D10 pin 
#define S4464952_HAL_ATIMER_PINPORT     BRD_D10_GPIO_PORT                                                     // default value set to D10 port
#define S4464952_HAL_ATIMER_PINCLK      __BRD_D10_GPIO_CLK()                                                  // default set to D10 clock
#define S4464952_HAL_ATIMER_PERIOD      2                                                                     // default set to 2ms
#define S4464952_HAL_ATIMER_CLKSPEED    25000                                                                 // default set to 25000Hz


#define S4464952_HAL_PWM_CLOCKFREQ          50000                                                            // default set to 100
#define S4464952_HAL_PWM_PULSEPERIOD        (S4464952_HAL_PWM_CLOCKFREQ/100)                                                            // default set to 100
#define S4464952_HAL_PWM_PERIOD             2*S4464952_HAL_PWM_PULSEPERIOD/10                                                            // default set to 100
#define S4464952_HAL_PWM_CHANNEL            TIM_CHANNEL_3                                                              // default set to 0
#define S4464952_HAL_PWM_TIMER              TIM1                                                             // default set to 0
#define S4464952_HAL_PWM_TIMER_CLK()        0                                                              // default set to 0
#define S4464952_HAL_PWM_TIMER_HANDLER      TIM_Init                                                              // default set to 0
#define S4464952_HAL_PWM_PIN                BRD_D3_PIN                                                     // default values set to D10 pin 
#define S4464952_HAL_PWM_PINGPIOPORT        BRD_D3_GPIO_PORT                                               // default value set to D10 port
#define S4464952_HAL_PWM_PINGPIOAF          GPIO_AF1_TIM1                                                              // default set to 0
#define S4464952_HAL_PWM_PINCLK             __TIM1_CLK_ENABLE()                                                              // default set to 0
#define S4464952_HAL_PWM_PINCLKSPEED        0                                                              // default set to 0


#endif

