/** 
 ************************************************************
 * @file /home/csse3010/csse3010/mylib/atimer/s4495585_hal_atimer.c
 * @author Aina Jauhara - s4464952
 * @date 14/03/2020
 * @brief mylib atimer file
 ***************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "board.h"
#include "processor_hal.h"
#include "debug_printf.h"
#include "s4464952_hal_atimer.h"


#ifdef S4464952_HAL_MYLIB_CONFIGURE_H
#include "s4464952_hal_mylib_configure.h"
#endif


/* Private typedef -----------------------------------------------------------*/
TIM_HandleTypeDef TIM_Init;
/* Private define ------------------------------------------------------------*/
#define s4464952_hal_atimer_timer_read()    			atimerCounterVal
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
int atimerClkspeedVal = S4464952_HAL_ATIMER_CLKSPEED  ;
int atimerPeriodVal = S4464952_HAL_ATIMER_PERIOD ;
unsigned short atimerPrescalerVal = 0;
int atimerCounterVal = 0 ;
int atimer_ms = 0 ;
/* Private function prototypes -----------------------------------------------*/
void s4464952_hal_atimer_init(void);                                                                      // initialise atimer
int s4464952_hal_atimer_timer_getms(void);                                                               // return atimer counter value (ms)
void s4464952_hal_atimer_timer_reset(void);                                                               // reset atimer counter value to zero
void s4464952_hal_atimer_timer_pause(void);                                                               // pause atimer
void s4464952_hal_atimer_timer_resume(void);                                                              // resume atimer 
void s4464952_hal_atimer_clkspeed_set(int frequency);                                                     // set atimer clock speed (hz)
void s4464952_hal_atimer_period_set(int period);                                                          // set atimer period (ms)
void s4464952_hal_atimer_init_pin(void);                                                                  // initialise atimer GPIO pin
void atimer_isr_callback(void);																		     // isr callback function


/**
 * @brief  initialise atimer
 * @param  none
 * @retval None
 */
void s4464952_hal_atimer_init(void){

	// Timer 3 clock enable
	__TIM3_CLK_ENABLE();

	// Equation to calculate the prescaler value
	atimerPrescalerVal = (uint16_t) ((SystemCoreClock / 2) / atimerClkspeedVal) - 1;

	/* TIM Base configuration */
	TIM_Init.Instance = TIM3;				//Enable Timer 3
	TIM_Init.Init.Period = (atimerClkspeedVal*atimerPeriodVal)/1000;	//Set period count
  	TIM_Init.Init.Prescaler = atimerPrescalerVal;	//Set prescaler value
  	TIM_Init.Init.ClockDivision = 0;			//Set clock division
	TIM_Init.Init.RepetitionCounter = 0;	// Set reload Value
  	TIM_Init.Init.CounterMode = TIM_COUNTERMODE_UP;	//Set timer to count up.

    /* Initialise Timer */
	HAL_TIM_Base_Init(&TIM_Init);

	/* Set priority of Timer 2 update Interrupt [0 (HIGH priority) to 15(LOW priority)] */
	/* 	DO NOT SET INTERRUPT PRIORITY HIGHER THAN 3 */
	HAL_NVIC_SetPriority(TIM3_IRQn, 10, 0);		//Set Main priority to 10 and sub-priority to 0.

	// Enable the Timer 2 interrupt
	HAL_NVIC_EnableIRQ(TIM3_IRQn);

	// Start Timer 2 base unit in interrupt mode
	HAL_TIM_Base_Start_IT(&TIM_Init);

	//call the GPIO init 
	s4464952_hal_atimer_init_pin();

}

/**
 * @brief  return atimer counter value (ms)
 * @param  none
 * @retval counter value (ms)
 */
int s4464952_hal_atimer_timer_getms(void){
	
    atimer_ms = atimerPeriodVal * s4464952_hal_atimer_timer_read();
    return atimer_ms ; 

}

/**
 * @brief  reset atimer counter value to zero
 * @param  none
 * @retval None
 */
void s4464952_hal_atimer_timer_reset(void){

    s4464952_hal_atimer_timer_read() = 0 ;

}

/**
 * @brief  pause atimer
 * @param  none
 * @retval None
 */
void s4464952_hal_atimer_timer_pause(void){
	
    TIM_Init.Instance->CR1 &= ~TIM_CR1_CEN;;
	debug_printf("pause");	//Print debug message pause
}

/**
 * @brief  resume atimer
 * @param  none
 * @retval None
 */
void s4464952_hal_atimer_timer_resume(void) {
	
   TIM_Init.Instance->CR1 |= TIM_CR1_CEN;;
   debug_printf("resume\n");	//Print debug message resume

}

/**
 * @brief  set atimer clock speed (hz)
 * @param  frequency
 * @retval None
 */
void s4464952_hal_atimer_clkspeed_set(int frequency) {
	
    atimerClkspeedVal = atimerClkspeedVal + frequency;
	debug_printf("frequency = %d\n\r",atimerClkspeedVal);	//Print debug message pause
    

}

/**
 * @brief  set atimer period (ms)
 * @param  period
 * @retval None
 */
void s4464952_hal_atimer_period_set(int period){

    atimerPeriodVal = atimerPeriodVal + period; 
	debug_printf("frequency = %d\n\r",atimerPeriodVal);	//Print debug message pause
	
}

/**
 * @brief  initialise atimer GPIO pin
 * @param  none
 * @retval None
 */
void s4464952_hal_atimer_init_pin(void){

    /*all param value is obtained from the config file*/
 	GPIO_InitTypeDef GPIO_InitStructure;

  	S4464952_HAL_ATIMER_PINCLK ;                        // enable default clock in config 

  	/*D10 pin as an output */
	GPIO_InitStructure.Pin = S4464952_HAL_ATIMER_PIN;	//Pin D10
  	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;		//Output Mode
  	GPIO_InitStructure.Pull = GPIO_PULLDOWN;			//Enable Pull up, down or no pull resister
  	GPIO_InitStructure.Speed = GPIO_SPEED_FAST;			//Pin latency
	HAL_GPIO_Init(S4464952_HAL_ATIMER_PINPORT, &GPIO_InitStructure);

	HAL_GPIO_WritePin(S4464952_HAL_ATIMER_PINPORT, S4464952_HAL_ATIMER_PIN, 0);

}

/**
 * @brief  isr callback function for the atimer counter
 * @param  none
 * @retval None
 */
void atimer_isr_callback(void){
	
    s4464952_hal_atimer_timer_read()++ ;

}

/**
 * @brief Period elapsed callback in non blocking mode
 * @param htim: Pointer to a TIM_HandleTypeDef that contains the configuration information for the TIM module.
 * @retval None
 */
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if (htim->Instance == TIM3)
	{

		atimer_isr_callback();

	}
}

//Override default mapping of this handler to Default_Handler
void TIM3_IRQHandler(void)
{
	HAL_TIM_IRQHandler(&TIM_Init);
}
