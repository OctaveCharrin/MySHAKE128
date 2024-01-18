#include "utils.h"
#include "padding.h"
#include "step_mapping.h"


int main(int argc, char *argv[]){

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n> < input_stream\n", argv[0]);
        return 1;
    }

    int n = atoi(argv[1]);

    uint64_t byte;
    uint64_t l = 0;
    int counter = 0;
    int len = 0;
    int idx = 0;
    char empty = 1;

    uint64_t* S = malloc(25*sizeof(uint64_t));
    for (int i=0; i<25; ++i){
        S[i] = 0;
    }

    while ((byte = getchar()) != EOF){
        empty = 0;
        l = l | byte<<(8*(7-counter));
        counter = (counter+1)%8;
        len++;
        printf("byte %lld is = 0x%llx\n", byte, byte);
        printf("lane is = 0x%llx\n", l);
        if (counter == 0){
            S[idx++] = l;
            l = 0;
        }
    }
    S[idx] = l;

    if(empty){printf("empty\n");}else{printf("not empty\n");}
    
    printf("End of line ***********\n\n");

    printf("before padding\n");
    printState(S);

    printf("len = %d\n", len);

    len = len * 8;
    pad(S, 168*8, len+4);
    
    printf("after padding\n");
    printState(S);

    printf("\n\nHash length n = %d\n", n);
    return 0;
}

