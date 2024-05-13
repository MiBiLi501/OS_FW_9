#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_REQUEST 2000
#define REQUEST_SIZE 1000
#define CYLINDER 5000

int requests[MAX_REQUEST];
int read[MAX_REQUEST];

int ascComparator(const void* a, const void* b) {
    int x = *(int*) a;
    int y = *(int*) b;
    
    return x-y;
}

int descComparator(const void* a, const void* b) {
    int x = *(int*) a;
    int y = *(int*) b;
    
    return y-x;
}

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

    qsort(requests, REQUEST_SIZE, sizeof(int), ascComparator);

    int mid = 0;
    
    while(requests[mid++] < headLoc);
    mid--;
    int temp[mid-1];
    for (int i = 0; i < mid; i++){
        temp[i] = requests[i];
    }

    for(int i = 0; i < mid/2; i++) {
        int x = requests[i];
        requests[i] = requests[mid-1-i];
        requests[mid-1-i] = x;
    }

    int direction = 1;
    int headMovements = 0;

    //SCAN
    while(1) {
        for (int i = 0; i < REQUEST_SIZE; i++) {
            if(headLoc == requests[i]) {
                read[i] = 1;
                continue;
            }
            if(read[i] || ((headLoc < requests[i]) ^ direction)) continue;
            
            headMovements += abs(headLoc - requests[i]);
            headLoc = requests[i];
            read[i] = 1;
        }

        int complete = 1;
        for (int i = 0; i < REQUEST_SIZE && complete; i++) complete = read[i];
        if (complete) break;
        
        
        headMovements += direction ? (CYLINDER-1)-headLoc : headLoc;
        headLoc = direction ? (CYLINDER-1) : 0;   
        direction = !direction;
    }
    
    printf("Total disk movements: %d\n", headMovements);

    return 0;
}