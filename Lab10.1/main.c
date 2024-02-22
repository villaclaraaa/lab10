#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "functions.h"
int alreadygetbooksfromfile = 0;
int main()
{
    struct books* head = NULL;

    unsigned int action = 10;
    printf("The SuperListProg!!!!!!!\n");
    printf("List of actions: 1-get books from file, 2-enter a book, 3-sort list, 4-delete book, 5-print the list, 6-write list to file,7-delete specific books, 8-finish the prog: \n");
    scanf("%d", &action);
    while (action != 8)
    {
        if (action == 1)
        {
            if (alreadygetbooksfromfile == 0)
            {
                getBooksFromFile(&head);
                printList(&head);
                alreadygetbooksfromfile++;
            }
            else
                printf("Already done\n");
        }
        else if (action == 2)
        {
            getBookFromUser(&head);
        }
        else if (action == 3)
        {
            if (head != NULL && head->next != NULL)
            {
                bubble_sort(&head);
                printList(&head);
            }
        }
        else if (action == 4)
        {
            if (head != NULL)
            {
                int index = 1;
                printf("Enter a number of book you want to delete: ");
                scanf("%d", &index);
                delete(&head, index);
            }
        }
        else if (action == 5)
        {
            if (head != NULL)
                printList(&head);
            else
                printf("The list is empty\n");
        }
        else if (action == 6)
        {
            if (head != NULL)
                writeInFile(&head);
        }
        else  if(action == 7)
        {
            deleteSpecificBooks(&head);
        }
        else
            printf("Wrong action\n");
       scanf("%d", &action);
    }
    freeList(&head);
    return 0;
}