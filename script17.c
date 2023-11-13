#include <dlfcn.h>

void authorize_tier3()
{
    void *handle = dlopen("../trash/tier3.so", 2);
    // void (*unlock_tier3x)() = dlsym(handle, "unlock_tier3");
    // unlock_tier3x();
}