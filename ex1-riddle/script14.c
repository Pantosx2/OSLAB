#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
    int fd, fd2;
    fd = open(".hello_there", O_RDWR);
    pid_t pid = -1;
    while (pid != 32767 && pid != 0)
        pid = fork();
    if (pid == 0)
    {
        pid_t mypid = getpid();
        if (mypid != 32767)
        {
            printf("Process %d dying...\n", mypid);
            return 0;
        }
        char *args[] = {"riddle", NULL};
        char *env[] = {NULL};

        execve("riddle", args, env);
    }
    else
    {
        return 0;
    }
}