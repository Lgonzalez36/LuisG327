#include <stdlib.h>

struct node_type {
  void *data;
  struct node_type *next;
};

struct list_type {
  size_t num_elements;
  struct node_type *head;
};

