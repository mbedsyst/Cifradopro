#include "RNG.h"

void RNG_ClockInit(void)
{
	RCC->CCIPR &= ~(RCC_CCIPR_CLK48SEL);
	RCC->CRRCR |= RCC_CRRCR_HSI48ON;
	while(!(RCC->CRRCR & RCC_CRRCR_HSI48RDY));
}

void RNG_Init(void)
{
	RNG_ClockInit();
	RCC->AHB2ENR |= RCC_AHB2ENR_RNGEN;
	while(!(RCC->AHB2ENR & RCC_AHB2ENR_RNGEN));
	RNG->CR &= ~(RNG_CR_CED);
	RNG->CR |= RNG_CR_RNGEN;
}

uint32_t RNG_GetRandom(void)
{
	uint32_t RNG_Value;
	if(RNG->SR & RNG_SR_SECS)
	{
		UART_Tx_String("RNG: Seed Error Occurred!\n\r");
		return 0;
	}
	if(RNG->SR & RNG_SR_CECS)
	{
		UART_Tx_String("RNG: Clock is too slow for operation!\n\r");
		return 0;
	}
	while(!(RNG->SR & RNG_SR_DRDY));
	if(RNG->DR != 0)
	{
		RNG_Value = RNG->DR;
		return RNG_Value;
	}
	else
	{
		UART_Tx_String("RNG: Data Register is Zero!\n\r");
		return 0;
	}
}

void RNG_GenerateRandom(uint8_t *buf, uint8_t len)
{
	uint8_t i;
	for(i = 0; i < len; i = i + 4)
	{
		*((uint32_t*)(buf + i)) = RNG_GetRandom();
	}
}




















