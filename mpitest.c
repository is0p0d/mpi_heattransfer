//jpm 2023
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>
#include <mpi.h>

int main(int argc, char* argv[])
{
    int comm_sz = 0,
        my_rank = 0;
    char* msg = "hello!";
    char rec[10];

    MPI_Init(NULL, NULL);
    MPI_Comm_size(MPI_COMM_WORLD, &comm_sz);
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    printf("MPI: Comm size: %i, Rank: %i\n", comm_sz, my_rank);

    if(my_rank == 0)
    {
        printf("Sending message: %s\n", msg);
        for (int i = 1; i < comm_sz; i++)
        {
            printf("sending to %i...\n",i);
            MPI_Send(&(msg[0]), 7, MPI_CHAR, i, 0, MPI_COMM_WORLD);
        }
    }
    else
    {
        MPI_Recv(&(rec[0]), 10, MPI_CHAR, 0, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
        printf("Received: %s\n", rec);
    }

    MPI_Finalize();
    return 0;
}