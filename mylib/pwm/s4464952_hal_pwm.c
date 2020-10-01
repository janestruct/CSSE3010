/**
 **************************************************************
 * @file /home/csse3010/csse3010/mylib/pwm/s4495585_hal_pwm.c
 * @author Aina Jauhara - s4464952
 * @date 14/03/2020
 * @brief mylib pwm file
 ***************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "board.h"
#include "processor_hal.h"
#include "debug_printf.h"
#include "s4464952_hal_pwm.h"

#ifdef S4464952_HAL_MYLIB_CONFIGURE_H
#include "s4464952_hal_mylib_configure.h"
#endif

/* Private typedef -----------------------------------------------------------*/
TIM_HandleTypeDef TIM_Init;
/* Private define ------------------------------------------------------------*/
#define PWM_TIMER_HANDLER	TIM_Init
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void s4464952_hal_pwm_init(void);                                                                           // initialise and start pwm (s)
void pwm_dutycycle_get(int DC);                                                                             // get duty cycle
void pwm_dutycycle_set(int DC, int VALUE);                                                                  // set duty cycle to value


/**
 * @brief  initialise and start pwm (s)
 * @param  none
 * @retval None
 */
void s4464952_hal_pwm_init(void){


	GPIO_InitTypeDef GPIO_InitStructure;
	TIM_OC_InitTypeDef PWMConfig;

	uint16_t PrescalerValue = 0;

	__TIM1_CLK_ENABLE();
	__BRD_D3_GPIO_CLK();

	GPIO_InitStructure.Pin = S4464952_HAL_PWM_PIN;
	GPIO_InitStructure.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	GPIO_InitStructure.Speed = GPIO_SPEED_FAST;
	GPIO_InitStructure.Alternate = S4464952_HAL_PWM_PINGPIOAF ;
	HAL_GPIO_Init(BRD_D3_GPIO_PORT, &GPIO_InitStructure);

	PrescalerValue = (uint16_t) ((SystemCoreClock /2) / S4464952_HAL_PWM_CLOCKFREQ) - 1;

	TIM_Init.Instance = S4464952_HAL_PWM_TIMER;
	TIM_Init.Init.Period = S4464952_HAL_PWM_PERIOD;
	TIM_Init.Init.Prescaler = PrescalerValue;
	TIM_Init.Init.ClockDivision = 0;
	TIM_Init.Init.RepetitionCounter = 0;
	TIM_Init.Init.CounterMode = TIM_COUNTERMODE_UP;

	PWMConfig.OCMode = TIM_OCMODE_PWM1;
	PWMConfig.Pulse = S4464952_HAL_PWM_PULSEPERIOD;
	PWMConfig.OCPolarity = TIM_OCPOLARITY_HIGH;
	PWMConfig.OCNPolarity = TIM_OCNPOLARITY_HIGH;
	PWMConfig.OCFastMode = TIM_OCFAST_DISABLE;
	PWMConfig.OCIdleState = TIM_OCIDLESTATE_RESET;
	PWMConfig.OCNIdleState = TIM_OCNIDLESTATE_RESET;

	HAL_TIM_PWM_Init(&TIM_Init);
	HAL_TIM_PWM_ConfigChannel(&TIM_Init, &PWMConfig, S4464952_HAL_PWM_CHANNEL);

	HAL_TIM_PWM_Start(&TIM_Init, S4464952_HAL_PWM_CHANNEL);
	
}

/**
 * @brief  get duty cycle
 * @param  DC
 * @retval None
 */
void pwm_dutycycle_get(int DC){
	
    __HAL_TIM_GET_COMPARE(&PWM_TIMER_HANDLER, S4464952_HAL_PWM_CHANNEL);
    DC = S4464952_HAL_PWM_CHANNEL;
    pwm_dutycycle_set(S4464952_HAL_PWM_CHANNEL,DC) ;
}

/**
 * @brief  set duty cycle to value
 * @param  DC, VALUE
 * @retval None
 */
void pwm_dutycycle_set(int DC, int VALUE){
    
    __HAL_TIM_SET_COMPARE(&PWM_TIMER_HANDLER, S4464952_HAL_PWM_CHANNEL, VALUE) ;


}

