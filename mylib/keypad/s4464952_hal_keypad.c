/** 
 ***************************************************************
 * @file /home/csse3010/csse3010/mylib/keypad/s4464952_hal_keypad.c
 * @author Aina Jauhara - s4464952
 * @date 03/04/2020
 * @brief mylib keypad file
 ***************************************************************
 */

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <time.h>
#include "stm32f4xx_hal.h"
#include "stm32f429xx.h"
#include "stm32f4xx_hal_gpio.h"
#include "stm32f4xx_hal_tim.h"
#include "board.h"
#include "processor_hal.h"
#include "debug_printf.h"
#include "s4464952_hal_keypad.h"

/* Private typedef -----------------------------------------------------------*/

/* Private define ------------------------------------------------------------*/
#define INIT_STATE          0
#define COL1_STATE          1
#define COL2_STATE          2
#define COL3_STATE          3
#define COL4_STATE          4
#define ROWSCAN_STATE       5
#define DEINIT_STATE        6

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
 int KeypadFsmCurrentstate;
int KeypadStatus;
int col = 0;
unsigned char KeypadValue;
/* Private function prototypes -----------------------------------------------*/
void s4464952_hal_keypad_init(void);                    // Set the state of the keypadFSM to INIT state
void s4464952_hal_keypad_deinit(void);                  // Set the state of the keypadFSM to DEINIT state.
void s4464952_hal_keypad_fsmprocessing(void);           // Keypad FSM processing loop
void keypad_gpio_init(void);                            // Initalise all GPIO pins.
void keypad_writecol(int colval);
int keypad_readrow(void);                               // Internal function for reading a row
int s4464952_hal_keypad_read_status(void);             // Return the KeypadStatus variable
int s4464952_keypad_read_key();
char s4464952_hal_keypad_read_ascii();

/**
 * @brief Set the state of the keypadFSM to INIT state
 * @param  None
 * @retval None
 */
void s4464952_hal_keypad_init(){

    KeypadFsmCurrentstate = INIT_STATE;
}

/**
 * @brief Set the state of the keypadFSM to DEINIT state
 * @param  None
 * @retval None
 */
void s4464952_hal_keypad_deinit(){

     KeypadFsmCurrentstate = DEINIT_STATE;
}
/**

/**
 * @brief Keypad FSM Processing
 * @param 
 * @retval 
 */
void s4464952_hal_keypad_fsmprocessing(){

     switch(KeypadFsmCurrentstate){

     case INIT_STATE:

               KeypadFsmCurrentstate = COL1_STATE; // Setting next state to COL1 state
              

          break;
          
          
     case COL1_STATE:

               col = 1;
               keypad_writecol(COL1_STATE);
               KeypadFsmCurrentstate = ROWSCAN_STATE; // Setting next value to ROWSCAN state
          
          break;
          
     case COL2_STATE:

               col = 2;
               keypad_writecol(COL2_STATE);
               KeypadFsmCurrentstate = ROWSCAN_STATE; // Setting next value to ROWSCAN state
         
          break;

     case COL3_STATE:

               col = 3;
               keypad_writecol(COL3_STATE);
               KeypadFsmCurrentstate = ROWSCAN_STATE; // Setting next value to ROWSCAN state

          break;

     case COL4_STATE:

               col = 4;
               keypad_writecol(COL4_STATE);
               KeypadFsmCurrentstate = ROWSCAN_STATE; // Setting next value to ROWSCAN state

          break;

     case ROWSCAN_STATE:

              keypad_readrow();
              
              if(col == 1){
               KeypadFsmCurrentstate = COL2_STATE;
              }
              if(col == 2){
               KeypadFsmCurrentstate = COL3_STATE;
              }
              if(col == 3){
               KeypadFsmCurrentstate = COL4_STATE;
              }
               if(col == 4){
               KeypadFsmCurrentstate = COL1_STATE;
              }

          break;

     case DEINIT_STATE:

               s4464952_hal_keypad_deinit();

          break;
     }
}
/**
 * @brief Write Column value to LOW
 * @param 
 * @retval 
 */
void keypad_writecol(int colval){

     if (colval == 1)
     {
          HAL_GPIO_WritePin(s4464952_HAL_KEYPAD_COL1PINPORT,s4464952_HAL_KEYPAD_COL1PIN, 0x00);
          HAL_GPIO_WritePin(s4464952_HAL_KEYPAD_COL2PINPORT,s4464952_HAL_KEYPAD_COL2PIN, 0x01);
          HAL_GPIO_WritePin(s4464952_HAL_KEYPAD_COL3PINPORT,s4464952_HAL_KEYPAD_COL3PIN, 0x01);
          HAL_GPIO_WritePin(s4464952_HAL_KEYPAD_COL4PINPORT,s4464952_HAL_KEYPAD_COL4PIN, 0x01);
     }
      if (colval == 2)
     {
          HAL_GPIO_WritePin(s4464952_HAL_KEYPAD_COL1PINPORT,s4464952_HAL_KEYPAD_COL1PIN, 0x01);
          HAL_GPIO_WritePin(s4464952_HAL_KEYPAD_COL2PINPORT,s4464952_HAL_KEYPAD_COL2PIN, 0x00);
          HAL_GPIO_WritePin(s4464952_HAL_KEYPAD_COL3PINPORT,s4464952_HAL_KEYPAD_COL3PIN, 0x01);
          HAL_GPIO_WritePin(s4464952_HAL_KEYPAD_COL4PINPORT,s4464952_HAL_KEYPAD_COL4PIN, 0x01);
     }
      if (colval == 3)
     {
          HAL_GPIO_WritePin(s4464952_HAL_KEYPAD_COL1PINPORT,s4464952_HAL_KEYPAD_COL1PIN, 0x01);
          HAL_GPIO_WritePin(s4464952_HAL_KEYPAD_COL2PINPORT,s4464952_HAL_KEYPAD_COL2PIN, 0x01);
          HAL_GPIO_WritePin(s4464952_HAL_KEYPAD_COL3PINPORT,s4464952_HAL_KEYPAD_COL3PIN, 0x00);
          HAL_GPIO_WritePin(s4464952_HAL_KEYPAD_COL4PINPORT,s4464952_HAL_KEYPAD_COL4PIN, 0x01);
     }
      if (colval == 4)
     {
          HAL_GPIO_WritePin(s4464952_HAL_KEYPAD_COL1PINPORT,s4464952_HAL_KEYPAD_COL1PIN, 0x01);
          HAL_GPIO_WritePin(s4464952_HAL_KEYPAD_COL2PINPORT,s4464952_HAL_KEYPAD_COL2PIN, 0x01);
          HAL_GPIO_WritePin(s4464952_HAL_KEYPAD_COL3PINPORT,s4464952_HAL_KEYPAD_COL3PIN, 0x01);
          HAL_GPIO_WritePin(s4464952_HAL_KEYPAD_COL4PINPORT,s4464952_HAL_KEYPAD_COL4PIN, 0x00);
     }
}
/**
 * @brief Reading Row
 * @param 
 * @retval row
 */
int keypad_readrow(){

    int row = 0;
    
   if (!HAL_GPIO_ReadPin(s4464952_HAL_KEYPAD_ROW4PINPORT,s4464952_HAL_KEYPAD_ROW4PIN))
   {
        row = 1;
   }
    if (!HAL_GPIO_ReadPin(s4464952_HAL_KEYPAD_ROW3PINPORT,s4464952_HAL_KEYPAD_ROW3PIN))
   {
        row = 2;
   }
    if (!HAL_GPIO_ReadPin(s4464952_HAL_KEYPAD_ROW2PINPORT,s4464952_HAL_KEYPAD_ROW2PIN))
   {
        row = 3;
   }
    if (!HAL_GPIO_ReadPin(s4464952_HAL_KEYPAD_ROW1PINPORT,s4464952_HAL_KEYPAD_ROW1PIN))
   {
        row = 4;
       
   }
     
    return row;
}
/**
 * @brief Read current status of Keypad
 * @param 
 * @retval KeypadStatus
 *
 */
int s4464952_hal_keypad_read_status(){

     int row_status = keypad_readrow();

     if (row_status != 0)
     {
          KeypadStatus = 1; //Key is pressed
     }
     else
     {
          KeypadStatus = 0; //No key is pressed
     }
    return KeypadStatus;

}
/**
 * @brief Read keypad value in hexadecimal
 * @param 
 * @retval 
 */
int s4464952_keypad_read_key()
{
     int column = col;
     int row = keypad_readrow();
     int key = 0;
     
     if (col == 1)
     {
          if (row == 1)
          {
               key = 4;
          }
          if (row == 2)
          {
               key = 3;
          }
          if (row == 3)
          {
               key = 2;
          }
          if (row == 4)
          {
               key = 1;
          }
          
     }
     if (col == 2)
     {
          if (row == 1)
          {
               key = 8;
          }
          if (row == 2)
          {
               key = 7;
          }
          if (row == 3)
          {
               key = 6;
          }
          if (row == 4)
          {
               key = 5;
          }
     }
     if (col == 3)
     {
          if (row == 1)
          {
               key = 12;
          }
          if (row == 2)
          {
               key = 11;
          }
          if (row == 3)
          {
               key = 10;
          }
          if (row == 4)
          {
               key = 9;
          }
     }
     if (col == 4)
     {
          if (row == 1)
          {
               key = 16;
          }
          if (row == 2)
          {
               key = 15;
          }
          if (row == 3)
          {
               key = 14;
          }
          if (row == 4)
          {
               key = 13;
          }
          
     }
    return key;
}
/**
 * @brief Convert Hexvalue to ASCII character
 * @param 
 * @retval KeypadValue
 */
char s4464952_hal_keypad_read_ascii(){

     int keyVal = s4464952_keypad_read_key();
     char output = 0;	

     if (keyVal == 1) {
		output = '1';
	}
	if (keyVal == 2) {
		output = '4'; 
	}
	if (keyVal == 3) {
		output = '7'; 
	}
	if (keyVal == 4) {
		output = '0'; 
	}
	if (keyVal == 5) {
		output = '2'; 
	}
	if (keyVal == 6) {
		output = '5'; 
	}
	if (keyVal == 7) {
		output = '8'; 
	}
	if (keyVal == 8) {
		output = 'F'; 
	}
	if (keyVal == 9) {
		output = '3'; 
	}
	if (keyVal == 10) {
		output = '6'; 
	}
	if (keyVal == 11) {
		output = '9'; 
	}
	if (keyVal == 12) {
		output = 'E'; 
	}
	if (keyVal == 13) {
		output = 'A'; 
	}
	if (keyVal == 14) {
		output = 'B'; 
	}
	if (keyVal == 15) {
		output = 'C'; 
	}
	if (keyVal == 16) {
		output = 'D'; 
	}				
	return output;   
}

/*
 * @brief Initalise all GPIO pins
 * @param  None
 * @retval None
 */
void keypad_gpio_init(){

    /* Enable the Row and Column's Clock (D2-D5,D7-D9 &A4) */
        s4464952_HAL_KEYPAD_COL1PINCLK;          
        s4464952_HAL_KEYPAD_COL2PINCLK;          
        s4464952_HAL_KEYPAD_COL3PINCLK;         
        s4464952_HAL_KEYPAD_COL4PINCLK; 
        s4464952_HAL_KEYPAD_ROW1PINCLK;         
        s4464952_HAL_KEYPAD_ROW2PINCLK;       
        s4464952_HAL_KEYPAD_ROW3PINCLK;       
        s4464952_HAL_KEYPAD_ROW4PINCLK;          
     
     /* Configure the D2 pin as an output */
    GPIO_InitStructure.Pin = s4464952_HAL_KEYPAD_COL4PIN;        //Pin
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;    //Output Mode
    GPIO_InitStructure.Pull = GPIO_PULLDOWN;      //Enable Pull up, down or no pull resister
    GPIO_InitStructure.Speed = GPIO_SPEED_FAST;     //Pin latency
    HAL_GPIO_Init(s4464952_HAL_KEYPAD_COL4PINPORT, &GPIO_InitStructure);  //Initialise Pin

     /* Configure the D3 pin as an output */
    GPIO_InitStructure.Pin = s4464952_HAL_KEYPAD_COL3PIN;        //Pin
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;    //Output Mode
    GPIO_InitStructure.Pull = GPIO_PULLDOWN;      //Enable Pull up, down or no pull resister
    GPIO_InitStructure.Speed = GPIO_SPEED_FAST;     //Pin latency
    HAL_GPIO_Init(s4464952_HAL_KEYPAD_COL3PINPORT, &GPIO_InitStructure);  //Initialise Pin

     /* Configure the D4 pin as an output */
    GPIO_InitStructure.Pin = s4464952_HAL_KEYPAD_COL2PIN;        //Pin
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;    //Output Mode
    GPIO_InitStructure.Pull = GPIO_PULLDOWN;      //Enable Pull up, down or no pull resister
    GPIO_InitStructure.Speed = GPIO_SPEED_FAST;     //Pin latency
    HAL_GPIO_Init(s4464952_HAL_KEYPAD_COL2PINPORT, &GPIO_InitStructure);  //Initialise Pin

     /* Configure the D5 pin as an output */
    GPIO_InitStructure.Pin = s4464952_HAL_KEYPAD_COL1PIN;        //Pin
    GPIO_InitStructure.Mode = GPIO_MODE_OUTPUT_PP;    //Output Mode
    GPIO_InitStructure.Pull = GPIO_PULLDOWN;      //Enable Pull up, down or no pull resister
    GPIO_InitStructure.Speed = GPIO_SPEED_FAST;     //Pin latency
    HAL_GPIO_Init(s4464952_HAL_KEYPAD_COL1PINPORT, &GPIO_InitStructure);  //Initialise Pin


  /* Configure the D7 pin as an input */
    GPIO_InitStructure.Pin = s4464952_HAL_KEYPAD_ROW4PIN;       //Pin
    GPIO_InitStructure.Mode = GPIO_MODE_INPUT;      //Input Mode
    GPIO_InitStructure.Pull = GPIO_PULLUP;      //Enable Pull up, down or no pull resister
    GPIO_InitStructure.Speed = GPIO_SPEED_FAST;     //Pin latency
    HAL_GPIO_Init(s4464952_HAL_KEYPAD_ROW4PINPORT, &GPIO_InitStructure);  //Initialise Pin
    
     /* Configure the D8 pin as an input */
    GPIO_InitStructure.Pin = s4464952_HAL_KEYPAD_ROW3PIN;       //Pin
    GPIO_InitStructure.Mode = GPIO_MODE_INPUT;      //Input Mode
    GPIO_InitStructure.Pull = GPIO_PULLUP;      //Enable Pull up, down or no pull resister
    GPIO_InitStructure.Speed = GPIO_SPEED_FAST;     //Pin latency
    HAL_GPIO_Init(s4464952_HAL_KEYPAD_ROW3PINPORT, &GPIO_InitStructure);  //Initialise Pin

     /* Configure the D9 pin as an input */
    GPIO_InitStructure.Pin = s4464952_HAL_KEYPAD_ROW2PIN;       //Pin
    GPIO_InitStructure.Mode = GPIO_MODE_INPUT;      //Input Mode
    GPIO_InitStructure.Pull = GPIO_PULLUP;      //Enable Pull up, down or no pull resister
    GPIO_InitStructure.Speed = GPIO_SPEED_FAST;     //Pin latency
    HAL_GPIO_Init(s4464952_HAL_KEYPAD_ROW2PINPORT, &GPIO_InitStructure);  //Initialise Pin

     /* Configure the A4 pin as an input */
    GPIO_InitStructure.Pin = s4464952_HAL_KEYPAD_ROW1PIN;       //Pin
    GPIO_InitStructure.Mode = GPIO_MODE_INPUT;      //Input Mode
    GPIO_InitStructure.Pull = GPIO_PULLUP;      //Enable Pull up, down or no pull resister
    GPIO_InitStructure.Speed = GPIO_SPEED_FAST;     //Pin latency
    HAL_GPIO_Init(s4464952_HAL_KEYPAD_ROW1PINPORT, &GPIO_InitStructure);  //Initialise Pin 
}

