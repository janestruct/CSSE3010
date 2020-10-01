/** 
 *************************************************************
 * @file /home/csse3010/csse3010/mylib/joystick/s4464952_hal_joystick.c
 * @author Aina Jauhara - s4464952
 * @date 14/03/2020
 * @brief mylib joystick file
 ***************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "board.h"
#include "processor_hal.h"
#include "debug_printf.h"
#include "s4464952_hal_joystick.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void s4464952_hal_joystick_init(void);                                          // initialise gpio pin and ADC 
int joystick_readxy(ADC_HandleTypeDef AdcHandle);                               // read x or y joystick value 

/**
 * @brief  read x or y joystick value
 * @param  none
 * @retval None
 */
int joystick_readxy(ADC_HandleTypeDef AdcHandle){
	
    unsigned int adc_value;
	
    HAL_ADC_Start(&AdcHandle); // Start ADC conversion

    // Wait for ADC conversion to finish
    while (HAL_ADC_PollForConversion(&AdcHandle, 10) != HAL_OK);

    adc_value = (uint16_t)(HAL_ADC_GetValue(&AdcHandle));
        
    return adc_value;

}

/**
 * @brief  initialise gpio pin and ADC 
 * @param  none
 * @retval None
 */
void s4464952_hal_joystick_init(void){
	
  GPIO_InitTypeDef GPIO_InitStructure;
  ADC_ChannelConfTypeDef xAdcChanConfig;
  ADC_ChannelConfTypeDef yAdcChanConfig;

	/*Joystick Z*/
	__BRD_A3_GPIO_CLK();
	
	GPIO_InitStructure.Pin = BRD_A3_PIN;
 	GPIO_InitStructure.Mode = GPIO_MODE_IT_RISING;
 	GPIO_InitStructure.Pull = GPIO_PULLUP;
 	GPIO_InitStructure.Speed = GPIO_SPEED_FAST;

 	HAL_GPIO_Init(BRD_A3_GPIO_PORT, &GPIO_InitStructure);
	 HAL_NVIC_SetPriority(BRD_A3_EXTI_IRQ, 10, 0);
 	HAL_NVIC_EnableIRQ(BRD_A3_EXTI_IRQ);

	/*Joystick X*/
	__BRD_A1_GPIO_CLK();

	GPIO_InitStructure.Pin = BRD_A1_PIN;
	GPIO_InitStructure.Mode = GPIO_MODE_ANALOG;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(BRD_A1_GPIO_PORT, &GPIO_InitStructure);
	
	/*Joystick Y*/
	__BRD_A2_GPIO_CLK();

	GPIO_InitStructure.Pin = BRD_A2_PIN;
	GPIO_InitStructure.Mode = GPIO_MODE_ANALOG;
	GPIO_InitStructure.Pull = GPIO_NOPULL;
	HAL_GPIO_Init(BRD_A2_GPIO_PORT, &GPIO_InitStructure);

  __ADC1_CLK_ENABLE();

	xAdcHandle.Instance = (ADC_TypeDef *)(ADC1_BASE);						//Use ADC1
	xAdcHandle.Init.ClockPrescaler        = ADC_CLOCKPRESCALER_PCLK_DIV2;	//Set clock prescaler
	xAdcHandle.Init.Resolution            = ADC_RESOLUTION12b;				//Set 12-bit data resolution
	xAdcHandle.Init.ScanConvMode          = DISABLE;
	xAdcHandle.Init.ContinuousConvMode    = DISABLE;
	xAdcHandle.Init.DiscontinuousConvMode = DISABLE;
	xAdcHandle.Init.NbrOfDiscConversion   = 0;
	xAdcHandle.Init.ExternalTrigConvEdge  = ADC_EXTERNALTRIGCONVEDGE_NONE;	//No Trigger
	xAdcHandle.Init.ExternalTrigConv      = ADC_EXTERNALTRIGCONV_T1_CC1;		//No Trigger
	xAdcHandle.Init.DataAlign             = ADC_DATAALIGN_RIGHT;				//Right align data
	xAdcHandle.Init.NbrOfConversion       = 1;
	xAdcHandle.Init.DMAContinuousRequests = DISABLE;
	xAdcHandle.Init.EOCSelection          = DISABLE;

    __ADC2_CLK_ENABLE();

	yAdcHandle.Instance = (ADC_TypeDef *)(ADC2_BASE);						//Use ADC2
	yAdcHandle.Init.ClockPrescaler        = ADC_CLOCKPRESCALER_PCLK_DIV2;	//Set clock prescaler
	yAdcHandle.Init.Resolution            = ADC_RESOLUTION12b;				//Set 12-bit data resolution
	yAdcHandle.Init.ScanConvMode          = DISABLE;
	yAdcHandle.Init.ContinuousConvMode    = DISABLE;
	yAdcHandle.Init.DiscontinuousConvMode = DISABLE;
	yAdcHandle.Init.NbrOfDiscConversion   = 0;
	yAdcHandle.Init.ExternalTrigConvEdge  = ADC_EXTERNALTRIGCONVEDGE_NONE;	//No Trigger
	yAdcHandle.Init.ExternalTrigConv      = ADC_EXTERNALTRIGCONV_T1_CC1;		//No Trigger
	yAdcHandle.Init.DataAlign             = ADC_DATAALIGN_RIGHT;				//Right align data
	yAdcHandle.Init.NbrOfConversion       = 1;
	yAdcHandle.Init.DMAContinuousRequests = DISABLE;
	yAdcHandle.Init.EOCSelection          = DISABLE;


	HAL_ADC_Init(&xAdcHandle);		//Initialise x ADC
	HAL_ADC_Init(&yAdcHandle);		//Initialise y ADC

	/* Configure A1 ADC Channel */
	xAdcChanConfig.Channel = BRD_A1_ADC_CHAN;							//Use AO pin
	xAdcChanConfig.Rank         = 1;
	xAdcChanConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
	xAdcChanConfig.Offset       = 0;

    /* Configure A2 ADC Channel */
	yAdcChanConfig.Channel = BRD_A2_ADC_CHAN;							//Use A1 pin
	yAdcChanConfig.Rank         = 1;
	yAdcChanConfig.SamplingTime = ADC_SAMPLETIME_3CYCLES;
	yAdcChanConfig.Offset       = 0;

	HAL_ADC_ConfigChannel(&xAdcHandle, &xAdcChanConfig);		//Initialise x - A1 ADC channel
  HAL_ADC_ConfigChannel(&yAdcHandle, &yAdcChanConfig);		//Initialise y - A2 ADC channel

  
}


