#include "UART.h"

/* USART2_TX - PD5
 * USART2_RX - PD6*/

void UART_Init(void)
{
	RCC->APB1ENR1	|= RCC_APB1ENR1_USART2EN;
	GPIOD->MODER	&= ~((0x03<<10) | (0x03<<12));
	GPIOD->MODER	|= 	((0x02<<10) | (0x02<<12));
	GPIOD->AFR[0]	|=	((0x07<<20) | (0x07<<24));
	USART2->CR1	&=	~((1U<<28) | (1U<<12));
	USART2->CR2	&=	~(0x03<<12);
	USART2->CR1 |=	(0x01<<0);
	USART2->CR1	|=	(0x01<<3);
}

void UART_Tx(char data)
{
	while(!(USART2->ISR & (1<<7)));
	USART2->TDR = data;
}

void UART_Tx_String(char *str)
{
	while (*str)
	{
		UART_Tx(*str++);
	}
}

uint8_t UART_Rx(void)
{
    while(!(USART2->ISR & (1<<5)));
    return (char)(USART2->RDR & 0xFF);
}
void UART_Rx_String(char *str, int len)
{
    int index = 0;
    uint8_t c;
    do
    {
        c = UART_Rx(); // Read a single character from UART
        if (c != '\0')
        {
            str[index++] = c;
        }
    } while (c != '\n' && c != '\r' && index < len - 1);
    str[index] = '\0';
}

uint32_t UART_Rx_Int(void)
{
    char buffer[10];
    UART_Rx_String(buffer, sizeof(buffer));
    return atoi(buffer);
}
