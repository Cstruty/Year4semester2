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
typedef struct wordcount
{
    char word[MAX_LEN];
    float count;
} WordCount;
float probability[MAX_WORDS][MAX_WORDS];
float cost[MAX_WORDS][MAX_WORDS];

typedef struct node
{
    char word[MAX_LEN];
    int frequency;

    struct node *left;
    struct node *right;
} Node;
// WordCount wordcount;
Node *createNode(char *word, int frequency)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    strcpy(newNode->word, word);
    newNode->frequency = frequency;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

void insert(Node **root, char *word, int frequency)
{
    if (*root == NULL)
    {
        *root = createNode(word, frequency);
    }
    else if (strcmp(word, (*root)->word) < 0)
    {
        insert(&(*root)->left, word, frequency);
    }
    else if (strcmp(word, (*root)->word) > 0)
    {
        insert(&(*root)->right, word, frequency);
    }
    else
    {
        (*root)->frequency += frequency;
    }
}
void printTree(Node *node)
{
    if (node == NULL)
    {
        return;
    }

    printTree(node->left);
    printf("%s (%d)\n", node->word, node->frequency);
    printTree(node->right);
}
// Build a subtree for a given range of words
// Node *buildSubtree(WordCount wordcount[MAX_WORDS], float probability[MAX_WORDS][MAX_WORDS], float cost[MAX_WORDS][MAX_WORDS], int i, int j)
// {
//     if (i > j)
//     {
//         return NULL;
//     }

//     float minCost = INFINITY;
//     int minRoot;
//     for (int r = i; r <= j; r++)
//     {
//         float c = ((r > i) ? cost[i][r - 1] : 0) +
//                   ((r < j) ? cost[r + 1][j] : 0) +
//                   probability[i][j];
//         if (c < minCost)
//         {
//             minCost = c;
//             minRoot = r;
//         }
//     }

//     Node *root = createNode(wordcount[minRoot].word, minCost);
//     root->left = buildSubtree(wordcount, probability, cost, i, minRoot - 1);
//     root->right = buildSubtree(wordcount, probability, cost, minRoot + 1, j);

//     return root;
// }
// Node *optimalBST(int n, WordCount wordcount[MAX_WORDS], float probability[MAX_WORDS][MAX_WORDS], float cost[MAX_WORDS][MAX_WORDS])
// {
//     Node *root = NULL;
//     float minCost;

//     // Compute cost for single-word trees
//     for (int i = 0; i < n; i++)
//     {
//         cost[i][i] = probability[i][i];
//         if (root == NULL)
//         {
//             root = createNode(wordcount[i].word, cost[i][i]);
//         }
//         else
//         {
//             insert(&root, wordcount[i].word, cost[i][i]);
//         }
//     }

//     // Compute cost for larger trees
//     for (int L = 2; L <= n; L++)
//     {
//         for (int i = 0; i <= n - L; i++)
//         {
//             int j = i + L - 1;
//             cost[i][j] = INFINITY;
//             for (int r = i; r <= j; r++)
//             {
//                 float c = ((r > i) ? cost[i][r - 1] : 0) +
//                           ((r < j) ? cost[r + 1][j] : 0) +
//                           probability[i][j];
//                 if (c < cost[i][j])
//                 {
//                     cost[i][j] = c;
//                     minCost = c;
//                     root = createNode(wordcount[r].word, cost[i][j]);
//                     root->left = buildSubtree(wordcount, probability, cost, i, r - 1);
//                     root->right = buildSubtree(wordcount, probability, cost, r + 1, j);
//                 }
//             }
//         }
//     }

//     return root;
// }

void search(Node *root, char *word)
{
    if (root == NULL)
    {
        printf("not found\n");
    }
    else if (strcmp(word, root->word) == 0)
    {
        printf("%s %.3f\n", root->word, root->frequency / (float)MAX_WORDS);
    }
    else if (strcmp(word, root->word) < 0)
    {
        printf("%s %.3f left\n", root->word, root->frequency / (float)MAX_WORDS);
        search(root->left, word);
    }
    else
    {
        printf("%s %.3f right\n", root->word, root->frequency / (float)MAX_WORDS);
        search(root->right, word);
    }
}

int main()
{

    char *filename = "data_A4_Q1.txt";
    FILE *fp = fopen(filename, "r"); // opens the file for reading
    if (fp == NULL)
    {
        printf("Failed to open file %s\n", filename);
        return 1;
    }
    char words[MAX_WORDS][MAX_LEN];
    int frequencies[MAX_WORDS] = {0};
    WordCount wordCounts[MAX_WORDS];
    char word[MAX_LEN];
    int totalWords = 0;
    int i = 0;
    while (fscanf(fp, "%s", word) != EOF)
    {

        // Convert word to lowercase
        for (int i = 0; i < strlen(word); i++)
        {
            word[i] = tolower(word[i]);
        }

        // Check if word already exists in wordCounts array
        int found = 0;
        for (int i = 0; i < totalWords; i++)
        {
            if (strcmp(wordCounts[i].word, word) == 0)
            {
                wordCounts[i].count++;
                found = 1;
                break;
            }
        }

        // If word not found, add it to wordCounts array
        if (!found)
        {
            strcpy(wordCounts[totalWords].word, word);
            wordCounts[totalWords].count = 1;
            totalWords++;
        }

        // Check if we've exceeded the maximum number of words
        if (totalWords >= MAX_WORDS)
        {
            printf("Exceeded maximum number of words (%d)\n", MAX_WORDS);
            break;
        }
    }

    fclose(fp);
    // float probability[MAX_WORDS][MAX_WORDS];
    memset(probability, 0, sizeof(probability[0][0]) * MAX_WORDS * MAX_WORDS);
    memset(cost, 0, sizeof(cost[0][0] * MAX_WORDS * MAX_WORDS));
    printf("words=%d\n", totalWords);
    for (int i = 0; i < totalWords; i++)
    {
        probability[i][i] = (float)(wordCounts[i].count / MAX_WORDS) * 100;
        if (strcmp(wordCounts[i].word, "of") == 0)
        {
            printf("count=%f\n", wordCounts[i].count);
            printf("prob=%f\n", probability[i][i]);
        }
        for (int j = i + 1; j < totalWords; j++)
        {
            wordCounts[i].count += wordCounts[j].count;
            probability[i][j] = (float)(frequencies[i] / MAX_WORDS) * 100;
        }
    }
    for (i = 0; i < totalWords; i++)
    {
        // if (strcmp(wordCounts[i].word, "undergraduate") == 0)
        // {
        // wordCounts[i].count = wordCounts[i].count / totalWords;
        // printf("prob=%f", probability)
        // printf("freq=%f  word=%s\n", wordCounts[i].count, wordCounts[i].word);
        // }
    }
    // Node *root = optimalBST(totalWords, wordCounts, probability, cost);
    // printTree(root);
    // char query[MAX_LEN];
    // while (1)
    // {
    //     printf("Enter a word to search for (or 'q' to quit): ");
    //     scanf("%s", query);
    //     if (strcmp(query, "q") == 0)
    //     {
    //         break;
    //     }
    //     search(root, query);
    // }
    return 0;
}