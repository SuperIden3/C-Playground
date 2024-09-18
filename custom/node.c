#include <stddef.h>
#include <stdlib.h>

struct Node {
  struct Node *next;
  void *data;
  struct Node *prev;
};

struct Node *new_Node(void *data) {
  struct Node *node = (struct Node *)malloc(sizeof(struct Node));
  if (node == NULL)
    return NULL;
  node->data = data;
  node->next = NULL;
  return node;
}

