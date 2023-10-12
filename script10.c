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
    fd = open("secret_number", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    dup2(fd, 42);
    pid_t pid = fork();
    if (pid != 0)
    {
        char *args[] = {"riddle", NULL};
        char *env[] = {NULL};

        execve("riddle", args, env);
    }
    else
    {
        fd2 = open("mind", O_RDWR | O_CREAT | O_TRUNC, S_IRUSR | S_IWUSR);
        sleep(2);
        char buffer[1024];
        int size = read(42, buffer, 1024);
        write(fd2, buffer, size);
        return 0;
    }
}