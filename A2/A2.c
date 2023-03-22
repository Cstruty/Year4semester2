#include "A2.H"
int fd[100][2];
int pipeindex[100];
int children = 0;
void mysig(int signum)
{
    int childStatus;
    pid_t childpid;
    int histogram[MAXCHAR] = {0};
    char filename[100];
    int i = 0;
    int index;
    //get childpid
    childpid = waitpid(-1, &childStatus, WNOHANG);
    signal(SIGCHLD, mysig);
    if (WIFEXITED(childStatus))
    {

        // Child exited normally
        if (WEXITSTATUS(childStatus) == 0)
        {
            //successful exit

            //find pipe index
            for (i = 0; i < 100; i++)
            {
                if (pipeindex[i] == childpid)
                {
                    index = i;
                    break;
                }
            }
            //read through the pipe
            read(fd[index][0], histogram, sizeof(histogram));
            char *buffer = malloc(sizeof(char) * 4096);
            //create file and add the histogram
            sprintf(filename, "hist%d.hist", childpid);
            int file_descriptor = open(filename, O_CREAT | O_WRONLY, 0666);
            for (i = 0; i < MAXCHAR; i++)
            {
                sprintf(buffer, "%c %d \n", i + 97, histogram[i]);
                write(file_descriptor, buffer, strlen(buffer));
            }
            close(file_descriptor);
            free(buffer);
        }
        else
        {
            //failure exit
            printf("failure program exited with 1 pid=%d\n", childpid);
            sleep(2);
        }
    }
    else if (WIFSIGNALED(childStatus))
    {
        printf("SIG special case pid=%d\n", childpid);
        sleep(2);
        //Special case
    }

    //now that we've gone through the process we have one less child
    children--;
}
int main(int argc, char *argv[])
{
    //init signal
    signal(SIGCHLD, mysig);
    pid_t childPid;
    int i, j, k, n, file, length;
    unsigned char *buf;
    int temphist[MAXCHAR] = {0};

    if (argc < 2)
    {
        write(STDOUT_FILENO, "error no file name inputed\n", strlen("error no file name inputed\n"));
        exit(0);
    }
    // //Create a pipe

    // //fork a child process
    for (i = 0; i < argc - 1; i++)
    {

        if (pipe(fd[i]) == -1)
        {
            perror("pipe");
            exit(1);
        }
        childPid = fork();
        children++;
        if (childPid == -1)
        {
            perror("fork");
            exit(1);
        }
        if (childPid == 0)
        {
            sleep(1);

            //child process

            close(fd[i][0]);

            if (strcmp(argv[i + 1], "SIG") == 0)
            {
                close(fd[i][1]);
                kill(getpid(), SIGINT);
            }
            //opening file
            file = open(argv[i + 1], O_RDONLY);
            if (file < 0)
            {
                perror("open");
                close(fd[i][1]);
                exit(1);
            }
            //making buf
            length = lseek(file, 0, SEEK_END);
            lseek(file, 0, SEEK_SET);
            buf = malloc(sizeof(char) * length * 2);

            //reading in file and making histogram
            while ((n = read(file, buf, length * 2)) > 0)
            {
                for (j = 0; j < n; j++)
                {
                    if (isalpha(buf[j]))
                    {
                        k = toupper(buf[j]) - 'A';
                        temphist[k]++;
                    }
                }
            }
            //closing file freeing buf
            close(file);
            free(buf);

            write(fd[i][1], temphist, sizeof(temphist));
            close(fd[i][1]);
            sleep(10 + 2 * i);
            exit(0);
        }
        else
        {
            pipeindex[i] = childPid;

            //parent process
            close(fd[i][1]);
        }
    }
    while (children > 0)
    {

        sleep(1);
    }

    return 0;
}