// Created by changsk on 2020/4/15.

#ifndef AES128_H
#define AES128_H

#include <stdint.h>

typedef struct{
    uint32_t eK[44], dK[44];    // encKey, decKey
    int Nr; // 10 rounds
}AesKey;

int loadStateArray(uint8_t state[4][4], const uint8_t *in);

int storeStateArray(uint8_t state[4][4], uint8_t *out);

int keyExpansion(const uint8_t *key, uint32_t keyLen, AesKey *aesKey);

// state xor with Initial vector 
int xoriv(uint8_t state[4][4], const uint8_t iv[4][4]);

int addRoundKey(uint8_t state[4][4], const uint32_t key[4]);

int subBytes(uint8_t state[4][4]);

int invSubBytes(uint8_t state[4][4]);

int shiftRows(uint8_t state[4][4]);

int invShiftRows(uint8_t state[4][4]);

uint8_t GMul(uint8_t a, uint8_t b);

int mixColumns(uint8_t state[4][4]);

int invMixColumns(uint8_t state[4][4]);

// data length must be multiple of 16B, so data need to be padded before encryption/decryption
int aesECBEncrypt(const uint8_t *key, uint32_t keyLen, const uint8_t *pt, int ptLen, uint8_t *ct, uint32_t ctlen);

int aesECBDecrypt(const uint8_t *key, uint32_t keyLen, const uint8_t *ct, uint8_t *pt, uint32_t len);

int aesCBCEncrypt(const uint8_t *key, uint32_t keyLen, const uint8_t *pt, int ptLen, uint8_t *ct, uint32_t ctlen, const uint8_t *iv);

int aesCBCDecrypt(const uint8_t *key, uint32_t keyLen, const uint8_t *ct, uint8_t *pt, uint32_t len, const uint8_t *iv);


int getCiphertextLen(uint8_t *plainText, int plainTextLen);

//Fill the plain text with PKCS7 
void PKCS7Padding(const uint8_t *input, int inputLen, uint8_t * plaintext, int CiphertextLen, int mode);


#endif //AES128_H

