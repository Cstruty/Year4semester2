//Collin Struthers mar 12 2023 1084915 A3
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <float.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#define MAX_LENGTH 30000
typedef struct endpoint
{
    int value;
    int is_start;
} Endpoint;

int cmp(const void *a, const void *b)
{
    int x = *((int *)a);
    int y = *((int *)b);
    return (x < y) ? -1 : (x > y);
}

int max_common_intervals(int intervals[][2], int size)
{
    // Collect all the points of the intervals in a sorted array
    int *sorted = malloc(sizeof(int) * (2 * size));
    int max_endpoint = 0;
    struct timespec start, end;

    for (int i = 0; i < size; i++)
    {
        sorted[2 * i] = intervals[i][0];
        sorted[2 * i + 1] = intervals[i][1];
        if (intervals[i][1] > max_endpoint)
            max_endpoint = intervals[i][1];
    }

    qsort(sorted, 2 * size, sizeof(int), cmp);

    // Find the maximum number of intervals that have a common point
    int max_count = 0;
    int count = 0;
    int final_point = 0;
    timespec_get(&start, TIME_UTC);
    for (int i = 1; i < 2 * size - 1; i++)
    {
        count = 0;

        for (int j = 0; j < size; j++)
        {
            //checks if the value of the enpoint is between the interval left and right side
            if (intervals[j][0] < sorted[i] && sorted[i] < intervals[j][1])
                count++;
        }
        if (count > max_count)
        {
            max_count = count;
            final_point = sorted[i];
        }
    }

    timespec_get(&end, TIME_UTC);
    long int elapsed_time_ns = (end.tv_sec - start.tv_sec) * 1000 + (end.tv_nsec - start.tv_nsec) / 1000000.0;
    printf("The maximum number of intervals: %d\n", max_count);
    printf("the interval include the point %d\n", final_point);
    printf("Elapsed time: %ld ms\n", elapsed_time_ns);
    free(sorted);
    return max_count;
}

int main(void)
{
    FILE *fp;
    int n1, n2;
    int count = 0;
    char filename[100];

    // Get file name from user
    printf("Please enter file name: ");
    fgets(filename, 100, stdin);
    filename[strcspn(filename, "\n")] = '\0';
    // Open file
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error: Failure to open file\n");
        exit(1);
    }

    // Get number of intervals in file
    while (fscanf(fp, "%d %d", &n1, &n2) == 2)
        count++;

    // Reset file pointer to beginning of file
    fseek(fp, 0, SEEK_SET);

    // Read intervals from file
    int intervals[count][2];
    for (int i = 0; i < count; i++)
        fscanf(fp, "%d %d", &intervals[i][0], &intervals[i][1]);

    // Find maximum number of common intervals
    max_common_intervals(intervals, count);

    fclose(fp);
    return 0;
}
