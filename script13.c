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
    pid_t pid = fork();
    if (pid != 0)
    {
        char *args[] = {"riddle", NULL};
        char *env[] = {NULL};

        execve("riddle", args, env);
    }
    else
    {
        sleep(2);
        ftruncate(fd, 32768);
        return 0;
    }
}