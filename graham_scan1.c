#include "stack.h"
#include "sort.h"

int CCW(struct point a, struct point b, struct point c)
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
    Stack a;

    struct point arr[STACK_LENGTH] =
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

    selectionSort(arr, 10);

    CREATE(&a);
    push(&a, arr[0].x, arr[0].y);

    return 0;
}