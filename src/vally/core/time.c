/*********************************************************************
 * time.c                                                            *
 *                                                                   *
 * Copyright (c) 2022 Dmytro Zykov                                   *
 *                                                                   *
 * This file is a part of the vally project, and may only be used,   *
 * modified and distributed under the terms of the MIT License,      *
 * LICENSE.md. By continuing to use, modify and distribute this file *
 * you inidicate that you have read the license and accept it fully. *
 *********************************************************************/

#include <vally/core/time.h>

#if defined(VALLY_PLATFORM_LINUX)

  #define _POSIX_C_SOURCE 199309L
  #include <sys/time.h>
  #include <time.h>

  f64 time_now() {
    struct timespec now;
    clock_gettime(CLOCK_MONOTONIC, &now);
    return now.tv_sec + now.tv_nsec * 0.000000001;
  }

#elif defined(VALLY_PLATFORM_WINDOWS)
  #include <windows.h>
  #include <time.h>

  static f64 clock_frequency;
  static LARGE_INTEGER start_time;

  void time_init() {
    LARGE_INTEGER frequency;
    QueryPerformanceFrequency(&frequency);
    clock_frequency = 1.0 / (f64)frequency.QuadPart;
    QueryPerformanceCounter(&start_time);
  }

  f64 time_now() {
    if (!clock_frequency) {
      time_init();
    }

    LARGE_INTEGER now_time;
    QueryPerformanceCounter(&now_time);
    return (f64)now_time.QuadPart * clock_frequency;
  }
#endif