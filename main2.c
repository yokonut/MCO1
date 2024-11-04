#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graham_scan2.c"

#define STACK_LENGTH 32768

int main()
{
    char input_filename[100], output_filename[100];
    FILE *input_file, *output_file;
    Stack main_stack, reverse_stack;
    struct point arr[STACK_LENGTH];
    int num_points, i;
    int orientation;

    // Ask user for the input and output file names
    printf("Enter the input filename (input-circle.txt): ");
    scanf("%s", input_filename);
    printf("Enter the output filename (anything-you-want.txt): ");
    scanf("%s", output_filename);

    // Read input file
    input_file = fopen(input_filename, "r");
    if (input_file == NULL)
    {
        printf("Error opening input file.\n");
        return 1;
    }

    // Write output file
    output_file = fopen(output_filename, "w");
    if (output_file == NULL)
    {
        printf("Error opening output file.\n");
        fclose(input_file);
        return 1;
    }

    fscanf(input_file, "%d", &num_points);
    if (num_points > STACK_LENGTH) // Exceeds limit of number of points
    {
        printf("Too many points, maximum allowed is %d.\n\nTerminating...\n", STACK_LENGTH);
        fclose(input_file);
        fclose(output_file);
        return 1;
    }
    else if (num_points < 3) // Number of points does not make a polygon
    {
        printf("Cannot make convex hull, minimum number of points is 3.\n\nTerminating...\n");
        fclose(input_file);
        fclose(output_file);
        return 1;
    }

    for (i = 0; i < num_points; i++)
    {
        fscanf(input_file, "%f %f", &arr[i].x, &arr[i].y);
    }
    fclose(input_file);

    // Set start time
    clock_t the_start = clock();

    fprintf(output_file, "Sorting Algorithm Used: Heap Sort\n");

    int anchor_index = findAnchorIndex(arr, num_points);

    // Initialize the stacks
    CREATE(&main_stack);
    CREATE(&reverse_stack);
    computeConvexHull(arr, num_points, &main_stack);

    int hull_size = 0;
    while (!ISEMPTY(&main_stack))
    {
        push(&reverse_stack, POP(&main_stack));
        hull_size++;
    }

    // End time
    clock_t the_end = clock();

    fprintf(output_file, "Total number of points in the final convex hull: %d\n", hull_size);
    fprintf(output_file, "Final Convex Hull Points (bottom-to-top):\n");

    // Copy data unto output file
    while (!ISEMPTY(&reverse_stack))
    {
        int idx = POP(&reverse_stack);
        fprintf(output_file, "(%f, %f)\n", arr[idx].x, arr[idx].y);
    }

    fclose(output_file);

    // Print out message
    printf("Convex hull points written to %s.\n", output_filename);
    printf("Elapsed time: %.6lf milliseconds\n", (double)(the_end - the_start) * 1000.0 / CLOCKS_PER_SEC);

    return 0;
}
