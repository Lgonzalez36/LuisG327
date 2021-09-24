#include "list_external.h"
#include <assert.h>
#include <stdio.h>
#include <string.h>

void *list_create(list_type *list, freeFunction freeFn, int data_size) {
    list->num_elements = 0;
    list->elements_size = data_size;
    list->head = NULL;
    list->tail = NULL;
    list->freeFn = freeFn;
    return 0;
}

void list_delete(list_type *list) {
    list_node *current;
    while(list->head != NULL) {
        current = list->head;
        list->head = current->next;
    if(list->freeFn) {
        list->freeFn(current->data);
    }
        free(current->data);
        free(current);
    }
    printf("**delete\n");
}

void *list_append(list_type *list, void *element) {
    printf("**in list_append\n");
    printf("element: %p\n", &element);
    printf("SizeofData: %d\n", list->elements_size);

    list_node *node = malloc(sizeof(list_node));
    node->data = malloc(list->elements_size);
    node->next = NULL;


    memcpy(node->data, element, list->elements_size);

    if(list->num_elements == 0) {
        list->head = list->tail = node;
    }
    else {
        list->tail->next = node;
        list->tail = node;
    }

    list->num_elements++;
    printf("___________________________________\n");
}

void *list_insert_at(list_type *list){
    // add but after 2x ditgits, the value is off
    // need to check for range and if head is null

    printf("Where would you like to insert?\n");
    printf("Enter positition number starting from i = 0\n");
    int pos;
    scanf("%d", &pos);
    printf("Enter new data:\n");
    void *newdata;
    scanf("%p",&newdata);
    //printf("insert element: %p\n", &newdata);
    //printf("insert element: %p\n", newdata); // maybe the best so far
    printf("insert at location: %d\n", pos);
    printf("_________________________________1\n");

    
    list_node *node = malloc(sizeof(list_node));
    node->data = malloc(list->elements_size);
    node->next = NULL;
    memcpy(node->data, &newdata, list->elements_size);
    int counter = 0;
    list_node *nodeptr;
    nodeptr = list->head;
    while(nodeptr!= NULL) {
        printf("COUNTRER***%d\n", counter);
        if (counter == (pos-1)) {
            node->next = nodeptr->next;
            nodeptr->next = node;
            break;

        }
        else {
            nodeptr = nodeptr->next;
            counter++;
        }
    }

    //print_list(&list, iterate_int);
    return 0;
}

void *list_remove_at(list_type *list) {
    printf("Where would you like to remove?\n");
    printf("Enter positition number starting from i = 0\n");
    int pos;
    scanf("%d", &pos);
    int counter = 0;
    list_node *next;
    list_node *tmp;
    tmp = list->head;
    if (tmp!= NULL && pos == 0) {
        list->head = tmp->next;
        free(tmp);
        return;
    }

    while(tmp!= NULL) {
        printf("COUNTRER***%d\n", counter);
        if (counter == (pos-1)) {
            printf("FOUND LOCATION IN REMOVE\n");
            next = tmp->next->next;
            free(tmp->next);
            tmp->next = next;
            break;
        }
        else{
            tmp = tmp->next;
            counter++;
        }
    }

}

void list_remove(list_type *list) {
    
    printf("NOT READY YET");
}

void *list_to_array(list_type *list, int type) {
    printf("IN ARRAY FUNC\n");
    if (type == 0){
        printf("IN TYPE 0\n");
        const int MAX = list->num_elements;
        int *ptr[MAX];
        list_node *nodeptr;
        nodeptr = list->head;
        for ( int i = 0; i < MAX; i++) {
            if (nodeptr != NULL){
                ptr[i] = nodeptr->data; /* assign the address of integer. */
                nodeptr = nodeptr->next;
            }
        }
        for ( int i = 0; i < MAX; i++) {
            printf("Value of var[%d] = %d\n", i, *ptr[i] );
        }
    }

    else if (type == 1) {
        printf("IN TYPE 1\n");
        const int MAX = list->num_elements;
        char *ptr[MAX];
        list_node *nodeptr;
        nodeptr = list->head;
        for ( int i = 0; i < MAX; i++) {
            if (nodeptr != NULL){
                ptr[i] = nodeptr->data; /* assign the address of integer. */
                nodeptr = nodeptr->next;
            }
        }
        for ( int i = 0; i < MAX; i++) {
            printf("Value of var[%d] = %s\n", i, *(char **)ptr[i] );
        }

    }

    else if (type == 2) {
        printf("IN TYPE 2\n");
        const int MAX = list->num_elements;
        float *ptr[MAX];
        list_node *nodeptr;
        nodeptr = list->head;
        for ( int i = 0; i < MAX; i++) {
            if (nodeptr != NULL){
                ptr[i] = nodeptr->data; /* assign the address of integer. */
                nodeptr = nodeptr->next;
            }
        }
        for ( int i = 0; i < MAX; i++) {
            printf("Value of var[%d] = %f\n", i, *(float *)ptr[i] );
        }
    }
}

unsigned int list_size(list_type *list){
    return (unsigned int)(list->num_elements);
}

bool list_is_empty(list_type *list){
    if (list->head == NULL){
        return true;
    }
    else{
        return false;
    }
    return true;
}

void print_list(list_type *list, listIterator iterator)
{
  assert(iterator != NULL);

  list_node *node = list->head;
  bool result = true;
  while(node != NULL && result) {
    result = iterator(node->data);
    node = node->next;
  }
}

bool iterate_string(void *data)
{
  printf("%s->", *(char **)data);
  return true;
}

void free_string(void *data)
{
  free(*(char **)data);
}

bool iterate_int(void *data) 
{
  printf("%d->", *(int *)data);
  return true;
}

bool iterate_float(void *data)
{
    printf("%f->", *(float *)data);
    return true;
}

int ask_num_nodes(){
    int num;
    printf("How many data do you want to input?\n");
    scanf("%d",&num);
    printf("Print n in the call %d\n",num);
    return num;
}

void print_menu2(){
    //Clear the screen
    system("cls");
    printf("\nWhat would you like to do with your Linked List?\n");
    //Select the Choice as per the requirements
    printf("\n\n\
        1: Insert at a specific location\n\
        2: Remove element from location\n\
        3: Remove all of the same elements from list\n\
        4: Convert Linked List to an array\n\
        5: Print list\n\
        6: Terminate the process \n\n\n");
    printf("\n\nenter your choice = ");
}

void print_main_menu(){
    //Clear the screen
    system("cls");
    //Select the Choice as per the requirements
    printf("\n\n\
        1: Create the Linked List of integer\n\
        2: Create the Linked List of character\n\
        3: Create the Linked List of float\n\
        4: Terminate the process \n\n\n");
    printf("\n\nenter your choice = ");
}

