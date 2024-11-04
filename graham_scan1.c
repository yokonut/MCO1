#include "stack.c"
#include "sort.c"

// Function to determine the direction (CCW for counterclockwise)
int CCW(struct point a, struct point b, struct point c)
{
    float area = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
    if (area < 0)
        return 1; // Clockwise
    if (area > 0)
        return 2; // Counterclockwise
    return 0;     // Collinear
}

// Function to find the squared distance between two points
float distance(struct point p1, struct point p2)
{
    return (p2.x - p1.x) * (p2.x - p1.x) + (p2.y - p1.y) * (p2.y - p1.y);
}

// Function to find the anchor point with the lowest y-coordinate
int findAnchorIndex(struct point arr[], int num_points)
{
    int anchor_index = 0;
    for (int i = 1; i < num_points; i++)
    {
        if (arr[i].y < arr[anchor_index].y ||
            (arr[i].y == arr[anchor_index].y && arr[i].x < arr[anchor_index].x))
        {
            anchor_index = i;
        }
    }
    return anchor_index;
}

// Main convex hull computation function
void computeConvexHull(struct point arr[], int num_points, Stack *main_stack)
{
    // Sort points by polar angle relative to the anchor
    selectionSort(arr, num_points);
    int anchor_index = findAnchorIndex(arr, num_points);

    // Initialize main_stack and add anchor point
    push(main_stack, anchor_index);

    for (int i = 0; i < num_points; i++)
    {
        if (i != anchor_index)
        {
            while (!ISEMPTY(main_stack) && main_stack->top > 0)
            {
                int top_index = TOP(*main_stack);
                int next_to_top_index = NEXT_TO_TOP(*main_stack);

                // Determine orientation of the sequence of points
                int orientation = CCW(arr[next_to_top_index], arr[top_index], arr[i]);
                if (orientation == 1)
                { // Clockwise
                    POP(main_stack);
                }
                else if (orientation == 0)
                { // Collinear
                    if (distance(arr[next_to_top_index], arr[top_index]) < distance(arr[next_to_top_index], arr[i]))
                    {
                        POP(main_stack);
                    }
                    else
                    {
                        break;
                    }
                }
                else
                {
                    break;
                }
            }
            push(main_stack, i); // Add current point to the hull
        }
    }
}
