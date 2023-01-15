// include libraries
#include <stdio.h>
#include "stm32f0xx_hal.h"
#include "bsp_hd44780.h"

/*start*/

/**/
void HD44780_PORT_CONTROL(void){
	GPIO_InitTypeDef GPIO_InitStruct;	
  
	GPIO_InitStruct.Pin = HD44780_E;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(HD44780_PORT_E, &GPIO_InitStruct);

	GPIO_InitStruct.Pin = HD44780_RS;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(HD44780_PORT_RS, &GPIO_InitStruct);
}

/**/
void HD44780_PORTDATA_OUT(void){
	GPIO_InitTypeDef GPIO_InitStruct;	
  GPIO_InitStruct.Pin = HD44780_D7 | HD44780_D6 | HD44780_D5 |HD44780_D4;
  GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
  HAL_GPIO_Init(HD44780_DATA, &GPIO_InitStruct);
}

/**/
void HD44780_ms(int ms){
	HAL_Delay(ms);
}

/**/
void HD44780_RS_SET(void){
HAL_GPIO_WritePin(HD44780_PORT_RS, HD44780_RS, GPIO_PIN_SET);
}

/**/
void HD44780_RS_CLR(void){
HAL_GPIO_WritePin(HD44780_PORT_RS, HD44780_RS, GPIO_PIN_RESET);
}

/**/
void HD44780_E_SET(void){
HAL_GPIO_WritePin(HD44780_PORT_E, HD44780_E, GPIO_PIN_SET);
}

/**/
void HD44780_E_CLR(void){
HAL_GPIO_WritePin(HD44780_PORT_E, HD44780_E, GPIO_PIN_RESET);
}

/**/
void HD44780_PulseE(void){
	HD44780_E_SET();	
	HD44780_ms(1);
	HD44780_E_CLR();
	HD44780_ms(1);	
}

/**/
void HD44780_WRITE_4bits(char data){

if(data & 0x80)	HAL_GPIO_WritePin(HD44780_DATA, HD44780_D7, GPIO_PIN_SET);
else HAL_GPIO_WritePin(HD44780_DATA, HD44780_D7, GPIO_PIN_RESET);

if(data & 0x40)	HAL_GPIO_WritePin(HD44780_DATA, HD44780_D6, GPIO_PIN_SET);
else HAL_GPIO_WritePin(HD44780_DATA, HD44780_D6, GPIO_PIN_RESET);

if(data & 0x20)	HAL_GPIO_WritePin(HD44780_DATA, HD44780_D5, GPIO_PIN_SET);
else HAL_GPIO_WritePin(HD44780_DATA, HD44780_D5, GPIO_PIN_RESET);
	
if(data & 0x10)	HAL_GPIO_WritePin(HD44780_DATA, HD44780_D4, GPIO_PIN_SET);
else HAL_GPIO_WritePin(HD44780_DATA, HD44780_D4, GPIO_PIN_RESET);
	
}

/**/
void HD44780_Send8bitsIn4bitMode (unsigned short int data){
	//upper 4 bits
	HD44780_E_SET();	
	HD44780_WRITE_4bits(data);
	HD44780_ms(1);
	HD44780_E_CLR();
	HD44780_ms(1);

	//lower 4 bits
	HD44780_E_SET();	
	HD44780_WRITE_4bits(data << 4);
	HD44780_ms(1);
	HD44780_E_CLR();
	HD44780_ms(1);
	
}

/**/
void HD44780_SendInstruction(unsigned short int data){
	HD44780_RS_CLR();
	HD44780_Send8bitsIn4bitMode(data);	
}

/**/
void HD44780_SendData(unsigned short int data){
	HD44780_RS_SET();
	HD44780_Send8bitsIn4bitMode(data);		
}

/**/
void HD44780_Clear(void){
	HD44780_SendInstruction(HD44780_DISP_CLEAR);
	HD44780_ms(5);
}

/**/
void HD44780_ReturnHome(void){
	HD44780_SendInstruction(HD44780_RETURN_HOME);
}

/**/
void HD44780_SetXY(int x,int y){
	if(x)x=10;
	switch(y){
		case 0:
			HD44780_SendInstruction(HD44780_POSITION | (HD44780_ROW1_START + x));
			break;
		case 1:
			HD44780_SendInstruction(HD44780_POSITION | (HD44780_ROW2_START + x));
			break;
		case 2:
			HD44780_SendInstruction(HD44780_POSITION | (HD44780_ROW1_START + 20 + x));
			break;
		case 3:
			HD44780_SendInstruction(HD44780_POSITION | (HD44780_ROW2_START + 20 + x));
	}			
}

/**/
void HD44780_Text(char *ptr){
	unsigned char i;
	i = 0;
	while(ptr[i]){
		HD44780_SendData(ptr[i]);
		i++;
	}
	
}

/**/
void HD44780_DisplayOn(void){
HD44780_SendInstruction(HD44780_DISP_ON);
}

/**/
void HD44780_DisplayOff(void){
HD44780_SendInstruction(HD44780_DISP_OFF);
}

/**/
void HD44780_Init(void){
	
	HD44780_PORT_CONTROL();
	HD44780_PORTDATA_OUT();	

	HD44780_RS_CLR();
	HD44780_E_CLR();
	HD44780_ms(16);
	
	HD44780_SendInstruction(HD44780_INIT_SEQ);
	HD44780_ms(5);	
	HD44780_PulseE();
	HD44780_ms(1);

	HD44780_PulseE();
	HD44780_ms(1);

	HD44780_SendInstruction(HD44780_4BIT_MODE);
	HD44780_PulseE();
	HD44780_ms(1);
	
	HD44780_SendInstruction(HD44780_4BIT_MODE | HD44780_2_ROWS | HD44780_FONT_5x8);
	HD44780_SendInstruction(HD44780_DISP_OFF);
	HD44780_SendInstruction(HD44780_DISP_CLEAR);
	HD44780_SendInstruction(HD44780_ENTRY_MODE);
	HD44780_SendInstruction(HD44780_DISP_ON);	
	HD44780_ms(5);

}

/*end*/
