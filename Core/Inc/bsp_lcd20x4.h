
#include "stm32f0xx_hal.h"

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __DVR_LCD20x4
#define __DVR_LCD20x4

#define	ALERTA_OFF			0
#define	ALERTA_ON 			1

extern int iAlerta;
extern int iBlink;

void vLCD20x4_ClearAll(void);
void vLCD20x4_ClearRows(void);
void vLCD20x4_ClearCells(void);
void vLCD20x4_Set(int);
void vLCD20x4_SetXY(int,int);
void vLCD20x4_Text(char*);
void vLCD20x4_Row(int,char*);
void vLCD20x4_Cell(int,int,char*);
void vLCD20x4_MessageStatic(char*,char*,char*,char*);
void vLCD20x4_Message(char*,char*,char*,char*);
void vLCD20x4_AlarmOn(char*,char*,char*,char*);
void vLCD20x4_AlarmOff(void);
void vLCD20x4_Alarm(void);
void vLCD20x4_BlinkRow(int);
void vLCD20x4_ForceRefreshRow(int);
void vLCD20x4_ForceRefreshRows(void);
void vLCD20x4_RefreshCells(void);
void vLCD20x4_RefreshRows(void);

#endif
