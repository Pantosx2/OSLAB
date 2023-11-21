#include <sys/types.h>
#include <unistd.h>
#include <sys/mman.h>
#include <dlfcn.h>
#include <stdio.h>
#include <signal.h>
#include <execinfo.h>
#include <stdlib.h>

void sigsegv_handler(int signo)
{
    if (kill(getpid(), SIGCONT) == -1)
    {
        perror("kill");
        exit(1);
    }
    // continue;
    printf("Received a segfault; continue...\n");
}

void setup_tier2()
{

    // Code for Challenge 16
    long int *p = mmap((void *)(long)0x6042000, 4096, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
    *p = getpid();

    signal(SIGSEGV, sigsegv_handler);

    // void *handle = dlopen("./tier3.so", RTLD_LAZY | RTLD_GLOBAL);
    // void (*unlock_tier3x)() = dlsym(handle, "unlock_tier3");
    // unlock_tier3x();
}