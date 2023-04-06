#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define size 20
struct data
{
    char id[7];
    char name[50];
    char type[30];
    int price;
    data *next, *prev;
} *head[size], *tail[size];

data *newData(char name[], char type[], int price)
{
    data *node = (data *)malloc(sizeof(data));
    strcpy(node->name, name);
    strcpy(node->type, type);
    node->price = price;
    char getID[7];
    sprintf(getID, "%c%c%d%d%d", type[0], type[1] - 32, rand() % 10, rand() % 10, rand() % 10);
    for (int i = 0; i < strlen(type); i++)
    {
        if (type[i] == ' ' && type[i + 1] != ' ')
        {
            getID[1] = type[i + 1];
        }
    }
    strcpy(node->id, getID);
    node->next = NULL;
    node->prev = NULL;
    return node;
}

int hash(char id[])
{
    int hashkey = 0;
    for (int i = 0; i < 5; i++)
    {
        hashkey += id[i];
        // hashkey = hashkey*10 + (id[i] - '0');
    }
    return (hashkey - 1) % size;
}

void insert(data *node)
{
    int key = hash(node->id);
    if (!head[key])
    {
        head[key] = tail[key] = node;
    }
    else
    {
        // tail[key]->next = node;
        // node->prev = tail[key];
        // tail[key] = node;
        data *curr = head[key]; // mulai dari head di index tertentu
        while (curr->next)
        {                      // kalo di sampingnya ada data
            curr = curr->next; // ke samping terus sampe nemu slot kosong
        }
        curr->next = node; // kalo ad slot kosong di sampingnya isi sama data baru
    }
}

void remove(char id[])
{
    int key = hash(id);
    if (!head[key])
    {
        puts("There is no data to be deleted");
    }

    if (head[key] == tail[key] && strcmp(head[key]->id, id) == 0)
    {
        head[key] = NULL;
        tail[key] = NULL;
        free(head[key]);
        printf("%s Successfully deleted", id);
        return;
    }
    else if (strcmp(head[key]->id, id) == 0)
    {
        data *temp = head[key];
        head[key] = head[key]->next;
        head[key]->prev = NULL;
        temp->next = NULL;
        free(temp);
        printf("%s Successfully deleted", id);
        return;
    }
    else if (strcmp(tail[key]->id, id) == 0)
    {
        data *temp = tail[key];
        tail[key] = tail[key]->prev;
        temp->prev = NULL;
        tail[key]->next = NULL;
        free(temp);
        printf("%s Successfully deleted", id);
        return;
    }
    else
    {
        data *curr = head[key]->next;
        while (curr && strcmp(curr->id, id) != 0)
        {
            curr = curr->next;
        }
        if (!curr)
        {
            puts("ID not found!");
            return;
        }
        else
        {
            data *after = curr->next;
            data *before = curr->prev;
            after->prev = before;
            before->next = after;
            curr->next = NULL;
            curr->prev = NULL;
            curr = NULL;
            free(curr);
        }
    }
}

void NODATA(int simpen)
{
    if (simpen == 0)
    {
        puts("There is no data");
    }
}

void display()
{
    int simpen = 0;
    for (int i = 0; i < size; i++)
    {
        if (!head[i])
        {
            simpen += 0;
        }

        data *curr = head[i];
        while (curr)
        {
            printf("ID: %s\n", curr->id);
            printf("Name: %s\n", curr->name);
            printf("Type: %s\n", curr->type);
            printf("Price: %d\n", curr->price);
            curr = curr->next;
            simpen += 1;
            return;
        }
    }
    NODATA(simpen);
}

int main()
{
    char id[7] = {0};
    char name[40] = {0};
    char type[40] = {0};
    int price = 0;
    printf("Enter your name: ");
    scanf("%s", &name);
    getchar();
    printf("Enter Type: ");
    scanf("%s", &type);
    getchar();
    printf("Enter Price: ");
    scanf("%d", &price);
    getchar();
    insert(newData(name, type, price));
    display();
    // puts("press enter to continue");
    // getchar();
    // puts("Enter id to remove");
    // scanf("%s", &id);
    // remove(id);
    return 0;
}