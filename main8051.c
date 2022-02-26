#include<reg51.h>
#include<stdio.h>
#include <string.h>
#include"serial.h"
#include"stdlib.h"
#include"delay.h"
#include"lcd.h"
sbit sw1=P0^0;
sbit sw2=P0^1;
sbit sw3=P0^2;

unsigned char card_id[12];
unsigned char current_byte = 0;
unsigned char BUFF[20];
int i=0;

unsigned char temp;

void ser_intr(void)interrupt 4           //Subroutine for Interrupt
 {
 	if(RI == 1)
	{
	   	temp = SBUF;	 
	 	RI = 0;
	}
	
	if(TI == 0)
	{
	 	TI =0;
	}
 }

void main(void)
{
	intLcd();
	putCLcdC(0X83);
	putSLcd("AMBULANCE");
	delay_ms(1000);
	TMOD=0x20;                                //Choosing Timer mode
	TH1=0xFD;                                   //Selecting Baud Rate
	SCON=0x50;                               //Serial mode selection
	TR1=1;
	IE=0x93;                                      //Enabling Serial Interrupt
	
	while(1)
	{
		putCSerial('A');
		delay_ms(50);
		putCLcdC(0X01);	
		putCLcdC(0Xc5);
		putSLcd("GREEN");
		delay_ms(1000);
		break;
	}
}