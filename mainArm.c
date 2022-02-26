#include "LPC214x.h"                        
#include "all.h"

extern DWORD UART0Count;
extern BYTE UART0Buffer[BUFSIZE];
extern DWORD UART1Count;
extern BYTE UART1Buffer[BUFSIZE];
#define UART0_HOST_BAUD  9600
#define UART1_HOST_BAUD  9600

#define IR_1 (1 << 16)
#define IR_2 (1 << 17)
#define IR_3 (1 << 18)
#define IR_4 (1 << 19)
#define IR_5 (1 << 20)
#define IR_6 (1 << 21)
#define LDR  (1 << 12)

unsigned int i;
int ir1=0;
int ir2=0;
int ir3=0;

int one=0;
int two=0;
int three=0;


unsigned char buff1[10],buff2[10],buff3[10],buff4[3],buff5[3],buff6[10];

float speed1=0.0,speed2=0.0,speed3=0.0;

void lcd_put(char *p)
{
	while(*p) // Point to character	 1

	{
		lcd_data_write(*p++);   // Send character then point to next character
	}
}

int main (void)
{
	IO1DIR &= ~(IR_1 | IR_2 | IR_3 | IR_4 |IR_5 | IR_6);
	IO0DIR &= ~LDR;
	init_lcd();
	uart0_init();
	uart1_init();
	init_VIC();
	clear();
	UARTInit(UART0,UART_BAUD(UART0_HOST_BAUD));
	clear();
	lcd_putstring(0,0,"VEHICLE TO VEHICLE");
	lcd_putstring(1,1,"COMMUNICATION ");
	delay(5000);
	intWIFI();
	
	while (1) 
	 {
		if((IO0PIN&LDR))
		{
	    clear();
	    lcd_putstring(0,0,"ACCIDENT AT HUB");
    	delay(5000);
	
		
				WIFIPutSSerial("AT+CIPSEND=0,20\r\n"); // MULTIPLE MODE SELECTION 
				delay(500);
				WIFIPutSSerial("ACCIDENT AT HUB      "); 
				delay(500);  
				WIFIPutSSerial("\n\r\r"); // 
				delay(1000);		
		
		}
	
		if(!(IO1PIN&IR_1))
		{
			ir1=1;
		}
		if(!(IO1PIN&IR_3))
		{
			ir2=1;
		}
		if(!(IO1PIN&IR_5))
		{
			ir3=1;
		}
		
		if(ir1==1)
		{
			one++;
			delay(2000);
			clear();
			sprintf(buff1,"%d",one);
			clear();
			lcd_command_write(0x80);
			lcd_put(buff1);
		}
		if(ir2==1)
		{
			two++;
			delay(1000);
			sprintf(buff2,"%d",two);
			lcd_command_write(0x85);
			lcd_put(buff2);
		} 
		if(ir3==1)
		{
			three++;
			delay(1000);
			sprintf(buff3,"%d",three);
			lcd_command_write(0x8A);
			lcd_put(buff3);
		}
		
		if(!(IO1PIN&IR_2))
		{
			ir1=0;
			speed1=((1.5)/(one));
			sprintf(buff4,"%.2fm/s",speed1);
			clear();
			lcd_putstring(0,2,"vehicle One");
			lcd_putstring(1,0,"Speed:");
			lcd_putstring(1,6,buff4);
			one=0;
			UARTSend(UART0,"B",1);
			delay(5000);
			WIFIPutSSerial("AT+CIPSEND=0,22\r\n"); // MULTIPLE MODE SELECTION 
				delay(500);
				WIFIPutSSerial("ROAD ONE VEHCILE FAST      "); 
				delay(500);  
				WIFIPutSSerial("\n\r\r"); // 
				delay(1000);
		}
		
		if(!(IO1PIN&IR_4))
		{
			ir2=0;
			speed2=((1.5)/(two));
			sprintf(buff5,"%.2fm/s",speed2);
			clear();
			lcd_putstring(0,2,"vehicle Two");
			lcd_putstring(1,0,"Speed:");
			lcd_putstring(1,6,buff5);
			two=0;
			UARTSend(UART0,"C",1);
			delay(5000);
			WIFIPutSSerial("AT+CIPSEND=0,22\r\n"); // MULTIPLE MODE SELECTION 
				delay(500);
				WIFIPutSSerial("ROAD TWO VEHICLE FAST         "); 
				delay(500);  
				WIFIPutSSerial("\n\r\r"); // 
				delay(1000);
		}
			if(!(IO1PIN&IR_6))
		{
			ir3=0;
			speed3=((1.5)/(three));
			sprintf(buff6,"%.2fm/s",speed3);
			clear();
			lcd_putstring(0,2,"vehicle Three");
			lcd_putstring(1,0,"Speed:");
			lcd_putstring(1,6,buff6);
			three=0;
			UARTSend(UART0,"D",1);
			delay(5000);
			WIFIPutSSerial("AT+CIPSEND=0,23\r\n"); // MULTIPLE MODE SELECTION 
				delay(500);
				WIFIPutSSerial("ROAD THREE VEHCILE FAST       "); 
				delay(500);  
			
				WIFIPutSSerial("\n\r\r"); // 
				delay(1000);
		}		
	}
}



