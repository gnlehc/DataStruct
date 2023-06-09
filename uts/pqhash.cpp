#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define size 20
struct data
{
    char name[40];
    char desc[40];
    char code[40];
    int age;
    int prior;
    data *next, *prev;
} *head[size], *tail[size];

int hash(int prior)
{
    return prior % 100;
}
data *createNode(char name[], int age, char desc[], char code[])
{
    data *newNode = (data *)calloc(1, sizeof(data));
    newNode->age = age;
    strcpy(newNode->name, name);
    strcpy(newNode->desc, desc);
    int p;
    if (strcmp(newNode->code, "Red") == 0)
    {
        p = 3;
    }
    else if (strcmp(newNode->code, "Yellow") == 0)
    {
        p = 2;
    }
    else if (strcmp(newNode->code, "Green") == 0)
    {
        p = 1;
    }
    strcpy(newNode->code, code);
    newNode->prior = p;
    return newNode;
}

void pushHead(data *node)
{
    int key = hash(node->prior);
    if (!head[key])
    {
        head[key] = tail[key] = node;
    }
    else
    {
        head[key]->prev = node;
        node->next = head[key];
        head[key] = node;
    }
}

void pushTail(data *node)
{
    int key = hash(node->prior);
    if (!head[key])
    {
        head[key] = tail[key] = node;
    }
    else
    {
        tail[key]->next = node;
        node->prev = tail[key];
        tail[key] = node;
    }
}

void pushMid(data *node)
{
    int key = hash(node->prior);
    if (!head[key])
    {
        pushHead(node);
    }
    else if (node->prior < tail[key]->prior)
    {
        pushTail(node);
    }
    else
    {
        data *curr = head[key];
        data *temp = node;
        while (curr->prior < node->prior)
        {
            curr = curr->next;
        }

        temp->prev = curr;
        temp->next = curr->next;
        curr->next->prev = temp;
        curr->next = temp;
    }
}

void printQueue()
{
    data *curr;
    int key = hash(curr->prior);
    curr = head[key];
    puts("Prior List");
    puts("============");
    while (curr)
    {
        printf("Name: %s\n", curr->name);
        printf("Age: %d\n", curr->age);
        printf("Description: %s\n", curr->desc);
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
        scanf("%s", &code);
        getchar();
        pushMid(createNode(name, age, syntp, code));
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