/**
  ******************************************************************************
  * @file    stage2/main.c
  * @author  Aina Jauhara - s4464952
  * @date    23/2/2020
  * @brief   Stage 2 main file
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "board.h"
#include "processor_hal.h"
#include "debug_printf.h"
#include "s4464952_hal_lta1000g.h"
#include "s4464952_hal_pb.h"
#include "s4464952_hal_iss.h"
#include "s4464952_hal_atimer.h"
#include "s4464952_hal_mylib_configure.h"
#include "s4464952_hal_joystick.h"
#include "s4464952_hal_pwm.h"



/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
int frequency;                  //atimer frequency 
int period;                     //atimer period
unsigned int atimer_tick;       //time in tick
int atimer_ms;                  //time in ms
char RxChar;
int led_value  = 0 ;
/* Private function prototypes -----------------------------------------------*/
void console_input (char RxChar) ; 
void s4464952_hal_atimer_clkspeed_set(int frequency);                                                     // set atimer clock speed (hz)
void s4464952_hal_atimer_period_set(int period);   
int function_set_led(int adc_value);


/**
  * @brief  Main program 
  * @param  None
  * @retval None
  */
int main(void)  {

  BRD_init();							//Initalise Board
  s4464952_hal_atimer_init(); 
  s4464952_hal_joystick_init();
  //s4464952_hal_pwm_init();
  s4464952_hal_lta1000g_init();


	/* Main processing loop */
	while (1) {

    RxChar = debug_getc()  ;

    if (RxChar == 'f') {

        s4464952_hal_atimer_timer_pause();
        debug_printf("pause atimer\n\r"); 

    }else if(RxChar == 'r'){

       s4464952_hal_atimer_timer_resume();
       debug_printf("resume atimer\n\r");

    }else if(RxChar == 'z'){

       s4464952_hal_atimer_timer_reset();
       debug_printf("reset atimer\n\r");

    }else if(RxChar == 'c'){

        atimer_tick = s4464952_hal_atimer_timer_getms();
        debug_printf("current atimer value: %d tick\n\r", atimer_tick);

    }else if(RxChar == 't'){

        atimer_ms = s4464952_hal_atimer_timer_getms();
        debug_printf("current atimer value: %d ms\n\r", atimer_ms);

    }else if(RxChar == '+'){

        period = 10 ;
        s4464952_hal_atimer_period_set(period);
        s4464952_hal_atimer_init();
        
    }else if(RxChar == '-'){

        period = -10 ;
        s4464952_hal_atimer_period_set(period);
        s4464952_hal_atimer_init();

    }else if(RxChar == 'i'){

        frequency = 1000 ;
        s4464952_hal_atimer_clkspeed_set(frequency);
        s4464952_hal_atimer_init();

    }else if(RxChar == 'd'){

        frequency = -1000 ;
        s4464952_hal_atimer_clkspeed_set(frequency);
        s4464952_hal_atimer_init();

    }
    
    
  }

}

/**
  * @brief  write led bar value  
  * @param  int led_val 
  * @retval int write_Val
  */
int function_set_led(int adc_value){

    adc_value = S4464952_HAL_JOYSTICK_X_READ();

	if(adc_value >= 0 && adc_value <= 410){
			led_value = 0x0001 ;
	}else if(adc_value > 410 && adc_value <=820){
			led_value = 0x0002 ;
	}else if(adc_value > 820 && adc_value <= 1230){
			led_value = 0x0004 ;
	}else if(adc_value > 1230 && adc_value <= 1640){
			led_value = 0x0008 ;
	}else if(adc_value > 1640 && adc_value <= 2047){
			led_value = 0x0010 ;
	}else if(adc_value > 2047 && adc_value <= 2096){
			led_value = 0x0020 ;
	}else if(adc_value > 2096 && adc_value <= 2460){
			led_value = 0x0040 ;
	}else if(adc_value > 2460 && adc_value <= 2870){
			led_value = 0x0080 ;
	}else if(adc_value > 2870 && adc_value <= 3280){
			led_value = 0x0100 ;
	}else if(adc_value > 3280 && adc_value <= 3690){
			led_value = 0x0200 ;        
	}
	return led_value ;
}


