#pragma once
#include <stdlib.h>
struct books
{
    char name[50];
    char author[50];
    int pages;
    int cost;
    struct books* next;
};

void toHead(struct books** head, struct books* bookToAdd)
{
    bookToAdd->next = *head;
    *head = bookToAdd;
}

void toBottom(struct books** head, struct books* bookToAdd)
{
    struct books* current =*head;
    while (current->next != NULL)
    {
        current = current->next;
    }
    current->next = bookToAdd;
    bookToAdd->next = NULL;
}

void toMiddle(struct books** head, struct books* bookToAdd, int index)
{
    struct books* current = *head;
    int i = 1;
    while (i != index - 1)
    {
        if (current->next == NULL)
        {
            printf("No such index to insert\n");
            return;
        }
        current = current->next;
        i++;
    }
    int* tempadress = current->next;
    current->next = bookToAdd;
    bookToAdd->next = tempadress;
}

void delete(struct books** head, int index)
{
    struct books* current = *head;
    if (index == 1)
    {
        *head = current->next;
        return;
    }
    int i = 1;
    while (i < index - 1)
    {
        if (current->next == NULL)
        {
            printf("No such index to delete\n");
            return;
        }
        current = current->next;
        i++;
    }
    current->next = current->next->next;
}

void swap(struct books** prev, struct books** firstToSwap)        //функція міняє місцями два елементи списку
{
    struct books* secondToSwap = (*firstToSwap)->next;
    struct books* Temp = secondToSwap;
    (*firstToSwap)->next = secondToSwap->next;
    secondToSwap->next = (*prev)->next;
    *firstToSwap = Temp;
    (*prev)->next = Temp;
}

void swap_head(struct books** ppHead)        //функція міняє місцями голову списку з наступним елементом
{
    struct books* secondToSwap = (*ppHead)->next;
    (*ppHead)->next = secondToSwap->next;
    secondToSwap->next = *ppHead;
}

void bubble_sort(struct books** ppHead)
{
    struct books* pItem = *ppHead;
    struct books* prevItem;

    int sorted_or_not = 1;
    char* surname1, * surname2;
    char author1[50];
    char author2[50];
    int count;
    do
    {
        pItem = *ppHead;
        count = 0;    //змінна слугуватиме перевіркою, чи не хочемо ми поміняти місцями голову списку
        sorted_or_not = 1;
        while (pItem->next)
        {
            strcpy(author1, pItem->author);
            strcpy(author2, pItem->next->author);

            /*відокремлення прізвищ*/
            surname1 = strtok(author1, " ");

            surname2 = strtok(author2, " ");

            if (strcmp(surname1, surname2) > 0)
            {
                sorted_or_not = 0;
                if (!count)        //якщо каунтер = 0, це значить, що ми мінятимемо місцями голову з наступним елементом
                {
                    *ppHead = (*ppHead)->next;
                    swap_head(&pItem);
                }
                else
                {
                    swap(&prevItem, &pItem);
                }
            }
            count++;
            prevItem = pItem;
            pItem = pItem->next;
        }
    } while (!sorted_or_not);
    printf("Success\n");
}

void getNewBook(struct books* newbook)
{
    printf("Enter a name of the book: ");
    gets(newbook->name);
    gets(newbook->name);

    printf("Enter an author of the book: ");
    gets(newbook->author);

    printf("Enter amount of pages in the book: ");
    scanf("%d", &newbook->pages);

    printf("Enter cost of the book: ");
    scanf("%d", &newbook->cost);
}

void linef(char c)
{
    for (int i = 0; i < 60; i++)
    {
        printf("%c", c);
    }
    printf("\n");
}

void printList(struct books** head)
{
    printf("*********THE LIST********\n");
    struct books* iterator = *head;
    while (iterator != NULL)
    {
        printf("|| [The name]\t\t\t|| %s\n", iterator->name);
        printf("|| [The author]\t\t\t|| %s\n", iterator->author);
        printf("|| [Number of pages]\t\t|| %d\n", iterator->pages);
        printf("|| [The cost]\t\t\t|| %d\n", iterator->cost);
        linef('=');

        iterator = iterator->next;
    }
}

void freeList(struct books** head)
{
    struct books* iterator = *head;
    while (iterator != NULL)
    {
        struct books* temp = iterator;
        iterator = iterator->next;
        free(temp);
    }
}

void getBooksFromFile(struct books** head)
{
    struct books* current = *head;
   if(*head != NULL)
    {
        while (current->next != NULL)
            current = current->next;
    }
    FILE* input;
    input = fopen("books10.txt", "r");
    char inputstr[1000];
    const char* limit = ",";

    while (fgets(inputstr, sizeof(inputstr), input) != NULL)
    {
        struct books* book = (struct books*)malloc(sizeof(struct books));
        char* pw = strtok(inputstr, limit);

        strcpy(book->name, pw);
        pw = strtok(NULL, limit);

        strcpy(book->author, pw);
        pw = strtok(NULL, limit);

        book->pages = atoi(pw);
        pw = strtok(NULL, limit);

        book->cost = atoi(pw);


        book->next = NULL;

        if (*head == NULL) {
            *head = book;
            current = book;
        }
        else
        {
            current->next = book;
            current = book;
        }

    }
    printf("Success\n");
    fclose(input);
}

void getBookFromUser(struct books** head)
{
    int poz = 0;
    struct books* newbook = (struct books*)malloc(sizeof(struct books));
    getNewBook(newbook);
    if (*head == NULL)
    {
        *head = newbook;
        newbook->next = NULL;
    }
    else
    { 
        printf("where to add a book(1-top, 2-middle, 3-bottom): ");//додавання нового елементу на місце обране користувачем(не працює якщо викликати функціїї
        scanf("%d", &poz);                                         //які зверху тому я просто написав код тих функцій тут, хотілось би пофіксти
        if (poz == 1)
        {
            toHead(&(*head), newbook);
        }
        else if (poz == 2)
        {
            printf("Enter a pozition to insert a book: ");
            scanf("%d", &poz);
            toMiddle(&(*head), newbook, poz);
        }
        else if (poz == 3)
        {
            toBottom(&(*head), newbook);
        }
    }
}

void writeInFile(struct books** head)
{
    FILE* output;
    output = fopen("booksOutput.txt", "w");

    struct books* current = *head;
    while(current != NULL)
    {
        fputs(current->name,output);
        fputs(",",output);
        fputs(current->author, output);
        fputs(",", output);
        fprintf(output, "%d", current->pages);
        fputs(",", output);
        fprintf(output, "%d", current->cost);
        fputs("\n", output);
        current = current->next;
    } 
    fclose(output);
}

void deleteSpecificBooks(struct books** head)
{
        struct books* iterator = *head;// видалення
        int pozition = 1;
        char letterToDelete[4] = { 'A','B','C','D' };
        while (iterator != NULL)
        {
            for (int i = 0; i < 4; i++)
            {
                if (iterator->author[0] == letterToDelete[i])
                {
                    delete(&(*head), pozition);
                    pozition--;//коли видаляється елемент позиція всіх пілся нього зміщується на 1 назад
                    break;
                }
            }
            pozition++;
            iterator = iterator->next;
        }
        printf("Success\n");
}
