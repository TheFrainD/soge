/*********************************************************************
 * logger.c                                                          *
 *                                                                   *
 * Copyright (c) 2022 Dmytro Zykov                                   *
 *                                                                   *
 * This file is a part of the vally project, and may only be used,   *
 * modified and distributed under the terms of the MIT License,      *
 * LICENSE.md. By continuing to use, modify and distribute this file *
 * you inidicate that you have read the license and accept it fully. *
 *********************************************************************/

#include <vally/core/logger.h>

b8 logger_init() {
  FILE *file = fopen("logs/vally.log", "w+");
  if (!file) {
    log_error("Could not open log file!");
    return FALSE;
  }
  log_add_fp(file, 0);
  return TRUE;
}