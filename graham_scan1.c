#include "stack.c"
#include "sort.c"


//vector multiplication to find if the direction is counterclockwise or clockwise
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

    for (int i = 0; i < 10; i++)
    {
        printf("Point %d: (%.2f, %.2f)\n", i, arr[i].x, arr[i].y);
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
    return 0;
}