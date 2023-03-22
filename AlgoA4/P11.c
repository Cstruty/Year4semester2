#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <float.h>
#include <ctype.h>
#include <stdbool.h>
#include <string.h>
#include <unistd.h>
#define MAX_WORDS 2045
#define MAX_LEN 50
int freq[MAX_WORDS];
//gets the freq of each word
void read_freq(FILE *fp)
{
    int i = 0;
    while (!feof(fp) && i < MAX_WORDS)
    {
        fscanf(fp, "%d", &freq[i]);
        i++;
    }
}
//gets each words and stores in array
int read_words(FILE *fp)
{
    int i = 0;
    while (!feof(fp) && i < MAX_WORDS)
    {
        fscanf(fp, "%s", words[i]);
        i++;
    }
    return i;
}
int main()
{
    int i, n;
    FILE *fp;
    fp = fopen("data A4 Q1.txt", "r");
    if (fp == NULL)
    {
        printf("Error: Unable to open file.\n");
        exit(1);
    }
    n = read_freq(fp);
    if (n <= 0)
    {
        printf("Error: File is empty.\n");
        exit(1);
    }
    // n = read_words(fp);
    // if (n <= 0)
    // {
    //     printf("Error: File is empty.\n");
    //     exit(1);
    // }
    // fclose(fp);
    // calc_tables(n);
    // search_bst(n);
    return 0;
}
