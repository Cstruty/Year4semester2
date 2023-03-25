#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#define MAX_WORDS 2045
#define MAX_LEN 50
int **men_rank;
int **women_rank;
int **marriages;
int size;
void printtable(int size, int **table)
{
    for (int i = 0; i < size; i++)
    {
        for (int j = 0; j < size; j++)
        {
            printf("%d\t", table[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}
// helper function to check if a woman is free
bool isWomanFree(int engaged_to[])
{

    for (int i = 0; i < size; i++)
    {
        if (engaged_to[i] == -1)
        {
            return true;
        }
    }

    return false;
}

// helper function to check if a man prefers a woman over his current partner
bool doesManPrefer(int **women_rank, int m, int w, int m1)
{
    for (int i = 0; i < size; i++)
    {
        if (women_rank[w][i] == m)
        {
            return true;
        }
        if (women_rank[w][i] == m1)
        {
            return false;
        }
    }
    return false;
}

// function to perform the stable marriage algorithm
void stableMarriage(int **men_rank, int **women_rank, int **marriages)
{

    int men_engaged[size];   // index of woman currently engaged to (-1 if not engaged)
    int women_engaged[size]; // index of man currently engaged to (-1 if not engaged)
    for (int i = 0; i < size; i++)
    {
        men_engaged[i] = -1;
        women_engaged[i] = -1;
    }
    int free_count = size; // number of free women

    while (free_count > 0)
    {
        // find a free man
        int m;
        for (m = 0; m < size; m++)
        {
            if (men_engaged[m] == -1)
            {
                break;
            }
        }
        // iterate over the man's preference list
        for (int i = 0; i < size && men_engaged[m] == -1; i++)
        {

            int w = men_rank[m][i];
            // if the woman is free, engage the man and woman
            if (women_engaged[w] == -1)
            {

                women_engaged[w] = m;
                men_engaged[m] = w;

                free_count--;
            }
            else
            {
                // if the woman prefers the man over her current partner, engage the man and woman
                int m1 = women_engaged[w];
                if (doesManPrefer(women_rank, m, w, m1))
                {

                    men_engaged[m1] = -1;
                    women_engaged[w] = m;
                    men_engaged[m] = w;
                }
            }
        }
    }
    //populate the marriage table
    for (int i = 0; i < size; i++)
    {
        marriages[i][men_engaged[i]] = 1;
    }
}
int main()
{
    char filename[MAX_LEN] = "data_A4_Q2.txt";
    FILE *fp = fopen(filename, "r"); // opens the file for reading
    if (fp == NULL)
    {
        printf("Error opening file.\n");
        return 1;
    }
    fscanf(fp, "%d", &size);
    //initializing
    men_rank = malloc(size * sizeof(int *));
    women_rank = malloc(size * sizeof(int *));
    marriages = malloc(size * sizeof(int *));
    int i = 0, j = 0;
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            men_rank[i] = (int *)malloc(size * sizeof(int));
            women_rank[i] = (int *)malloc(size * sizeof(int));
            marriages[i] = (int *)malloc(size * sizeof(int));
        }
    }
    //populating all the tables
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            fscanf(fp, "%d", &men_rank[i][j]);
            men_rank[i][j]--;
        }
    }
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            fscanf(fp, "%d", &women_rank[i][j]);
            women_rank[i][j]--;
        }
    }
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            marriages[i][j] = 0;
        }
    }
    //find the stable marraiges and print them
    stableMarriage(men_rank, women_rank, marriages);
    printtable(size, marriages);
    //freeing
    for (i = 0; i < size; i++)
    {
        free(women_rank[i]);
        free(men_rank[i]);
        free(marriages[i]);
    }

    free(women_rank);
    free(men_rank);
    free(marriages);
    return 0;
}