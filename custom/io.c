#include <stdio.h>
#include <string.h>
#include <stdlib.h>

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
