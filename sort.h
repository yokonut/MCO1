// Selection sort in C

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define STACK_LENGTH 32768

struct points
{
    float x;
    float y;
};

struct points arr[STACK_LENGTH];

void swap(struct points *a, struct points *b);
void selectionSort(struct points arr[], int size);
void mergesort(struct points arr[], int size);
void merge_sort_recursion(struct points arr[], int l, int r, struct points anchor);
void merge_sorted_array(struct points arr[], int l, int m, int r, struct points anchor);

void swap(struct points *a, struct points *b)
{
    struct points temp = *a;
    *a = *b;
    *b = temp;
}

struct points findAnchor(struct points arr[], int size)
{
    struct points anchor = arr[0];
    for (int i = 1; i < size; i++)
    {
        if (arr[i].y < anchor.y || (arr[i].y == anchor.y && arr[i].x < anchor.x))
        {
            anchor = arr[i];
        }
    }
    return anchor;
}

float calculateAngle(struct points p, struct points anchor)
{
    return atan2(p.y - anchor.y, p.x - anchor.x);
}

void selectionSort(struct points arr[], int size)
{
    struct points anchor = findAnchor(arr, size);

    for (int j = 0; j < size - 1; j++)
    {
        int min_idx = j;
        for (int i = j + 1; i < size; i++)
        {

            float angle1 = calculateAngle(arr[i], anchor);
            float angle2 = calculateAngle(arr[min_idx], anchor);

            if (angle1 < angle2)
            {
                min_idx = i;
            }
        }
        swap(&arr[min_idx], &arr[j]);
    }
}
void mergesort(struct points arr[], int size)
{
    struct points anchor = findAnchor(arr, size);
    merge_sort_recursion(arr, 0, size - 1, anchor);
}

void merge_sort_recursion(struct points arr[], int l, int r, struct points anchor)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        merge_sort_recursion(arr, l, m, anchor);
        merge_sort_recursion(arr, m + 1, r, anchor);
        merge_sorted_array(arr, l, m, r, anchor);
    }
}

void merge_sorted_array(struct points arr[], int l, int m, int r, struct points anchor)
{

    int left_length = m - l + 1;
    int right_length = r - m;

    struct points temp_left[left_length], temp_right[right_length];

    for (int i = 0; i < left_length; i++)
        temp_left[i] = arr[l + i];
    for (int i = 0; i < right_length; i++)
        temp_right[i] = arr[m + 1 + i];

    int i = 0, j = 0, k = l;
    while (i < left_length && j < right_length)
    {
        float angle_left = calculateAngle(temp_left[i], anchor);
        float angle_right = calculateAngle(temp_right[j], anchor);
        if (angle_left < angle_right)
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