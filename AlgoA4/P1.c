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
    n = read_words(fp);
    if (n <= 0)
    {
        printf("Error: File is empty.\n");
        exit(1);
    }
    fclose(fp);
    calc_tables(n);
    search_bst(n);
    return 0;
}
