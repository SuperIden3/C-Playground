#include <stdlib.h>

/**
 * Reverses the elements of an array in-place.
 * @param array Pointer to the array to be reversed.
 * @param size The number of elements in the array.
 * @param element_size The size of each element in bytes.
 */
void reverse_array(void *array, size_t size, size_t element_size);

/**
 * Converts a positive integer into the destination base's equivalent.
 * 
 * @note This function does not support negative numbers.
 * @param num The number to convert from in base 10.
 * @param base The base to convert to.
 * @return Either an allocated `"0"` string if `num == 0`, `NULL` if the base does not follow `2 <= base <= 36` or if memory allocation fails, or a string containing the converted number if successful.
 */
char *to_base(unsigned int num, unsigned int base);

/**
 * Frees a pointer.
 * @param pointer The pointer to be freed.
 * @note `pointer` **must** be in this format: `(void**)&<pointer-name>`.
 */
void custom_free(void **pointer);

/**
 * Prints a pointer with its contents.
 * @param ptr Pointer that points to a set of hex values.
 * @param size Number of bytes to print.
 */
void memory_printf(const void *ptr, size_t size);

/**
 * Generates a random decimal between 0 (inclusive) and 1 (exclusive).
 */
double custom_rand();
