/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <string.h>

#include "bsp_hd44780.h"
#include "bsp_lcd20x4.h"

char sLCD20X4RAM[4][22];
char sLCD20X4RAM_BUFFER[4][22];

char sLCD20X4RAMCELL[2][4][22];
char sLCD20X4RAMCELL_BUFFER[2][4][22];


int iAlerta = 0;
int iBlink = 0;	

/**/
void vLCD20x4_ClearAll(void){
	HD44780_Clear();	
	memset(sLCD20X4RAM_BUFFER,0,sizeof(sLCD20X4RAM_BUFFER));
	memset(sLCD20X4RAMCELL_BUFFER,0,sizeof(sLCD20X4RAMCELL_BUFFER));
}

/**/
void vLCD20x4_ClearRows(void){
	HD44780_Clear();		
	memset(sLCD20X4RAM_BUFFER,0,sizeof(sLCD20X4RAM_BUFFER));
}

/**/
void vLCD20x4_ClearCells(void){
	HD44780_Clear();	
	memset(sLCD20X4RAMCELL_BUFFER,0,sizeof(sLCD20X4RAMCELL_BUFFER));
}

/**/
void vLCD20x4_SetXY(int x,int y){
	if(x>=20 || y>=4){x=0;y=0;}
	
	HD44780_SetXY(x,y);
}

/**/
void vLCD20x4_Text(char *ptr){
	if(*ptr==0)return;		
	HD44780_Text(ptr);
}

/**/
void vLCD20x4_Row(int row,char *ptr){
	if(strlen(ptr)>20)return;
	memset(sLCD20X4RAM[row],0,sizeof(sLCD20X4RAM[row]));
	strcpy(sLCD20X4RAM[row],ptr);
}

/**/
void vLCD20x4_Cell(int col, int row,char *ptr){
	if(strlen(ptr)>10)return;
	memset(sLCD20X4RAMCELL[col][row],0,sizeof(sLCD20X4RAMCELL[col][row]));
	strcpy(sLCD20X4RAMCELL[col][row],ptr);
}

/**/
void vLCD20x4_BlinkRow(int row){
if(row==0 || row>4)return;
	row--;
	if(iBlink==0){    
		vLCD20x4_SetXY(0,row);
		vLCD20x4_Text("                    ");
		iBlink = 1;
	}
	else{
		vLCD20x4_SetXY(0,row);
		vLCD20x4_Text(sLCD20X4RAM_BUFFER[row]);		
		iBlink = 0;
	}
}

/**/
void vLCD20x4_MessageStatic(char *ptr1,char *ptr2,char *ptr3,char *ptr4){	
	
	HD44780_Clear();	
	if(strlen(ptr1)>0){
		vLCD20x4_SetXY(0,0);
		vLCD20x4_Text(ptr1);
	}
	if(strlen(ptr2)>0){
		vLCD20x4_SetXY(0,1);
		vLCD20x4_Text(ptr2);
	}
	if(strlen(ptr3)>0){
		vLCD20x4_SetXY(0,2);
		vLCD20x4_Text(ptr3);
	}
	if(strlen(ptr4)>0){
		vLCD20x4_SetXY(0,3);
		vLCD20x4_Text(ptr4);
	}		
}

/**/
void vLCD20x4_Message(char *ptr1,char *ptr2,char *ptr3,char *ptr4){	
	
	HD44780_Clear();	
	if(strlen(ptr1)>0){
		vLCD20x4_SetXY(0,0);
		vLCD20x4_Text(ptr1);
	}
	if(strlen(ptr2)>0){
		vLCD20x4_SetXY(0,1);
		vLCD20x4_Text(ptr2);
	}
	if(strlen(ptr3)>0){
		vLCD20x4_SetXY(0,2);
		vLCD20x4_Text(ptr3);
	}
	if(strlen(ptr4)>0){
		vLCD20x4_SetXY(0,3);
		vLCD20x4_Text(ptr4);
	}		
	HAL_Delay(4000);

	HD44780_Clear();
	vLCD20x4_SetXY(0,0);
	vLCD20x4_Text(sLCD20X4RAM_BUFFER[0]);
	vLCD20x4_SetXY(0,1);
	vLCD20x4_Text(sLCD20X4RAM_BUFFER[1]);
	vLCD20x4_SetXY(0,2);
	vLCD20x4_Text(sLCD20X4RAM_BUFFER[2]);
	vLCD20x4_SetXY(0,3);
	vLCD20x4_Text(sLCD20X4RAM_BUFFER[3]);
	
}

/**/
void vLCD20x4_AlarmOn(char *ptr1,char *ptr2,char *ptr3,char *ptr4){	
	HD44780_Clear();		
	if(strlen(ptr1)>0){
		vLCD20x4_SetXY(0,0);
		vLCD20x4_Text(ptr1);
	}
	if(strlen(ptr2)>0){
		vLCD20x4_SetXY(0,1);
		vLCD20x4_Text(ptr2);
	}
	if(strlen(ptr3)>0){
		vLCD20x4_SetXY(0,2);
		vLCD20x4_Text(ptr3);
	}
	if(strlen(ptr4)>0){
		vLCD20x4_SetXY(0,3);
		vLCD20x4_Text(ptr4);
	}			
	iAlerta = ALERTA_ON;
}

/**/
void vLCD20x4_AlarmOff(void){	
	iAlerta = ALERTA_OFF;
	HD44780_Clear();
	vLCD20x4_SetXY(0,0);
	vLCD20x4_Text(sLCD20X4RAM_BUFFER[0]);
	vLCD20x4_SetXY(0,1);
	vLCD20x4_Text(sLCD20X4RAM_BUFFER[1]);
	vLCD20x4_SetXY(0,2);
	vLCD20x4_Text(sLCD20X4RAM_BUFFER[2]);
	vLCD20x4_SetXY(0,3);
	vLCD20x4_Text(sLCD20X4RAM_BUFFER[3]);	
	HD44780_DisplayOn();
}

/**/
void vLCD20x4_Alarm(void){	
	static int blink = 0;		
	if(blink==0){    
		HD44780_DisplayOff();
		blink = 1;
	}
	else{
		HD44780_DisplayOn();
		blink = 0;
	}
}

/**/
void vLCD20x4_ForceRefreshRow(int row){
	if(row>4 || row<1)return;
	row--;
	vLCD20x4_SetXY(0,row);
	vLCD20x4_Text(sLCD20X4RAM_BUFFER[row]);	
}

/**/
void vLCD20x4_ForceRefreshRows(void){
	char i;	
	for(i=0;i<4;i++){
		vLCD20x4_ForceRefreshRow(i);
	}
}

/**/
void vLCD20x4_RefreshRows(void){
	char i;	
	for(i=0;i<4;i++){
		if(strcmp(sLCD20X4RAM_BUFFER[i],sLCD20X4RAM[i]))
		{
			vLCD20x4_SetXY(0,i);
			vLCD20x4_Text(sLCD20X4RAM[i]);
			strcpy(sLCD20X4RAM_BUFFER[i],sLCD20X4RAM[i]);		
		}	
	}	
}

/**/
void vLCD20x4_RefreshCells(void){
	char x,y;	
	for(y=0;y<4;y++){
		for(x=0;x<2;x++){
			if(strcmp(sLCD20X4RAMCELL_BUFFER[x][y],sLCD20X4RAMCELL[x][y]))
			{
				
				vLCD20x4_SetXY(x,y);
				vLCD20x4_Text(sLCD20X4RAMCELL[x][y]);
				strcpy(sLCD20X4RAMCELL_BUFFER[x][y],sLCD20X4RAMCELL[x][y]);		
			}
		}	
	}	
}
/**/


