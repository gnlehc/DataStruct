#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct hospital
{
    char name[40];
    int age;
    char syntp[40];
    char code[10];
    int prior;
    hospital *next, *prev;
} *head, *tail;

hospital *newNode(char name[], int age, char syntp[], char code[])
{
    hospital *node = (hospital *)calloc(1, sizeof(hospital));
    strcpy(node->name, name);
    strcpy(node->syntp, syntp);
    strcmp(node->code, code);
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
    node->prior = p;
    return node;
}

void insert(hospital *node)
{
    if (!head)
    {
        head = tail = node;
    }
    else if (node->prior > head->prior)
    {
        node->next = head;
        head->prev = node;
        head = node;
    }
    else if (node->prior < tail->prior)
    {
        node->prev = tail;
        tail->next = node;
        tail = node;
    }
    else
    {
        hospital *curr = head;
        while (node->prior <= curr->prior)
        {
            curr = curr->next;
        }
        node->next = curr;
        node->prev = curr->prev;
        curr->prev->next = node;
        curr->prev = node;
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
    puts("NULL");
}

void menu()
{
    int chs = 0;
    char name[40] = {0};
    char syntp[40] = {0};
    int age = 0;
    char code[10] = {0};
    puts("BlueJack Hospital");
    puts("====================");
    puts("1. Insert");
    puts("2. View");
    puts("3. Next Queue");
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
        scanf("%[^\n]", &code);
        getchar();
        insert(newNode(name, age, syntp, code));
        printQueue();
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