#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

const char *__digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

void reverse_array(void *array, size_t size, size_t element_size) {
  char *char_ptr = (char *)array;
  for (size_t i = 0; i < size / 2; i++) {
    char temp[element_size];
    memcpy(temp, char_ptr + i * element_size, element_size);
    memcpy(char_ptr + i * element_size, char_ptr + (size - i - 1) * element_size, element_size);
    memcpy(char_ptr + (size - i - 1) * element_size, temp, element_size);
  }
}

char *to_base(unsigned int num, unsigned int base) {
  if (num == 0) {
    return strdup("0");
  }
  if (base < 2 || base > 36) {
    fprintf(stderr, "Invalid base %u.\n", base);
    return NULL;
  }
  unsigned int max_length = 32;
  char *result = (char *)malloc((max_length + 1) * sizeof(char));
  if (result == NULL)
    return NULL;
  int index = 0;
  while (num > 0) {
    unsigned int remainder = num % base;
    result[index++] = __digits[remainder];
    num /= base;
  }
  reverse_array(result, index, sizeof(char));
  result[index] = '\0';
  return result;
}

void custom_free(void **pointer) {
  if (pointer == NULL || *pointer == NULL)
  {
    fprintf(stderr, "Pointer (%p) already NULL (or not in this format): %s\n", (void *)pointer, strerror(errno));
    exit(EXIT_FAILURE);
  }
  free(*pointer);
  *pointer = NULL;
}

void memory_printf(const void *ptr, size_t size) {
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

double custom_rand() {
  int rand1 = rand();
  double rand2 = (double)rand1 / (double)RAND_MAX;
  return rand2;
}

