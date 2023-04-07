#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#define MAX_SIZE 25

int main()
{

    char file_name[50] = "data_A5_Q1_1.txt";
    int subset_sum = 1200, num_subsets = 0, num_valid_subsets = 0;
    struct timespec start, end;

    //getting file and sum
    printf("Brute force program for subset sum problem\n");
    printf("Enter the file name and subset sum: \n");
    scanf("%s %d", file_name, &subset_sum);
    FILE *fp = fopen(file_name, "r");
    //if file cannot be open
    if (fp == NULL)
    {
        printf("Error: File not found!\n");
        return 1;
    }

    int set[MAX_SIZE];
    int i = 0;
    while (fscanf(fp, "%d", &set[i]) != EOF)
    {
        i++;
    }

    fclose(fp);
    int num_subsets_possible = 1 << MAX_SIZE; // 2^n subsets possible
    timespec_get(&start, TIME_UTC);
    for (int i = 0; i < num_subsets_possible; i++)
    {
        // Initialize sum and j to zero for each subset
        int sum = 0;
        int j = i;

        // Loop through each element of the set
        for (int k = 0; k < MAX_SIZE; k++)
        {
            // determine if the kth element should be added to the subset sum
            // by checking if the kth bit of j is set to 1
            if (j % 2 == 1)
            {
                sum += set[k];
            }

            // shift right to check the next bit of j for the next element in the subset
            j = j / 2;
        }

        // increment the count of subsets checked
        num_subsets++;

        // if the sum of the current subset equals the desired subset_sum, increment count of valid subsets
        if (sum == subset_sum)
        {
            num_valid_subsets++;
        }
    }
    //printing out results
    timespec_get(&end, TIME_UTC);
    long int elapsed_time_ns = (end.tv_sec - start.tv_sec) * 1000 + (end.tv_nsec - start.tv_nsec) / 1000000.0;
    printf("Number of all the subsets: %d\n", num_subsets);
    printf("Number of the subsets whose sums are %d: %d\n", subset_sum, num_valid_subsets);
    printf("Execution time = %ld ms\n", elapsed_time_ns);
    return 0;
}
