#include <stdio.h>
#include <stdlib.h>
#include <math.h>


struct point
{
    float x;
    float y;
};



#define STACK_MAX 32768


struct point arr[STACK_MAX];

void swap(struct point *a, struct point *b);
struct point findAnchor(struct point arr[], int size);
float calculateAngle(struct point p, struct point anchor);
void selectionSort(struct point arr[], int size);
void heapify(struct point arr[], int n, int i, struct point anchor);
void heapSort(struct point arr[], int size);