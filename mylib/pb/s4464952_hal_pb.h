/** 
 **************************************************************
 * @file /home/csse3010/csse3010/mylib/lta1000g/s4464952_hal_lta1000g.h
 * @author Aina Jauhara - s4464952
 * @date 23/2/2020
 * @brief header file contains LED bar functions used by main.c
 ***************************************************************
 * EXTERNAL FUNCTIONS 
 ***************************************************************
 * s4464952_hal_pb_on_init()             - enable pb source
 * s4464952_hal_pb_on_isr()              - pb isr
 * s4464952_hal_pb_on_deinit()           - disable iss pin source
 * s4464952_hal_pb_iss_init()            - enable iss pin source
 * s4464952_hal_pb_iss_isr()             - iss pin source isr
 * s4464952_hal_pb_iss_deinit()          - disable pb source
 *************************************************************** 
 */

#ifndef S4464952_HAL_PB_H
#define S4464952_HAL_PB_H

void s4464952_hal_pb_on_init(void);             //enable pb source
int s4464952_hal_pb_on_isr(void);              //pb isr
void s4464952_hal_pb_on_deinit(void);           //disable iss pin source
void s4464952_hal_pb_iss_init(void);            //enable iss pin source
int s4464952_hal_pb_iss_isr(void);             //iss pin source isr
void s4464952_hal_pb_iss_deinit(void);          //disable pb source

#endif

