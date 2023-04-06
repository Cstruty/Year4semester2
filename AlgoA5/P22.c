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
int initmax = 0;
bool finaltaken[ROWS] = {false};
int runningtotal = 0;
// void findInitHighest()
// {
//     int i, j, max = 0, temp = 0;

//     for (i = 0; i < ROWS; i++)
//     {
//         temp = 0;
//         for (j = 0; j < COLS; j++)
//         {
//             if (matrix[i][j] > temp)
//             {
//                 temp = matrix[i][j];
//             }
//         }
//         printf("temp=%d\n", temp);
//         max += temp;
//     }
//     initmax = max;
//     printf("initmax= %d\n", initmax);
// }
int finaltotal = 0;
int finalindex = 0;
void findHighest(int start)
{
    bool taken[ROWS] = {false};
    int i, j;
    int max = 0;
    int index = 0;
    int total = 0;
    int currentvalue = 0;
    finaltotal = 0;
    finalindex = 0;
    for (int k = 0; k < ROWS; k++)
    {
        if (finaltaken[k] == false)
        {
            currentvalue = matrix[start][k];
            taken[k] = true;
            // printf("current value %d k=%d\n", currentvalue, k);
            total = 0;
            for (i = start + 1; i < ROWS; i++)
            {
                max = 0;
                for (j = 0; j < ROWS; j++)
                {
                    if (taken[j] == false && matrix[i][j] > max && finaltaken[j] == false)
                    {
                        // printf("hello\n");
                        index = j;
                        max = matrix[i][j];
                    }
                }
                taken[index] = true;
                // printf("%d\n", matrix[i][index]);
                total += matrix[i][index];
            }
            for (j = 0; j < ROWS; j++)
            {
                taken[j] = false;
            }
            if (total + currentvalue > finaltotal)
            {

                finaltotal = total + currentvalue;
                finalindex = k;
                // printf("start =%d total=%d index=%d current value=%d\n", start, finaltotal, finalindex, currentvalue);
            }
        }
    }
    runningtotal += currentvalue;
    printf("start =%d total=%d index=%d current value=%d\n", start, finaltotal, finalindex, currentvalue);
    finaltaken[finalindex] = true;
}
void branchandbound()
{
    int found = 0;
    //all the rows had to have been found for the while loop to finish
    while (found < ROWS - 1)
    {
        findHighest(found);
        // return;
        found++;
    }
}
int main()
{
    FILE *fp;
    struct timespec start, end;
    int i, j;
    int job[ROWS];

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
    // findInitHighest();
    timespec_get(&start, TIME_UTC);
    timespec_get(&end, TIME_UTC);
    branchandbound();
    long int elapsed_time_ns = (end.tv_sec - start.tv_sec) * 1000 + (end.tv_nsec - start.tv_nsec) / 1000000.0;
    //flipping the job array, I built it the wrong way but I flip it to what it should be
    // for (int i = 0; i < ROWS; i++)
    // {
    //     rearranged[min_job[i]] = i + 1;
    // }

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
