/***************************************************************************************
 * Author: Luis Gonzalez
 * Date  : 9/24/2021
 * Class : CSCE 327 Linux Programming
 * Prof  : Aloia
 ***************************************************************************************
 * Program 1 - linked list implemenation in c -yuk
 * Main Driver to test out the linked list I made
 * see README for additional information on how it works, and what doesn't work
 ***************************************************************************************
*/

#include "list_external.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/*
 *
 *
 * 
 *
*/

/*
 * Main ()
 * starts by printing the main menu and asking user to make a selection
*/
int main(void) {
    // Vars
    int iChoice = 0;
    list_type LIST;
    int iChoice2 = 0;
    while (1) {
        print_main_menu();
        scanf("%d",&iChoice);
        switch(iChoice) {
            case 1: {   // test cases for an int linked list
                int n = ask_num_nodes();
                unsigned int_size = sizeof(int); 
                list_create(&LIST, NULL, int_size);
                
                for (int i=0; i<n; i++) {
                    void *data;
                    printf("Enter data number: %d\n", i+1);
                    scanf("%p",&data);
                    list_append(&LIST, &data);
                }

                printf("\n\n\n");
                printf("___________________________________\n");
                printf("Your Linked List: \n");
                print_list(&LIST, iterate_int);
                printf("\n");
                printf("List Size: %d\n", list_size(&LIST));
                printf("___________________________________\n");
                printf("\n\n");
                while(1) {
                    print_menu2();
                    scanf("%d",&iChoice2);
                    if (iChoice2 == 1) {   // 1: Insert at a specific location WORKING
                        list_insert_at(&LIST);
                        print_list(&LIST, iterate_int);
                    }
                    else if (iChoice2 == 2) {   // 2: Remove element from location WORKING
                        list_remove_at(&LIST);
                        print_list(&LIST, iterate_int);
                    }
                    else if (iChoice2 == 3) {   // 3: Remove all of the same elements from list
                        list_remove(&LIST);
                        print_list(&LIST, iterate_int);
                    }
                    else if (iChoice2 == 4) {   // 4: Convert Linked List to an array WORKING
                        int type = 0;
                        list_to_array(&LIST, type);
                    }
                    else if (iChoice2 == 5) {   // 5: Print list WORKING
                        print_list(&LIST, iterate_int);
                    }
                    else if (iChoice2 == 6) {   // 6: terminate WORKING
                        list_delete(&LIST);
                        exit(1);
                    }
                    else { // try again
                        printf("Invalid choice\n");
                        system("pause");
                    }
                }
            }

            case 2: {  // test cases for an char linked list
                int n = ask_num_nodes();
                unsigned char_size = sizeof(char *); 
                list_create(&LIST, free_string, char_size);
                void *data;
                const char *strings[n];
                size_t malloc_size = 100;
                for (int i=0; i<n; i++) {
                    strings[i] = malloc(malloc_size * sizeof(char));
                    printf("Enter word number: %d\n", i+1);
                    scanf("%99s",strings[i]);
                }

                char *word;
                for (int i=0; i<n; i++) {
                    word = strdup(strings[i]);
                    list_append(&LIST, &word);
                    free(strings[i]);
                    strings[i] = NULL;
                }
                printf("\n\n\n");
                printf("___________________________________\n");
                print_list(&LIST, iterate_string);
                printf("\n");
                printf("List Size: %d\n", list_size(&LIST));
                printf("___________________________________\n");
                while (1) {
                    print_menu2();
                    scanf("%d",&iChoice2);
                    if (iChoice2 == 1) {   // 1: Insert at a specific location NOT WORKING
                        list_insert_at(&LIST);
                        print_list(&LIST, iterate_string); 
                    }
                    else if (iChoice2 == 2) {   // 2: Remove element from location WORKING
                        list_remove_at(&LIST);
                        print_list(&LIST, iterate_string);
                    }
                    else if (iChoice2 == 3) {   // 3: Remove all of the same elements from list
                        list_remove(&LIST);
                        print_list(&LIST, iterate_string);
                    }
                    else if (iChoice2 == 4) {   // 4: Convert Linked List to an array WORKING
                        list_to_array(&LIST,1);
                    }
                    else if (iChoice2 == 5) {   // 5: Print list WORKING
                        print_list(&LIST, iterate_string);
                    }
                    else if (iChoice2 == 6) {   // 6: Go back to main menu WORKING
                        list_delete(&LIST);
                        exit(1);
                    }
                    else { // try again
                        printf("Invalid choice\n");
                        system("pause");
                    }
                }
            }

            case 3: { // test cases for an float linked list
                int n = ask_num_nodes();
                unsigned float_size = sizeof(float); 
                list_create(&LIST, free_string, float_size);
                void *data;
                for (int i=0; i<n; i++) {
                    printf("Enter float data : %d\n", i+1);
                    scanf("%f",&data);
                    list_append(&LIST, &data);
                }

                printf("\n\n\n");
                printf("___________________________________\n");
                print_list(&LIST, iterate_float);
                printf("\n");
                printf("List Size: %d\n", list_size(&LIST));
                printf("___________________________________\n");
                while (1){
                    print_menu2();
                    scanf("%d",&iChoice2);
                    if (iChoice2 == 1) {   // 1: Insert at a specific location NOT WORKING
                        list_insert_at(&LIST);
                        print_list(&LIST, iterate_float);
                    }
                    else if (iChoice2 == 2) {   // 2: Remove element from location WORKING
                        list_remove_at(&LIST);
                        print_list(&LIST, iterate_float);
                    }
                    else if (iChoice2 == 3) {   // 3: Remove all of the same elements from list
                        list_remove(&LIST);
                        print_list(&LIST, iterate_float);
                    }
                    else if (iChoice2 == 4) {   // 4: Convert Linked List to an array WORKING
                        list_to_array(&LIST, 2);
                    }
                    else if (iChoice2 == 5) {   // 5: Print list WORKING
                        print_list(&LIST, iterate_float);
                    }
                    else if (iChoice2 == 6) {   // 6: Terminate WORKING
                        list_delete(&LIST);
                        exit(1);
                    }
                    else { // try again
                        printf("Invalid choice\n");
                        system("pause");
                    }
                }
            }

            case 4: {
                printf("\n\nprocess is terminated\n ");
                exit(1);
            }

            default: {
                printf("Invalid choice\n");
                system("pause");
                break;
            }
        }
    }
    return 0;
}