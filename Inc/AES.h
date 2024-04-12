#ifndef	__AES_H__
#define	__AES_H__

#include "stm32l4s5xx.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

void AES_Init();
void AES_DeInit();
void AES_ECB_Encrypt(uint8_t *Key, uint8_t *input, uint8_t *output);
void AES_ECB_Decrypt(uint8_t *Key, uint8_t *input, uint8_t *output);
void AES_CBC_Encrypt(uint8_t *Key, uint8_t *IV, uint8_t *input, uint8_t *output);
void AES_CBC_Decrypt(uint8_t *Key, uint8_t *IV, uint8_t *input, uint8_t *output);
void AES_CTR_Encrypt(uint8_t *Key, uint8_t *IV, uint8_t *input, uint8_t *output);
void AES_CTR_Decrypt(uint8_t *Key, uint8_t *IV, uint8_t *input, uint8_t *output);
1
#endif
