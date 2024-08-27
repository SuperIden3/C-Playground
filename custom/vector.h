#include <stdlib.h>

/**
 * A structure used to represent dynamic `Vector` objects.
 */
struct Vector {
  void *data; /** The buffer containing the elements of the vector. */
  size_t size; /** The number of elements in the vector. */
  size_t capacity; /** The capacity of the vector. */
  size_t element_size; /** The size of each element in the vector. */
};

/**
 * Creates a new `Vector` with the specified initial capacity and element size.
 * @param initial_capacity The initial capacity of the `Vector`.
 * @param element_size The size of each element in the `Vector`.
 * @return A pointer to the newly created `Vector`, or `NULL` if memory allocation fails.
 */
struct Vector *new_Vector(size_t initial_capacity, size_t element_size);

/**
 * Reserves a new capacity for the given `Vector`, reallocating memory if necessary.
 * @param vec The `Vector` to reserve capacity for.
 * @param new_capacity The new capacity to reserve.
 */
void vector_reserve(struct Vector *vec, size_t new_capacity);

/**
 * Appends a new element to the end of the given Vector.
 * @param vec The Vector to append the element to.
 * @param element The element to append to the Vector.
 */
void vector_push_back(struct Vector *vec, const void *element);