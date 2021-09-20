#include <unistd.h>
#include <stdlib.h>
#include <stdbool.h>

// incomplete data type to hide internal implementation details
typedef struct list_type list_type;
typedef struct node_type node, *nodePointer;

// Function declarations
list_type *list_create();
void list_delete(list_type *list);

// Append the element at the end of the list
void list_append(list_type *list, void *element);

// Append the element at a particular location.
// If location is beyond the end of the list, append the item at the end of the list
// Returns the location of the new element.
unsigned int list_insert_at(list_type *list, void *element, unsigned int location);

// Remove the element at location from the list
// Returns a pointer to the element removed, null if there is no element at that location
void *list_remove_at(list_type *list, unsigned int location);

// Remove the element from the list
void list_remove(list_type *list, void *element);

// Returns the list of element pointers as an array
void *list_to_array(list_type *list);

// Returns the number of elements in the list.
unsigned int list_size(list_type *list);

// Returns true if empty, false otherwise.
bool list_is_empty(list_type *list);