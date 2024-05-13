#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_REQUEST 2000
#define REQUEST_SIZE 1000

int requests[MAX_REQUEST];

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
    if(argc != 3) {
        printf("Please enter the initial position of the disk head and the text file containing the requests.");
        exit(-1);
    }

    int headLoc = atoi(argv[1]);
    FILE* in = fopen(argv[2], "r");
    
    for (int i = 0; i < REQUEST_SIZE; i++) fscanf(in, "%d", requests+i);
    
    fclose(in);

    qsort(requests, REQUEST_SIZE, sizeof(int), ascComparator);
    
    int l = requests[0];
    int r = requests[REQUEST_SIZE-1];

    if(headLoc > l){
        if(abs(headLoc-l) < abs(headLoc-r)) {
            int mid = 0;
            
            while(requests[mid++] < headLoc);
            mid--;
            qsort(requests, mid, sizeof(int), descComparator);
        }
        else {
            int mid = 0;
            
            while(requests[mid++] < headLoc);
            mid--;
            int temp[mid-1];
            for (int i = 0; i < mid; i++){
                temp[i] = requests[i];
            }

            for(int i = 0; i < mid/2; i++) {
                int x = temp[i];
                temp[i] = temp[mid-1-i];
                temp[mid-1-i] = x;
            }
            
            for (int i = 0; i < REQUEST_SIZE; i++){
                if(i >= REQUEST_SIZE-mid) {
                    requests[i] = temp[i+mid-REQUEST_SIZE];
                    continue;
                }

                requests[i] = requests[i+mid];
            }
        }
    }

    int headMovements = 0;

    //FCFS
    for (int i = 0; i < REQUEST_SIZE; i++) {
        headMovements += abs(headLoc - requests[i]);
        headLoc = requests[i];
    }

    printf("Total disk: %d\n", headMovements);

    return 0;
}