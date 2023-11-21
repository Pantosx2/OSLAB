#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
    int fd;
    fd = open("magic_mirror", O_RDWR);
    dup2(fd, 34);
    dup2(fd, 33);
    dup2(fd, 54);
    dup2(fd, 53);
    char *const *A[1];
    const char *a = "./riddle";
    A[1] = a;
    execve("./riddle", A, NULL);
}