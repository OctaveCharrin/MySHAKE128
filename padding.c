#include "padding.h"

//x = r en bits et m = len(N)+4 en bits
padding pad10x1(int x, int m){
    //printf("x = %d, m = %d\n", x, m);

    if (x<=0 || m<0){
        printf("Incorrect input in pad10*1: x must be positive and m must be non-negative\n");
        return nullPadding();

    } else {
        int j = safeModulo(-m-2, x); /* number of 0s that are missing */        
        //printf("j = %d\n", j);
        j = (j+6)/8; /* number of bytes that the full padding contains */
        //printf("then j = %d\n", j);
        
        padding p;
        initPadding(&p, j);

        if (j==1){
            p.c[0] = 0xf9; // = 1111 1001
        } else {
            p.c[0] = 0xf8; // = 1111 1000
            p.c[p.len-1] = 1;
        }
        return p;
    }
}

void pad(uint64_t* S, int x, int m){
    padding p = pad10x1(x, m);
    
    int q = p.len/8;
    int r = p.len - (8*q);
    //printf("q = %d, r = %d\n", q, r);

    uint64_t l;
    l = S[20 - q];
    for (int i=0; i<r; ++i){
        uint64_t c = (uint64_t)p.c[i];
        l = l | (c<<(8*(r-1-i)));
    }
    S[20 - q] = l;

    for (int i=q; i>0; --i){
        l = 0;
        for(int j=0; j<8; ++j){
            uint64_t c = p.c[r+8*(q-i)+j];
            l = l | c<<(8*(7-j));
        }
        S[21-i]=l;
    }
}