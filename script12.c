#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main(int argc, char **argv)
{
    if (argc != 3)
        return 1;
    int fd = open(argv[1], O_RDWR);
    lseek(fd, 0x6f, SEEK_SET);
    write(fd, argv[2], 1);
    close(fd);
}