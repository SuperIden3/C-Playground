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
void debug_printf(const char *format, ...) {
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
void free_pointer(void **pointer) {
    if (pointer == NULL || *pointer == NULL) {
      debug_printf("Pointer is NULL.");
      error_printf("Pointer is NULL, cannot free %p.\n", *pointer);
      return;
    }
    free(*pointer);
    *pointer = NULL;
}

int main()
{
  uint8_t *i = (uint8_t*)malloc(1 * sizeof(uint8_t)); // Allocates 1 empty space of memory meant to be taken by an integer.
  *i = 108; // Assignes the empty space with the integer 1.
  printf("%d\n", *i); // Prints the integer.
  free_pointer((void**)&i); // Gets rid of the allocated space.
  
  return 0;
}