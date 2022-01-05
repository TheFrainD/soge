#ifndef VALLY_CORE_ASSERTIONS_H_
#define VALLY_CORE_ASSERTIONS_H_

#include "defines.h"

#define VASSERTIONS_ENABLED

void report_assert_fail(const char *expression, const char *message, const char *file, i32 line);

#ifdef VASSERTIONS_ENABLED
#if _MSC_VER
#include <intrin.h>
#define debug_break() __debugbreak()
#else
#define debug_break() __builtin_trap()
#endif

#define VASSERT(EXPR) {if(EXPR){}else{report_assert_fail(#EXPR, "", __FILE__, __LINE__);debug_break();}}
#define VASSERT_MSG(EXPR, MSG) {if(EXPR){}else{report_assert_fail(#EXPR, MSG, __FILE__, __LINE__);debug_break();}}

#else
#define VASSERT(EXPR)
#define VASSERT(EXPR, MSG)
#endif // !VASSERTIONS_ENABLED

#endif // !VALLY_CORE_ASSERTIONS_H_