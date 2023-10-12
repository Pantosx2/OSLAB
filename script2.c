#include <signal.h>
#include <stdio.h>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        printf("Give the pid of the procces to be signalled\n");
        return 1;
    }

    int pid = atoi(argv[1]);
    kill(pid, SIGCONT);
    return 0;
}