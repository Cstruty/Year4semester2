#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#include <limits.h>
#define ROWS 12
#define COLS 12

int min_total = 0;
int matrix[ROWS][COLS];
int min_job[ROWS] = {0};
//factorial to find max possible size
int factorial(int n)
{
    int result = 1;
    for (int i = 2; i <= n; i++)
    {
        result *= i;
    }
    return result;
}

void permute(int *job, int *min_assignment, int i, int n)
{
    int j, temp;
    int cost;

    if (i == n)
    { // base case we've hit the end of the list and we can see if the sum is greated
        cost = 0;
        for (j = 0; j < n; j++)
        {
            cost += matrix[j][job[j]]; // compute cost for this permutation
        }
        if (cost > min_total)
        { // update minimum cost and assignment
            min_total = cost;
            for (j = 0; j < n; j++)
            {
                min_assignment[j] = job[j];
            }
        }
    }
    else
    {
        for (j = i; j < n; j++)
        { // recursive case
            temp = job[i];
            job[i] = job[j];
            job[j] = temp;
            //kinda same as P12 where were jumping at the way to the end to see the sum
            permute(job, min_assignment, i + 1, n);
            temp = job[i];
            job[i] = job[j];
            job[j] = temp;
        }
    }
}
//printing for testing purposes
void printmatrix(int matrix[ROWS][COLS])
{
    int i, j;
    for (i = 0; i < ROWS; i++)
    {
        for (j = 0; j < COLS; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

int main()
{
    FILE *fp;
    struct timespec start, end;
    int i, j;
    int job[ROWS];

    int rearranged[ROWS];
    int posassignments = factorial(ROWS);
    char file_name[50] = "data_A5_Q2_1.txt";
    printf("Brute force program for assignment problem\n");
    printf("Enter the file name: ");
    scanf("%s", file_name);
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

    timespec_get(&start, TIME_UTC);
    permute(job, min_job, 0, ROWS);
    timespec_get(&end, TIME_UTC);
    long int elapsed_time_ns = (end.tv_sec - start.tv_sec) * 1000 + (end.tv_nsec - start.tv_nsec) / 1000000.0;
    //flipping the job array, I built it the wrong way but I flip it to what it should be
    for (int i = 0; i < ROWS; i++)
    {
        rearranged[min_job[i]] = i + 1;
    }
    //printing
    printf("The number of all possible assignments: %d\n", posassignments);
    printf("Maximum total value: %d\n", min_total);
    printf("The person-job assignment selected:\n");
    for (i = 0; i < ROWS; i++)
    {
        printf("%d ", rearranged[i]);
    }
    printf("\n");

    printf("Execution time = %ld ms\n", elapsed_time_ns);

    fclose(fp);
    return 0;
}
