/** 
 **************************************************************
 * @file /home/csse3010/csse3010/mylib/iss/s4464952_hal_iss.h
 * @author Aina Jauhara - s4464952
 * @date 23/2/2020
 * @brief header file contains iss functions used by main.c
 ***************************************************************
 * EXTERNAL FUNCTIONS 
 ***************************************************************
 * void s4464952_hal_iss_init(void)                                                                           - initialise iss counter
 * void s4464952_hal_iss_synchroniser(unsigned char signal_source_index)                                      - sync input signal
 * void s4464952_hal_iss_eventcounter_read(unsigned char signal_source_index)                                 - return specified event counter value
 * void s4464952_hal_iss_lasttimer_read(unsigned char signal_source_index)                                    - return specified last time value
 * void s4464952_hal_iss_eventcounter_reset(unsigned char signal_source_index)                                - reset specified event counter value
 * void s4464952_hal_iss_lasttimer_reset(unsigned char signal_source_index)                                   - reset specified last time value
 * void s4464952_hal_iss_delaytimer_ctrl(unsigned char signal_source_index,int delay_value)                   - set delat value for specified source
 *************************************************************** 
 */

#ifndef S4464952_HAL_ISS_H
#define S4464952_HAL_ISS_H


void s4464952_hal_iss_init(void);                                                                           //initialise iss counter
void s4464952_hal_iss_synchroniser(unsigned char signal_source_index);                                      //sync input signal
void s4464952_hal_iss_eventcounter_read(unsigned char signal_source_index);                                 //return specified event counter value
void s4464952_hal_iss_lasttimer_read(unsigned char signal_source_index);                                    //return specified last time value
void s4464952_hal_iss_eventcounter_reset(unsigned char signal_source_index);                                //reset specified event counter value
void s4464952_hal_iss_lasttimer_reset(unsigned char signal_source_index);                                   //reset specified last time value
void s4464952_hal_iss_delaytimer_ctrl(unsigned char signal_source_index,int delay_value);                   //set delat value for specified source


#endif

