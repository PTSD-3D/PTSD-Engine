#include "PTSDAssert.h"

void _M_Assert(const char* expr_str, bool expr, const char* file, int line, const char* msg)
{
    if (!expr)
    {
        std::string m = "Assert failed:\t" + std::string(msg) + "\n"
            + "Expected:\t" + expr_str + "\n"
            + "Source:\t\t" + file + ", line " + std::to_string(line) + "\n";
        PTSD::LOG(m.c_str(),PTSD::Critical);
        abort();
    }
}