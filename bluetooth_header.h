#include<LPC21xx.h>
void config_uart0(void); 
void tx_uart0(char);
char rx_uart(void);
char *str_rx(void);
void str_tx(char*);
char str[20];
void config_uart0(void)
{
	PINSEL0=0X05;
	U0LCR=0X83;
	U0DLL=97;
	U0DLM=0;
	U0LCR=0X03;
}
void tx_uart0(char ch)
{
	while((U0LSR>>5)&1==0);
	U0THR=ch;
}
char rx_uart(void)
{
	while((U0LSR&0X01)==0);
	return U0RBR;
}
char *str_rx(void)
{
    char rxbyte;
    unsigned int i=0;

    do
    {
        rxbyte=rx_uart();
    }while(rxbyte=='\r' || rxbyte=='\n');

    while(1)
    {
        if(rxbyte=='\r' || rxbyte=='\n')
        {
            break;
        }

        if(i<sizeof(str)-1)
        {
            str[i++]=rxbyte;
        }
		 rxbyte=rx_uart();
    }

    str[i]='\0';

    return str;
}

void str_tx(char*str)
{
	while(*str){
	tx_uart0(*str++);
}
}

