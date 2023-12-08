//jpm 2023
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <time.h>
//#include <mpi.h>

int main(int argc, char* argv[])
{
    if (argc < 1)
    {
        printf("ERROR: You must specify an array size.\n");
        return 1;
    }
    
    uint64_t matrixSize = atoi(argv[1]);

    //adjust the matrix size to account for our heating elements
    uint64_t matRow = matrixSize+2;
    uint64_t matCol = matrixSize+2;

}