#include <stdlib.h>
#include <stdbool.h>

/**
 * A structure used to represent dynamic `String` objects.
 */
struct String {
  char *buffer; /** The buffer containing the characters of the string. It'll be dynamically allocated. */
  size_t size; /** The length of the string. */
};

/**
 * Creates a new `String` object with the specified buffer and length.
 * @param buffer The buffer containing the characters of the string.
 * @param length The length of the string.
 * @return A `String` object, or `NULL` if memory allocation fails.
 */
struct String *new_String(const char *buffer);

/**
 * Frees the memory allocated for a `String` object.
 * @param str_obj Pointer to the `String` object to be freed.
 * @return `true` if the memory was successfully freed, `false` if the pointer to the `String` object is `NULL`, or if the buffer is already `NULL`.
 */
bool free_String(struct String *str_obj);

/**
 * Appends a constant buffer to a `String` object and also updates the size of the `String` object.
 * @param str_obj A pointer to the `String` object for the concatenation.
 * @param buffer The constant buffer to append to the `String` object.
 * @return `true` if successful or `false` if memory reallocation fails for cnocatenation.
 */
bool String_append(struct String *str_obj, const char *buffer);

