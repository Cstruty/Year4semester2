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

int finalindex = 0;
int runningtotal = 0;
int findHighest2(int start)
{
    int i, j;
    int max = 0;
    int index = 0;
    int total = 0;
    int currentvalue = 0;
    int finaltotal = 0;
    //go through all the current values that were at
    for (int k = 0; k < ROWS; k++)
    {
        //if it hasn't been used we go through and calculate cost
        if (!used[k])
        {
            currentvalue = matrix[start][k];

            total = 0;
            used[k] = 1;
            //starting at one below the current index we count cost
            for (i = start + 1; i < ROWS; i++)
            {
                max = 0;
                for (j = 0; j < ROWS; j++)
                {
                    //find the max value for the current person
                    if (matrix[i][j] > max && !used[j])
                    {

                        index = j;
                        max = matrix[i][j];
                    }
                }

                //add to a total
                total += matrix[i][index];
            }
            //if for the person cost (k) total is greater than what
            //has been found so far, we replace the finaltotal
            if (total + currentvalue > finaltotal)
            {

                finaltotal = total + currentvalue;
                finalindex = k;
            }
            //make sure to set the used back to 0
            used[k] = 0;
        }
    }
    printf("Maximum upper bound: %d\n", finaltotal + runningtotal);
    return matrix[start][finalindex];
}

void branchandbound(int job[ROWS])
{
    int remaining_ub;
    for (int i = 0; i < ROWS; i++)
    {
        //this goes through each level, finds the maximum upper bound
        remaining_ub = findHighest2(i);
        //then sets that col to used
        used[finalindex] = 1;
        //puts the index in the job array
        job[i] = finalindex;
        //adds value to running total
        runningtotal += remaining_ub;
    }
    return;
}
int main()
{
    FILE *fp;
    struct timespec start, end;
    int i, j;
    int job[ROWS] = {0};
    int rearranged[ROWS];
    char file_name[50] = "data_A5_Q2_1.txt";
    printf("Branch and bound program for assignment problem\n");
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
    branchandbound(job);

    //flipping the job array, I built it the wrong way but I flip it to what it should be
    for (int i = 0; i < ROWS; i++)
    {
        rearranged[job[i]] = i + 1;
    }

    //printing stuff off
    for (i = 0; i < ROWS; i++)
    {
        printf("%d ", rearranged[i]);
    }
    printf("\n");
    timespec_get(&end, TIME_UTC);
    printf("Max total value: %d\n", runningtotal);
    long int elapsed_time_ns = (end.tv_sec - start.tv_sec) * 1000 + (end.tv_nsec - start.tv_nsec) / 100000.0;
    printf("Execution time = %ld ms\n", elapsed_time_ns);

    fclose(fp);
    return 0;
}
