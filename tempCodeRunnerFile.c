void randomizePoints(struct point arr[], int size)
{
    srand(time(NULL)); // Seed the random number generator
    for (int i = 0; i < size; i++)
    {
        arr[i].x = ((float)rand() / RAND_MAX) * 100; // Random float between 0 and 100
        arr[i].y = ((float)rand() / RAND_MAX) * 100; // Random float between 0 and 100
    }
}

