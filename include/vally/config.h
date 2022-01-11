//================================================================================
// Vally 0.1a
//--------------------------------------------------------------------------------
// Copyright (c) 2021 Dmytro Zykov

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

#ifndef VALLY_CONFIG_H_
#define VALLY_CONFIG_H_

#include <stdint.h>

//=============================//
// Identify OS                 //
//=============================//
#if defined(_WIN32)

  // Windows
  #define VALLY_PLATFORM_WINDOWS

#elif defined(__linux__)

  // Linux
  #define VALLY_PLATFORM_LINUX

#else

  #error This OS is not supported by Vally

#endif

//====================================//
// Define import and export macros    //
//====================================//
#if !defined(VALLY_STATIC)

  #if defined(VALLY_PLATFORM_WINDOWS)

    // Special keywords for Windows
    #if defined(VALLY_BUILD_DLL)

      #define VALLY_API __declspec(dllexport)

    #else
    
      #define VALLY_API __declspec(dllimport)

    #endif

    #if defined(_MSC_VER)

      #pragma warning(disable: 4251)

    #endif

  #else // Linux

    #if defined(VALLY_BUILD_DLL)

      #define VALLY_API __attribute__((visibility("default")))

    #else

      #define VALLY_API

    #endif

  #endif

#else

  // Static library does not require import and export macros
  #define VALLY_API

#endif


//=================================//
// Define custom fixed-size types  //
//=================================//
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef int8_t  i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

typedef float f32;
typedef double f64;

typedef int32_t b32;
typedef uint8_t b8;


#define TRUE 1
#define FALSE 0

#define NULL ((void *)0)

#define BIT_MASK(n) (1 << n)
#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

// Inlining
#if defined(__clang__) || defined(__gcc__)
#define VALLY_INLINE __attribute__((always_inline)) inline
#define VALLY_NOINLINE __attribute__((noinline))
#elif defined(_MSC_VER)
#define VALLY_INLINE __forceinline
#define VALLY_NOINLINE __declspec(noinline)
#else
#define VALLY_INLINE static inline
#define VALLY_NOINLINE
#endif

#endif // VALLY_CONFIG_H_