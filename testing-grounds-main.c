/*
This code still requires testing
- Dale
*/


#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "stack.c"
#include "testing-grounds-sort.c"  // Note this function is just for testing the elapsed time

#define MAX_POINTS 100

int main() {
    char input_filename[100], output_filename[100];
    FILE *input_file, *output_file;
    struct point arr[MAX_POINTS];
    int num_points, sort_choice;
    int i;

    printf("Enter the input filename: ");
    scanf("%99s", input_filename);
    printf("Enter the output filename: ");
    scanf("%99s", output_filename);

    input_file = fopen(input_filename, "r");
    if (input_file == NULL) {
        fprintf(stderr, "Error opening input file.\n");
        return 1;
    }

    output_file = fopen(output_filename, "w");
    if (output_file == NULL) {
        fprintf(stderr, "Error opening output file.\n");
        fclose(input_file);
        return 1;
    }

    if (fscanf(input_file, "%d", &num_points) != 1 || num_points > MAX_POINTS) {
        fprintf(stderr, "Error reading number of points or too many points (max %d).\n", MAX_POINTS);
        fclose(input_file);
        fclose(output_file);
        return 1;
    }

    for (i = 0; i < num_points; i++) {
        if (fscanf(input_file, "%f %f", &arr[i].x, &arr[i].y) != 2) {
            fprintf(stderr, "Error reading points from file.\n");
            fclose(input_file);
            fclose(output_file);
            return 1;
        }
    }
    fclose(input_file);

    printf("Choose sorting algorithm:\n");
    printf("1. Selection Sort\n");
    printf("2. Heap Sort\n");
    printf("Enter choice (1 or 2): ");
    if (scanf("%d", &sort_choice) != 1 || (sort_choice != 1 && sort_choice != 2)) {
        fprintf(stderr, "Invalid sorting choice.\n");
        fclose(output_file);
        return 1;
    }

    double elapsed_times[MAX_POINTS] = {0};

    if (sort_choice == 1) {
        selectionSort(arr, num_points, elapsed_times);
        fprintf(output_file, "Sorting Algorithm Used: Selection Sort\n");
    } else {
        heapSort(arr, num_points, elapsed_times);
        fprintf(output_file, "Sorting Algorithm Used: Heap Sort\n");
    }

    for (i = 0; i < num_points; i++) {
        fprintf(output_file, "(%f, %f)\t\t%.7f ms\n", arr[i].x, arr[i].y, elapsed_times[i]);
    }

    fclose(output_file);
    printf("Sorted points with timing information written to %s.\n", output_filename);
    return 0;
}

