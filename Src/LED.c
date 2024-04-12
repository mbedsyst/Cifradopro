#include "LED.h"

void LED_Init(void)
{
	RCC->AHB2ENR |= ((1<<1) | (1<<2));
	while(!(RCC->AHB2ENR & ((1<<1) | (1<<2))));
	GPIOB->MODER &= ~((0x03U<<14) | (0x03<<28));
	GPIOC->MODER &= ~(0x03U<<14);
	GPIOB->MODER |=  ((0x01<<14) | (0x01<<28));
	GPIOC->MODER |=  (0x01U<<14);
}
void LED1_ON(void)
{
	GPIOC->BSRR |= (1<<7);
}
void LED2_ON(void)
{
	GPIOB->BSRR |= (1<<7);
}
void LED3_ON(void)
{
	GPIOB->BSRR |= (1<<14);
}
void LED1_OFF(void)
{
	GPIOC->BSRR |= (1<<23);
}
void LED2_OFF(void)
{
	GPIOB->BSRR |= (1<<23);
}
void LED3_OFF(void)
{
	GPIOB->BSRR |= (1<<30);
}
void LED_ON(void)
{
	GPIOC->BSRR |= (1<<7);
	GPIOB->BSRR |= (1<<7);
	GPIOB->BSRR |= (1<<14);
}
void LED_OFF(void)
{
	GPIOC->BSRR |= (1<<23);
	GPIOB->BSRR |= (1<<23);
	GPIOB->BSRR |= (1<<30);
}
