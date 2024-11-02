#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "stack.c"
#include "sort.c"

#define STACK_LENGTH 100

// Function to determine the direction (CCW for counterclockwise) 
float CCW(struct point a, struct point b, struct point c) {
    float area = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    if (area < 0)
        return -1; // Clockwise
    if (area > 0)
        return 1;  // Counterclockwise
    return 0;     // Collinear
}

// Function to find the starting anchor point 
int findAnchorIndex(struct point arr[], int num_points) {
    int anchor_index = 0;
    int i;
    for (i = 1; i < num_points; i++) {
    	//lowest point or leftmost if tied
        if (arr[i].y < arr[anchor_index].y || (arr[i].y == arr[anchor_index].y && arr[i].x < arr[anchor_index].x)) {
            anchor_index = i;
        }
    }
    return anchor_index;
}

int main() {
    char input_filename[100], output_filename[100];
    FILE *input_file, *output_file;
    Stack main_stack, reverse_stack;
    struct point arr[STACK_LENGTH];
    int num_points, i;

    // Ask user for the input and output file names
    printf("Enter the input filename (input-circle.txt): ");
    scanf("%s", input_filename);
    printf("Enter the output filename (anything-you-want.txt): ");
    scanf("%s", output_filename);

    // Read input file
    input_file = fopen(input_filename, "r");
    if (input_file == NULL) {
        printf("Error opening input file.\n");
        return 1;
    }

    // Write output file
    output_file = fopen(output_filename, "w");
    if (output_file == NULL) {
        printf("Error opening output file.\n");
        fclose(input_file);
        return 1;
    }

    fscanf(input_file, "%d", &num_points);
    if (num_points > STACK_LENGTH) {
        printf("Too many points, maximum allowed is %d.\n\nTerminating...\n", STACK_LENGTH);
        fclose(input_file);
        fclose(output_file);
        return 1;
    }

    for (i = 0; i < num_points; i++) {
        fscanf(input_file, "%f %f", &arr[i].x, &arr[i].y);
    }
    fclose(input_file);

    // Sort the points using Selection Sort
    selectionSort(arr, num_points);
    fprintf(output_file, "Sorting Algorithm Used: Selection Sort\n");

    int anchor_index = findAnchorIndex(arr, num_points);

    // Initialize the stacks
    CREATE(&main_stack);
    CREATE(&reverse_stack);
    push(&main_stack, anchor_index);

    for (i = 0; i < num_points; i++) {
        if (i == anchor_index) continue;
        while (!ISEMPTY(&main_stack) && main_stack.top > 0 &&
               CCW(arr[NEXT_TO_TOP(main_stack)], arr[TOP(main_stack)], arr[i]) <= 0) {
            POP(&main_stack);
        }
        push(&main_stack, i);
    }

    int hull_size = 0;
    while (!ISEMPTY(&main_stack)) {
        push(&reverse_stack, POP(&main_stack));
        hull_size++;
    }

    fprintf(output_file, "Total number of points in the final convex hull: %d\n", hull_size);
    fprintf(output_file, "Final Convex Hull Points (bottom-to-top):\n");

    while (!ISEMPTY(&reverse_stack)) {
        int idx = POP(&reverse_stack);
        fprintf(output_file, "(%f, %f)\n", arr[idx].x, arr[idx].y);
    }

    fclose(output_file);
    printf("Convex hull points written to %s.\n", output_filename);

    return 0;
}
