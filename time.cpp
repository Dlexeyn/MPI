#include <mpi.h>
#include <cstdio>

int main(int argc, char** argv) {
    int ProcNum, ProcRank, RecvRank;
    double start = 0, end = 0;

    MPI_Status Status;

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD,&ProcNum);
    MPI_Comm_rank(MPI_COMM_WORLD, &ProcRank);

    MPI_Barrier(MPI_COMM_WORLD);
    start = MPI_Wtime();

    if (ProcRank == 0) {
        for (int i = 1; i < ProcNum; i++) {
            MPI_Recv(&RecvRank, 1, MPI_INT,
                     MPI_ANY_SOURCE,
                     MPI_ANY_TAG,
                     MPI_COMM_WORLD,
                     &Status);
        }
    }
    else
        MPI_Send(&ProcRank, 1, MPI_INT,
                 0,
                 0,
                 MPI_COMM_WORLD);

    MPI_Barrier(MPI_COMM_WORLD);
    end = MPI_Wtime();

    MPI_Finalize();

    if (ProcRank == 0) {
        printf("%f\n", end - start);
    }

    return 0;
}