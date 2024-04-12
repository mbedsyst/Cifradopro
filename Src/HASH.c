#include "HASH.h"

void HASH_WriteData();
void HASH_ReadDigest();

void HASH_Init(void)
{
	// Disable Clock gate to HASH Processor
	RCC->AHB2ENR |= RCC_AHB2ENR_HASHEN;
	while(!(RCC->AHB2ENR & RCC_AHB2ENR_HASHEN));
}
void HASH_DeInit()
{
	// Enable Clock gate to HASH Processor
	RCC->AHB2ENR &= ~(RCC_AHB2ENR_HASHEN);
}

void HASH_WriteData(uint8_t *input_data)
{
	// Counter for calculating size and as a Control Variable
    uint32_t i = 0;
    // Calculate size of data
    while (input_data[i] != '\0')
    {
        i++;
    }
	// Calculate the number of 512-bit blocks
	uint32_t NumBlocks = i / 64;
	// Input whole blocks of data
	for (uint32_t block = 0; block < NumBlocks; block++)
	{
		// Input 16 words to the HASH Core
		for (i = 0; i < 64; i += 4)
		{
			// Store input data to Temporary variable
			uint32_t data = (input_data[block * 64 + i] << 24) |
	                        (input_data[block * 64 + i + 1] << 16) |
	                        (input_data[block * 64 + i + 2] << 8) |
	                        (input_data[block * 64 + i + 3]);
			// Write 32-bit data to the HASH_DIN register
	        HASH->DIN = data;
	    }
		// Wait for FIFO to be empty after entering 16 words
		while(!(HASH->SR & HASH_SR_DINIS));
	}
}

void HASH_ReadDigest(uint8_t size)
{
	uint32_t data;
	uint8_t sbuf[100];
	switch(size)
	{
		case '4':
			UART_Tx_String("SHA-1 Digest: \r\n");
			for(uint8_t i = 0; i < 4; i++)
			{
				data = HASH->HR[i];
				for (uint8_t j = 0; j < 4; j++)
				{
					sprintf(sbuf, "%c", (data >> (8 * j)) & 0xFF);
					UART_Tx_String(sbuf);
				}
			}
			UART_Tx_String("\n\r");
			break;

		case '5':
			UART_Tx_String("MD5 Digest: \r\n");
			for(uint8_t i = 0; i < 5; i++)
			{
				data = HASH->HR[i];
				for (uint8_t j = 0; j < 4; j++)
				{
					sprintf(sbuf, "%c", (data >> (8 * j)) & 0xFF);
					UART_Tx_String(sbuf);

				}
			}
			UART_Tx_String("\n\r");
			break;

		case '7':
			UART_Tx_String("SHA-224 Digest: \r\n");
			for(uint8_t i = 0; i < 7; i++)
			{
				data = HASH->HR[i];
				for (uint8_t j = 0; j < 4; j++)
				{
					sprintf(sbuf, "%c", (data >> (8 * j)) & 0xFF);
					UART_Tx_String(sbuf);
				}
			}
			UART_Tx_String("\n\r");
			break;

		case '8':
			UART_Tx_String("SHA-256 Digest: \r\n");
			for(uint8_t i = 0; i < 8; i++)
			{
				data = HASH->HR[i];
				for (uint8_t j = 0; j < 4; j++)
				{
					sprintf(sbuf, "%c", (data >> (8 * j)) & 0xFF);
					UART_Tx_String(sbuf);
				}
			}
			UART_Tx_String("\n\r");
			break;
	}
}

void HASH_MD5(uint8_t *Input)
{
	// Set MD5 as Algorithm
	HASH->CR &= ~((0x01<<7) | (0x01<<18));
	HASH->CR |= (0x01<<7);
	// Set Mode to Hash Mode
	HASH->CR &= ~(0x01<<6);
	// Set Datatype as Byte
	HASH->CR |= (0x02<<4);
	// Set No. of Valid Bits in Last Word
	HASH->STR &= ~(0x1F<<0);
	// Initializa Message Digest Calculation
	HASH->CR |= (0x01<<2);
	// Write the Data to Data Input Register
	HASH_WriteData(Input);
	// Start final Digest Calculation
	HASH->STR |= HASH_STR_DCAL;
	// Wait for Digest Calculation to Complete
	while(!(HASH->SR & HASH_SR_DCIS));
	// Read Hash Digest Registers
	HASH_ReadDigest(4);
}

void HASH_SHA1(uint8_t *Input)
{
	// Set SHA-1 as Algorithm
	HASH->CR &= ~((0x01<<7) | (0x01<<18));
	// Set Mode to Hash Mode
	HASH->CR &= ~(0x01<<6);
	// Set Datatype as Byte
	HASH->CR |= (0x02<<4);
	// Set No. of Valid Bits in Last Word
	HASH->STR &= ~(0x1F<<0);
	// Initializa Message Digest Calculation
	HASH->CR |= (0x01<<2);
	// Write the Data to Data Input Register
	HASH_WriteData(Input);
	// Start final Digest Calculation
	HASH->STR |= HASH_STR_DCAL;
	// Wait for Digest Calculation to Complete
	while(!(HASH->SR & HASH_SR_DCIS));
	// Read Hash Digest Registers
	HASH_ReadDigest(5);
}

void HASH_SHA224(uint8_t *Input)
{
	// Set SHA-224 as Algorithm
	HASH->CR &= ~((0x01<<7) | (0x01<<18));
	HASH->CR |= (0x01<<18);
	// Set Mode to Hash Mode
	HASH->CR &= ~(0x01<<6);
	// Set Datatype as Byte
	HASH->CR |= (0x02<<4);
	// Set No. of Valid Bits in Last Word
	HASH->STR &= ~(0x1F<<0);
	// Initialize Message Digest Calculation
	HASH->CR |= (0x01<<2);
	// Write the Data to Data Input Register
	HASH_WriteData(Input);
	// Start final Digest Calculation
	HASH->STR |= HASH_STR_DCAL;
	// Wait for Digest Calculation to Complete
	while(!(HASH->SR & HASH_SR_DCIS));
	// Read Hash Digest Registers
	HASH_ReadDigest(7);
}

void HASH_SHA256(uint8_t *Input)
{
	// Set SHA-256 as Algorithm
	HASH->CR &= ~((0x01<<7) | (0x01<<18));
	HASH->CR |=  ((0x01<<7) | (0x01<<18));
	// Set Mode to Hash Mode
	HASH->CR &= ~(0x01<<6);
	// Set Datatype as Byte
	HASH->CR |= (0x02<<4);
	// Set No. of Valid Bits in Last Word
	HASH->STR &= ~(0x1F<<0);
	// Initialize Message Digest Calculation
	HASH->CR |= (0x01<<2);
	// Write the Data to Data Input Register
	HASH_WriteData(Input);
	// Start final Digest Calculation
	HASH->STR |= HASH_STR_DCAL;
	// Wait for Digest Calculation to Complete
	while(!(HASH->SR & HASH_SR_DCIS));
	// Read Hash Digest Registers
	HASH_ReadDigest(8);
}

void HASH_HMAC(uint8_t *Input, uint8_t *Key)
{
	// Set MODE to HMAC Operation
	HASH->CR |= HASH_CR_MODE;
	// Set Keysize to 64 bytes
	HASH->CR &= ~(HASH_CR_LKEY);
	// Set SHA-256 as Algorithm
	HASH->CR &= ~((0x01<<7) | (0x01<<18));
	HASH->CR |=  ((0x01<<7) | (0x01<<18));
	// Set No. of Valid Bits in Last Word
	HASH->STR &= ~(0x1F<<0);
	// Set the INIT bit
	HASH->CR |= HASH_CR_INIT;
	// Write Key into HASH_DIN
	HASH_WriteData(Key);
	// Set DCAL bit
	HASH->STR |= HASH_STR_DCAL;
	// Wait for DINIS to be set
	while(!(HASH->SR & HASH_SR_DINIS));
	// Write Message into HASH_DIN
	HASH_WriteData(Input);
	// Set No. of Valid Bits in Last Word
	HASH->STR &= ~(0x1F<<0);
	// Set DCAL bit
	HASH->STR |= HASH_STR_DCAL;
	// Wait for DINIS to be set
	while(!(HASH->SR & HASH_SR_DINIS));
	// Write Key into HASH_DIN
	HASH_WriteData(Key);
	// Set No. of Valid Bits in Last Word
	HASH->STR &= ~(0x1F<<0);
	// Set DCAL bit
	HASH->STR |= HASH_STR_DCAL;
	// Wait for Digest Calculation to Complete
	while(!(HASH->SR & HASH_SR_DCIS));
	// Read Message Digest
	HASH_ReadDigest(8);
}
