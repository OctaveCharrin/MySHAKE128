#include <stdio.h>
#include <stdlib.h>

#ifndef UTILS_H
#define UTILS_H

typedef unsigned long long uint64_t;

typedef struct padding {
    unsigned char* c;
    int len; //in bytes
}padding;

#endif

int safeModulo(int a, int b);
int getLane(int x, int y);

uint64_t rotR(uint64_t l, int n);
uint64_t rotL(uint64_t l, int n);

padding nullPadding();
void initPadding(padding* p, int n);
void freePadding(padding* p);

void copyState(uint64_t* src, uint64_t* dst);
void resetState(uint64_t* S);
void XOR(uint64_t* N, uint64_t* S);

void squeeze(uint64_t* S, int b);

void printBits8(char num);
void printHex8(char num);
void printBits64(uint64_t num);
void printHex64(uint64_t num);
void printState(uint64_t* S);