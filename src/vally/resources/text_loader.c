#include <vally/resources/text_loader.h>

#include <stdio.h>
#include <stdlib.h>

#include <vally/core/logger.h>

char *load_text_file(const char* path) {
  FILE *file;
  long length;
  char *buffer;

  // Open the file
  file = fopen(path, "rb");
  if (!file) {
    LOG_ERROR("Could not load file at \"%s\"!", path);
    return "";
  }

  // Calculate buffer's length
  fseek(file, 0, SEEK_END);
  length = ftell(file);
  rewind(file);

  // Allocate memory for the buffer
  buffer = calloc(1, length + 1);
  if (!buffer) {
    LOG_ERROR("Could not lallocate memory for buffer \"%s\"!", path);
    fclose(file);
    return "";
  }

  // Read the file into the buffer
  fread(buffer, 1, length, file);
  fclose(file);

  return buffer;
}