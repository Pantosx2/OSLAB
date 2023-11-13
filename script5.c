#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
    int fd;
    fd = open(".hello_there", O_RDONLY);
    dup2(fd, 99);
    char *const *A[1];
    const char *a = "./riddle";
    A[1] = a;
    execve("./riddle", A, NULL);
}
