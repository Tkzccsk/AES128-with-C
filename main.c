// Created by changsk on 2020/4/15.

#include <stdio.h>
#include "AES128.h"
#include "utils.h"

#define BLOCKSIZE 16
#define KEYSIZE 16

enum WORKMODE { CBC, ECB};

void case1(enum WORKMODE);
void case2(enum WORKMODE);

int main() 
{
	
	//case1(ECB);
	case2(CBC);
}


void case1(enum WORKMODE mode)
{
	const uint8_t key[KEYSIZE] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c,};
    const uint8_t pt[BLOCKSIZE]={0x32, 0x43, 0xf6, 0xa8, 0x88, 0x5a, 0x30, 0x8d, 0x31, 0x31, 0x98, 0xa2, 0xe0, 0x37, 0x07, 0x34};
    uint8_t ct[BLOCKSIZE] = {0};
    uint8_t plain[BLOCKSIZE] = {0};
    if(mode == CBC) printf("*********in CBC mode*********\n");
    else if(mode == ECB) printf("*********in ECB mode*********\n");
	printHex(pt, BLOCKSIZE, "plain data:");
	uint8_t iv[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
	
	if((mode == CBC))
	{	
    	aesCBCEncrypt(key, KEYSIZE, pt, BLOCKSIZE, ct, BLOCKSIZE, iv);
	}
	else if(mode == ECB)
	{
		aesECBEncrypt(key, KEYSIZE, pt, BLOCKSIZE, ct, BLOCKSIZE);
	}
	
    printHex(ct, BLOCKSIZE, "after encryption:");

	if(mode == CBC)
	{
		aesCBCDecrypt(key, KEYSIZE, ct, plain, BLOCKSIZE, iv);
	}
	else if(mode == ECB)
	{
		aesECBDecrypt(key, KEYSIZE, ct, plain, BLOCKSIZE);
	}
    
    printHex(plain, BLOCKSIZE, "after decryption:");
}	

void case2(enum WORKMODE mode)
{
	const uint8_t key[KEYSIZE] = {0x2b, 0x7e, 0x15, 0x16, 0x28, 0xae, 0xd2, 0xa6, 0xab, 0xf7, 0x15, 0x88, 0x09, 0xcf, 0x4f, 0x3c,};
    char input[100];
    if(mode == CBC) printf("*********in CBC mode*********\n");
    else if(mode == ECB) printf("*********in ECB mode*********\n");
    printf("please input words(Not more than 100 words):");
    scanf("%s", input);
    int inputLen = 0;
    while(input[inputLen++] != '\0');
    inputLen--;
    printChar(input, inputLen, "input data in char:");
    
    //encrypt
    int CiphertextLen = getCiphertextLen((uint8_t*)input, inputLen);
    uint8_t ciphertext[CiphertextLen];
    uint8_t iv[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    if(mode == CBC)
    {
    	aesCBCEncrypt(key, KEYSIZE, (uint8_t*)input, inputLen, ciphertext, CiphertextLen, iv);
    }
    else if(mode == ECB)
    {
    	aesECBEncrypt(key, KEYSIZE, (uint8_t*)input, inputLen, ciphertext, CiphertextLen);
    }
    
    printHex(ciphertext, CiphertextLen, "after encryption in hex:");
    
    //decrypt
	uint8_t plaintextFull[CiphertextLen];
	if(mode == CBC)
	{
		aesCBCDecrypt(key, KEYSIZE, ciphertext, plaintextFull, CiphertextLen, iv);
	}
	else if(mode == ECB)
	{
		aesECBDecrypt(key, KEYSIZE, ciphertext, plaintextFull, CiphertextLen);
	}
    printHex(plaintextFull, CiphertextLen, "after decryption in hex:");
    int numOfPadding = getNumOfPadding(plaintextFull, CiphertextLen);
    printChar((char*)plaintextFull, CiphertextLen - numOfPadding, "after decryption in char:");
}

