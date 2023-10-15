#include <mpi.h>
#include <climits>
#include <list>
#include <algorithm>

// Множитель данных
const int K = 3;


int findMin(const int *pInt, int BLOCK_SIZE);

void printArray(int *pInt, int BLOCK_SIZE);

bool isFindedInList(const std::list<int>& list, int &item);

int main(int argc, char *argv[]) {

    int size;
    int rank;

    const int ROOT = 0;

    MPI_Init(&argc, &argv);

    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    int localMin;
    int globalMin;
    int *A;
    int arraySize = 0;

    if (rank == ROOT) {
        int numWorkProcs = size - 1;
        int lastBlockSize;

        // Генерируем размер на основе количества процессов
        int tempSize = 1 * K;
        for(int i = 0; i < numWorkProcs; i++){
            arraySize += tempSize;
            tempSize *= 2;
        }
        lastBlockSize = tempSize / 2;

        A = new int[arraySize];

        srand(time(0));

        for (int i = 0; i < arraySize; i++)
            A[i] = 1 + rand() % 10;

        printf("Сгенерированный массив:\n");
        printArray(A, arraySize);

        std::list<int> useIndexes;
        std::map<int, int> indexMap;

        int prevIndex = 0;
        int dest = 0;
        
        // Отправка частей массива по процессам
        for(int i = 1; i <= numWorkProcs; i++)
        {
            // В цикле выбирается случайный индекс, который еще
            // не использовался
            do{
                dest = rand() % (numWorkProcs - 1 + 1) + 1;
                if(i == 1)
                    break;
            }
            while(isFindedInList(useIndexes, dest));
            useIndexes.push_back(dest);
            
            // Сначала размер
            MPI_Send(&lastBlockSize,
                     1,
                     MPI_INT,
                     dest,
                     0,
                     MPI_COMM_WORLD);

            // Затем сам массив
            MPI_Send(&A[prevIndex],
                     lastBlockSize,
                     MPI_INT,
                     dest,
                     0,
                     MPI_COMM_WORLD);
            indexMap[lastBlockSize] = prevIndex;
            prevIndex += lastBlockSize;

            lastBlockSize /= 2;
        }

        localMin = INT_MAX;

        // Получаем обработанные данные
        for(int i = 1; i <= numWorkProcs; i++)
        {
            int recvSize;
            MPI_Recv(&recvSize,
                     1,
                     MPI_INT,
                     MPI_ANY_SOURCE,
                     MPI_ANY_TAG,
                     MPI_COMM_WORLD,
                     MPI_STATUS_IGNORE);

            int *recvArray = new int[recvSize];

            MPI_Recv(recvArray,
                     recvSize,
                     MPI_INT,
                     MPI_ANY_SOURCE,
                     recvSize,
                     MPI_COMM_WORLD,
                     MPI_STATUS_IGNORE);

            int sIndex = indexMap[recvSize];
            // Заменяем данные
            for(int k = 0; k < recvSize; sIndex++, k++){
                A[sIndex] = recvArray[k];
            }
        }

        // Работа ненулевого процесса
    } else {

        // Получение размера и массива
        int localSize;
        MPI_Recv(&localSize,
                 1,
                 MPI_INT,
                 MPI_ANY_SOURCE,
                 MPI_ANY_TAG,
                 MPI_COMM_WORLD,
                 MPI_STATUS_IGNORE);

        int *localArray = new int[localSize];

        MPI_Recv(localArray,
                 localSize,
                 MPI_INT,
                 ROOT,
                 MPI_ANY_TAG,
                 MPI_COMM_WORLD,
                 MPI_STATUS_IGNORE);

        // Обработка
        localMin = findMin(localArray, localSize);
        for(int i = 0; i < localSize; i++){
            localArray[i] -= localMin;
        }
        printf("\nMin for P%d is %d.\n", rank, localMin);
        printf("P%d get array with size: %d\n", rank, localSize);
        printf("P%d set:\n", rank);
        printArray(localArray, localSize);



        // Отправка данных назад
        MPI_Send(&localSize,
                 1,
                 MPI_INT,
                 ROOT,
                 1,
                 MPI_COMM_WORLD);

        MPI_Send(localArray,
                 localSize,
                 MPI_INT,
                 ROOT,
                 localSize,
                 MPI_COMM_WORLD);
    }

    // Получаем глобальный минимум
    MPI_Reduce(&localMin,
               &globalMin,
               1,
               MPI_INT,
               MPI_MIN,
               ROOT,
               MPI_COMM_WORLD);

    if (rank == ROOT){
        printf("\nGlobal min: %d\n", globalMin);
        printArray(A, arraySize);
    }

    MPI_Finalize();
    return 0;
}

bool isFindedInList(const std::list<int>& list, int &item) {
    auto it = std::find(list.begin(), list.end(), item);
    if(it != list.end())
        return true;
    return false;
}

void printArray(int *pInt, int BLOCK_SIZE) {
    for(int i = 0; i < BLOCK_SIZE; i++){
        printf(" %d ", pInt[i]);
        if((i + 1) % 12 == 0){
            printf("\n");
        }
    }
    printf("\n");
}

int findMin(const int *pInt, int BLOCK_SIZE) {
    int minEl = INT_MAX;
    for(int i = 0; i < BLOCK_SIZE; i++){
        if(pInt[i] < minEl){
            minEl = pInt[i];
        }
    }
    return minEl;
}
