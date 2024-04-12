#ifndef __RNG_H__
#define __RNG_H__

#include "stm32l4s5xx.h"

void RNG_Init(void);
uint32_t RNG_GetRandom(void);
void RNG_GenerateRandom(uint8_t *buf, uint8_t len);

#endif
