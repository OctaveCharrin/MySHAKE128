#include "utils.h"
#include "padding.h"
#include "step_mapping.h"


int main(int argc, char *argv[]){

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n> < input_stream\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);
    int r = 168;
    int n_round = 24;

    uint64_t byte;
    uint64_t lane = 0;
    int pos_in_lane = 0;
    int lenN = 0;
    int n_lane = 0;
    char empty_string = 1;

    // Init input string and state buffers
    uint64_t *N, *S;
    N = malloc(25*sizeof(uint64_t));
    for (int i=0; i<25; ++i){
        N[i] = 0;
    }
    S = malloc(25*sizeof(uint64_t));
    for (int i=0; i<25; ++i){
        S[i] = 0;
    }

    // Read input stream
    char fileStatus = (byte = getchar());
    if (fileStatus != EOF) empty_string = 0;
    while (fileStatus != EOF){
        lenN++;
        lane = lane | byte<<(8*(7-pos_in_lane));
        pos_in_lane = (pos_in_lane+1)%8;
        
        // Lane completed
        if (pos_in_lane == 0){
            N[n_lane++] = lane;
            lane = 0;
        }       

        // Input string completed
        if (lenN == r){
            printf("doing something with complete state:\n");

            XOR(N, S);
            keccakp(S, n_round);


            printState(N);
            resetState(N);
            
            lenN = 0;
            n_lane = 0;
        }
        fileStatus = (byte = getchar());
    }

    // End of file attained
    printf("*********** End of line ***********\n\n");
    if (lenN != 0 || empty_string){
        N[n_lane] = lane;

        // Incomplete input string: padding
        printf("before padding\n");
        printState(N);
        printf("len = %d bytes\n", lenN);
        padding p = pad10x1(8*r, 8*lenN+4);
        pad(N, p);
        freePadding(&p);
        printf("after padding\n");
        printState(N);
    }

    printf("\n\nHash length n = %d\n", n);

    return 0;
}

