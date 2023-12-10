//jpm 2023
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <time.h>
//#include <mpi.h>

void matInit(float* matrix, uint64_t maxRow, uint64_t maxCol);
void matPrint(float* matrix, uint64_t maxRow, uint64_t maxCol);
float pointCalc(float center, float north, float south, float east, float west);
void matCalc(float* matrix, uint64_t maxRow, uint64_t startRow, uint64_t startCol, uint64_t endRow, uint64_t endCol);
float* matPart(float* matrix, uint64_t maxRow, uint64_t startRow, uint64_t startCol, uint64_t endRow, uint64_t endCol);

int main(int argc, char* argv[])
{
    printf("arg count: %i\n", argc);
    if (argc < 4)
    {
        printf("ERROR: You must specify an array size, a step number, and a node count.\n");
        return 1;
    }
    
    uint64_t matrixSize = atoi(argv[1]);
    uint64_t stepCount = atoi(argv[2]);
    uint64_t nodeCount = atoi(argv[3]);



    //adjust the matrix size to account for our heating elements
    uint64_t matRow = matrixSize+2;
    uint64_t matCol = matrixSize+2;

    //statically allocate the matrix for now
    // arr[row][col]
    //float matrix[matRow*matCol];
    float* matrix = (float *)malloc((matRow * matCol)*sizeof(float));
    if (!matrix)
    {
        printf("ERROR: malloc fail\n");
        return 1;
    }
    printf("Initializing then printing matrix of size %ix%i\n", matRow, matCol);
    matInit(matrix, matRow, matCol);
    //matPrint(matrix, matRow, matCol);
    for (int step = 0; step < stepCount; step++)
    {
        printf("STEP %i\n", step);
        matCalc(matrix, matRow, 1, 1, matRow-1, matCol -1);
        matPrint(matrix, matRow, matCol);
    }
    free (matrix);
    return 0;
}

void matInit(float* matrix, uint64_t maxRow, uint64_t maxCol)
{
    printf("matInit\n");
    for(int m = 0; m < maxRow; m++)
    {
        for(int n = 0; n < maxCol; n++)
        {
            if (n == 0 || n == maxCol-1) 
                *((matrix+m*maxRow)+n) = 1.0;
            else 
                *((matrix+m*maxRow)+n) = 0.0;
        }
    }
}
void matPrint(float* matrix, uint64_t maxRow, uint64_t maxCol)
{
    float val = 0.0;
    for(int m = 0; m < maxRow; m++)
    {
        for(int n = 0; n < maxCol; n++)
        {
            val = *((matrix+m*maxRow)+n);
            if (val < .25) printf("\033[38;5;51m%.2f, ",val);
            else if (val >= .25 && val < .50) printf("\033[38;5;220m%.2f, ",val);
            else if (val >=.50 && val < .75) printf("\033[38;5;202m%.2f, ",val);
            else if (val >= .75) printf("\033[38;5;196m%.2f, ",val);
            else printf("\033[39m%.2f, ",val);
            
        }
        printf("\033[39m\n");
    }
}

float pointCalc(float center, float north, float south, float east, float west)
{
    //printf("pointCalc\n");
    return ((center+north+south+east+west)/5.0); 
}

void matCalc(float* matrix, uint64_t maxRow, uint64_t startRow, uint64_t startCol, uint64_t endRow, uint64_t endCol)
{
    printf("matCalc\n");
    float center = 0.0,
          north = 0.0,
          south = 0.0,
          east = 0.0,
          west = 0.0;
    for(int y = startRow; y < endRow; y++)
    {
        for(int x = startCol; x < endCol; x++)
        {
            center = *((matrix+x*maxRow)+y);
            north = *((matrix+(x+1)*maxRow)+y);
            south = *((matrix+(x-1)*maxRow)+y);
            east = *((matrix+x*maxRow)+(y+1));
            west = *((matrix+x*maxRow)+(y-1));
            
            //printf("At %ix%i: center: %f, north: %f, south: %f, east: %f, west: %f\n", x, y, center, north, south, east, west);
            *((matrix+x*maxRow)+y) = pointCalc(center, north, south, east, west);
        }
    } 
}