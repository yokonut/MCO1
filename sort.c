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
	int i;
	// first initialize the anchor into the first array
    struct point anchor = arr[0]; 
    for (i = 1; i < size; i++)
    {
    	//checks the smallest y value point if the y values are equal check the smallest x
        if (arr[i].y < anchor.y || (arr[i].y == anchor.y && arr[i].x < anchor.x)) 
        {
        	//assign the smaller value
            anchor = arr[i];  
        }
    }
    return anchor;  
}

//calculates the angle from previous current and next point
float calculateAngle(struct point p, struct point anchor)
{
    return atan2(p.y - anchor.y, p.x - anchor.x);   
}


//selection sort
void selectionSort(struct point arr[], int size)
{
	int i, j;
    struct point anchor = findAnchor(arr, size);    // call anchor function and assign it to struct anchor



    for (j = 0; j < size - 1; j++)
    {
        int min_idx = j;                            
        for (i = j + 1; i < size; i++)
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



// Function to heapify a subtree rooted with node i which is an index in arr[]
void heapify(struct point arr[], int n, int i, struct point anchor) { //n is size of heap
	// Initialize largest as root
    int largest_val = i;  
    int left = 2 * i + 1;  
    int right = 2 * i + 2;

    // Calculate angles for the current root, left, and right 
    float angle_largest = calculateAngle(arr[largest_val], anchor);     //IT'S LARGEST VAL RIGHT
    if (left < n && calculateAngle(arr[left], anchor) > angle_largest) {
        largest_val = left;
        angle_largest = calculateAngle(arr[left], anchor);
    }
    if (right < n && calculateAngle(arr[right], anchor) > angle_largest) {
        largest_val = right;
    }

    // Swap and continue heapifying if the root is not largest
    if (largest_val != i) {
        swap(&arr[i], &arr[largest_val]);
        heapify(arr, n, largest_val, anchor);
    }
}

// Function to perform heap sort on an array of points
void heapSort(struct point arr[], int size) {
    struct point anchor = findAnchor(arr, size);  
	int i;
    // Rearranhge the array
    for (i = size / 2 - 1; i >= 0; i--) {
        heapify(arr, size, i, anchor);
    }

    for (i = size - 1; i > 0; i--) {
        // Move the current root to end
        swap(&arr[0], &arr[i]);

        // Call max heapify on the reduced heap
        heapify(arr, i, 0, anchor);
    }
}

