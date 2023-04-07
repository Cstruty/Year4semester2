#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#define MAX_SIZE 25
int set[MAX_SIZE];
int subset_sum = 1200, num_subsets = 0, dead_end = 0;
void Backtrack(int start, int sum, int size)
{
    //going all the way to the end, it is found that the sum is equal to sum set sum
    //so +1 is added to count
    if (sum == subset_sum)
    {
        num_subsets++;
        return;
    }
    if (start == size || sum > subset_sum)
    {
        //dead end reached, we've reached the end of the array
        //or the current sum is greater than the sum were trying to find
        dead_end++;
        return;
    }
    //doing the same as P11 we start at start, then iterate through and
    //what is different is now we recursively call backtrack adding the sum of the current index
    //to the sum
    for (int i = start; i < size; i++)
    {

        Backtrack(i + 1, sum + set[i], size);
    }
}
int main()
{

    char file_name[50] = "data_A5_Q1_1.txt";

    struct timespec start, end;

    //getting file and sum
    printf("Backtracking program for subset sum problem\n");
    printf("Enter the file name and subset sum: \n");
    scanf("%s %d", file_name, &subset_sum);
    FILE *fp = fopen(file_name, "r");
    //if file cannot be open
    if (fp == NULL)
    {
        printf("Error: File not found!\n");
        return 1;
    }
    int i = 0;
    while (fscanf(fp, "%d", &set[i]) != EOF)
    {
        i++;
    }

    fclose(fp);
    timespec_get(&start, TIME_UTC);
    Backtrack(0, 0, MAX_SIZE);
    //printing out results

    timespec_get(&end, TIME_UTC);
    long int elapsed_time_ns = (end.tv_sec - start.tv_sec) * 1000 + (end.tv_nsec - start.tv_nsec) / 1000000.0;
    printf("Number of dead ends: %d\n", dead_end);
    printf("Number of the subsets whose sums are %d: %d\n", subset_sum, num_subsets);
    printf("Execution time = %ld ms\n", elapsed_time_ns);
    return 0;
}
