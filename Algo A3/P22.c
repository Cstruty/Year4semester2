//Collin Struthers mar 12 2023 1084915 A3
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <stdbool.h>

#define MAX_LENGTH 44049

int table[256];

void shifttable(char pattern[])
{
    int i, patternlength;
    patternlength = strlen(pattern) - 1;

    // Initialize all entries in table with patternlength
    for (i = 0; i < 256; i++)
    {
        table[i] = patternlength;
    }

    // Update table with actual values from pattern
    for (i = 0; i < patternlength - 1; i++)
    {
        table[(int)pattern[i]] = patternlength - 1 - i;
    }
}

void horspool(char *text, char *pattern)
{
    struct timespec start, end;
    int length, i, matchsofar, patterncount, patternlength, shifts;
    patternlength = strlen(pattern) - 1;
    patterncount = 0;
    shifts = 0;
    length = strlen(text);
    timespec_get(&start, TIME_UTC);
    shifttable(pattern);

    i = patternlength;
    while (i <= length - 1)
    {
        matchsofar = 0;
        //so far it is a match
        while (matchsofar < patternlength && (pattern[patternlength - 1 - matchsofar] == text[i - matchsofar]))
        {
            matchsofar++;
        }
        //if it ends up being a match add to pattern count
        if (matchsofar == patternlength)
        {
            patterncount++;
        }
        //whatever value we started on, we use the table to shift that amount
        shifts++;
        i += table[(int)text[i]];
    }

    timespec_get(&end, TIME_UTC);
    long int elapsed_time_ns = (end.tv_sec - start.tv_sec) * 1000 + (end.tv_nsec - start.tv_nsec) / 1000000.0;

    printf("Count = %d\n", patterncount);
    printf("Shifts= %d\n", shifts);
    printf("Elapsed time: %ld ms\n", elapsed_time_ns);
}

int main(void)
{
    FILE *fp;
    char pattern[52];
    long filesize;

    // Open file
    fp = fopen("data_A3_Q2.txt", "r");

    if (fp == NULL)
    {
        printf("Error: Failed to open file\n");
        exit(1);
    }

    // Get file size
    fseek(fp, 0, SEEK_END);
    filesize = ftell(fp);
    rewind(fp);

    printf("Please enter the pattern: \n");
    fgets(pattern, 52, stdin);

    char *text = malloc(sizeof(char) * filesize + 1);
    fread(text, 1, filesize, fp);
    text[filesize] = '\0';
    //search using horspool
    horspool(text, pattern);

    free(text);
    fclose(fp);

    return 0;
}
