#include <mpi.h>
#include <climits>
#include <list>
#include <algorithm>
#include <random>
#include <fstream>

const int ROOT = 0;

// Вариант 3

void create_rand_nums(int len, int *array);

void printArray(int len, int *array);

int main(int argc, char *argv[]) {

    int size;
    int rank;
    double start = 0, end = 0;

    int elements_per_proc = 3;

    int *rand_nums;

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    MPI_Barrier(MPI_COMM_WORLD);
    start = MPI_Wtime();

    if (rank == 0) {
        int global_size = elements_per_proc * size;
        rand_nums = (int*) malloc(sizeof(int) * (global_size));
        create_rand_nums(global_size, rand_nums);
        printf("Сгенерированный набор чисел:\n");
        printArray(global_size, rand_nums);
    }

    int *sub_rand_nums = (int*) malloc(sizeof(int) * elements_per_proc);

    MPI_Scatter(rand_nums, elements_per_proc, MPI_INT, sub_rand_nums,
                elements_per_proc, MPI_INT, 0, MPI_COMM_WORLD);

    printf("Proccess %d: ", rank);
    printArray(elements_per_proc, sub_rand_nums);

    MPI_Barrier(MPI_COMM_WORLD);
    end = MPI_Wtime();

    MPI_Finalize();

    if (rank == ROOT){
        printf("%f\n", end - start);
    }

    return 0;
}

void create_rand_nums(int len, int *array) {
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(2, 100);
    for (int i = 0; i < len; i++) {
        array[i] = dist(gen);
    }
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
