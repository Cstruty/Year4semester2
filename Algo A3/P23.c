//Collin Struthers sun mar 12 2023 1084915 A3
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <float.h>
#include <ctype.h>
#include <stdbool.h>
#define MAX_LENGTH 44049

int badchar[256];
int goodchar[256];
int max(int a, int b) { return (a > b) ? a : b; }
//making the bad char table
void badchartable(char *pattern)
{
    int i;
    int patternlength = strlen(pattern) - 1;
    for (i = 0; i < 256; i++)
    {
        //getting otehr values
        badchar[i] = -1;
    }
    for (i = 0; i < patternlength - 1; i++)
    { //getting the values from the pattern
        badchar[(int)pattern[i]] = i;
    }
}

void boyermoore(char *text, char *pattern)
{
    struct timespec start, end;
    int length, i, patterncount, patternlength, shifts;
    patternlength = strlen(pattern) - 1;
    patterncount = 0;
    shifts = 0;
    length = strlen(text);
    timespec_get(&start, TIME_UTC);
    badchartable(pattern);

    i = 0;
    int j = 0;
    while (j <= length - patternlength)
    {

        i = patternlength - 1;

        //decrements if the same
        while (i >= 0 && (pattern[i] == text[i + j]))
        {

            i--;
        }

        //adds to patterncount if match and indexes using bad char
        if (i < 0)
        {
            patterncount++;
            j += (j + patternlength < length) ? patternlength - badchar[(int)text[j + patternlength]] : 1;
        }
        else
        {
            //increments usign bad char

            j += max(1, i - badchar[(int)text[i + j]]);
        }

        shifts++;
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
    fp = fopen("data_A3_Q2.txt", "r");
    char pattern[52];
    long filesize;
    // check if the file was successfully opened
    if (fp == NULL)
    {
        printf("Error Failure to open file\n");
        exit(1);
    }
    printf("Brute Force String Search\n");
    fseek(fp, 0, SEEK_END);
    filesize = ftell(fp);
    rewind(fp);
    // prompt the user for the pattern to search for
    printf("Please enter the pattern: \n");
    fgets(pattern, 52, stdin);
    char *text = malloc(sizeof(char) * filesize + 1);
    fread(text, 1, filesize, fp);

    text[filesize] = '\0';
    //search using boyer moore
    boyermoore(text, pattern);

    free(text);

    fclose(fp);
}