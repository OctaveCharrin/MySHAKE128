#include <stdio.h>
#include <stdlib.h>

typedef unsigned long long uint64_t;

uint64_t f(){
    return 6;
}

int index(int x, int y){
    return 5*y + x;
}

int main(int argc, char *argv[]){

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n> < input_stream\n", argv[0]);
        return 1;
    }

    char byte;
    uint64_t lane;
    int counter = 0;
    int l = 8;

    while ((byte = getchar()) != EOF){
        lane = lane<<8 + byte;
        printf("byte %c is = 0x%x\n", byte, byte);
        counter = ++counter%l;
    }


    printf("Hash length n = %d\n", atoi(argv[1]));
    return 0;
}

