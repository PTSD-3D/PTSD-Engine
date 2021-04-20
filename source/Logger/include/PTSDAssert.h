#pragma once
#include "LogManager.h"

#ifndef NDEBUG
#   define PTSD_ASSERT(Expr, Msg) \
    _M_Assert(#Expr, Expr, __FILE__, __LINE__, Msg)
#else
#   define PTSD_ASSERT(Expr, Msg) ;
#endif

void _M_Assert(const char* expr_str, bool expr, const char* file, int line, const char* msg);
