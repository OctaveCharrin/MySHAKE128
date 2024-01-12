#include <stdio.h>
#include <stdlib.h>


int main(int argc, char *argv[]){

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <n> < input_stream\n", argv[0]);
        return 1;
    }

    char byte;
    
    while ((byte = getchar()) != EOF){

    }


    printf("Hash length n = %d\n", atoi(argv[1]));
    return 0;
}

