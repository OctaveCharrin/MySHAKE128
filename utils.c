#include "utils.h"

int safeModulo(int a, int b){
    int res = a;
    if (res<0){
        do {
            res = res + b;
        } while (res < 0);
    } else {
        while (res - b >= 0){
            res = res - b;
        }
    }
    return res;
}

int getLane(int x, int y){
    return 5*y + x;
}

uint64_t rotR(uint64_t l, int n){
    n = n%64;
    return (l>>n) | (l<<(64-n));
}

uint64_t rotL(uint64_t l, int n){
    n = n%64;
    return (l<<n) | (l>>(64-n));
}

padding nullPadding(){
    padding p;
    p.c = malloc(sizeof(char));
    p.c[0] = 0;
    p.len = -1;
    return p;
}

void initPadding(padding* p, int n){
    p->c = malloc((n)*sizeof(char));
    if (p->c == NULL) printf("initPadding: initialization failed...\n");
    for (int i=0; i<n; ++i){
        p->c[i] = 0;
    }
    p->len = n;
}

void freePadding(padding* p) {
    free(p->c);
    p->c = NULL;
    p->len = 0;
}

void resetState(uint64_t* S){
    for (int i=0; i<25; ++i){
        S[i] = 0;
    }
}

void XOR(uint64_t* N, uint64_t* S){
    for (int i=0; i<25; ++i){
        S[i] = N[i] ^ S[i];
    }
}











void printBits(unsigned long long num) {
    int bitSize = sizeof(unsigned long long) * 8; // Number of bits in unsigned long long

    for (int i = bitSize - 1; i >= 0; i--) {
        unsigned long long mask = 1ULL << i;
        int bit = (num & mask) ? 1 : 0;
        printf("%d", bit);

        if (i % 8 == 0) {
            // Add a space every 8 bits for better readability
            printf(" ");
        }
    }
    printf("\n");
}

void printHex(unsigned long long num) {
    int nibbleSize = sizeof(unsigned long long) * 2; // Number of hexadecimal digits in unsigned long long

    for (int i = nibbleSize - 1; i >= 0; i--) {
        unsigned long long mask = 0xFULL << (i * 4);
        int nibble = (num & mask) >> (i * 4);
        printf("%X", nibble);
    }
    printf("\n");
}

void printState(uint64_t* S){
    for (int i=0; i<25; ++i){
        printHex(S[i]);
    }
}