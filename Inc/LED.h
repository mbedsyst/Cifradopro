#ifndef __LED_H__
#define __LED_H__

#include "stm32l4r5xx.h"

void LED_Init(void);
void LED1_ON(void);
void LED2_ON(void);
void LED3_ON(void);
void LED1_OFF(void);
void LED2_OFF(void);
void LED3_OFF(void);
void LED_ON(void);
void LED_OFF(void);
void LED1_TOGGLE(void);
void LED2_TOGGLE(void);
void LED3_TOGGLE(void);

#endif
