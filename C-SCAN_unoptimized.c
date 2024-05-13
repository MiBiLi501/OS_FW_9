#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_REQUEST 2000
#define REQUEST_SIZE 1000
#define CYLINDER 5000

int read[MAX_REQUEST];
int requests[MAX_REQUEST];

int main(int argc, char* argv[]) {
    memset(read, 0, sizeof(read));
    memset(requests, 0, sizeof(requests));
    
    if(argc != 3) {
        printf("Please enter the initial position of the disk head and the text file containing the requests.");
        exit(-1);
    }

    int headLoc = atoi(argv[1]);
    FILE* in = fopen(argv[2], "r");

    for (int i = 0; i < REQUEST_SIZE; i++) fscanf(in, "%d", requests+i);

    fclose(in);

    int headMovements = 0;

    //C-SCAN
    while(1) {
        for (int i = 0; i < REQUEST_SIZE; i++) {
            if(headLoc == requests[i]) {
                read[i] = 1;
                continue;
            }
            if(read[i] || headLoc > requests[i]) continue;
            
            headMovements += requests[i] - headLoc;
            headLoc = requests[i];
            read[i] = 1;
        }

        int complete = 1;
        for (int i = 0; i < REQUEST_SIZE && complete; i++) complete = read[i];
        if (complete) break;
        
        
        headMovements += 2*(CYLINDER-1) - headLoc;
        headLoc = 0;
    }

    printf("Total disk movements: %d\n", headMovements);

    return 0;
}