#include <unistd.h>

extern "C"
{

void swab(const void* bfrom, void* bto, ssize_t n) __attribute__((visibility("default")));

void swab(const void* bfrom, void* bto, ssize_t n)
{
    const char* from = (const char*)bfrom;
    char* to = (char*)bto;
    n &= ~((ssize_t)1);
    while (n > 1)
    {
        const char b0 = from[--n];
        const char b1 = from[--n];
        to[n] = b0;
        to[n+1] = b1;
    }
}

} // extern "C"
