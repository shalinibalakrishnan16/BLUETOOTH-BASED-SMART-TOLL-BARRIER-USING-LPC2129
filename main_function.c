#include<lpc21xx.h>
#include"lcd_header.h"
#include"bluetooth_header.h"
#include"servo_motor.h"
#define led1 (1<<10)
void PROJECT_INIT(void);
char *gate;
char *cmd_open="open";
char *cmd_close="close";

void EXT_INT0_isr(void)__irq
{
	LCD_COMMAND(0X01);
	LCD_COMMAND(0X80);
	LCD_STR("VEHICLE FOUND");
	str_tx("VEHICLE IS DETECTED\r\n");
	delay_ms(1000);

	LCD_COMMAND(0X01);
	LCD_COMMAND(0X80);
	LCD_STR("OPEN or CLOSE ?");
	str_tx("GATE: OPEN or CLOSE\r\n");

	gate = str_rx();          

	LCD_COMMAND(0X01);
	LCD_COMMAND(0X80);
	LCD_STR(gate);
	delay_ms(1000);

	if(strcmp(gate,cmd_open)==0)
	{
		IOCLR0 = led1;
		PWM_90deg();
		str_tx("GATE OPENED\r\n");
		LCD_COMMAND(0X01);
		LCD_COMMAND(0X80);
		LCD_STR("GATE OPENED");
	}
	else if(strcmp(gate,cmd_close)==0)
	{
		IOSET0 = led1;
		PWM_0deg();
		str_tx("GATE CLOSED\r\n");
		LCD_COMMAND(0X01);
		LCD_COMMAND(0X80);
		LCD_STR("GATE CLOSED");
	}
	else
	{
		str_tx("INVALID COMMAND\r\n");
		LCD_COMMAND(0X01);
		LCD_COMMAND(0X80);
		LCD_STR("INVALID CMD");
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
	PINSEL1|=1<<0;            
	IODIR0|= led1;            
	IOSET0 = led1;            

	VICIntSelect = 0X00000000;

	VICVectCntl0 = (1<<5)|14;
	VICVectAddr0 = (int)EXT_INT0_isr;

	EXTMODE = 0X01;
	EXTPOLAR = 0X00;

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

