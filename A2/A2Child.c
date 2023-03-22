#include "A2.H"
int main(int argc, char *argv[])
{

    if(argc < 2){
        write(STDOUT_FILENO, "error no file name inputed\n", strlen("error no file name inputed\n"));
        exit(0);
    }
    printf("hello\n");
   
}