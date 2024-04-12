#include "AES.h"

void AES_Init()
{
	RCC->AHB2ENR |= RCC_AHB2ENR_AESEN;
	while(!(RCC->AHB2ENR & RCC_AHB2ENR_AESEN));
}

void AES_DeInit()
{
	RCC->AHB2ENR &= ~(RCC_AHB2ENR_AESEN);
}

void AES_WriteKey(uint8_t *Key, uint8_t size)
{
	uint8_t  i, j;
    uint8_t  KeyIndex = 0;
    uint32_t KeyValue = 0;
    // Process 4 bytes at a time. Size is in bytes.
    for (i = 0; i < size - 3; i += 4)
    {
        KeyValue = 0;
        // Convert 4 bytes to a 32-bit integer
        for (j = 0; j < 4; j++)
        {
            KeyValue |= ((uint32_t)Key[i + j]) << (j * 8);
        }
        // Write the 32-bit value to the key register
        switch (KeyIndex)
        {
        	case 0: AES->KEYR0 = KeyValue; break;
        	case 1: AES->KEYR1 = KeyValue; break;
        	case 2: AES->KEYR2 = KeyValue; break;
        	case 3: AES->KEYR3 = KeyValue; break;
        	case 4: AES->KEYR4 = KeyValue; break;
        	case 5: AES->KEYR5 = KeyValue; break;
        	case 6: AES->KEYR6 = KeyValue; break;
        	case 7: AES->KEYR7 = KeyValue; break;
        	default:                       break;
        }
        KeyIndex++;
    }
}
void AES_WriteInitVector(uint8_t *IV, bool Mode)
{
	uint8_t  i;
	bool Mode;
    uint32_t InitValue = 0;
    if(Mode == 0)
    {
    	// Convert 16 bytes to a 128-bit integer
    	for (i = 0; i < 16; i++)
    	{
    		InitValue |= ((uint32_t)IV[i]) << ((i % 4) * 8);
    		// Every 4 bytes, write the 32-bit value to AES_IVR
        	if (i % 4 == 3)
        	{
            	switch (i / 4)
            	{
            		case 0: AES->IVR0 = InitValue; break;
            		case 1: AES->IVR1 = InitValue; break;
            		case 2: AES->IVR2 = InitValue; break;
            		case 3: AES->IVR3 = InitValue; break;
           		 	default:                       break;

            	}
            	InitValue = 0; // Reset the 32-bit value for the next iteration
        	}
    	}
    }
    else
    {
    	// Convert 16 bytes to a 128-bit integer
    	for (i = 0; i < 16; i++)
    	{
    		InitValue |= ((uint32_t)IV[i]) << ((i % 4) * 8);
    		// Every 4 bytes, write the 32-bit value to AES_IVR
        	if (i % 4 == 3)
        	{
            	switch (i / 4)
            	{
            		case 0: AES->IVR3 = InitValue; break;
            		case 1: AES->IVR2 = InitValue; break;
            		case 2: AES->IVR1 = InitValue; break;
            		case 3: AES->IVR0 = InitValue; break;
           		 	default:                       break;

            	}
            	InitValue = 0; // Reset the 32-bit value for the next iteration
        	}
    	}
    }
}

void AES_WriteData(uint8_t *input)
{
	uint8_t  i, j;
    uint32_t data = 0;
    for (i = 0; i < 16; i += 4)
    {
        data = 0;
        // Convert 4 bytes to a 32-bit integer
        for (j = 0; j < 4; j++)
        {
            data |= ((uint32_t)input[i + j]) << (j * 8);
        }
        // Write the 32-bit value to the AES_DINR register
        switch (i / 4)
        {
        	case 0: AES->DINR = data; break;
        	case 1: AES->DINR = data; break;
        	case 2: AES->DINR = data; break;
        	case 3: AES->DINR = data; break;
        	default:                  break;
        }
    }
}

void AES_ReadData(uint8_t *output)
{
	int i, j;
    uint32_t data = 0;
    for (int i = 0; i < 16; i += 4)
    {
        // Read the 32-bit value from the AES_DOUTR register
        switch (i / 4)
        {
        	case 0: data = AES->DOUTR; break;
        	case 1: data = AES->DOUTR; break;
        	case 2: data = AES->DOUTR; break;
        	case 3: data = AES->DOUTR; break;
        	default:                   break;
        }
        // Convert the 32-bit integer to 4 bytes
        for (j = 0; j < 4; j++)
        {
            output[i + j] = (data >> (j * 8)) & 0xFF;
        }
    }
}
void AES_ECB_Encrypt(uint8_t *Key, uint8_t *input, uint8_t *output)
{
	uint8_t sbuf[100];
	// Counter for calculating size and as a Control Variable
    uint32_t i = 0;
    // Calculate size of data to be encrypted
    while (input[i] != '\0')
    {
        i++;
    }
    // Convert Input Array size into AES block size
    uint32_t InputSize = i / 16;
    i = 0;
    // Calculate size of Key used
    while (Key[i] != '\0')
    {
        i++;
    }
    // Make a copy of Key Size
    uint8_t KeySize = i;
	// Disable AES Peripheral
	AES->CR &= ~(AES_CR_EN);
	// Select AES Operating Mode as Encryption
	AES->CR &= ~(0x03<<3);
	// Select AES Chaining Mode as ECB
	AES->CR &= ~((0x03<<5) | (0x01<<16));
	// Select Datatype as byte
	AES->CR |= (0x01<<1);
	// Set Keysize
	if(KeySize == 16)
	{
		AES->CR &= ~(0x01<<18);
	}
	else
	{
		AES->CR |= (0x01<<18);
	}
	// Write the AES Encryption Key
	AES_WriteKey(Key, KeySize);
	// Enable AES Peripheral
	AES->CR |= (AES_CR_EN);
	// Loop through the Input Array in blocks of 16 bytes
	for(i = 0; i < InputSize; i = i + 16)
	{
		// Write Data to AES_DINR register
		AES_WriteData(&input[i*16]);
		// Wait for CCF bit to be set in AES_SR
		while(!(AES->SR & AES_SR_CCF));
		// Read Data from AES_DOUR register
		AES_ReadData(&output[i*16]);
		// Clear CCFC Flag in AES_CR register
		AES->CR |= AES_CR_CCFC;
		// Print Encrypted Data to Terminal
		sprintf(sbuf,"Block %d: ", i/16);
        UART_Tx_String(sbuf);
        for (int j = 0; j < 16; j++)
        {
        	sprintf(sbuf, "%02X ", output[i * 16 + j]);
        	UART_Tx_String(sbuf);
        }
        UART_Tx_String("\r\n");
	}
    // Disable AES Peripheral
	AES->CR &= ~(AES_CR_EN);
}
void AES_ECB_Decrypt(uint8_t *Key, uint8_t *input, uint8_t *output)
{
	uint8_t sbuf[100];
	// Counter for calculating size and as a Control Variable
    uint32_t i = 0;
    // Calculate size of data to be encrypted
    while (input[i] != '\0')
    {
        i++;
    }
    // Convert Input Array size into AES block size
    uint32_t InputSize = i / 16;
    i = 0;
    // Calculate size of Key used
    while (Key[i] != '\0')
    {
        i++;
    }
    // Make a copy of Key Size
    uint8_t KeySize = i;
	// Disable AES Peripheral
	AES->CR &= ~(AES_CR_EN);
	// Set AES Operating Mode as Key Derivation
	AES->CR |= (0x01<<3);
	// Set Keysize
	if(KeySize == 16)
	{
		AES->CR &= ~(0x01<<18);
	}
	else
	{
		AES->CR |= (0x01<<18);
	}
	// Write the AES Decryption Key
	AES_WriteKey(Key, KeySize);
	// Enable AES Peripheral
	AES->CR |= (AES_CR_EN);
	// Wait for CCF bit to be set in AES_SR
	while(!(AES->SR & AES_SR_CCF));
	// Clear CCFC Flag in AES_CR register
	AES->CR |= AES_CR_CCFC;
	// Set AES Operating Mode as Decryption
	AES->CR |= (0x02<<3);
	// Select AES Chaining Mode as ECB
	AES->CR &= ~((0x03<<5) | (0x01<<16));
	// Select Datatype as byte
	AES->CR |= (0x01<<1);
	// Enable AES Peripheral
	AES->CR |= (AES_CR_EN);
	// Loop through the Input Array in blocks of 16 bytes
	for(i = 0; i < InputSize; i = i + 16)
	{
		// Write Data to AES_DINR register
		AES_WriteData(&input[i*16]);
		// Wait for CCF bit to be set in AES_SR
		while(!(AES->SR & AES_SR_CCF));
		// Read Data from AES_DOUR register
		AES_ReadData(&output[i*16]);
		// Clear CCFC Flag in AES_CR register
		AES->CR |= AES_CR_CCFC;
		// Print Decrypted Data to Terminal
		sprintf(sbuf,"Block %d: ", i/16);
        UART_Tx_String(sbuf);
        for (int j = 0; j < 16; j++)
        {
        	sprintf(sbuf, "%02X ", output[i * 16 + j]);
        	UART_Tx_String(sbuf);
        }
        UART_Tx_String("\r\n");
	}
    // Disable AES Peripheral
	AES->CR &= ~(AES_CR_EN);
}

void AES_CBC_Encrypt(uint8_t *Key, uint8_t *IV, uint8_t *input, uint8_t *output)
{
	uint8_t sbuf[100];
	// Counter for calculating size and as a Control Variable
    uint32_t i = 0;
    // Calculate size of data to be encrypted
    while (input[i] != '\0')
    {
        i++;
    }
    // Convert Input Array size into AES block size
    uint32_t InputSize = i / 16;
    i = 0;
    // Calculate size of Key used
    while (Key[i] != '\0')
    {
        i++;
    }
    // Make a copy of Key Size
    uint8_t KeySize = i;
	// Disable AES Peripheral
	AES->CR &= ~(AES_CR_EN);
	// Select AES Operating Mode as Encryption
	AES->CR &= ~(0x03<<3);
	// Select AES Chaining Mode as CBC
	AES->CR &= ~((0x03<<5) | (0x01<<16));
	AES->CR |= (0x01<<5);
	// Select Datatype as byte
	AES->CR |= (0x01<<1);
	// Set Keysize
	if(KeySize == 16)
	{
		AES->CR &= ~(0x01<<18);
	}
	else
	{
		AES->CR |= (0x01<<18);
	}
	// Write the AES Encryption Key
	AES_WriteKey(Key, KeySize);
	// Write the Initialization Vector
	AES_WriteInitVector(IV, 0);
	// Enable AES Peripheral
	AES->CR |= (AES_CR_EN);
	// Loop through the Input Array in blocks of 16 bytes
	for(i = 0; i < InputSize; i = i + 16)
	{
		// Write Data to AES_DINR register
		AES_WriteData(&input[i]);
		// Wait for CCF bit to be set in AES_SR
		while(!(AES->SR & AES_SR_CCF));
		// Read Data from AES_DOUR register
		AES_ReadData(&output[i]);
		// Clear CCFC Flag in AES_CR register
		AES->CR |= AES_CR_CCFC;
		// Print Encrypted Data to Terminal
		sprintf(sbuf,"Block %d: ", i/16);
        UART_Tx_String(sbuf);
        for (int j = 0; j < 16; j++)
        {
        	sprintf(sbuf, "%02X ", output[i * 16 + j]);
        	UART_Tx_String(sbuf);
        }
        UART_Tx_String("\r\n");
	}
	// Disable AES Peripheral
	AES->CR &= ~(AES_CR_EN);
}

void AES_CBC_Decrypt(uint8_t *Key, uint8_t *IV, uint8_t *input, uint8_t *output)
{
	uint8_t sbuf[100];
	// Counter for calculating size and as a Control Variable
    uint32_t i = 0;
    // Calculate size of data to be encrypted
    while (input[i] != '\0')
    {
        i++;
    }
    // Convert Input Array size into AES block size
    uint32_t InputSize = i / 16;
    i = 0;
    // Calculate size of Key used
    while (Key[i] != '\0')
    {
        i++;
    }
    // Make a copy of Key Size
    uint32_t KeySize = i;
	// Disable AES Peripheral
	AES->CR &= ~(AES_CR_EN);
	// Set AES Operating Mode as Key Derivation
	AES->CR |= (0x01<<3);
	// Set Keysize
	if(KeySize == 16)
	{
		AES->CR &= ~(0x01<<18);
	}
	else
	{
		AES->CR |= (0x01<<18);
	}
	// Write the AES Decryption Key
	AES_WriteKey(Key, KeySize);
	// Write the Initialization Vector
	AES_WriteInitVector(IV);
	// Enable AES Peripheral
	AES->CR |= (AES_CR_EN);
	// Wait for CCF bit to be set in AES_SR
	while(!(AES->SR & AES_SR_CCF));
	// Clear CCFC Flag
	AES->CR |= (AES_CR_CCFC);
	// Set AES Operating Mode as Decryption
	AES->CR |= (0x02<<3);
	// Select AES Chaining Mode as CBC
	AES->CR &= ~((0x03<<5) | (0x01<<16));
	AES->CR |= (0x01<<5);
	// Select Datatype as byte
	AES->CR |= (0x01<<1);
	// Write the Initialization Vector
	AES_WriteInitVector(IV, 0);
	// Enable AES Peripheral
	AES->CR |= (AES_CR_EN);
	// Loop through the Input Array in blocks of 16 bytes
	for(i = 0; i < InputSize; i = i + 16)
	{
		// Write Data to AES_DINR register
		AES_WriteData(&input[i]);
		// Wait for CCF bit to be set in AES_SR
		while(!(AES->SR & AES_SR_CCF));
		// Read Data from AES_DOUR register
		AES_ReadData(&output[i]);
		// Clear CCFC Flag in AES_CR register
		AES->CR |= AES_CR_CCFC;
		// Print Encrypted Data to Terminal
		sprintf(sbuf,"Block %d: ", i/16);
        UART_Tx_String(sbuf);
        for (int j = 0; j < 16; j++)
        {
        	sprintf(sbuf, "%02X ", output[i * 16 + j]);
        	UART_Tx_String(sbuf);
        }
        UART_Tx_String("\r\n");
	}
	// Disable AES Peripheral
	AES->CR &= ~(AES_CR_EN);
}

void AES_CTR_Encrypt(uint8_t *Key, uint8_t *IV, uint8_t *input, uint8_t *output)
{
	uint8_t sbuf[100];
	// Counter for calculating size and as a Control Variable
    uint32_t i = 0;
    // Calculate size of data to be encrypted
    while (input[i] != '\0')
    {
        i++;
    }
    // Convert Input Array size into AES block size
    uint32_t InputSize = i / 16;
    i = 0;
    // Calculate size of Key used
    while (Key[i] != '\0')
    {
        i++;
    }
    // Make a copy of Key Size
    uint8_t KeySize = i;
	// Disable AES Peripheral
	AES->CR &= ~(AES_CR_EN);
	// Select AES Chaining Mode as CTR
	AES->CR &= ~((0x03<<5) | (0x01<<16));
	AES->CR |= (0x02<<5);
	// Select AES Operating Mode as Encryption
	AES->CR &= ~(0x03<<3);
	// Set Keysize
	if(KeySize == 16)
	{
		AES->CR &= ~(0x01<<18);
	}
	else
	{
		AES->CR |= (0x01<<18);
	}
	// Write the AES Encryption Key
	AES_WriteKey(Key, KeySize);
	// Write the Initialization Vector in Reverse
	AES_WriteInitVector(IV, 1);
	// Enable AES Peripheral
	AES->CR |= (AES_CR_EN);
	// Loop through the Input Array in blocks of 16 bytes
	for(i = 0; i < InputSize; i = i + 16)
	{
		// Write Data to AES_DINR register
		AES_WriteData(&input[i]);
		// Wait for CCF bit to be set in AES_SR
		while(!(AES->SR & AES_SR_CCF));
		// Read Data from AES_DOUR register
		AES_ReadData(&output[i]);
		// Clear CCFC Flag in AES_CR register
		AES->CR |= AES_CR_CCFC;
		// Print Encrypted Data to Terminal
		sprintf(sbuf,"Block %d: ", i/16);
        UART_Tx_String(sbuf);
        for (int j = 0; j < 16; j++)
        {
        	sprintf(sbuf, "%02X ", output[i * 16 + j]);
        	UART_Tx_String(sbuf);
        }
        UART_Tx_String("\r\n");
	}
	// Disable AES Peripheral
	AES->CR &= ~(AES_CR_EN);
}

void AES_CTR_Decrypt(uint8_t *Key, uint8_t *IV, uint8_t *input, uint8_t *output)
{
	uint8_t sbuf[100];
	// Counter for calculating size and as a Control Variable
    uint32_t i = 0;
    // Calculate size of data to be encrypted
    while (input[i] != '\0')
    {
        i++;
    }
    // Convert Input Array size into AES block size
    uint32_t InputSize = i / 16;
    i = 0;
    // Calculate size of Key used
    while (Key[i] != '\0')
    {
        i++;
    }
    // Make a copy of Key Size
    uint8_t KeySize = i;
	// Disable AES Peripheral
	AES->CR &= ~(AES_CR_EN);
	// Select AES Chaining Mode as CTR
	AES->CR &= ~((0x03<<5) | (0x01<<16));
	AES->CR |= (0x02<<5);
	// Select AES Operating Mode as Decryption
	AES->CR &= ~(0x03<<3);
	AES->CR |= (0x02<<3);
	// Set Keysize
	if(KeySize == 16)
	{
		AES->CR &= ~(0x01<<18);
	}
	else
	{
		AES->CR |= (0x01<<18);
	}
	// Write the AES Key
	AES_WriteKey(Key, KeySize);
	// Write the Initialization Vector in Reverse
	AES_WriteInitVector(IV, 1);
	// Enable AES Peripheral
	AES->CR |= (AES_CR_EN);
	// Loop through the Input Array in blocks of 16 bytes
	for(i = 0; i < InputSize; i = i + 16)
	{
		// Write Data to AES_DINR register
		AES_WriteData(&input[i]);
		// Wait for CCF bit to be set in AES_SR
		while(!(AES->SR & AES_SR_CCF));
		// Read Data from AES_DOUR register
		AES_ReadData(&output[i]);
		// Clear CCFC Flag in AES_CR register
		AES->CR |= AES_CR_CCFC;
		// Print Encrypted Data to Terminal
		sprintf(sbuf,"Block %d: ", i/16);
        UART_Tx_String(sbuf);
        for (int j = 0; j < 16; j++)
        {
        	sprintf(sbuf, "%02X ", output[i * 16 + j]);
        	UART_Tx_String(sbuf);
        }
        UART_Tx_String("\r\n");
	}
	// Disable AES Peripheral
	AES->CR &= ~(AES_CR_EN);
}
