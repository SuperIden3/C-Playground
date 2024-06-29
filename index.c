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
    exit(EXIT_FAILURE);
  }
  debug_printf("DEBUG: Pointer %p will be freed...\n", pointer);
  free(*pointer);
  *pointer = NULL;
  debug_printf("DEBUG: Value of %p is freed and is set to NULL.\n", pointer);
}
/**
 * @brief Prints a pointer with its contents.
 * @param ptr Pointer that points to a set of hex values.
 * @param size Number of bytes to print.
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
  char *ptr_1 = (char *)malloc(sizeof(char) * 12);
  printf("%p\n", ptr_1);
  for(int i = 0; i < 12; ++i)
    ptr_1[i] = "Hello World!"[i];
  printf("%s\n", ptr_1);
  custom_free((void **)&ptr_1);

  return 0;
}