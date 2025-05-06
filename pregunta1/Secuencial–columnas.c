/**
 * Codigo tomado de
 *   https://stackoverflow.com/questions/17138599/cpu-cache-understanding-using-a-c-program
 * Codigo derivado de
 *   http://igoro.com/archive/gallery-of-processor-cache-effects/
 *
 * Forma de compilacion
 *   gcc -Wall -O3  demo.c -o demo
 *
 **/
#include <stdio.h>
#include <sys/time.h>
#include <time.h>
#include <unistd.h>
#include <stdlib.h>

#define MAX_SIZE (4096 * 4096)

int main()
{
    clock_t start, end;
    // double cpu_time;
    int i = 0;
    int j = 0;
    int k = 0;

    /* MAX_SIZE array is too big for stack.This is an unfortunate rough edge of
     * the way the stack works.  It lives in a fixed-size buffer, set by the
     * program executable's configuration according to the operating system, but
     * its actual size is seldom checked against the available space. */

    start = clock();

    int *arr = (int *)malloc(MAX_SIZE * sizeof(int));

    if (arr == NULL)
    {
        printf("Asignacion de memoria a la variable 'arr' fallo");
        return 1;
    }

    printf("\nSecuencial – Columnas \n");
    for (j = 1; j <= 1024; j <<= 1)
    {
        /* Loop 2 */
        for (k = 0; k < 4096; k += j)
            for (int i = 0; i < 4096; i++)
                arr[i,k] += 3;
    }

    free(arr);

    end = clock();
    printf("\t Tiempo ejecuccion %ld \n", (end - start));
    return 0;
}