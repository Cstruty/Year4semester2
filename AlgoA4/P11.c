//Collin Struthers A4 1084915 March 25 2023
//This function make a optimal binary search tree
#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <float.h>
#define MAX_WORDS 2045
#define MAX_LEN 50
//node
typedef struct node
{
    float Prob;
    char word[MAX_LEN];
    struct node *left;
    struct node *right;
} Node;
int R[MAX_WORDS][MAX_WORDS] = {0};
float C[MAX_WORDS][MAX_WORDS] = {0};
//node creation
Node *createNode(char key[MAX_LEN], float P)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    strcpy(newNode->word, key);
    newNode->Prob = P;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}
//freeing tree
void freeTree(Node *root)
{
    if (root != NULL)
    {
        freeTree(root->left);
        freeTree(root->right);
        free(root);
    }
}
void sort_strings(char arr[MAX_WORDS][MAX_LEN], int n, int count[MAX_WORDS])
{
    // Bubble sort algorithm using a for loop
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            char temp[MAX_LEN];
            int tempint = count[j];
            strcpy(temp, arr[j]);
            if (strcmp(arr[j], arr[j + 1]) > 0)
            {
                //swap string and count
                count[j] = count[j + 1];
                count[j + 1] = tempint;
                strcpy(arr[j], arr[j + 1]);
                strcpy(arr[j + 1], temp);
            }
        }
    }
}
//creating optimal BST
int optimalBST(char keys[MAX_WORDS][MAX_LEN], int n, float P[MAX_WORDS])
{
    int i, j, k, d;
    float minval = 0.0, sum;
    minval = DBL_MAX;
    memset(C, 0.0, sizeof(C[0][0]) * n * n);
    for (i = 1; i <= n; i++)
    {
        C[i][i - 1] = 0;
        C[i][i] = P[i];
        R[i][i] = i;
    }
    C[n + 1][n] = 0;

    for (d = 1; d <= n - 1; d++)
    {
        for (i = 1; i <= n - d; i++)
        {
            j = i + d;
            minval = DBL_MAX;
            for (k = i; k <= j; k++)
            {
                if (C[i][k - 1] + C[k + 1][j] < minval)
                {
                    minval = C[i][k - 1] + C[k + 1][j];
                    R[i][j] = k;
                }
            }
            sum = P[i];
            for (k = i + 1; k <= j; k++)
            {
                sum += P[k];
            }
            C[i][j] = minval + sum;
        }
    }

    return C[1][n];
}
//print tree for testing
void printTree(Node *root, int level)
{
    if (root == NULL)
    {
        return;
    }
    printTree(root->right, level + 1); // recursively print the right subtree
    for (int i = 0; i < level; i++)
    {
        printf("\t"); // print tabs to show depth of current node
    }
    printf("%s %f\n", root->word, root->Prob); // print the word stored in the current node
    printTree(root->left, level + 1);          // recursively print the left subtree
}
//creates the optimal BST by using the R array
Node *buildOptimalBST(char keys[MAX_WORDS][MAX_LEN], int R[][MAX_WORDS], int i, int j, float P[MAX_WORDS])
{
    if (i >= j)
    {
        return NULL;
    }
    int rootIndex = R[i][j];
    Node *root = createNode(keys[rootIndex], C[i][j]);
    root->left = buildOptimalBST(keys, R, i, rootIndex - 1, P);
    root->right = buildOptimalBST(keys, R, rootIndex + 1, j, P);
    return root;
}
void search(Node *root, char *word)
{
    //searches the function using STRCMP
    if (root == NULL)
    {
        printf("not found\n");
    }
    else if (strcmp(root->word, word) == 0)
    {
        printf("Compared with %s (%.3f), found\n", root->word, root->Prob);
    }
    else if (strcmp(root->word, word) > 0)
    {
        printf("Compared with %s (%.3f), go left subtree\n", root->word, root->Prob);
        search(root->left, word);
    }
    else
    {
        printf("Compared with %s (%.3f), go right subtree\n", root->word, root->Prob);
        search(root->right, word);
    }
}
int main()
{
    char filename[MAX_LEN] = "data_A4_Q1.txt";

    char word[MAX_LEN], keys[MAX_WORDS][MAX_LEN];
    int totalWords = 0, found = 0;
    float probability[MAX_WORDS] = {0};
    int count[MAX_WORDS] = {0};
    FILE *fp = fopen(filename, "r"); // opens the file for reading
    while (fscanf(fp, "%s", word) != EOF)
    {

        // Convert word to lowercase
        for (int i = 0; i < strlen(word); i++)
        {
            word[i] = tolower(word[i]);
        }
        //check if word was added
        found = 0;
        for (int i = 0; i < totalWords; i++)
        {
            //if already added adds one to count
            if (strcmp(keys[i], word) == 0)
            {
                count[i]++;
                found = 1;
                break;
            }
        }
        if (!found)
        {
            //if not added, adds to keys and adds to count
            if (strcmp(word, " ") != 0)
            {
                count[totalWords] = 1;
                strcpy(keys[totalWords], word);
                totalWords++;
            }
        }

        // Check if we've exceeded the maximum number of words
        if (totalWords >= MAX_WORDS)
        {
            printf("Exceeded maximum number of words (%d)\n", MAX_WORDS);
            break;
        }
    }
    //sorts the words alphabetically and the count
    sort_strings(keys, totalWords, count);
    for (int i = 0; i < totalWords; i++)
    {
        probability[i] = ((float)count[i] / MAX_WORDS);
    }
    //computes the optimalBST puts in R and C
    optimalBST(keys, totalWords, probability);
    //gets user input
    char searchword[MAX_LEN];
    printf("please enter word\n");
    fgets(searchword, MAX_LEN, stdin);
    searchword[strcspn(searchword, "\n")] = 0;
    //builds the optimalBST
    Node *root = buildOptimalBST(keys, R, 1, totalWords, probability);
    //search using search word
    search(root, searchword);
    fclose(fp);
    freeTree(root);
    return 0;
}