#include <time.h>
#include <stdio.h>
#include <math.h>  // For atan2

// Define the point structure here
struct point {
    float x;
    float y;
};

// Function to swap points
void swap(struct point *a, struct point *b) {
    struct point temp = *a;
    *a = *b;
    *b = temp;
}

// Function to find the anchor point
struct point findAnchor(struct point arr[], int size) {
    int i;
    struct point anchor = arr[0];
    for (i = 1; i < size; i++) {
        if (arr[i].y < anchor.y || (arr[i].y == anchor.y && arr[i].x < anchor.x)) {
            anchor = arr[i];
        }
    }
    return anchor;
}

// Function to calculate angle
float calculateAngle(struct point p, struct point anchor) {
    return atan2(p.y - anchor.y, p.x - anchor.x);
}

// Selection Sort with timing
void selectionSort(struct point arr[], int size, double elapsed_times[]) {
    int i, j;
    struct point anchor = findAnchor(arr, size);
    float angles[size];
    clock_t start, end;

    // Precompute angles to avoid recalculating in inner loop
    for (i = 0; i < size; i++) {
        angles[i] = calculateAngle(arr[i], anchor);
    }

    start = clock();

    for (j = 0; j < size - 1; j++) {
        int min_idx = j;
        for (i = j + 1; i < size; i++) {
            if (angles[i] < angles[min_idx]) {
                min_idx = i;
            }
        }
        swap(&arr[min_idx], &arr[j]);

        // Swap angles for consistency with points
        float temp_angle = angles[min_idx];
        angles[min_idx] = angles[j];
        angles[j] = temp_angle;

        // Calculate elapsed time for this point and store it
        end = clock();
        elapsed_times[j] = ((double)(end - start) / CLOCKS_PER_SEC) * 1000;  // Convert to milliseconds
    }

    // Final time measurement for the last point
    end = clock();
    elapsed_times[size - 1] = ((double)(end - start) / CLOCKS_PER_SEC) * 1000; // Record the last time
}

// Heapify helper function for heap sort
void heapify(struct point arr[], int n, int i, struct point anchor, float angles[]) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && angles[left] > angles[largest]) {
        largest = left;
    }
    if (right < n && angles[right] > angles[largest]) {
        largest = right;
    }

    if (largest != i) {
        swap(&arr[i], &arr[largest]);

        // Swap angles to remain consistent with points
        float temp_angle = angles[i];
        angles[i] = angles[largest];
        angles[largest] = temp_angle;

        heapify(arr, n, largest, anchor, angles);
    }
}

// Heap Sort with timing
void heapSort(struct point arr[], int size, double elapsed_times[]) {
    struct point anchor = findAnchor(arr, size);
    float angles[size];
    clock_t start, end;
    int i;

    // Precompute angles
    for (i = 0; i < size; i++) {
        angles[i] = calculateAngle(arr[i], anchor);
    }

    start = clock();

    // Build heap
    for (i = size / 2 - 1; i >= 0; i--) {
        heapify(arr, size, i, anchor, angles);
    }

    // Extract elements from heap one by one
    for (i = size - 1; i > 0; i--) {
        swap(&arr[0], &arr[i]);

        // Swap corresponding angles
        float temp_angle = angles[0];
        angles[0] = angles[i];
        angles[i] = temp_angle;

        heapify(arr, i, 0, anchor, angles);

        // Calculate elapsed time for each extracted element
        end = clock();
        elapsed_times[size - i - 1] = ((double)(end - start) / CLOCKS_PER_SEC) * 1000;  // Convert to milliseconds
    }

    // Final time measurement for the last sorted element
    end = clock();
    elapsed_times[size - 1] = ((double)(end - start) / CLOCKS_PER_SEC) * 1000; // Record the last time
}

