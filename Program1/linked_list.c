#include "list_internal.h"
#include "list_external.h"


int main(void)
{
    int iRetValue = -1;
    int iChoice = 0;
    int iNumberNode =0;
    int iCount = 0;
    int iPosition =0;
    /*Start with the empty list */
    nodePointer head = NULL;
    while(1)
    {
        //Clear the screen
        system("cls");
        //Select the Choice as per the requirements
        printf("\n\n\
            1: Create the Linked List of character\n\
            2: Create the Linked List of integer\n\
            3: Create the Linked List of float\n\
            4: terminatethe process \n\n\n");
        printf("\n\nenter your choice = ");
        scanf("%d",&iChoice);
        switch(iChoice)
        {
        case 1:
        {
            char acBuffer[4] = {'a','b','c','d'};
            iNumberNode = Number_Node(acBuffer);
            for(iCount =0; iCount <iNumberNode ; iCount++)
            {
                CreateLinkedList(&head, (acBuffer + iCount),DATA_SIZE(acBuffer));
            }
            PrintTheCharater(head);
            break;
        }
        case 2:
        {
            int acBuffer[4] = {1, 2, 3, 4};
            iNumberNode = Number_Node(acBuffer);
            for(iCount =0; iCount <iNumberNode ; iCount++)
            {
                CreateLinkedList(&head, (acBuffer + iCount),DATA_SIZE(acBuffer));
            }
            PrintTheInteger(head);
            break;
        }
        case 3:
        {
            float acBuffer[4] = {1.1, 2.2, 3.3, 4.4};
            iNumberNode = Number_Node(acBuffer);
            for(iCount =0; iCount <iNumberNode ; iCount++)
            {
                CreateLinkedList(&head, (acBuffer + iCount),DATA_SIZE(acBuffer));
            }
            PrintTheFloat(head);
            break;
        }
        case 4:
        {
            printf("\n\nprocess is terminated\n ");
            exit(1);
        }
        default:
        {
            printf("Invalid choice\n");
            system("pause");
            break;
        }
        }
        //Free all allocated memory
        FreeAllocatedMemory(&head);
    }
    return 0;
}