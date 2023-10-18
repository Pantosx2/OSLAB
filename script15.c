#include <sys/types.h>
#include <unistd.h>
#include <sys/mman.h>
#include <dlfcn.h>

void setup_tier2()
{

    long int *p = mmap((void *)(long)0x6042000, 4096, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
    *p = getpid();
    void *authorize_tier3 = dlopen("./tier3.so", 2);
}