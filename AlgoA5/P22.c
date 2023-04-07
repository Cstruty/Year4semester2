#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#include <limits.h>

#define ROWS 12
#define COLS 12

int matrix[ROWS][COLS];
int used[ROWS] = {0};
int max_job[ROWS] = {0};
int best_cost = INT_MIN;
int findInitHighest()
{
    int i, j, max = 0, temp = 0;

    for (i = 0; i < ROWS; i++)
    {
        temp = 0;
        for (j = 0; j < COLS; j++)
        {
            if (matrix[i][j] > temp)
            {
                temp = matrix[i][j];
            }
        }
        max += temp;
    }
    return max;
}
int findHighest(int start)
{
    int i, j, max = 0;

    for (i = start; i < ROWS; i++)
    {
        for (j = 0; j < COLS; j++)
        {
            if (matrix[i][j] > max && !used[j])
            {
                max = matrix[i][j];
            }
        }
    }
    return max;
}
int finalindex = 0;
int maxupperbound = 0;
int runningtotal = 0;
int findHighest2(int start)
{
    int i, j;
    int max = 0;
    int index = 0;
    int total = 0;
    int currentvalue = 0;
    int finaltotal = 0;

    for (int k = 0; k < ROWS; k++)
    {
        if (!used[k])
        {
            currentvalue = matrix[start][k];
            // printf("currentvalue=%d\n", currentvalue);
            // printf("current value %d k=%d\n", currentvalue, k);
            total = 0;
            used[k] = 1;
            // printf("start=%d\n", start);
            for (i = start + 1; i < ROWS; i++)
            {
                max = 0;
                for (j = 0; j < ROWS; j++)
                {
                    if (matrix[i][j] > max && !used[j])
                    {
                        // printf("hello\n");
                        index = j;
                        max = matrix[i][j];
                    }
                }

                // printf("%d\n", matrix[i][index]);
                // if (k == 3)
                // {
                //     printf("i=%d index=%d value=%d\n", i, index + 1, max);
                // }
                total += matrix[i][index];
            }
            if (total + currentvalue > finaltotal)
            {

                finaltotal = total + currentvalue;
                finalindex = k;
            }
            used[k] = 0;
        }
    }
    printf("finaltotal=%d\n", finaltotal + runningtotal);
    return matrix[start][finalindex];
}

void branchandbound(int assignments[ROWS], int index, int total, int initmax)
{
    int remaining_ub;
    for (int i = 0; i < ROWS; i++)
    {
        remaining_ub = findHighest2(i);
        used[finalindex] = 1;
        runningtotal += remaining_ub;
    }
    // = findHighest2(index);
    // runningtotal += remaining_ub;
    // remaining_ub = findHighest2(index + 1);
    // runningtotal += remaining_ub;
    return;
    // printf("remaining=%d\n", remaining_ub);
    // return;
    // printf("person=%d job value=%d\n", ROWS - index, remaining_ub);
    //not as good as our best cost
    // return 0;
    if (total + remaining_ub <= best_cost)
    {

        return;
    }
    //if at end it will assign things
    if (index == ROWS)
    {
        if (total > best_cost)
        {
            printf("total= %d\n", total + remaining_ub);
            best_cost = total;
            for (int i = 0; i < ROWS; i++)
            {
                max_job[i] = assignments[i];
            }
        }
        return;
    }
    for (int j = 0; j < ROWS; j++)
    {
        if (!used[j])
        {
            used[j] = 1;
            assignments[index] = j;
            branchandbound(assignments, index + 1, total + matrix[index][j], initmax);
            used[j] = 0;
        }
    }
}
int main()
{
    FILE *fp;
    struct timespec start, end;
    int i, j;
    int job[ROWS];
    int assignment[ROWS] = {0};
    int rearranged[ROWS];

    fp = fopen("data_A5_Q2_1.txt", "r");
    if (fp == NULL)
    {
        printf("Error: could not open file.\n");
        return 1;
    }

    // Read matrix from file
    for (i = 0; i < ROWS; i++)
    {
        for (j = 0; j < COLS; j++)
        {
            fscanf(fp, "%d", &matrix[i][j]);
        }
    }
    for (i = 0; i < ROWS; i++)
    {
        job[i] = i; // initialize array with indices
    }

    // Brute force algorithm
    //assign jobs in order for first run
    int initmax = findInitHighest();
    timespec_get(&start, TIME_UTC);
    branchandbound(assignment, 0, 0, initmax);
    timespec_get(&end, TIME_UTC);

    long int elapsed_time_ns = (end.tv_sec - start.tv_sec) * 1000 + (end.tv_nsec - start.tv_nsec) / 1000000.0;
    //flipping the job array, I built it the wrong way but I flip it to what it should be
    // for (int i = 0; i < ROWS; i++)
    // {
    //     rearranged[min_job[i]] = i + 1;
    // }

    // printf("Maximum total value: %d\n", min_total);
    // printf("The person-job assignment selected:\n");
    for (i = 0; i < ROWS; i++)
    {
        printf("%d ", max_job[i]);
    }
    printf("\n");

    printf("Execution time = %ld ms\n", elapsed_time_ns);

    fclose(fp);
    return 0;
}
