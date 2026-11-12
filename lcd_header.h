#include<lpc21xx.h>
#include<string.h>
#define lcd_d 0x0f<<23
#define RS 1<<27
#define E 1<<28

void LCD_INIT(void);
void LCD_COMMAND(unsigned char);
void LCD_DATA(unsigned char);
void LCD_STR(char *);
void delay_ms(unsigned int);

void LCD_INIT(void)
{
	IODIR1 = lcd_d|RS|E;
	LCD_COMMAND(0X01);
	LCD_COMMAND(0X02);
	LCD_COMMAND(0X0C);
	LCD_COMMAND(0X28);
}
void LCD_COMMAND(unsigned char cmd)
{
	IOCLR1 = lcd_d;
	IOSET1 = (cmd&0XF0)<<19;
	IOCLR1 = RS;
	IOSET1 = E;
	delay_ms(2);
	IOCLR1 = E;
	
	IOCLR1 = lcd_d;
	IOSET1 = (cmd&0X0F)<<23;
	IOCLR1 = RS;
	IOSET1 = E;
	delay_ms(2);
	IOCLR1 = E;		
}
void LCD_DATA(unsigned char d)
{
    IOCLR1 = lcd_d;
	IOSET1 = (d&0XF0)<<19;
	IOSET1 = RS;
	IOSET1 = E;
	delay_ms(2);
	IOCLR1 = E;
	
	IOCLR1 = lcd_d;
	IOSET1 = (d&0X0F)<<23;
	IOSET1 = RS;
	IOSET1 = E;
	delay_ms(2);
	IOCLR1 = E;
}
void LCD_STR(char *str)
{
	int cnt=0;
	while(*str)
	{
		cnt++;
		LCD_DATA(*str++);
		if(cnt==16)
			LCD_COMMAND(0XC0);
	}
}

void delay_ms(unsigned int ms)
{
	T0PR = 15000-1;
	T0TCR = 0X01;
	while(T0TC<ms);
	T0TCR|=0X02;
	T0TCR = 0X00; 
}
