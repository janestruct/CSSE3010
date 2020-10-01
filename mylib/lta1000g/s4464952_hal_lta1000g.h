/** 
 **************************************************************
 * @file /home/csse3010/csse3010/mylib/lta1000g/s4464952_hal_lta1000g.h
 * @author Aina Jauhara - s4464952
 * @date 23/2/2020
 * @brief header file contains LED bar functions used by main.c
 ***************************************************************
 * EXTERNAL FUNCTIONS 
 ***************************************************************
 * void s4464952_hal_lta1000g_init(void);                                          - initialise LED
 * void lta1000g_seg_set(int segment, unsigned char segment_value);                - set value for GPIO pin 
 * void s4464952_hal_lta1000g_write(unsigned short value);                         - write LED bar segment
 *************************************************************** 
 */

#ifndef S4464952_HAL_LTA1000G_H
#define S4464952_HAL_LTA1000G_H

void s4464952_hal_lta1000g_init(void);                                          //initialise LED
void lta1000g_seg_set(int segment, unsigned char segment_value);                //set value for GPIO pin 
void s4464952_hal_lta1000g_write(unsigned short value);                         //write LED bar segment

#endif