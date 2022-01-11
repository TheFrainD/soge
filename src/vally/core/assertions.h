//================================================================================
// Vally 0.1indev
//--------------------------------------------------------------------------------
// Copyright (c) 2022 Dmytro Zykov

// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//=================================================================================

//=====================================
// Provides with custom assertions.   |
// ONLY for internal use.             |
//=====================================

#ifndef VALLY_ASSERTIONS_H_
#define VALLY_ASSERTIONS_H_

#include <vally/config.h>
#include <vally/core/logger.h>

#if defined(VALLY_DEBUG)

  #define ASSERTIONS_ENABLED

#endif

#ifdef ASSERTIONS_ENABLED

  #if _MSC_VER  // for Windows

  #include <intrin.h>
  #define debug_break() __debugbreak()

  #else

  #define debug_break() __builtin_trap()

  #endif

  #define ASSERT(EXPR) {\
      if (EXPR){ \
      } else {\
        VALLY_FATAL("Assertion failure: (%s), -- %s:%d", #EXPR, __FILE__, __LINE__);\
        debug_break();\
      }\
    }

  #define ASSERT_MSG(EXPR, MSG) {\
      if (EXPR){ \
      } else {\
        VALLY_FATAL("Assertion failure: (%s), %s -- %s:%d", #EXPR, #MSG, __FILE__, __LINE__);\
        debug_break();\
      }\
    }

#else

  #define ASSERT(EXPR)
  #define ASSERT(EXPR, MSG)

#endif // ASSERTIONS_ENABLED

#endif // VALLY_ASSERTIONS_H_