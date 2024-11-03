#include "stack.c"
#include "sort.c"
#include <time.h>

// CAN delete when we have data to put
void randomizePoints(struct point arr[], int size)
{
    srand(time(NULL)); // Seed the random number generator
    for (int i = 0; i < size; i++)
    {
        arr[i].x = ((float)rand() / RAND_MAX) * 100; // Random float between 0 and 100
        arr[i].y = ((float)rand() / RAND_MAX) * 100; // Random float between 0 and 100
    }
}

float CCW(struct point a, struct point b, struct point c)
{
    float area = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    if (area < 0)
        return -1;
    if (area > 0)
        return 1;                   

    return 0;
}

int main()
{

    int index = 0;
    Stack a;

    struct point arr[STACK_LENGTH];

    //just randomizing poitns
    randomizePoints(arr, 10);


    clock_t the_start = clock();
    mergesort(arr, 10);

    for(int i =0; i < 10; i++){
        printf("(%f,%f)\n", arr[i].x, arr[i].y);
    }

    CREATE(&a);
    push(&a, index);

    for (int i = 1; i < 10; i++)
    {
        while (a.top > 0 && CCW(arr[NEXT_TO_TOP(a)], arr[TOP(a)], arr[i]) <= 0)
        {
            POP(&a);
        }
        push(&a, i);
    }

    printf("Convex Hull:\n");
    while (!ISEMPTY(&a))
    {
        int idx = POP(&a);
        printf("(%f, %f)\n", arr[idx].x, arr[idx].y);
    }

    clock_t end_time = clock();

    double time_taken = ((double)(end_time - the_start)) /CLOCKS_PER_SEC;
    printf("Time taken: %.6f seconds\n", time_taken);

    return 0;
}