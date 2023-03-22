//Collin Struthers mar 12 2023 1084915 A3
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <float.h>
#include <stdbool.h>

#define MAX_LENGTH 44049

void bruteforce(FILE *fp, char *pattern)
{
    // variables to keep track of timing, the current word, and the length of the word
    struct timespec start, end;
    char currentword[512];
    int length, i, matchsofar, patterncount, patternlength, j, shifts;

    // get length of pattern
    patternlength = strlen(pattern) - 1;
    patterncount = 0;
    shifts = 0;

    timespec_get(&start, TIME_UTC);

    // iterate over every word in the file
    while (fgets(currentword, 512, fp) != NULL)
    {
        length = strlen(currentword);

        currentword[length] = '\0';

        // reset the match count and the pattern index
        matchsofar = 0;
        j = 0;

        // iterate over every character in the current word
        for (i = 0; i < length - 1; i++)
        {
            if (pattern[j] == currentword[i])
            {
                // if the characters match, increment the match count and the pattern index
                matchsofar++;
                j++;
            }
            else
            {
                // if the characters don't match, reset the match count and the pattern index
                matchsofar = 0;
                j = 0;
            }

            // if we have a complete match, increment the pattern count, reset the match count and the pattern index
            if (matchsofar == patternlength)
            {
                patterncount++;
                matchsofar = 0;
                j = 0;
            }

            // increment the shift count
            shifts++;
        }
    }

    timespec_get(&end, TIME_UTC);
    long int elapsed_time_ns = (end.tv_sec - start.tv_sec) * 1000 + (end.tv_nsec - start.tv_nsec) / 1000000.0;

    // print the counts and timing information
    printf("Count = %d\n", patterncount);
    printf("Shifts= %d\n", shifts);
    printf("Elapsed time: %ld ms\n", elapsed_time_ns);
}

int main(void)
{
    FILE *fp;
    char pattern[52];

    fp = fopen("data_A3_Q2.txt", "r");

    // check if the file was successfully opened
    if (fp == NULL)
    {
        printf("Error Failure to open file\n");
        exit(1);
    }

    // prompt the user for the pattern to search for
    printf("Brute Force String Search\n");
    printf("Please enter the pattern: \n");
    fgets(pattern, 52, stdin);

    // search for the pattern using the brute force algorithm
    bruteforce(fp, pattern);

    // close the input file
    fclose(fp);

    return 0;
}
