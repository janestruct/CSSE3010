/** 
 *************************************************************
 * @file /home/csse3010/csse3010/mylib/hamming/s4464952_lib_hamming.h
 * @author Aina Jauhara - s4464952
 * @date 03/04/2020
 * @brief header file contains hamming functions used by s4464952_hal_hamming.c
 ***************************************************************
 * EXTERNAL FUNCTIONS 
 ***************************************************************
 * uint16_t s4464952_lib_hamming_byte_encode(uint8_t input);
 * uint8_t s4464952_lib_hamming_byte_decode(uint16_t data); 
 * uint8_t hamming_hbyte_encode(uint8_t in); 
 * uint8_t s4464952_lib_hamming_decode_error(uint8_t in);                                                                          
 *************************************************************** 
 */

#ifndef S4464952_LIB_HAMMING_H
#define S4464952_LIB_HAMMING_H

uint16_t s4464952_lib_hamming_byte_encode(uint8_t input);                    // Return the 16bit encoded value of a byte
uint8_t s4464952_lib_hamming_byte_decode(uint16_t input);                     // Return the decoded half byte from a byte
uint8_t hamming_hbyte_encode(uint8_t in);                                   // Internal function to Encode a half byte
uint8_t s4464952_lib_hamming_decode_error(uint8_t in);                      // Return the error type

#endif

