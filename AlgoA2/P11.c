#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define MAX_LENGTH 50000
//Collin Struthers 1084915 Assignment 2 feb 12 2023
//this program uses the bruteforce algorithm to sort an array and tells the number of inversion and the sort time
int selection_sort(int Arr[], int n)
{
    //this is the selection sort function to count how many are there
    int count = 0;
    for (int i = 0; i < n; i++)
    {
        for (int j = i + 1; j < n; j++)
        {
            if (Arr[i] > Arr[j])
            {
                count++;
            }
        }
    }
    return count;
}
int main(void)
{
    struct timespec start, end;
    FILE *fp;
    int i = 0;
    int count = 0;
    //opening file
    fp = fopen("data_A2_Q1.txt", "r");
    if (fp == NULL)
    {
        printf("test\n");
    }
    int Arr[MAX_LENGTH];
    int value;
    //putting it into aray
    for (i = 0; i < MAX_LENGTH; i++)
    {
        fscanf(fp, "%d", &value);
        Arr[i] = value;
    }

    // Close the file
    fclose(fp);
    //sorting array and getting count and time execution
    timespec_get(&start, TIME_UTC);
    count = selection_sort(Arr, MAX_LENGTH);
    timespec_get(&end, TIME_UTC);
    long int elapsed_time_ns = (end.tv_sec - start.tv_sec) * 1000 + (end.tv_nsec - start.tv_nsec) / 1000000.0;
    printf("Elapsed time: %ld ms\n", elapsed_time_ns);
    printf("Count = %d\n", count);
    // Print the contents of the int array
}