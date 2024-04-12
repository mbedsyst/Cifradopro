#include "HSM_Lib.h"
#include <stdlib.h>
#include <stdio.h>

#define MAX_DATA_SIZE	4096
#define MAX_KEY_SIZE	256

uint8_t* CreateInputData(void);
uint8_t* CreateInputKey(void);
void DisplayMainMenu(void);
void DisplayKeyGeneratorMenu(void);
void DisplayEncryptionMenu(void);
void DisplayDecryptionMenu(void);
void DisplayHashingMenu(void);
void DisplayOneTimePadMenu(void);
void KeyGeneratorService(uint8_t option);
void EncryptionService(uint8_t option, uint8_t *input, uint8_t *key);
void EncryptionService(uint8_t option, uint8_t *input, uint8_t *key);
void DecryptionService(uint8_t option, uint8_t *input, uint8_t *key);
void HashingService(uint8_t option, uint8_t *input, uint8_t *key);
void OneTimePadService(uint8_t option);

uint8_t* CreateInputData(void)
{
    int dataSize;
    char sbuf[100];
    char inputData[MAX_DATA_SIZE];
    sprintf(sbuf,"Enter the size of data (less than or equal to %d): ", MAX_DATA_SIZE );
    UART_Tx_String(sbuf);
    dataSize = UART_Rx_Int();
    if (dataSize <= 0 || dataSize > MAX_DATA_SIZE)
    {
        UART_Tx_String("Error: Data size exceeds the maximum allowed size.\n");
        return 0;
    }
    // Allocate memory for inputData based on the user input
    char *inputData = (char *)malloc(dataSize * sizeof(char));
    if (inputData == NULL)
    {
    	UART_Tx_String("Error: Memory allocation failed.\n");
        return;
    }
    // Read the input data
    UART_Tx_String("Enter data: \r\n");
    UART_RxString(inputData, dataSize);
}

uint8_t* CreateInputKey(void)
{
	int keySize;
    char sbuf[100];
    char key[MAX_DATA_SIZE];
    sprintf(sbuf,"Enter the size of data (less than or equal to %d): ", MAX_KEY_SIZE );
    UART_Tx_String(sbuf);
    keySize = UART_Rx_Int();
    if (keySize <= 0 || keySize > MAX_DATA_SIZE)
    {
        UART_Tx_String("Error: Data size exceeds the maximum allowed size.\n");
        return;
    }
    // Allocate memory for inputData based on the user input
    char *key = (char *)malloc(keySize * sizeof(char));
    if (key == NULL) {
    	UART_Tx_String("Error: Memory allocation failed.\n");
        return;
    }
    // Read the input data
    UART_Tx_String("Enter data: ");
    UART_RxString(key, keySize);
}

void ClearScreen(void)
{
	UART_Tx_String("\x1b[2J");
}

void InitialiseHSM(void)
{
	LED_Init();
	GPIO_Init();
	UART_Init();
	AES_Init();
	RNG_Init();
	HASH_Init();
}

void DisplayHSMBanner(void)
{
    UART_Tx_String("################################################################################\r\n");
	UART_Tx_String("#                    _  __               _                                     #\r\n");
    UART_Tx_String("#                ___(_)/ _|_ __ __ _  __| | ___  _ __  _ __ ___                #\r\n");
    UART_Tx_String("#               / __| | |_| '__/ _` |/ _` |/ _ \| '_ \| '__/ _ \               #\r\n");
    UART_Tx_String("#              | (__| |  _| | | (_| | (_| | (_) | |_) | | | (_) |              #\r\n");
    UART_Tx_String("#               \___|_|_| |_|  \__,_|\__,_|\___/| .__/|_|  \___/               #\r\n");
    UART_Tx_String("#                                               |_|                            #\r\n");
    UART_Tx_String("#                                                                              #\r\n");
    UART_Tx_String("################################################################################\r\n");
    UART_Tx_String("cifradopro, is a minimal hardware security module (HSM) powered by the \r\n");
    UART_Tx_String("STM32L4S5ZI microcontroller. It can securely generate cryptographic keys, \r\n");
    UART_Tx_String("can encrypt and decrypt data securely, includes hashing functions for \r\n");
    UART_Tx_String("generating hash values of data, and can generate one-time pads. It allows you \r\n");
    UART_Tx_String("to store generated keys on an external memory, protecting them from \r\n");
    UART_Tx_String("physical tampering and ensuring their security.\r\n");
    UART_Tx_String("\r\n");
}

uint8_t ChooseOption(void)
{
	uint8_t c;
	return UART_Rx();
}

void DisplayMainMenu(void)
{
	UART_Tx_String("################################################################################\r\n");
	UART_Tx_String("Service Category Menu\r\n");
	UART_Tx_String("	(1) Key Generation Services\r\n");
	UART_Tx_String("	(2) Encryption Services\r\n");
	UART_Tx_String("	(3) Decryption Services\r\n");
	UART_Tx_String("	(4) Hashing Services\r\n");
	UART_Tx_String("	(5) One Time Pad Generation Services\r\n");
	UART_Tx_String("\r\n");
	UART_Tx_String(" !! Caution !!");
	UART_Tx_String("   Choose any service with the number mentioned against it. \r\n");
	UART_Tx_String("   Key Generation Service generates Keys for Cryptographic Use. OTP Generation services \r\n");
	UART_Tx_String("   genereate random numbers to be XORed with plaintext for encryption. Encryption and \r\n");
	UART_Tx_String("   Decrytpion services use Advanced Encryption Standard in Cipher Block Chaining Mode. \r\n");
	UART_Tx_String("   Hashing service provides Checksum, SHA-256 and HMAC calculations.\r\n");
	UART_Tx_String("\r\n");
	UART_Tx_String("Choose any Service: \r\n");

}

void DisplayKeyGeneratorMenu(void)
{
	UART_Tx_String("################################################################################\r\n");
	UART_Tx_String("Key Generator Service Menu\r\n");
	UART_Tx_String("	(1) Generate 128-bit Random Key\r\n");
	UART_Tx_String("	(2) Generate 192-bit Random Key\r\n");
	UART_Tx_String("	(3) Generate 256-bit Random Key\r\n");
	UART_Tx_String("\r\n");
	UART_Tx_String("!! Caution !! : \r\n");
	UART_Tx_String("\r\n");
	UART_Tx_String("\r\n");
	UART_Tx_String("\r\n");
	UART_Tx_String("\r\n");
	UART_Tx_String("\r\n");
	UART_Tx_String("\r\n");
	UART_Tx_String("Choose any Service: \r\n");
}

void DisplayEncryptionMenu(void)
{
	UART_Tx_String("################################################################################\r\n");
	UART_Tx_String("Encryption Service Menu\r\n");
	UART_Tx_String("	(1) AES-128 CBC Encryption\r\n");
	UART_Tx_String("	(2) AES-256 CBC Encryption\r\n");
	UART_Tx_String("!! Caution !! : \r\n");
	UART_Tx_String("\r\n");
	UART_Tx_String("Choose any Service: \r\n");
}

void DisplayDecryptionMenu(void)
{
	UART_Tx_String("################################################################################\r\n");
	UART_Tx_String("Decryption Service Menu\r\n");
	UART_Tx_String("	(1) AES-128 CBC Decryption\r\n");
	UART_Tx_String("	(2) AES-256 CBC Decryption\r\n");
	UART_Tx_String("!! Caution !! : \r\n");
	UART_Tx_String("\r\n");
	UART_Tx_String("Choose any Service: \r\n");
}

void DisplayHashingMenu(void)
{
	UART_Tx_String("################################################################################\r\n");
	UART_Tx_String("Hashing Service Menu\r\n");
	UART_Tx_String("	(1) CRC-32 Checksum\r\n");
	UART_Tx_String("	(2) SHA-256 Hashing\r\n");
	UART_Tx_String("	(3) HMAC Computing using SHA-256\r\n");
	UART_Tx_String("!! Caution !! : \r\n");
	UART_Tx_String("\r\n");
	UART_Tx_String("Choose any Service: \r\n");
}

void DisplayOneTimePadMenu(void)
{
	UART_Tx_String("################################################################################\r\n");
	UART_Tx_String("Decryption Service Menu\r\n");
	UART_Tx_String("	(1) 128-bit One Time Pad\r\n");
	UART_Tx_String("	(2) 256-bit One Time Pad\r\n");
	UART_Tx_String("	(3) 512-bit One Time Pad\r\n");
	UART_Tx_String("	(4) 1024-bit One Time Pad\r\n");
	UART_Tx_String("	(5) 2048-bit One Time Pad\r\n");
	UART_Tx_String("!! Caution !! : \r\n");
	UART_Tx_String("\r\n");
	UART_Tx_String("Choose any Service: \r\n");
}

void KeyGeneratorService(uint8_t option)
{
	switch(option)
	{
		case '1':
			uint8_t buf[16];
			RNG_GenerateRandom(buf, 128);
		    UART_Tx_String("Generated Key (128-bit): \r\n");
		    for (int i = 0; i < 16; i++)
		    {
		    	UART_Tx_String("%c", (char)buf[i]);
		    }
		    UART_Tx_String("\r\n");
			break;
		case '2':
			uint8_t buf[24];
			RNG_GenerateRandom(buf, 192);
		    UART_Tx_String("Generated Key (192-bit): \r\n");
		    for (int i = 0; i < 24; i++)
		    {
		    	UART_Tx_String("%c", (char)buf[i]);
		    }
		    UART_Tx_String("\r\n");
			break;
		case '3':
			uint8_t buf[32];
			RNG_GenerateRandom(buf, 256);
		    UART_Tx_String("Generated Key (256-bit): \r\n");
		    for (int i = 0; i < 32; i++)
		    {
		    	UART_Tx_String("%c", (char)buf[i]);
		    }
		    UART_Tx_String("\r\n");
			break;
		default:
			UART_Tx_String("Error: Select a valid option.\r\n");
			break;
	}
}

void EncryptionService(uint8_t option, uint8_t *input, uint8_t *key)
{
	switch(option)
	{
		case '1':
			uint8_t iv[16];
		    while (input[i] != '\0')
		    {
		        i++;
		    }
		    uint8_t output[i];
			RNG_GenerateRandom(iv, 128);
		    UART_Tx_String("AES-128 CBC Encrypted Ciphertext: \r\n");
		    UART_Tx_String("\r\n");
			AES_CBC_Encrypt(key, iv, input, output);
			break;
		case '2':
			uint8_t iv[16];
		    while (input[i] != '\0')
		    {
		        i++;
		    }
		    uint8_t output[i];
			RNG_GenerateRandom(iv, 128);
		    UART_Tx_String("AES-256 CBC Encrypted Ciphertext: \r\n");
		    UART_Tx_String("\r\n");
			AES_CBC_Encrypt(key, iv, input, output);
			break;
		default:
			UART_Tx_String("Error: Select a valid option.\r\n");
			break;
	}
}

void DecryptionService(uint8_t option, uint8_t *input, uint8_t *key)
{
	switch(option)
	{
		case '1':
			uint8_t iv[16];
			 while (input[i] != '\0')
			{
				i++;
			}
			uint8_t output[i];
			RNG_GenerateRandom(iv, 128);
		    UART_Tx_String("AES-128 CBC Decrypted Ciphertext: \r\n");
		    UART_Tx_String("\r\n");
			AES_CBC_Decrypt(key, iv, input, output);
			break;
		case '2':
			uint8_t iv[16];
		    while (input[i] != '\0')
			{
				i++;
			}
			uint8_t output[i];
			RNG_GenerateRandom(iv, 128);
		    UART_Tx_String("AES-256 CBC Decrypted Ciphertext: \r\n");
		    UART_Tx_String("\r\n");
			AES_CBC_Decrypt(key, iv, input, output);
			break;
		default:
			UART_Tx_String("Error: Select a valid option.\r\n");
			break;
	}
}

void HashingService(uint8_t option, uint8_t *input, uint8_t *key)
{
	switch(option)
	{
		case '1':
			//CRC-32 Functions
			break;
		case '2':
			HASH_SHA256(input);
			break;
		case '3':
			HASH_HMAC(input, key);
		default:
			UART_Tx_String("Error: Select a valid option.\r\n");
			break;
	}
}

void OneTimePadService(uint8_t option)
{
	switch(option)
	{
		case '1':
			uint8_t buf[16];
			char sbuf[1];
			RNG_GenerateRandom(buf, 128);
		    UART_Tx_String("Generated Key (128-bit): \r\n");
		    for (int i = 0; i < 16; i++)
		    {
		    	sprintf(sbuf,"%c", (char)buf[i]);
		    	UART_Tx_String(sbuf);
			    UART_Tx_String("\t");
			    if(i % 4 == 0)
			    {
			    	UART_Tx_String("\r\n");
			    }
		    }
		    UART_Tx_String("\r\n");
			break;
		case '2':
			uint8_t buf[16];
			char sbuf[1];
			RNG_GenerateRandom(buf, 128);
		    UART_Tx_String("Generated Key (128-bit): \r\n");
		    for (int i = 0; i < 16; i++)
		    {
		    	sprintf(sbuf,"%c", (char)buf[i]);
		    	UART_Tx_String(sbuf);
			    UART_Tx_String("\t");
			    if(i % 4 == 0)
			    {
			    	UART_Tx_String("\r\n");
			    }
		    }
		    UART_Tx_String("\r\n");
			break;
		case '3':
			uint8_t buf[16];
			char sbuf[1];
			RNG_GenerateRandom(buf, 128);
		    UART_Tx_String("Generated Key (128-bit): \r\n");
		    for (int i = 0; i < 16; i++)
		    {
		    	sprintf(sbuf,"%c", (char)buf[i]);
		    	UART_Tx_String(sbuf);
			    UART_Tx_String("\t");
			    if(i % 4 == 0)
			    {
			    	UART_Tx_String("\r\n");
			    }
		    }
		    UART_Tx_String("\r\n");
			break;
		case '4':
			uint8_t buf[16];
			char sbuf[1];
			RNG_GenerateRandom(buf, 128);
		    UART_Tx_String("Generated Key (128-bit): \r\n");
		    for (int i = 0; i < 16; i++)
		    {
		    	sprintf(sbuf,"%c", (char)buf[i]);
		    	UART_Tx_String(sbuf);
			    UART_Tx_String("\t");
			    if(i % 4 == 0)
			    {
			    	UART_Tx_String("\r\n");
			    }
		    }
		    UART_Tx_String("\r\n");
			break;
		case '5':
			uint8_t buf[16];
			char sbuf[1];
			RNG_GenerateRandom(buf, 128);
		    UART_Tx_String("Generated Key (128-bit): \r\n");
		    for (int i = 0; i < 16; i++)
		    {
		    	sprintf(sbuf,"%c", (char)buf[i]);
		    	UART_Tx_String(sbuf);
			    UART_Tx_String("\t");
			    if(i % 4 == 0)
			    {
			    	UART_Tx_String("\r\n");
			    }
		    }
		    UART_Tx_String("\r\n");
			break;
		default:
			UART_Tx_String("Error: Select a valid option.\r\n");
			break;
	}
}


void MenuFunction(void)
{
	uint8_t MainCMD = 0;
	uint8_t SubCMD = 0;
	DisplayMainMenu();
	MainCMD = ChooseOption();
	ClearScreen();
	switch(MainCMD)
	{
		case '1':
			DisplayKeyGeneratorMenu();
			SubCMD = ChooseOption();
			ClearScreen();
			switch(SubCMD)
			{
				case '1':
					KeyGeneratorService(1);
					break;
				case '2':
					KeyGeneratorService(2);
					break;
				case '3':
					KeyGeneratorService(3);
					break;
				default:
					UART_Tx_String("Error: Select a valid option.\r\n");
					break;
			}
			break;

		case '2':
			DisplayEncryptionMenu();
			SubCMD = ChooseOption();
			ClearScreen();
			char* input = CreateInputData();
			char* key = CreateInputKey();
			switch(SubCMD)
			{
				case '1':
		            if (inputData != NULL && key != NULL)
		            {
		                EncryptionService(1, input, key);
		                free(input);
		                free(key);
		            }
					break;
				case '2':
		            if (input != NULL && key != NULL)
		            {
		                EncryptionService(2, input, key);
		                free(input);
		                free(key);
		            }
					break;
				default:
					UART_Tx_String("Error: Select a valid option.\r\n");
					break;
			}
			break;
		case '3':
			DisplayDecryptionMenu();
			SubCMD = ChooseOption();
			ClearScreen();
			char* input = CreateInputData();
			char* key = CreateInputKey();
			switch(SubCMD)
			{
				case '1':
		            if (input != NULL && key != NULL)
		            {
		                DecryptionService(1, input, key);
		                free(input);
		                free(key);
		            }
					break;
				case '2':
		            if (input != NULL && key != NULL)
		            {
		                DecryptionService(2, input, key);
		                free(input);
		                free(key);
		            }
					break;
				default:
					UART_Tx_String("Error: Select a valid option.\r\n");
					break;
			}
			break;
		case '4':
			DisplayHashingMenu();
			SubCMD = ChooseOption();
			ClearScreen();
			char* input = CreateInputData();
			switch(SubCMD)
			{
				case '1':
					if (inputData != NULL && key == NULL)
					{
						HashingService(1, input, key);
						free(inputData);
					}
					break;
				case '2':
					if (input != NULL && key != NULL)
					{
						HashingService(2, input, key);
						free(inputData);
					}
					break;
				case '3':
					if (input != NULL && key != NULL)
					{
						HashingService(3, input, key);
						free(input);
					}
					break;
				default:
					UART_Tx_String("Error: Select a valid option.\r\n");
					break;
			}
			break;
		case '5':
			DisplayOneTimePadMenu();
			SubCMD = ChooseOption();
			ClearScreen();
			switch(SubCMD)
			{
			case '1':
				OneTimePadService(1);
				break;
			case '2':
				OneTimePadService(2);
				break;
			case '3':
				OneTimePadService(3);
				break;
			case '4':
				OneTimePadService(4);
				break;
			case '5':
				OneTimePadService(5);
				break;
			default:
				UART_Tx_String("Error: Select a valid option.\r\n");
				break;
			}
			break;

		default:
			UART_Tx_String("Error: Select a valid option.\r\n");
			break;
	}
	ClearScreen();
}
