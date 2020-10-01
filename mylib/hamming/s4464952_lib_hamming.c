/** 
 ************************************************************
 * @file /home/csse3010/csse3010/mylib/hamming/s4464952_lib_hamming.c
 * @author Aina Jauhara - s4464952
 * @date 03/04/2020
 * @brief mylib hamming file
 ***************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include "board.h"
#include "processor_hal.h"
#include "debug_printf.h"
#include "s4464952_lib_hamming.h"


/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
uint16_t s4464952_lib_hamming_byte_encode(uint8_t input);                    // Return the 16bit encoded value of a byte
uint8_t s4464952_lib_hamming_byte_decode(uint16_t input);                     // Return the decoded half byte from a byte
uint8_t hamming_hbyte_encode(uint8_t in);                                   // Internal function to Encode a half byte
uint8_t s4464952_lib_hamming_decode_error(uint8_t in);                      // Return the error type


/**
 * @brief  Return the 16bit encoded value of a byte
 * @param  none
 * @retval byte
 */
uint16_t s4464952_lib_hamming_byte_encode(uint8_t input){

	uint16_t out;

	/* first encode D0..D3 (first 4 bits),
	 * then D4..D7 (second 4 bits).
	 */
	out = hamming_hbyte_encode(input & 0xF) |
		(hamming_hbyte_encode(input >> 4) << 8);

	return(out);

}

/**
 * @brief  Return the decoded half byte 
 * @param  none
 * @retval none
 */
uint8_t s4464952_lib_hamming_byte_decode(uint16_t input){

	uint8_t lsb;
	uint8_t msb;
	uint8_t byte;

	lsb = (input & 0x00ff);
	msb = (input & 0xff00) >> 8;

	lsb = s4464952_lib_hamming_decode_error(lsb);
	msb = s4464952_lib_hamming_decode_error(msb);
	
	byte = (msb << 4) | lsb;

	return (byte);

}

/**
 * @brief  Internal function to Encode a half byte
 * @param  none
 * @retval None
 */
uint8_t hamming_hbyte_encode(uint8_t in){

	uint8_t d0, d1, d2, d3;
	uint8_t p0 = 0, h0, h1, h2;
	uint8_t z;
	uint8_t out;

	/* extract bits */
	d0 = !!(in & 0x1);
	d1 = !!(in & 0x2);
	d2 = !!(in & 0x4);
	d3 = !!(in & 0x8);

	/* calculate hamming parity bits */
	h0 = d0 ^ d1 ^ d2;
	h1 = d0 ^ d2 ^ d3;
	h2 = d0 ^ d1 ^ d3;

	/* generate out byte without parity bit P0 */
	out = (h0 << 1) | (h1 << 2) | (h2 << 3) |
		(d0 << 4) | (d1 << 5) | (d2 << 6) | (d3 << 7);

	/* calculate even parity bit */
	for (z = 1; z<8; z++)
		p0 = p0 ^ !!(out & (1 << z));

	out |= p0;

	return(out);

}

/**
 * @brief  Return the error type
 * @param  none
 * @retval None
 */
uint8_t s4464952_lib_hamming_decode_error(uint8_t in){

	uint8_t out;
	uint8_t d3, d2, d1, d0;

	/* extract bits */
	d3 = !!(in & 0x80);
	d2 = !!(in & 0x40);
	d1 = !!(in & 0x20);
	d0 = !!(in & 0x10);

	uint8_t p0 = d0 ^ d1 ^ d2 ^ d3;

	out = (d3 << 3) | ( d2 << 2 ) | ( d1 << 1 ) | ( d0 << 0 );


	/* If syndrome indicates no error */
	if(!out) {
		/* If parity correct - no errors */
		if(p0 == !!(in & 1)) {
			
			return 0;

		/* If parity incorrect - parity is error */
		} else {

			return 1;
		}

	}
}
