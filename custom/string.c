#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <stdio.h>

struct String {
  char *buffer;
  size_t size;
};

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