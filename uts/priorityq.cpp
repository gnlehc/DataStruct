#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct hospital
{
    char name[40];
    int age;
    char syntp[40];
    char code[40];
    int prior;
    hospital *next, *prev;
} *head, *tail;

hospital *newNode(char name[], int age, char syntp[], char code[])
{
    hospital *node = (hospital *)calloc(1, sizeof(hospital));
    strcpy(node->name, name);
    strcpy(node->syntp, syntp);
    node->age = age;
    int p = 0;
    if (strcmp(code, "Red") == 0)
    {
        p = 3;
    }
    else if (strcmp(code, "Yellow") == 0)
    {
        p = 2;
    }
    else if (strcmp(code, "Green") == 0)
    {
        p = 1;
    }
    strcpy(node->code, code);
    node->prior = p;
    return node;
}

void pushHead(hospital *node)
{
    if (!head)
    {
        head = tail = node;
    }
    else
    {
        head->prev = node;
        node->next = head;
        head = node;
    }
}

void pushTail(hospital *node)
{
    if (head)
    {
        head = tail = node;
    }
    else
    {
        tail->next = node;
        node->prev = tail;
        tail = node;
    }
}
// push mid
void insert(hospital *node)
{
    hospital *curr;
    hospital *prev;
    if (!head)
    {
        pushHead(node);
    }
    else if (head == tail)
    {
        if (node->prior <= head->prior)
        {
            pushTail(node);
        }
        else
        {
            pushHead(node);
        }
    }
    else
    {
        curr = tail;
        prev = NULL;
        while (curr && curr->prior < node->prior)
        {
            prev = curr;
            curr = curr->next;
        }
        if (curr == tail)
        {
            pushTail(node);
        }
        else if (prev = head)
        {
            pushHead(node);
        }
        else
        {
            prev->next = node;
            node->prev = prev;
            curr->prev = node;
            node->next = curr;
        }
    }
}

void printQueue()
{
    hospital *curr = head;
    puts("Prior List");
    puts("============");
    while (curr)
    {
        printf("Name: %s\n", curr->name);
        printf("Age: %d\n", curr->age);
        printf("Description: %s\n", curr->syntp);
        printf("Code: %s\n", curr->code);
        printf("Prior: %d\n", curr->prior);
        curr = curr->next;
    }
    return;
}

void menu()
{
    int chs = 0;
    char name[40] = {0};
    char syntp[40] = {0};
    int age = 0;
    char code[40] = {0};
    puts("Hospital");
    puts("====================");
    puts("1. Insert");
    puts("2. View");
    puts("3. Delete Queue");
    puts("4. Exit");
    printf(">>> ");
    scanf("%d", &chs);
    getchar();
    switch (chs)
    {
    case 1:
        printf("Input Your Name: ");
        scanf("%[^\n]", &name);
        getchar();
        printf("Input Your Age: ");
        scanf("%d", &age);
        getchar();
        printf("Input Your Description: ");
        scanf("%[^\n]", &syntp);
        getchar();
        printf("Input Your Code: ");
        scanf("%s", &code);
        getchar();
        insert(newNode(name, age, syntp, code));
        printQueue();
        printf("Press Enter to continue...");
        getchar();
        system("cls");
        break;
    case 2:
        printQueue();
        printf("Press Enter to continue...");
        getchar();
        system("cls");
        break;
    case 3:
        break;
    case 4:
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