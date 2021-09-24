#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

// incomplete data type to hide internal implementation details
typedef bool (*listIterator)(void *);
typedef void (*freeFunction)(void *);
typedef struct node_type {
  void *data;
  struct node_type *next;
} list_node;

 typedef struct list_type{
  int elements_size;
  int num_elements;
  freeFunction freeFn;
  struct node_type *head;
  struct node_type *tail;
} list_type;


// Function declarations
void *list_create(list_type *list, freeFunction freeF, int data_size);

void list_delete(list_type *list);

// Append the element at the end of the list
void *list_append(list_type *list, void *element);

// Append the element at a particular location.
// If location is beyond the end of the list, append the item at the end of the list
// Returns the location of the new element.
void *list_insert_at(list_type *list, int type);

// Remove the element at location from the list
// Returns a pointer to the element removed, null if there is no element at that location
void *list_remove_at(list_type *list);

// Remove the element of the first instance from the list
void list_remove(list_type *list);

// Returns the list of element pointers as an array
void *list_to_array(list_type *list, int type);

// Returns the number of elements in the list.
unsigned int list_size(list_type *list);

// Returns true if empty, false otherwise.
bool list_is_empty(list_type *list);

int ask_num_nodes();

void print_list(list_type *list, listIterator iterator);

bool iterate_string(void *data);

void free_string(void *data);

bool iterate_int(void *data);

bool iterate_float(void *data);

void print_main_menu();

void print_menu2();

void char_menue();

void float_menue();