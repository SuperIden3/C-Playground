#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdalign.h>
#include <stdint.h>
#include <stdatomic.h>
#include <stdfix.h>

/**
 * Prints messages when `-DDEBUG` is added.
 */
void debug_printf(const char *format, ...)
{
#ifdef DEBUG
  va_list args;
  va_start(args, format);
  vfprintf(stdout, format, args);
  va_end(args);
  printf("\n");
#endif
}
/**
 * For `printf`ing to `stderr`.
 */
void error_printf(const char *format, ...)
{
  va_list args;
  va_start(args, format);
  vfprintf(stderr, format, args);
  va_end(args);
}
/**
 * Frees a pointer.
 * @param pointer Must be in this format: `(void**)&<pointer-name>`.
 */
void free_pointer(void **pointer)
{
  if (pointer == NULL || *pointer == NULL)
  {
    debug_printf("Pointer is NULL.");
    error_printf("Pointer is NULL, cannot free %p.\n", *pointer);
    return;
  }
  free(*pointer);
  *pointer = NULL;
}

int main()
{
  float *ptr_i = (float *)malloc(1 * sizeof(float));
  *ptr_i = 1.5;
  printf("%g\n", *ptr_i);
  free_pointer((void **)&ptr_i);
  
  return 0;
}