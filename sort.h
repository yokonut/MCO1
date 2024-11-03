#include <stdio.h>
#include <stdlib.h>
#include <math.h>


struct point
{
    float x;
    float y;
};



#define STACK_LENGTH 32768


struct point arr[STACK_LENGTH];

void swap(struct point *a, struct point *b);
struct point findAnchor(struct point arr[], int size);
float calculateAngle(struct point p, struct point anchor);
void selectionSort(struct point arr[], int size);
void mergesort(struct point arr[], int size);
void merge_sort_recursion(struct point arr[], int l, int r, struct point anchor);
void merge_sorted_array(struct point arr[], int l, int m, int r, struct point anchor);
