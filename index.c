#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio_ext.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <time.h>
#include <math.h>
#include <assert.h>
#include <errno.h>
#include <ctype.h>
#include <limits.h>
#include <float.h>
#include <complex.h>
#include <inttypes.h>
#include <tgmath.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/mman.h>
#include <sys/ioctl.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

const char *__digits = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";

struct Vector {
  void *data;
  size_t size;
  size_t capacity;
  size_t element_size;
};

/**
 * Creates a new Vector with the specified initial capacity and element size.
 *
 * @param initial_capacity The initial capacity of the Vector.
 * @param element_size The size of each element in the Vector.
 *
 * @return A pointer to the newly created Vector, or NULL if memory allocation fails.
 */
struct Vector *new_Vector(size_t initial_capacity, size_t element_size) {
  struct Vector *vec = (struct Vector *)malloc(sizeof(struct Vector));
  if (vec == NULL)
    return NULL;
  vec->data = malloc(initial_capacity * element_size);
  if (vec->data == NULL) {
    free(vec);
    return NULL;
  }
  vec->size = 0;
  vec->capacity = initial_capacity;
  vec->element_size = element_size;
  return vec;
}

/**
 * Reserves a new capacity for the given Vector, reallocating memory if necessary.
 *
 * @param vec The Vector to reserve capacity for.
 * @param new_capacity The new capacity to reserve.
 *
 * @return None
 */
void vector_reserve(struct Vector *vec, size_t new_capacity) {
  if (vec->capacity >= new_capacity)
    return;
  void *new_data = realloc(vec->data, new_capacity * vec->element_size);
  if (new_data == NULL) {
    perror("Failed to reallocate memory for Vector");
    exit(1);
  }
  vec->data = new_data;
  vec->capacity = new_capacity;
}

/**
 * Appends a new element to the end of the given Vector.
 *
 * @param vec The Vector to append the element to.
 * @param element The element to append to the Vector.
 *
 * @return None
 */
void vector_push_back(struct Vector *vec, const void *element) {
  if (vec->size == vec->capacity)
    vector_reserve(vec, vec->capacity * 2 + 1);
  memcpy(vec->data + vec->size * vec->element_size, element, vec->element_size);
  vec->size++;
}

/**
 * @struct Node
 * @brief A linked list node structure.
 *
 * A @c struct Node contains a pointer to the next node in the linked list,
 * and a generic pointer to the data stored in the node.
 *
 * @var next Pointer to the next node in the linked list.
 * @var data Generic pointer to the data stored in the node.
 */
struct Node {
  struct Node *next;
  void *data;
};

/**
 * Creates a new Node with the given data.
 *
 * @param data The data to be stored in the new Node.
 * @return A pointer to the newly created Node, or NULL if memory allocation fails.
 */
struct Node *new_Node(void *data) {
  struct Node *node = (struct Node *)malloc(sizeof(struct Node));
  if (node == NULL)
    return NULL;
  node->data = data;
  node->next = NULL;
  return node;
}

/**
 * Asks the user a question and reads their response from standard input.
 *
 * @param question The question to be asked to the user.
 * @return A dynamically allocated string containing the user's response, or NULL on failure.
 */
char *ask(const char *question) {
  printf("%s", question);
  fflush(stdout);
  char *buffer = NULL;
  size_t size = 0;
  if (getline(&buffer, &size, stdin) == -1) {
    perror("Failed to read input");
    free(buffer);
    return NULL;
  }
  buffer[strcspn(buffer, "\n")] = '\0';
  return buffer;
}

/**
 * Reverses the elements of an array in-place.
 *
 * @param array Pointer to the array to be reversed.
 * @param size The number of elements in the array.
 * @param element_size The size of each element in bytes.
 *
 * @throws None
 */
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

/**
 * @brief Prints messages when `-DDEBUG` is added.
 */
void debug_printf(const char *format, ...) {
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
void error_printf(const char *format, ...) {
  va_list args;
  va_start(args, format);
  vfprintf(stderr, format, args);
  va_end(args);
}
/**
 * @brief Frees a pointer.
 * @note `pointer` must be in this format: `(void**)&<pointer-name>`.
 */
void custom_free(void **pointer) {
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
/**
 * @brief Generates a random decimal between 0 (inclusive) and 1 (exclusive).
 */
double custom_rand() {
  int rand1 = rand();
  debug_printf("DEBUG: Randomly generated number: %i.\n", rand1);
  double rand2 = (double)rand1 / (double)RAND_MAX;
  debug_printf("DEBUG: Random number from 0 to 1: %.54lf.\n", rand2);
  return rand2;
}

/**
 * A structure used to represent dynamic `String` objects.
 */
struct String {
  char *buffer;
  size_t size;
};

/**
 * Creates a new String object with the specified buffer and length.
 *
 * @param buffer The buffer containing the characters of the string.
 * @param length The length of the string.
 *
 * @return A `String` object, or `NULL` if memory allocation fails.
 */
struct String *new_String(const char *buffer) {
  struct String *str_obj = (struct String *)malloc(sizeof(struct String)); 
  if (str_obj == NULL) {
    perror("Failed to allocate memory for String object");
    return NULL;
  }
  str_obj->size = strlen(buffer); 
  str_obj->buffer = (char *)malloc(sizeof(char) * (str_obj->size + 1)); 
  if (str_obj->buffer == NULL) {
    perror("Failed to allocate memory for String buffer");
    free(str_obj);
    return NULL;
  }
  memcpy(str_obj->buffer, buffer, str_obj->size); 
  str_obj->buffer[str_obj->size] = '\0'; 
  return str_obj;
}

/**
 * Appends a constant buffer to a `String` object and also updates the size of the `String` object.
 * @param str_obj A pointer to the `String` object for the concatenation.
 * @param buffer The constant buffer to append to the `String` object.
 * @return `true` if successful or `false` if memory reallocation fails for cnocatenation.
 */
bool String_append(struct String *str_obj, const char *buffer) {
  size_t size = str_obj->size + strlen(buffer) + 1;
  char *new_buffer = (char *)realloc(str_obj->buffer, sizeof(char) * size);
  if (new_buffer == NULL) {
    perror("Failed to reallocate memory for new buffer");
    return false;
  }
  str_obj->buffer = new_buffer;
  str_obj->size = size - 1;
  strcat(str_obj->buffer, buffer);
  return true;
}

/**
 * Frees the memory allocated for a String object.
 *
 * @param str_obj Pointer to the String object to be freed.
 *
 * @return `true` if the memory was successfully freed, `false` if the pointer to the
 *         String object is NULL, or if the buffer is already NULL.
 */
bool free_String(struct String *str_obj) {
  if (str_obj == NULL) {
    perror("String object already NULL");
    return false;
  }
  if (str_obj->buffer != NULL) {
    memset(str_obj->buffer, 0, str_obj->size);
    free(str_obj->buffer);
  }
  str_obj->buffer = NULL; 
  str_obj->size = 0;
  free(str_obj);
  return true; 
}

int main() {
  srand(time(0));

  int size = 5;
  double *numbers = malloc(sizeof(double) * size);
  for(int i = 0; i < size; i++)
    numbers[i] = custom_rand();
  printf("%.2f\n", numbers[0]);
  free(numbers);

  return 0;
}
