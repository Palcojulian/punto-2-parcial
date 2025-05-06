#include <stdio.h>
#include <stdlib.h>
#include <omp.h>
#define M 40
#define TH 4

void schedule_static(int arr[], int size);
void schedule_dinamic(int arr[], int size);
void schedule_guided(int arr[], int size);
int fibonacci(int n);
int generateRandomNum();

int main()
{
    int arrayTests[M];    
    for (int i = 0; i < M; i++) {
        arrayTests[i] = generateRandomNum();
    }

    schedule_static(arrayTests, M);
    schedule_dinamic(arrayTests, M);
    schedule_guided(arrayTests, M);
    
    return 0;
}


void schedule_static(int arr[], int size)
{

    printf("static \n");
    int nExecutionsByThread[TH] = {0};
    double inicio = omp_get_wtime();

    #pragma omp parallel num_threads(TH)
    {
        #pragma omp for schedule(static)
        for (int i = 0; i < size; i++) {
            int id_thread = omp_get_thread_num();
            #pragma omp atomic
            nExecutionsByThread[id_thread]++;

            fibonacci(arr[i]);
        }
    }

    double fin = omp_get_wtime();
    double executionTime = fin - inicio;
    for (int i = 0; i < TH; i++) {
        printf("Hilo %d ejecutó %d veces\n", i, nExecutionsByThread[i]);
    }

    printf("Tiempo ejecución static: %f segundos\n", executionTime);
}

void schedule_dinamic(int arr[], int size) {
    printf("\ndinamic \n");
    int nExecutionsByThread[TH] = {0};
    double inicio = omp_get_wtime();
    #pragma omp parallel num_threads(TH)
    {
        #pragma omp for schedule(dynamic, 1)
        for (int i = 0; i < size; i++) {
            int id_thread = omp_get_thread_num();
            #pragma omp atomic
            nExecutionsByThread[id_thread]++;
            fibonacci(arr[i]);
        }
    }

    double fin = omp_get_wtime();
    double executionTime = fin - inicio;

    for (int i = 0; i < TH; i++) {
        printf("Hilo %d ejecutó %d veces\n", i, nExecutionsByThread[i]);
    }

    printf("Tiempo ejecución dinamic: %f segundos\n", executionTime);
}

void schedule_guided(int arr[], int size) {
    printf("\nguided \n");
    int nExecutionsByThread[TH];
    double inicio = omp_get_wtime();
    #pragma omp parallel num_threads(TH)
    {
        #pragma omp for schedule(guided, 1)
        for (int i = 0; i < size; i++) {
            int id_thread = omp_get_thread_num();
            #pragma omp atomic
            nExecutionsByThread[id_thread]++;
            fibonacci(arr[i]);
        }
    }

    double fin = omp_get_wtime();
    double executionTime = fin - inicio;

    for (int i = 0; i < TH; i++) {
        printf("Hilo %d ejecutó %d veces\n", i, nExecutionsByThread[i]);
    }

    printf("Tiempo ejecución guided: %f segundos\n", executionTime);
}

int fibonacci(int n)
{
    if (n < 2)
        return n;
    return fibonacci(n - 1) + fibonacci(n - 2);
}

int generateRandomNum() {
    return rand() % 6 + 30;
}