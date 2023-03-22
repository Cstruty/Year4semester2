#include <stdio.h>
#include <stdbool.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#define BUFFSIZE 4096
void readFile(char *fileName, bool displaymode);
bool getDisplayMode(char *buf, int *size);
char *readin(char *buf, int *size);
void string2hexString(unsigned char *input, char *output, int *size);