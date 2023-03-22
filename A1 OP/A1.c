#include "A1.H"
int main(void)
{
    char *buf = malloc(sizeof(char) * BUFFSIZE), *fileName = malloc(sizeof(char) * BUFFSIZE),
         *displaymodestring = malloc(sizeof(char) * BUFFSIZE);
    int size = BUFFSIZE, filesize = BUFFSIZE, displaymodesize = BUFFSIZE;
    bool displayMode = false, invalid = true;
    //while loop that doesn't close until x is entered
    strcpy(buf, "temp");
    strcpy(displaymodestring, "temp");
    strcpy(fileName, "temp");
    while (strcmp(buf, "x"))
    {
        printf("The Current Output Mode is: %s\n", displayMode ? "Hex" : "ASCII");
        printf("Please Enter Input\n");
        printf("'o' To Enter File Name\n");
        printf("'d' to select display mode\n");
        printf("'x' to exit\n");
        buf = readin(buf, &size);
        if (strcmp(buf, "d") == 0)
        {
            displayMode = getDisplayMode(displaymodestring, &displaymodesize);
        }
        else if (strcmp(buf, "o") == 0)
        {
            printf("Please Enter the File Name\n");
            fileName = readin(fileName, &filesize);
            readFile(fileName, displayMode);
            while (invalid)
            {
                //waits for valid input to go back to main menu
                printf("Please Enter Input\n");
                printf("'m' to return to main menu\n");
                printf("'x to exit\n");
                buf = readin(buf, &size);
                if (strcmp(buf, "x") == 0)
                {
                    invalid = false;
                }
                else if (strcmp(buf, "m") == 0)
                {
                    strcpy(buf, "d");
                    invalid = false;
                }
                else
                {
                    printf("error invalid input\n");
                }
            }
            invalid = true;
        }
        else if (strcmp(buf, "x") == 0)
        {
        }
        else
        {
            printf("error invalid input\n");
        }
    }
    //freeing and closing after while loop
    free(buf);
    free(fileName);
    free(displaymodestring);
    exit(0);
}
//opens file using open
void readFile(char *filename, bool displaymode)
{
    int fd = 0, n = 0, i = 0;
    unsigned char *buf;
    char *hex;
    fd = open(filename, O_RDONLY);
    int length = lseek(fd, 0, SEEK_END);
    lseek(fd, 0, SEEK_SET);
    buf = malloc(sizeof(char) * length * 2);
    hex = malloc(sizeof(char) * length * 2 * 8);
    if (fd < 0)
    {
        fprintf(stderr, "Could not open file %s\n", filename);
    }
    while ((n = read(fd, buf, BUFFSIZE)) > 0)
    {
        if (buf != NULL)
        {
            if (displaymode)
            {
                //if hex is the display mode it goes here
                string2hexString(buf, hex, &length);
                printf("%s", hex);
            }
            else
            {
                for (i = 0; i < length; i++)
                {
                    //changing invalid characters to valid characters
                    if ((buf[i] >= 0 && buf[i] <= 9) || (buf[i] >= 11 && buf[i] <= 31))
                    {

                        buf[i] = ' ';
                    }
                    else if (buf[i] >= 127)
                    {
                        buf[i] = '?';
                    }
                }

                if (write(STDOUT_FILENO, buf, n) != n)
                {
                    fprintf(stderr, "write error");
                }
                if (n < 0)
                {
                    fprintf(stderr, "read error from %s\n", filename);
                }
            }
        }
        else
        {
            //if the buf gets no characters
            printf("error no characters are getting retrieved from the file");
        }
    }
    //freeing
    printf("\n");
    close(fd);
    free(buf);
    free(hex);
}
bool getDisplayMode(char *buf, int *size)
{
    //gettting display mode
    printf("Please Enter 'a' for ASCII and 'h' for hex\n");
    // int n;
    bool invalid = true;

    do
    {
        //gets input and checks if it's valid
        buf = readin(buf, size);
        invalid = (strcmp(buf, "a") != 0 && strcmp(buf, "h") != 0);
        if (invalid)
        {
            printf("error invalid input\n");
        }

    } while (invalid);
    //will then return the read mode
    return (strcmp(buf, "h") ? false : true);
    free(buf);
}
char *readin(char *buf, int *size)
{
    //reads in characters
    int i = 0, n = 0;
    char c;
    if (buf != NULL)
    {
        memset(buf, 0, strlen(buf));
    }
    //read in character one at a time and puts into buf
    while ((n = read(STDIN_FILENO, &c, 1) > 0) && c != '\n')
    {
        buf[i] = c;
        i++;
    }
    buf[i + 1] = '\0';
    return buf;
}
//function taken and modified from
//https://www.includehelp.com/c/convert-ascii-string-to-hexadecimal-string-in-c.aspx#:~:text=Extract%20characters%20from%20the%20input,character%20to%20the%20output%20string.
void string2hexString(unsigned char *input, char *output, int *size)
{
    int i = 0, line = 0, loop = 0;
    char linetext[11];
    while (input[loop] != '\0' || (*size) != loop)
    {
        //first time around puts the 0's for hex
        if (loop == 0)
        {

            sprintf(linetext, "%08x", line);
            strcat(linetext, "  ");
            strcat(output, linetext);
            i += 10;
        }

        if (loop % 8 == 0 && loop != 0)
        {

            if (loop % 16 == 0)
            {
                //adds nl and the line num if 16 characters
                strcat(output, "\n");
                line += 16;
                sprintf(linetext, "%08x", line);
                strcat(linetext, "  ");

                strcat(output, linetext);
                i += 11;
            }
            else if (loop % 8 == 0)
            {
                //adds double space if 8 characters
                strcat(output, " ");
                i++;
            }
        }
        //converts input into hex and puts in output
        sprintf((char *)(output + i), "%02X", input[loop]);
        strcat(output, " ");
        i += 3;
        loop += 1;
        if (input[loop] == '\0' && (*size) == loop)
        {
            //at end of file, enter nl and puts the index of the final character
            output[i] = '\n';
            sprintf(linetext, "%08x", loop);
            strcat(linetext, "  ");
            strcat(output, linetext);
            i += 12;
        }
    }
    //insert NULL at the end of the output string
    output[i++] = '\0';
}