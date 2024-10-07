#include "sort.h"


int main()
{
    struct points data[STACK_LENGTH];

    struct points arr[STACK_LENGTH] =
        {
            {14.39, 14.98},
            {3.10, 5.00},
            {2.11, 8.46},
            {14.25, 8.66},
            {5.82, 19.58},
            {17.09, 17.7},
            {11.40, 4.96},
            {3.74, 9.07},
            {1.08, 11.89},
            {8.85, 8.11}};

    /*
        srand(time(NULL));
        for (int i = 0; i < 10; i++)
        {
            arr[i].x = ((float)rand() / RAND_MAX) * 100; // Random float between 0 and 100
            arr[i].y = ((float)rand() / RAND_MAX) * 100; // Random float between 0 and 100
        }
    */
    struct points anchor = findAnchor(arr, 10);

    printf("Anchor point of this array is :(%.2f,%.2f)\n", anchor.x, anchor.y);

    mergesort(arr, 10);
    for (int i = 0; i < 10; i++)
    {
        printf("Point %d: (%.2f, %.2f)\n", i, arr[i].x, arr[i].y);
    }
}