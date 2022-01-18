/*********************************************************************
 * config.h                                                          *
 *                                                                   *
 * Copyright (c) 2022 Dmytro Zykov                                   *
 *                                                                   *
 * This file is a part of the vally project, and may only be used,   *
 * modified and distributed under the terms of the MIT License,      *
 * LICENSE.md. By continuing to use, modify and distribute this file *
 * you inidicate that you have read the license and accept it fully. *
 *********************************************************************/

#ifndef VALLY_CONFIG_H_
#define VALLY_CONFIG_H_

#include <stdint.h>

/**
 * @brief Identify OS.
 * 
 */
#if defined(_WIN32)

  // Windows
  #define VALLY_PLATFORM_WINDOWS

#elif defined(__linux__)

  // Linux
  #define VALLY_PLATFORM_LINUX

#else

  #error This OS is not supported by Vally

#endif

/**
 * @brief Define import and export macros.
 * 
 */
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

/**
 * @brief Fixed-size unsigned types.
 * 
 */
typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

/**
 * @brief Fixed-size integer types.
 * 
 */
typedef int8_t  i8;
typedef int16_t i16;
typedef int32_t i32;
typedef int64_t i64;

/**
 * @brief Fixed-size decimal types.
 * 
 */
typedef float f32;
typedef double f64;

/**
 * @brief Custom booleans.
 * 
 */
typedef int32_t b32;
typedef uint8_t b8;


/**
 * @brief Boolean values.
 * 
 */
#define TRUE 1
#define FALSE 0

/**
 * @brief Creates a bit mask with certain bit toggled on.
 * 
 */
#define BIT_MASK(n) (1 << n)

#define MIN(a,b) (((a)<(b))?(a):(b))
#define MAX(a,b) (((a)>(b))?(a):(b))

#endif // VALLY_CONFIG_H_