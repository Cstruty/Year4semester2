#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#define MAX_LENGTH 50000
//Collin Struthers 1084915 Assignment 2 feb 12 2023
//this program uses the mergesort algorithm to sort an array and tells the number of inversion and the sort time
int merge(int Arr[], int left, int mid, int right)
{
    int count = 0;
    int len1 = mid - left + 1;
    int len2 = right - mid;
    int temp1[len1], temp2[len2];
    int i, j, k;
    //put left side into temp1 array
    for (i = 0; i < len1; i++)
    {
        temp1[i] = Arr[left + i];
    }
    //put right side into temp2 array
    for (i = 0; i < len2; i++)
    {
        temp2[i] = Arr[mid + i + 1];
    }
    i = 0;
    j = 0;
    k = left;
    //go through both arrays and check if values are greater, if so swap
    while (i < len1 && j < len2)
    {
        if (temp1[i] > temp2[j])
        {

            Arr[k] = temp2[j];
            j++;
            count += (mid - i - left + 1);
        }
        else
        {
            Arr[k] = temp1[i];
            i++;
        }
        k++;
    }
    //j or i can be greater than len1 or len2
    //we have to make sure if that happens that we still add the rest of the sorted array into
    //orignal array, for that reason we have these while loops
    while (i < len1)
    {
        Arr[k] = temp1[i];
        k++;
        i++;
    }
    while (j < len2)
    {
        Arr[k] = temp2[j];
        k++;
        j++;
    }
    return count;
}
int mergesort(int Arr[], int left, int right)
{
    //splits the array into left and right
    int mid = 0;
    int count = 0;

    if (left < right)
    {
        mid = left + (right - left) / 2;
        count = mergesort(Arr, left, mid);
        count += mergesort(Arr, mid + 1, right);
        count += merge(Arr, left, mid, right);
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
        printf("Error Failure to open file\n");
        exit(1);
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
    count = mergesort(Arr, 0, MAX_LENGTH - 1);
    timespec_get(&end, TIME_UTC);
    long int elapsed_time_ns = (end.tv_sec - start.tv_sec) * 1000 + (end.tv_nsec - start.tv_nsec) / 1000000.0;
    printf("Elapsed time: %ld ms\n", elapsed_time_ns);
    printf("Count = %d\n", count);
    // Print the contents of the int array
}