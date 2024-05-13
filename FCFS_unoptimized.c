#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_REQUEST 2000
#define REQUEST_SIZE 1000

int requests[MAX_REQUEST];

int main(int argc, char* argv[]) {
    if(argc != 3) {
        printf("Please enter the initial position of the disk head and the text file containing the requests.");
        exit(-1);
    }

    int headLoc = atoi(argv[1]);
    FILE* in = fopen(argv[2], "r");

    for (int i = 0; i < REQUEST_SIZE; i++) fscanf(in, "%d", requests+i);

    fclose(in);
    
    int headMovements = 0;

    //FCFS
    for (int i = 0; i < REQUEST_SIZE; i++) {
        headMovements += abs(headLoc - requests[i]);
        headLoc = requests[i];
    }
    
    printf("Total disk movements: %d\n", headMovements);

    return 0;
}