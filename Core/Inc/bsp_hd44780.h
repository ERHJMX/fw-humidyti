#include "stm32f0xx_hal.h"

#ifndef __HD44780_H__
#define __HD44780_H__

#define	HD44780_E						GPIO_PIN_13	//P7_OUT_Pin
#define	HD44780_PORT_E			GPIOB
#define	HD44780_RS					GPIO_PIN_11	//P9_OUT_Pin
#define	HD44780_PORT_RS			GPIOB


#define	HD44780_D7					GPIO_PIN_10	//P10_OUT_Pin
#define	HD44780_D6					GPIO_PIN_9	//P11_OUT_Pin
#define	HD44780_D5					GPIO_PIN_8	//P12_OUT_Pin
#define	HD44780_D4					GPIO_PIN_7	//P13_OUT_Pin
#define	HD44780_DATA				GPIOB

#define BIT7 0x80
#define BIT6 0x40
#define BIT5 0x20
#define BIT4 0x10
#define BIT3 0x08
#define BIT2 0x04
#define BIT1 0x02
#define BIT0 0x01
  
#define HD44780_BUSY_FLAG    HD44780_DB7
#define HD44780_INIT_SEQ     0x30
#define HD44780_DISP_CLEAR   0x01
#define HD44780_DISP_OFF     0x08
#define HD44780_DISP_ON      0x0C
#define HD44780_CURSOR_ON    0x0E
#define HD44780_CURSOR_BLINK 0x0F
#define HD44780_RETURN_HOME  0x02 
#define HD44780_ENTRY_MODE   0x06
#define HD44780_4BIT_MODE    0x20
#define HD44780_8BIT_MODE    0x30
#define HD44780_2_ROWS       0x08
#define HD44780_FONT_5x8     0x00
#define HD44780_FONT_5x10    0x04
#define HD44780_POSITION     0x80

#define HD44780_SHIFT        0x10
#define HD44780_CURSOR       0x00
#define HD44780_DISPLAY      0x08
#define HD44780_LEFT         0x00
#define HD44780_RIGHT        0x04

#define HD44780_ROWS         2//4
#define HD44780_COLS         20

#define HD44780_ROW1_START   0x0
#define HD44780_ROW2_START   0x40


void HD44780_RS_SET(void);
void HD44780_RS_CLR(void);
void HD44780_E_SET(void);
void HD44780_E_CLR(void);
void HD44780_WRITE(char);

void HD44780_Clear(void);
void HD44780_ReturnHome(void);
void HD44780_SetXY(int,int);
void HD44780_Text(char*);
void HD44780_DisplayOn(void);
void HD44780_DisplayOff(void);
void HD44780_Init(void);

#endif
