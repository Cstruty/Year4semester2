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
#include <unistd.h>
#define MAX_LENGTH 30000
#define _POSIX_C_SOURCE 200809L

// takes in an array of intervals and the number of intervals,
// and finds the common point that overlaps with the most number of intervals.
void maxcommonintervals(int intervals[][2], int size)
{
    int i, j, count, maxcount, finalcommonpoint;
    int min_endpoint = intervals[0][0], max_endpoint = intervals[0][1];

    // Find the minimum and maximum endpoints of all intervals.
    struct timespec start, end;
    timespec_get(&start, TIME_UTC);
    for (i = 1; i < size; i++)
    {
        if (intervals[i][0] < min_endpoint)
            min_endpoint = intervals[i][0];
        if (intervals[i][1] > max_endpoint)
            max_endpoint = intervals[i][1];
    }

    maxcount = 0;

    // Iterate through all possible common points between min_endpoint and max_endpoint,
    // and count the number of intervals that overlap with each point.
    for (i = min_endpoint + 1; i < max_endpoint; i++)
    {
        count = 0;
        for (j = 0; j < size; j++)
        {
            if (i > intervals[j][0] && i < intervals[j][1])
                count++;
        }
        if (count > maxcount)
        {
            maxcount = count;
            finalcommonpoint = i;
        }
    }
    sleep(2);
    timespec_get(&end, TIME_UTC);
    long int elapsed_time_ns = (end.tv_sec - start.tv_sec) * 1000 + (end.tv_nsec - start.tv_nsec) / 1000000.0;

    // Print the maximum number of intervals that overlap with a common point,
    // and the common point itself.
    printf("The maximum number of intervals: %d\n", maxcount);
    printf("the interval include the point %d\n", finalcommonpoint);

    printf("Elapsed time: %ld ms\n", elapsed_time_ns);
}

int main(void)
{
    FILE *fp;
    int n1, n2;
    int count = 0;
    char filename[100];
    printf("please enter file name\n");
    fgets(filename, 100, stdin);
    filename[strcspn(filename, "\n")] = '\0';
    fp = fopen(filename, "r");
    if (fp == NULL)
    {
        printf("Error Failure to open file\n");
        exit(1);
    }

    // Count the number of intervals in the file.
    while (fscanf(fp, "%d %d", &n1, &n2) == 2)
    {
        count++;
    }

    fseek(fp, 0, SEEK_SET);

    int intervals[count][2];

    // Read all the intervals from the file.
    for (int i = 0; i < count; i++)
    {
        fscanf(fp, "%d %d", &intervals[i][0], &intervals[i][1]);
    }

    // Find the common point that overlaps with the most number of intervals.
    maxcommonintervals(intervals, count);

    // Close the file.
    fclose(fp);
}