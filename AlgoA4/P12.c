#include <stdio.h>
#include <limits.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
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
//free the tree
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
//creates the Greedy BST by using the R array
Node *buildGreedyBST(char keys[MAX_WORDS][MAX_LEN], int start, int end, float P[MAX_WORDS])
{
    if (start >= end)
    {
        return NULL;
    }
    //find the word with largest prob
    double prob = 0;
    int index = start;
    for (int i = start; i < end; i++)
    {
        if (P[i] > prob)
        {

            index = i;
            prob = P[i];
        }
    }
    //splits table in half
    Node *root = createNode(keys[index], prob);
    root->left = buildGreedyBST(keys, start, index, P);
    root->right = buildGreedyBST(keys, index + 1, end, P);
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
    float probability[MAX_WORDS];
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
    Node *root = buildGreedyBST(keys, 0, totalWords, probability);
    //gets user input
    char searchword[MAX_LEN];
    printf("please enter word\n");
    fgets(searchword, MAX_LEN, stdin);
    searchword[strcspn(searchword, "\n")] = 0;
    //builds the optimalBST

    //search using search word
    search(root, searchword);
    fclose(fp);
    freeTree(root);
    return 0;
}