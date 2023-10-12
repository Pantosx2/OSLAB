#include <sys/types.h>
#include <unistd.h>
#include <sys/mman.h>
#include <dlfcn.h>
#include <stdio.h>

void authorize_tier3()
{
    void *p1 = dlopen("/home/pantos/Downloads/riddle-20231009-0/tier3.so", 2);
    // char *p = dlsym(p1, "password");
    // puts("HI");
    // puts(p);
}