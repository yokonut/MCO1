#include "sort.h"

int main()
{
    struct point data[STACK_LENGTH];

    struct point arr[STACK_LENGTH] =
    {
        {4.4, 8.8},
        {3.3, 6.6},
        {9.9, 19.8},
        {2.2, 4.4},
        {0.0, 0.0},
        {8.8, 17.6},
        {5.5, 11.0},
        {6.6, 13.2},
        {1.1, 2.2},
        {7.7, 15.4}
    };

    /*
        srand(time(NULL));
        for (int i = 0; i < 10; i++)
        {
            arr[i].x = ((float)rand() / RAND_MAX) * 100; // Random float between 0 and 100
            arr[i].y = ((float)rand() / RAND_MAX) * 100; // Random float between 0 and 100
        }
    */

    selectionSort(arr,10);

   // mergesort(arr,10);
    for (int i = 0; i < 10; i++)
    {
        printf("Point %d: (%.2f, %.2f)\n", i, arr[i].x, arr[i].y);
    }
}