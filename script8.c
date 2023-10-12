#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>

int main()
{
    char file[4] = "bf00";
    char f0 = '0';
    char *buffer = malloc(1024);
    for (int i = 0; i < 1024; i++)
        buffer[i] = 'X';
    for (int j = 0; j < 10; j++)
    {
        file[3] = f0;
        printf("Started writing %s...\n", file);
        int fd = open(file, O_CREAT | O_RDWR | O_TRUNC, S_IRUSR | S_IWUSR);
        for (unsigned long long int i = 0; i < 1048576; i++)
            write(fd, buffer, 1024);
        write(fd, "Checking footers", 16);
        close(fd);
        f0++;
        printf("Finished\n");
    }
}