#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct Vector {
  void *data;
  size_t size;
  size_t capacity;
  size_t element_size;
};

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

void vector_push_back(struct Vector *vec, void *element) {
  if (vec->size == vec->capacity)
    vector_reserve(vec, vec->capacity * 2 + 1);
  memcpy(vec->data + vec->size * vec->element_size, element, vec->element_size);
  vec->size++;
}
