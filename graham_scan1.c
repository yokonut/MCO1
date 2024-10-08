#include "stack.c"
#include "sort.c"
#include "time.h"



void randomizePoints(struct point arr[], int size)
{
    srand(time(NULL)); // Seed the random number generator
    for (int i = 0; i < size; i++)
    {
        arr[i].x = ((float)rand() / RAND_MAX) * 100; // Random float between 0 and 100
        arr[i].y = ((float)rand() / RAND_MAX) * 100; // Random float between 0 and 100
    }
}


// vector multiplication to find if the direction is counterclockwise or clockwise
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

    randomizePoints(arr,10);

    // Record start time
    clock_t start_time = clock();

    // scan 1 uses selection sort
    selectionSort(arr, 10);

    CREATE(&a);      // initialize stack
    push(&a, index); // adds the anchor point to the stack first

    for (int i = 1; i < 10; i++)
    {

        while (a.top > 0 && CCW(arr[NEXT_TO_TOP(a)], arr[TOP(a)], arr[i]) <= 0) // condition a.top > 0 makes sure stack has atleast 2 data, and CWW function computes
        {
            POP(&a); // pops if CWW returns -1
        }
        push(&a, i); // pushes all points where CWW isn't -1
    }


    printf("Convex Hull:\n");
    while (!ISEMPTY(&a))
    {
        int idx = POP(&a);
        printf("(%f, %f)\n", arr[idx].x, arr[idx].y);
    }


    clock_t end_time = clock();
    double time_taken = ((double)(end_time - start_time)) / CLOCKS_PER_SEC;
    printf("Time taken: %.6f seconds\n", time_taken);

    return 0;
}