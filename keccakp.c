#include "keccakp.h"


void theta(uint64_t* A){
    uint64_t * C = malloc(5*sizeof(uint64_t));
    uint64_t * D = malloc(5*sizeof(uint64_t));

    for (int x=0; x<5; ++x){
        C[x] = A[getLane(x, 0)] ^ A[getLane(x, 1)] ^ A[getLane(x, 2)] ^ A[getLane(x, 3)] ^ A[getLane(x, 4)];
    }
    for (int x=0; x<5; ++x){
        D[x] = C[(x+4)%5] ^ rotL(C[(x+1)%5], 1);
    }
    for (int x=0; x<5; ++x){
        for (int y=0; y<5; ++y){
            A[getLane(x, y)] = A[getLane(x, y)] ^ D[x];
        }
    }
    free(C);
    free(D);
}

void rho(uint64_t* A){
    uint64_t* A_ = malloc(25*sizeof(uint64_t));
    
    A_[getLane(0, 0)] = A[getLane(0, 0)];
    int x = 1;
    int y = 0;
    for (int t = 0; t<24; ++t){
        A_[getLane(x, y)] = rotL(A[getLane(x, y)], (t+1)*(t+2)/2);
        int temp = x;
        x = y;
        y = (2*temp + 3*y)%5;
    }
    copyState(A_, A);
    free(A_);
}

void pi(uint64_t* A){
    uint64_t* A_ = malloc(25*sizeof(uint64_t));

    for (int x=0; x<5; ++x){
        for (int y=0; y<5; ++y){
            int X = (x+3*y)%5;
            int Y = x;
            A_[getLane(x, y)]= A[getLane(X, Y)];
        }
    }
    copyState(A_, A);
    free(A_);
}

void chi(uint64_t* A){
    uint64_t* A_ = malloc(25*sizeof(uint64_t));

    for (int x=0; x<5; ++x){
        for (int y=0; y<5; ++y){
            A_[getLane(x, y)]= A[getLane(x, y)] ^ ((~A[getLane((x+1)%5, y)]) & A[getLane((x+2)%5, y)]);
        }
    }
    copyState(A_, A);
    free(A_);
}

unsigned int rc(int t){
    t = t%255;
    if (t == 0) return 1;
    unsigned int R = 1;
    unsigned int bit0 = 1;
    unsigned int bit4 = 1<<4;
    unsigned int bit5 = 1<<5;
    unsigned int bit6 = 1<<6;
    unsigned int bit8 = 1<<8;
    unsigned int trunc8 = 255;
    for(int i=0; i<t; ++i){
        R = R<<1;
        // Kill the bit by XORing it with itself and add the right value
        R = (R ^ (R&bit0))  |  ((R&bit0) ^ ((R&bit8)>>8));
        R = (R ^ (R&bit4))  |  ((R&bit4) ^ ((R&bit8)>>4));
        R = (R ^ (R&bit5))  |  ((R&bit5) ^ ((R&bit8)>>3));
        R = (R ^ (R&bit6))  |  ((R&bit6) ^ ((R&bit8)>>2));
        R = R & trunc8;
    }
    return R & bit0;
}

void iota(uint64_t* A, int ir){
    int l = 6;
    uint64_t RC = 0;
    uint64_t bit;
    for (int j=0; j<=l; ++j){
        bit = (uint64_t)rc(j + 7*ir);
        RC = RC | bit<<((1<<j)-1);
    }
    A[getLane(0, 0)] = A[getLane(0, 0)] ^ RC;
}

void keccakp(uint64_t *A, int n_round){
    for (int ir=0; ir<n_round; ++ir){
        //printf("\n--- Round %d ---\n\n", ir);
        theta(A);
        // printf("After theta:\n");
        // printState(A);
        
        rho(A);
        // printf("After rho:\n");
        // printState(A);

        pi(A);
        // printf("After pi:\n");
        // printState(A);
        
        chi(A);
        // printf("After chi:\n");
        // printState(A);

        iota(A, ir);
        // printf("After iota:\n");
        // printState(A);
    }
}
