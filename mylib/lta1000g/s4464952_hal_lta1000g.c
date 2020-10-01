 /** 
 **************************************************************
 * @file /home/csse3010/csse3010/mylib/lta1000g/s4464952_hal_lta1000g.c
 * @author Aina Jauhara - s4464952
 * @date 23/02/2020
 * @brief mylib lta1000g file
 ***************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "board.h"
#include "stm32f4xx_hal.h"
#include "debug_printf.h"
#include "s4464952_hal_lta1000g.h"
/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
void s4464952_hal_lta1000g_init(void);
void lta1000g_seg_set(int segment, unsigned char segment_value);
void s4464952_hal_lta1000g_write(unsigned short value);


/**
 * @brief  write to pins
 * @param  LED BAR value from main.c
 * @retval None
 */
void s4464952_hal_lta1000g_write(unsigned short value){
	
	int i;
	unsigned short segment_value;
 
	for(i = 0; i < 10; i++){
		segment_value = (i, value & 1);
		/*bit shift segment value using >> operator*/
		value = (value >> 1) ; 
		lta1000g_seg_set(i, segment_value);
	}
}


/**
 * @brief  set LED segment pins ON or OFF
 * @param  set segment pin to it's corresponding value
 * @retval None
 */
void lta1000g_seg_set(int segment, unsigned char segment_value){

/*Array stores PIN values for D16 - D25*/
uint32_t BRD_Dxx_PIN[] = {BRD_D16_PIN,BRD_D17_PIN,BRD_D18_PIN,BRD_D19_PIN,BRD_D20_PIN,BRD_D21_PIN,BRD_D22_PIN,BRD_D23_PIN,BRD_D24_PIN,BRD_D25_PIN};

/*Array stores PORT values for D16 - D25*/
 GPIO_TypeDef *BRD_DXX_GPIO_PORT[] = {BRD_D16_GPIO_PORT,BRD_D17_GPIO_PORT,BRD_D18_GPIO_PORT,BRD_D19_GPIO_PORT,BRD_D20_GPIO_PORT,BRD_D21_GPIO_PORT,BRD_D22_GPIO_PORT,BRD_D23_GPIO_PORT,BRD_D24_GPIO_PORT,BRD_D25_GPIO_PORT};

	/* operate D16 to 25 pins */
	HAL_GPIO_WritePin(BRD_DXX_GPIO_PORT[segment], BRD_Dxx_PIN[segment], segment_value);
	}

/**
 * @brief  Initialise Hardware for D register PINs
 * @param  None
 * @retval None
 */
void s4464952_hal_lta1000g_init(void) {

GPIO_InitTypeDef  GPIO_InitStructure;

	/* Enable the D16-D25 Clock */
  		__BRD_D16_GPIO_CLK();
		__BRD_D17_GPIO_CLK();
		__BRD_D18_GPIO_CLK();
		__BRD_D19_GPIO_CLK();
		__BRD_D20_GPIO_CLK();
		__BRD_D21_GPIO_CLK();
		__BRD_D22_GPIO_CLK();
		__BRD_D23_GPIO_CLK();
		__BRD_D24_GPIO_CLK();
		__BRD_D25_GPIO_CLK();


  	/* Configure the D16-D25 pin as the output */
	GPIO_InitStructure.Pin = BRD_D16_PIN;					//Pin
  	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;			//Output Mode
  	GPIO_InitStructure.Pull = GPIO_PULLDOWN;				//Enable Pull up, down or no pull resister
  	GPIO_InitStructure.Speed = GPIO_SPEED_FAST;				//Pin latency
  	HAL_GPIO_Init(BRD_D16_GPIO_PORT, &GPIO_InitStructure);	//Initialise Pin

	GPIO_InitStructure.Pin = BRD_D17_PIN;					//Pin
  	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;			//Output Mode
  	GPIO_InitStructure.Pull = GPIO_PULLDOWN;				//Enable Pull up, down or no pull resister
  	GPIO_InitStructure.Speed = GPIO_SPEED_FAST;				//Pin latency
  	HAL_GPIO_Init(BRD_D17_GPIO_PORT, &GPIO_InitStructure);	//Initialise Pin

	GPIO_InitStructure.Pin = BRD_D18_PIN;					//Pin
  	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;			//Output Mode
  	GPIO_InitStructure.Pull = GPIO_PULLDOWN;				//Enable Pull up, down or no pull resister
  	GPIO_InitStructure.Speed = GPIO_SPEED_FAST;				//Pin latency
  	HAL_GPIO_Init(BRD_D18_GPIO_PORT, &GPIO_InitStructure);	//Initialise Pin

	GPIO_InitStructure.Pin = BRD_D19_PIN;					//Pin
  	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;			//Output Mode
  	GPIO_InitStructure.Pull = GPIO_PULLDOWN;				//Enable Pull up, down or no pull resister
  	GPIO_InitStructure.Speed = GPIO_SPEED_FAST;				//Pin latency
  	HAL_GPIO_Init(BRD_D19_GPIO_PORT, &GPIO_InitStructure);	//Initialise Pin

	GPIO_InitStructure.Pin = BRD_D20_PIN;					//Pin
  	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;			//Output Mode
  	GPIO_InitStructure.Pull = GPIO_PULLDOWN;				//Enable Pull up, down or no pull resister
  	GPIO_InitStructure.Speed = GPIO_SPEED_FAST;				//Pin latency
  	HAL_GPIO_Init(BRD_D20_GPIO_PORT, &GPIO_InitStructure);	//Initialise Pin

	GPIO_InitStructure.Pin = BRD_D21_PIN;					//Pin
  	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;			//Output Mode
  	GPIO_InitStructure.Pull = GPIO_PULLDOWN;				//Enable Pull up, down or no pull resister
  	GPIO_InitStructure.Speed = GPIO_SPEED_FAST;				//Pin latency
  	HAL_GPIO_Init(BRD_D21_GPIO_PORT, &GPIO_InitStructure);	//Initialise Pin
		
	GPIO_InitStructure.Pin = BRD_D22_PIN;					//Pin
  	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;			//Output Mode
  	GPIO_InitStructure.Pull = GPIO_PULLDOWN;				//Enable Pull up, down or no pull resister
  	GPIO_InitStructure.Speed = GPIO_SPEED_FAST;				//Pin latency
  	HAL_GPIO_Init(BRD_D22_GPIO_PORT, &GPIO_InitStructure);	//Initialise Pin

	GPIO_InitStructure.Pin = BRD_D23_PIN;					//Pin
  	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;			//Output Mode
  	GPIO_InitStructure.Pull = GPIO_PULLDOWN;				//Enable Pull up, down or no pull resister
  	GPIO_InitStructure.Speed = GPIO_SPEED_FAST;				//Pin latency
  	HAL_GPIO_Init(BRD_D23_GPIO_PORT, &GPIO_InitStructure);	//Initialise Pin

	GPIO_InitStructure.Pin = BRD_D24_PIN;					//Pin
  	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;			//Output Mode
  	GPIO_InitStructure.Pull = GPIO_PULLDOWN;				//Enable Pull up, down or no pull resister
  	GPIO_InitStructure.Speed = GPIO_SPEED_FAST;				//Pin latency
  	HAL_GPIO_Init(BRD_D24_GPIO_PORT, &GPIO_InitStructure);	//Initialise Pin

	GPIO_InitStructure.Pin = BRD_D25_PIN;					//Pin
  	GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;			//Output Mode
  	GPIO_InitStructure.Pull = GPIO_PULLDOWN;				//Enable Pull up, down or no pull resister
  	GPIO_InitStructure.Speed = GPIO_SPEED_FAST;				//Pin latency
  	HAL_GPIO_Init(BRD_D25_GPIO_PORT, &GPIO_InitStructure);	//Initialise Pin


}


