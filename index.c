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
#include <time.h>
#include <malloc.h>

/**
 * @brief Prints messages when `-DDEBUG` is added.
 */
void debug_printf(const char *format, ...)
{
#ifdef DEBUG
  va_list args;
  va_start(args, format);
  vfprintf(stdout, format, args);
  va_end(args);
#endif
}
/**
 * @brief For `printf`ing to `stderr`.
 */
void error_printf(const char *format, ...)
{
  va_list args;
  va_start(args, format);
  vfprintf(stderr, format, args);
  va_end(args);
}
/**
 * @brief Frees a pointer.
 * @note `pointer` must be in this format: `(void**)&<pointer-name>`.
 */
void custom_free(void **pointer)
{
  if (pointer == NULL || *pointer == NULL)
  {
    debug_printf("%p is NULL.\n", pointer);
    error_printf("ERROR:\n\t%p = 0x0;\tpointer is NULL.\n", pointer);
    return;
  }
  debug_printf("DEBUG: Pointer %p will be freed...\n", pointer);
  free(*pointer);
  *pointer = NULL;
  debug_printf("DEBUG: Value of %p is freed and is set to NULL.\n", pointer);
}
/**
 * @brief Prints a pointer with its contents.
 */
void memory_printf(const void *ptr, size_t size)
{
  const unsigned char *byte_ptr = (const unsigned char *)ptr;
  for (size_t i = 0; i < size; ++i)
  {
    if (i % 16 == 0)
    {
      printf("\n%p: ", (void *)(byte_ptr + i)); // Print address
    }
    printf("%02x ", byte_ptr[i]); // Print byte value in hex
  }
  printf("\n");
}


int main()
{
  float *ptr_i = (float *)malloc(1 * sizeof(float));
  *ptr_i = 1.5;
  printf("%g\n", *ptr_i);
  custom_free((void **)&ptr_i);

  return 0;
}