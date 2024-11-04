#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "graham_scan1.c" // Includes computeConvexHull

#define STACK_LENGTH 32768

int main()
{
    char input_filename[100], output_filename[100];
    FILE *input_file, *output_file;
    struct point arr[STACK_LENGTH];
    Stack main_stack, reverse_stack;
    int num_points, i;

    // Prompt user for filenames
    printf("Enter the input filename (e.g., input-circle.txt): ");
    scanf("%s", input_filename);
    printf("Enter the output filename (e.g., output.txt): ");
    scanf("%s", output_filename);

    // Open input file
    input_file = fopen(input_filename, "r");
    if (input_file == NULL)
    {
        printf("Error: Could not open input file.\n");
        return 1;
    }

    // Open output file
    output_file = fopen(output_filename, "w");
    if (output_file == NULL)
    {
        printf("Error: Could not open output file.\n");
        fclose(input_file);
        return 1;
    }

    // Read number of points
    fscanf(input_file, "%d", &num_points);
    if (num_points > STACK_LENGTH)
    {
        printf("Error: Too many points, maximum allowed is %d.\n", STACK_LENGTH);
        fclose(input_file);
        fclose(output_file);
        return 1;
    }
    else if (num_points < 3)
    {
        printf("Error: At least 3 points are required to form a convex hull.\n");
        fclose(input_file);
        fclose(output_file);
        return 1;
    }

    // Read points into array
    for (i = 0; i < num_points; i++)
    {
        fscanf(input_file, "%f %f", &arr[i].x, &arr[i].y);
    }
    fclose(input_file);

    // Start time measurement
    clock_t start = clock();

    fprintf(output_file, "Sorting Algorithm Used: Selection Sort\n");

    // Compute convex hull
    CREATE(&main_stack);
    CREATE(&reverse_stack);
    computeConvexHull(arr, num_points, &main_stack); // Pass the stack to computeConvexHull

    // Move stack contents to reverse_stack to count and write points in correct order
    int hull_size = 0;
    while (!ISEMPTY(&main_stack))
    {
        push(&reverse_stack, POP(&main_stack));
        hull_size++;
    }

    // End time measurement
    clock_t end = clock();

    // Write results to output file
    fprintf(output_file, "Total number of points in the convex hull: %d\n", hull_size);
    fprintf(output_file, "Convex Hull Points (bottom-to-top):\n");
    while (!ISEMPTY(&reverse_stack))
    {
        int idx = POP(&reverse_stack);
        fprintf(output_file, "(%f, %f)\n", arr[idx].x, arr[idx].y);
    }

    fclose(output_file);
    printf("Convex hull points written to %s.\n", output_filename);
    printf("Elapsed time: %.6lf milliseconds\n", (double)(end - start) * 1000.0 / CLOCKS_PER_SEC);

    return 0;
}
