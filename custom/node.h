/**
 * A linked list node structure.
 * 
 * A `Node` contains a pointer to the next `Node` in the linked list, and a generic pointer to the data stored in the node.
 */
struct Node {
  struct Node *next; /** Pointer to the next `Node` in the linked list. */
  void *data; /** Generic pointer to the data stored in the `Node`. */
  struct Node *prev; /** Pointer to the previous `Node` in the linked list. */
};

/**
 * Creates a new Node with the given data.
 *
 * @param data The data to be stored in the new `Node`.
 * @return A pointer to the newly created `Node`, or `NULL` if memory allocation fails.
 */
struct Node *new_Node(void *data);
