#include <memory.h>
#include <stdarg.h>
#include <stdint.h>
#include <stdio.h>

int printf(const char *restrict format, ...) {
  va_list args;
  va_start(args);
  int result = vprintf(format, args);
  va_end(args);
  return result;
}

int fprintf(FILE *restrict stream, const char *restrict format, ...) {
  va_list args;
  va_start(args);
  int result = vfprintf(stream, format, args);
  va_end(args);
  return result;
}

int sprintf(char *restrict buffer, const char *restrict format, ...) {
  va_list args;
  va_start(args);
  int result = vsprintf(buffer, format, args);
  va_end(args);
  return result;
}

int snprintf(char *restrict buffer, size_t bufsz, const char *restrict format,
             ...) {
  va_list args;
  va_start(args);
  int result = vsnprintf(buffer, bufsz, format, args);
  va_end(args);
  return result;
}

int vprintf(const char *restrict format, va_list vlist) {
  return vfprintf(stdout, format, vlist);
}

struct string_file_data {
  char *buf;
  size_t remaining; // should be one fewer than the buffer size so the null
                    // terminator can be written
};

size_t write_string_file(void *data, size_t len, char *bytes) {
  struct string_file_data *sfdata = data;
  if (len > sfdata->remaining) {
    len = sfdata->remaining;
  }
  memcpy(sfdata->buf, bytes, len);
  sfdata->buf += len;
  sfdata->remaining -= len;
}

size_t read_string_file(void *data, size_t len, char *bytes) {
  for (;;) {
  } // TODO
}

void close_string_file(void *data) {
  struct string_file_data *sfdata = data;
  *sfdata->buf = 0;
}

#define STRING_FILE(buf, file, bufsz)                                          \
  struct string_file_data data = {buf, bufsz - 1};                             \
  FILE file = {                                                                \
      .data = &data,                                                           \
      .write = write_string_file,                                              \
      .read = read_string_file,                                                \
      .close = close_string_file,                                              \
  }

int vsprintf(char *restrict buffer, const char *restrict format,
             va_list vlist) {
  STRING_FILE(buffer, file, SIZE_MAX);
  int result = vfprintf(&file, format, vlist);
  fclose(&file);
  return result;
}

int vsnprintf(char *restrict buffer, size_t bufsz, const char *restrict format,
              va_list vlist) {
  STRING_FILE(buffer, file, bufsz);
  int result = vfprintf(&file, format, vlist);
  fclose(&file);
  return result;
}
