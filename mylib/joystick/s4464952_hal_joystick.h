/** 
 *************************************************************
 * @file /home/csse3010/csse3010/mylib/joystick/s4464952_hal_joystick.h
 * @author Aina Jauhara - s4464952
 * @date 14/3/2020
 * @brief header file contains joystick functions used by s4464952_hal_joystick.c
 ***************************************************************
 * EXTERNAL FUNCTIONS 
 ***************************************************************
 *************************************************************** 
 */

#ifndef S4464952_HAL_JOYSTICK_H
#define S4464952_HAL_JOYSTICK_H


ADC_HandleTypeDef xAdcHandle;
ADC_HandleTypeDef yAdcHandle;


void s4464952_hal_joystick_init(void);                                                                        // initialise gpio pin and ADC 
int joystick_readxy(ADC_HandleTypeDef AdcHandle);                                                             // read joystick value

#define S4464952_HAL_JOYSTICK_X_READ()              joystick_readxy(xAdcHandle)                               // function to read x value
#define S4464952_HAL_JOYSTICK_Y_READ()              joystick_readxy(yAdcHandle)                               // function to read y value

#endif


