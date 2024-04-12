#ifndef __UART_H__
#define __UART_H__

#include "stm32l4r5xx.h"
#include <stdlib.h>

void UART_Init(void);
void UART_Tx(char data);
void UART_Tx_String(char *str);
uint8_t UART_Rx(void);
void UART_RxString(char *str, int len);
uint32_t UART_Rx_Int(void);

#endif
