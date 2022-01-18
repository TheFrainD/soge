/*********************************************************************
 * assertions.h                                                      *
 *                                                                   *
 * Copyright (c) 2022 Dmytro Zykov                                   *
 *                                                                   *
 * This file is a part of the vally project, and may only be used,   *
 * modified and distributed under the terms of the MIT License,      *
 * LICENSE.md. By continuing to use, modify and distribute this file *
 * you inidicate that you have read the license and accept it fully. *
 *********************************************************************/

/**
 * @brief Provides with cutsom assertions
 * @warning only for internal use
 */

#ifndef VALLY_ASSERTIONS_H_
#define VALLY_ASSERTIONS_H_

#include <vally/config.h>
#include <vally/core/logger.h>

#if defined(VALLY_DEBUG)

  #define ASSERTIONS_ENABLED

#endif

#if defined(ASSERTIONS_ENABLED)

  #if defined(_MSC_VER)  // for Windows

  #include <intrin.h>
  #define debug_break() __debugbreak()

  #else

  #define debug_break() __builtin_trap()

  #endif

  #define ASSERT(EXPR) {\
      if (EXPR){ \
      } else {\
        LOG_FATAL("Assertion failure: (%s), -- %s:%d", #EXPR, __FILE__, __LINE__);\
        debug_break();\
      }\
    }

  #define ASSERT_MSG(EXPR, MSG) {\
      if (EXPR){ \
      } else {\
        LOG_FATAL("Assertion failure: (%s), %s -- %s:%d", #EXPR, #MSG, __FILE__, __LINE__);\
        debug_break();\
      }\
    }

#else

  #define ASSERT(EXPR)
  #define ASSERT(EXPR, MSG)

#endif // ASSERTIONS_ENABLED

#endif // VALLY_ASSERTIONS_H_