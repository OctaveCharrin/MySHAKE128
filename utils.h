#include <stdio.h>
#include <stdlib.h>

#ifndef UTILS_H
#define UTILS_H

typedef unsigned long long uint64_t;

typedef struct lane {
    char isEmpty;
    uint64_t value;
}lane;

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

void printState(uint64_t* S);