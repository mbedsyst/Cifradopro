#ifndef __HASH_H__
#define __HASH_H__

#include "stm32l4s5xx.h"

void HASH_Init(void);
void HASH_DeInit();

void HASH_MD5(uint8_t *Input);
void HASH_SHA1(uint8_t *Input);
void HASH_SHA224(uint8_t *Input);
void HASH_SHA256(uint8_t *Input);
void HASH_HMAC(uint8_t *Input, uint8_t *Key);

#endif
