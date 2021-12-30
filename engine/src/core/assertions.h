#ifndef SOGE_CORE_ASSERTIONS_H_
#define SOGE_CORE_ASSERTIONS_H_

#include "defines.h"

#define SASSERTIONS_ENABLED

void report_assert_fail(const char *expression, const char *message, const char *file, i32 line);

#ifdef SASSERTIONS_ENABLED
#if _MSC_VER
#include <intrin.h>
#define debug_break() __debugbreak()
#else
#define debug_break() __builtin_trap()
#endif

#define SASSERT(EXPR) {if(EXPR){}else{report_assert_fail(#EXPR, "", __FILE__, __LINE__);debug_break();}}
#define SASSERT_MSG(EXPR, MSG) {if(EXPR){}else{report_assert_fail(#EXPR, MSG, __FILE__, __LINE__);debug_break();}}

#else
#define SASSERT(EXPR)
#define SASSERT(EXPR, MSG)
#endif // !SASSERTIONS_ENABLED

#endif // !SOGE_CORE_ASSERTIONS_H_