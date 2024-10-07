// Selection sort in C

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define STACK_LENGTH 32768

struct point
{
    float x;
    float y;
};

struct point arr[STACK_LENGTH];

void swap(struct point *a, struct point *b);
void selectionSort(struct point arr[], int size);
void mergesort(struct point arr[], int size);
void merge_sort_recursion(struct point arr[], int l, int r);
void merge_sorted_array(struct point arr[], int l, int m, int r);

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
        int min_idx = j;
        for (int i = j + 1; i < size; i++)
        {
            if (arr[i].y < arr[min_idx].y || (arr[i].y == arr[min_idx].y && arr[i].x < arr[min_idx].x))
            {
                min_idx = i;
            }
        }
        swap(&arr[min_idx], &arr[j]);
    }
}
void mergesort(struct point arr[], int size)
{
    merge_sort_recursion(arr, 0, size - 1);
}

void merge_sort_recursion(struct point arr[], int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        merge_sort_recursion(arr, l, m);
        merge_sort_recursion(arr, m + 1, r);
        merge_sorted_array(arr, l, m, r);
    }
}

void merge_sorted_array(struct point arr[], int l, int m, int r)
{

    int left_length = m - l + 1;
    int right_length = r - m;

    struct point temp_left[left_length], temp_right[right_length];

    for (int i = 0; i < left_length; i++)
        temp_left[i] = arr[l + i];
    for (int i = 0; i < right_length; i++)
        temp_right[i] = arr[m + 1 + i];

    int i = 0, j = 0, k = l;
    while (i < left_length && j < right_length)
    {
        if (temp_left[i].y < temp_right[j].y ||
            (temp_left[i].y == temp_right[j].y && temp_left[i].x <= temp_right[j].x))
        {
            arr[k++] = temp_left[i++];
        }
        else
        {
            arr[k++] = temp_right[j++];
        }
    }

    while (i < left_length)
        arr[k++] = temp_left[i++];
    while (j < right_length)
        arr[k++] = temp_right[j++];
}