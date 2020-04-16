// Created by changsk on 2020/4/15.

#include <stdio.h>
#include "utils.h"

void printHex(const uint8_t *ptr, int len, char *tag) {
    printf("%s\n\tdata[%d]: ", tag, len);
    int i = 0;
    for (; i < len; ++i) {
        printf("%02X ", *ptr++);
    }
    printf("\n");
}

void printChar(const char *ptr, int len, char *tag) {
    printf("%s\n\tdata[%d]: ", tag, len);
    int i = 0;
    for (; i < len; ++i) {
        printf("%c ", (*ptr++));
    }
    printf("\n");
}

void printState(uint8_t (*state)[4], char *tag) {
    printf("%s\n", tag);
    int i = 0;
    for (; i < 4; ++i) {
        printf("%02X %02X %02X %02X\n", state[i][0], state[i][1], state[i][2], state[i][3]);
    }
    printf("\n");
}

////Given curlen, find the first Integer multiple of 16 number that greater than or equal to curlen
int findTrueLen(int curlen)
{
	if(curlen <= 0) {
		printf("curlen must > 0");
		return -1;
	}
	if((curlen % BLOCKSIZE) == 0) return curlen;
	else return (curlen / BLOCKSIZE + 1)* BLOCKSIZE;
}

//length of padding 
int getNumOfPadding(uint8_t* plaintextFull, int CiphertextLen)
{
	uint8_t *p = plaintextFull - BLOCKSIZE;
	int numOfPadding = 0;
	int i = 0;
	for(i = 0; i < BLOCKSIZE;i++)
	{
		if(p[i] != (uint8_t)BLOCKSIZE) break;
	}	
	if(i == BLOCKSIZE) numOfPadding = BLOCKSIZE;
	else numOfPadding = plaintextFull[CiphertextLen - 1];
	return numOfPadding;
}
