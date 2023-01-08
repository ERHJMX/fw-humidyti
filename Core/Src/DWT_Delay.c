/*
 * File: DWT_Delay.c
 * Driver Name: [[ DWT Delay ]]
 * SW Layer:   ECUAL
 * Created on: Jun 28, 2020
 * Author:     Khaled Magdy
 * -------------------------------------------
 * For More Information, Tutorials, etc.
 * Visit Website: www.DeepBlueMbedded.com
 *
 */

#include "DWT_Delay.h"

uint32_t DWT_Delay_Init(void){
 return 0;
}
// This Function Provides Delay In Microseconds Using DWT
void DWT_Delay_us(uint32_t au32_microseconds)
{
	for(uint32_t t=0;t<au32_microseconds;t++){
		for(char x=0;x<47;x++){}
	}
}

// This Function Provides Delay In Milliseconds Using DWT
void DWT_Delay_ms(volatile uint32_t au32_milliseconds)
{
  HAL_Delay(au32_milliseconds);
}
