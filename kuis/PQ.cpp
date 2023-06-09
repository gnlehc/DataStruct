#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct pq
{
    char code[40];
    char name[40];
    int age;
    int prior;
    pq *next, *prev;
} *first, *last;

pq *createNode(char code[], char name[], int age)
{
    pq *node = (pq *)calloc(1, sizeof(pq));
    // pake calloc next dan prev tidak perlu di NULL kan
    strcpy(node->name, name);
    node->age = age;
    int prior = 0;
    if (strcmp(code, "Platinum") == 0)
    {
        prior = 1;
    }
    else if (strcmp(code, "Gold") == 0)
    {
        prior = 2;
    }
    else if (strcmp(code, "Silver") == 0)
    {
        prior = 3;
    }
    strcpy(node->code, code);
    node->prior = prior;
    return node;
}

pq *insert(char code[], char name[], int age)
{
    pq *node = createNode(code, name, age);
    if (!first)
    {
        first = last = node;
    }
    else
    {
        pq *curr = first;

        while (curr && curr->prior <= node->prior)
        {
            curr = curr->next;
        }

        if (curr)
        {
            pq *before = curr->prev;
            before->next = node;
            node->prev = before;
            node->next = curr;
            curr->prev = node;
        }
        else
        {
            // push tail
            last->next = node;
            node->prev = last;
            last = node;
        }
    }
}

void display()
{
    pq *curr = first;
    int i = 0;
    while (curr)
    {
        i++;
        printf("%02d. | %d | %s | %d |\n", i, curr->prior, curr->name, curr->age);
        curr = curr->next;
    }
}

void removePriority()
{
    if (!first)
    {
        return;
    }
    else if (first == last)
    {
        free(first);
        first = last = NULL;
        puts("Successfully deleted");
    }
    else
    {
        pq *candidateFirst = first->next;
        first->next = candidateFirst->prev = NULL;
        first = candidateFirst;
        puts("Successfully deleted");
    }
}

void popHead()
{
    if (!first)
    {
        return;
    }
    else if (first = last)
    {
        free(first);
        first = last = NULL;
    }
    else
    {
        pq *newHead = first->next;
        first->next = newHead->prev = NULL;
        free(first);
        first = newHead;
    }
}

void removeALL()
{
    while (first)
    {
        popHead();
    }
    puts("Queue has been cleared");
}

void menu()
{
    int chs = 0;
    char name[40] = {0};
    int age = 0;
    char code[40] = {0};
    puts("Hospital");
    puts("====================");
    puts("1. Insert");
    puts("2. View");
    puts("3. Delete Queue");
    puts("4. Delete All Queue");
    puts("5. Exit");
    printf(">>> ");
    scanf("%d", &chs);
    getchar();
    switch (chs)
    {
    case 1:
        printf("Input Your Code: ");
        scanf("%s", &code);
        getchar();
        printf("Input Your Name: ");
        scanf("%[^\n]", &name);
        getchar();
        printf("Input Your Age: ");
        scanf("%d", &age);
        getchar();
        insert(code, name, age);
        printf("Press Enter to continue...");
        getchar();
        system("cls");
        break;
    case 2:
        display();
        printf("Press Enter to continue...");
        getchar();
        system("cls");
        break;
    case 3:
        removePriority();
        break;
    case 4:
        removeALL();
        break;
    case 5:
        exit(0);
        break;
    default:
        break;
    }
}

int main()
{
    while (true)
    {
        menu();
    }

    return 0;
}
