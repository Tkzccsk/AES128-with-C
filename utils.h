// Created by changsk on 2020/4/15.

#ifndef AES128_UTILS_H
#define AES128_UTILS_H

#define BLOCKSIZE 16

#include <stdint.h>

void printChar(const char *ptr, int len, char *tag);

void printHex(const uint8_t *ptr, int len, char *tag);

void printState(uint8_t state[4][4], char *tag);

//Given curlen, find the first Integer multiple of 16 number that greater than or equal to curlen
int findTrueLen(int curlen);

//length of padding 
int getNumOfPadding(uint8_t* plaintextFull, int CiphertextLen);

#endif //AES128_UTILS_H
