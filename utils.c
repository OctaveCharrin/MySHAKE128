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

void copyState(uint64_t* src, uint64_t* dst){
    for (int i=0; i<25; ++i){
        dst[i] = src[i];
    }
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

void squeeze(uint64_t* S, int b){
    int line = 0;
    int byte = 0;
    uint64_t mask;
    while(b!=0){
        mask = 0xFFULL << (8*byte);
        char c = (char)((S[line] & mask)>>(8*byte));
        printHex8(c);
        byte++;
        if(byte==8){
            byte = 0;
            line++;
        }
        b--;
    }
}

void printBits8(char num) {
    for (int i = 7; i >= 0; i--) {
        printf("%d", (num & (1 << i)) ? 1 : 0);
    }
}

void printHex8(char num) {
    printf("%02X", (unsigned char)num);
}

void printBits64(uint64_t num) {
    int bitSize = sizeof(uint64_t) * 8; // Number of bits in uint64_t

    for (int i = bitSize - 1; i >= 0; i--) {
        uint64_t mask = 1ULL << i;
        int bit = (num & mask) ? 1 : 0;
        printf("%d", bit);

        if (i % 8 == 0) {
            // Add a space every 8 bits for better readability
            printf(" ");
        }
    }
}

void printHex64(uint64_t num) {
    int nibbleSize = sizeof(uint64_t) * 2; // Number of hexadecimal digits in uint64_t

    for (int i = nibbleSize - 1; i >= 0; i--) {
        uint64_t mask = 0xFULL << (i * 4);
        int nibble = (num & mask) >> (i * 4);
        printf("%X", nibble);
    }
}

void printState(uint64_t* S){
    for (int i=1; i<26; ++i){
        printHex64(S[i-1]);
        printf(" ");
        if (i%5 == 0) printf("\n");
    }
}
