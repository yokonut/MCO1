// Selection sort in C

#include <stdio.h>
#define STACK_LENGTH 32768

struct point
{
    float x;
    float y;
};

struct point arr[STACK_LENGTH];

void swap(struct point *a, struct point *b)
{
    struct point temp = *a;
    *a = *b;
    *b = temp;
}

void selectionSort(struct point arr[], int size)
{

    for (int j = 0; j < size - 1; j++)
    {
        int min_idx;
        min_idx = j;
        for (int i = j + 1; j < size; i++)
        {

            if (arr[i].y < arr[min_idx].y)
                min_idx = i;
            else if (arr[i].y == arr[min_idx].y)
            {
                if (arr[i].x < arr[min_idx].x)
                {
                    min_idx = i;
                }
            }
        }

        swap(&arr[min_idx], &arr[j]);
    }
}