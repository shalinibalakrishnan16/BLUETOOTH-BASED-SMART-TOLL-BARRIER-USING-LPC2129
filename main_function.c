#include<lpc21xx.h>
#include"lcd_header.h"
#include"bluetooth_header.h"
#include"servo_motor.h"
#define led1 1<<10
void PROJECT_INIT(void);
char *gate;
char *open="open";
char *close="close";

void EXT_INT0_isr(void)__irq
{
	
	LCD_STR("SOMEONE IS DETECTED");	
	str_tx("SOMEONE IS DETECTED\n");
	LCD_COMMAND(0X01);
	LCD_COMMAND(0X80);
	LCD_STR("GATE: OPEN (or) CLOSE : ");
	str_tx("GATE: OPEN (or) CLOSE\n");
	gate = str_rx();
	LCD_COMMAND(0X01);
	LCD_STR(gate);
	delay_ms(1000);

	if(strcmp(gate,open)==0)
	{
		IOCLR0 = led1;
		
		PWM_90deg();
		str_tx("GATE OPENED\n");
		LCD_COMMAND(0X01);
		LCD_COMMAND(0X80);
		LCD_STR("GATE OPENED");	
			
	}
	if(strcmp(gate,close)==0)
	{
		IOSET0 = led1;
		
		PWM_0deg();
		str_tx("GATE closed\n");
		LCD_COMMAND(0X01);
		LCD_COMMAND(0X80);
		LCD_STR("GATE closeD");		
	}
	EXTINT = 0X01;
	VICVectAddr = 0;
}
int main()
{
	int cnt = 0;
	config_uart0();
	LCD_INIT();
	PROJECT_INIT();
	PWM_INIT();
	PINSEL1|=1<<0;//SELECT P0.16 CONFIGURED AS EINT0 PIN
	IODIR0|= led1;
	IOSET0 = led1;



	//All are selected as IRQ
	VICIntSelect = 0X00000000;

	//allocate slot0 for EINT0
	VICVectCntl0 = (1<<5)|14;
	VICVectAddr0 = (int)EXT_INT0_isr;

	//falling edge triggered mode
	EXTMODE = 0X01;
	EXTPOLAR = 0X00;

	//To enable external interrupt0 and external interuupt 1
	VICIntEnable = (1<<14);

	while(1)
	{
		cnt++;
	}
}
void PROJECT_INIT(void)
{
	char project_name[40]="TITLE : SMART TOLL BARRIER"; 	
	
	LCD_COMMAND(0X80);
	LCD_STR(project_name);
	delay_ms(5000);
	LCD_COMMAND(0X01);
	LCD_COMMAND(0X80);	
}

