#include "sort.h"

//swapping function of two struct point datatypes
void swap(struct point *a, struct point *b)
{
    struct point temp = *a;
    *a = *b;
    *b = temp;
}

// finds the anchor of the points and returns that point
struct point findAnchor(struct point arr[], int size)
{
    struct point anchor = arr[0]; // first initialize the anchor into the first array
    for (int i = 1; i < size; i++)
    {
        if (arr[i].y < anchor.y || (arr[i].y == anchor.y && arr[i].x < anchor.x)) //checks the smallest y value point if there y values are equal check the smallest x
        {
            anchor = arr[i];                                                      //assign the smaller value 
        }
    }
    return anchor;  //return the anchor point
}

//calculates the angle from previous current and next point
float calculateAngle(struct point p, struct point anchor)
{
    return atan2(p.y - anchor.y, p.x - anchor.x);   //idk this was given in a site 
}


//selection sort
void selectionSort(struct point arr[], int size)
{
    struct point anchor = findAnchor(arr, size);    // call anchor function and assign it to struct anchor

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

//merge sort
void mergesort(struct point arr[], int size)
{
    struct point anchor = findAnchor(arr, size);
    merge_sort_recursion(arr, 0, size - 1, anchor);
}

void merge_sort_recursion(struct point arr[], int l, int r, struct point anchor)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        merge_sort_recursion(arr, l, m, anchor);
        merge_sort_recursion(arr, m + 1, r, anchor);
        merge_sorted_array(arr, l, m, r, anchor);
    }
}

void merge_sorted_array(struct point arr[], int l, int m, int r, struct point anchor)
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


/*
int main()
{
    struct point data[STACK_LENGTH];

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

   
    struct point anchor = findAnchor(arr, 10);

    printf("Anchor point of this array is :(%.2f,%.2f)\n", anchor.x, anchor.y);

    mergesort(arr, 10);
    for (int i = 0; i < 10; i++)
    {
        printf("Point %d: (%.2f, %.2f)\n", i, arr[i].x, arr[i].y);
    }
}

*/
