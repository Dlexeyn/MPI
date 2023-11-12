#include <mpi.h>
#include <algorithm>
#include <random>

const int ROOT = 0;

// Вариант 10

void printArray(int len, int *array);

int main(int argc, char *argv[]) {
    MPI_Init(&argc, &argv);

    int world_rank, world_size;
    MPI_Comm_rank(MPI_COMM_WORLD, &world_rank);
    MPI_Comm_size(MPI_COMM_WORLD, &world_size);

    int N = (world_rank % 2 == 0) ? 2 : 1;
    int A = world_rank + 1;

    MPI_Barrier(MPI_COMM_WORLD);
    double t1 = MPI_Wtime();
    MPI_Comm group_comm;
    MPI_Comm_split(MPI_COMM_WORLD, N, world_rank, &group_comm);

    int group_rank, group_size;
    MPI_Comm_rank(group_comm, &group_rank);
    MPI_Comm_size(group_comm, &group_size);

    int* A_array = (int*) malloc(sizeof (int) * group_size);
    MPI_Allgather(&A, 1, MPI_INT,
                  A_array, 1, MPI_INT, group_comm);

    printf("global rank: %d \t group rank: %d\n",
           world_rank, group_rank);
    printArray(group_size, A_array);

    MPI_Comm_free(&group_comm);

    MPI_Barrier(MPI_COMM_WORLD);
    double t2 = MPI_Wtime();
    if(world_rank == 0)
        printf("Time: %f\n", t2 - t1);

    MPI_Finalize();

    return 0;
}

void printArray(int len, int *array) {
    for(int i = 0; i < len; i++){
        printf(" %d ", array[i]);
        if((i + 1) % 12 == 0){
            printf("\n");
        }
    }
    printf("\n");
}
