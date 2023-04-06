#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define size 50
struct ticket
{
    char id[7];
    char name[40];
    int age;
    char Tclass[40];
    int days;
    int price;
    ticket *next, *prev;
} *head[size], *tail[size];

ticket *newTicket(char name[], int age, char Tclass[], int days)
{
    ticket *node = (ticket *)malloc(sizeof(ticket));
    strcpy(node->name, name);
    strcpy(node->Tclass, Tclass);
    node->age = age;
    node->days = days;
    char getID[7];
    sprintf(getID, "%c%c%d%d%d", Tclass[0], Tclass[1], rand() % 10, rand() % 10, rand() % 10);
    for (int i = 0; i < strlen(Tclass); i++)
    {
        if (Tclass[i] == ' ' && Tclass[i + 1] != ' ')
        {
            getID[1] = Tclass[i + 1];
        }
    }
    int prc = 0;
    if (strcmp(Tclass, "First Class") == 0)
    {
        prc = (500 * days);
    }
    else if (strcmp(Tclass, "Business Class") == 0)
    {
        prc = (400 * days);
    }
    else if (strcmp(Tclass, "Economy Class") == 0)
    {
        prc = (300 * days);
    }
    node->price = prc;
    strcpy(node->id, getID);
    node->next = NULL;
    node->prev = NULL;
    return node;
}

// int hash(char id[])
// {
//     int hashkey = 0;
//     for (int i = 2; i < 5; i++)
//     {
//         hashkey += id[i];
//     }
//     return (hashkey - 1) % size;
// }

int hash(char id[]){
    int hashkey = 0;
    for(int i = 2; i < 5; i++){
        hashkey = hashkey*10 + (id[i] - '0');
    }
    return hashkey % size;
}

void insert(ticket *node)
{
    int key = hash(node->id);
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

void NODATA(int simpen)
{
    if (simpen == 0)
    {
        puts("There is no data");
    }
}

void print()
{
    int simpen = 0;
    for (int i = 0; i < size; i++)
    {
        if (!head[i])
        {
            simpen += 0;
        }

        ticket *curr = head[i];
        while (curr)
        {
            printf("ID: %s\n", curr->id);
            printf("Name: %s\n", curr->name);
            printf("Class: %s\n", curr->Tclass);
            printf("Days: %d\n", curr->days);
            printf("Total price: %d\n", curr->price);
            curr = curr->next;
            simpen += 1;
            return;
        }
    }
    NODATA(simpen);
}

void remove(char id[])
{
    int key = hash(id);
    if (!head[key])
    {
        puts("There is no data");
        return;
    }

    // ticket *curr = head[key]->next;
    if (head[key] == tail[key] && strcmp(head[key]->id, id) == 0)
    {
        head[key] = NULL;
        tail[key] = NULL;
        free(head[key]);
        printf("Ticket %s Successfully deleted\n", id);
        return;
    }
    else if (strcmp(head[key]->id, id) == 0)
    {
        ticket *temp = head[key];
        head[key] = head[key]->next;
        head[key]->prev = NULL;
        temp->next = NULL;
        free(temp);
        printf("Ticket %s Successfully deleted\n", id);
        return;
    }
    else if (strcmp(tail[key]->id, id) == 0)
    {
        ticket *temp = tail[key];
        tail[key] = tail[key]->prev;
        temp->prev = NULL;
        tail[key]->next = NULL;
        free(temp);
        printf("Ticket %s Successfully deleted\n", id);
        return;
    }
    else
    {
        ticket *curr = head[key]->next;
        while (curr && strcmp(curr->id, id) != 0)
        {
            curr = curr->next;
        }

        if (!curr)
        {
            puts("id not found");
        }
        else
        {
            ticket *after = curr->next;
            ticket *before = curr->prev;

            after->prev = before;
            before->next = after;

            curr->next = NULL;
            curr->prev = NULL;
            curr = NULL;
            free(curr);
            printf("Ticket %s Successfully deleted\n", id);
        }
    }
}

bool search(char id[])
{
    int key = hash(id);
    ticket *curr = head[key];
    if (!head[key])
    {
        puts("Data not found");
        return false;
    }

    else if (strcmp(head[key]->id, id) == 0)
    {
        printf("ID: %s\n", curr->id);
        printf("Name: %s\n", curr->name);
        printf("Class: %s\n", curr->Tclass);
        printf("Days: %d\n", curr->days);
        printf("Total price: %d\n", curr->price);
        return true;
    }
    else if (strcmp(tail[key]->id, id) == 0)
    {
        printf("ID: %s\n", curr->id);
        printf("Name: %s\n", curr->name);
        printf("Class: %s\n", curr->Tclass);
        printf("Days: %d\n", curr->days);
        printf("Total price: %d\n", curr->price);
        return true;
    }
    while (curr)
    {
        if (strcmp(curr->id, id) == 0)
        {
            printf("ID: %s\n", curr->id);
            printf("Name: %s\n", curr->name);
            printf("Class: %s\n", curr->Tclass);
            printf("Days: %d\n", curr->days);
            printf("Total price: %d\n", curr->price);
            return true;
        }
    }
    return false;
}

void currentData(ticket *node)
{
    insert(node);
    printf("Id: %s\n", node->id);
    printf("Price: %d\n", node->price);
}

void menu()
{
    int chs = 0;
    char name[40];
    int age = -1;
    char Tclass[40];
    int days = -1;
    int len = 0;
    char id[7] = {0};
    puts("1. Buy Cruise Ticket");
    puts("2. View All Cruise Ticket");
    puts("3. Delete Cruise Ticket");
    puts("4. Exit");
    printf(">>> ");
    scanf("%d", &chs);
    getchar();
    switch (chs)
    {
    case 1:
        while (len < 5 || len > 20)
        {
            printf("Input Your Name: ");
            scanf("%[^\n]", &name);
            len = strlen(name);
            getchar();
        }
        while (age < 0 || age > 100)
        {
            age = 0;
            printf("Input Your age: ");
            scanf("%d", &age);
            getchar();
            fflush(stdin);
        }
        while (strcmp(Tclass, "First Class") != 0 && strcmp(Tclass, "Business Class") != 0 && strcmp(Tclass, "Economy Class") != 0)
        {
            Tclass[40] = {0};
            printf("Input Your Ticket Class: ");
            scanf("%[^\n]", &Tclass);
            getchar();
        }
        while (days < 0 || days > 15)
        {
            days = 0;
            printf("Input days: ");
            scanf("%d", &days);
            getchar();
        }
        currentData(newTicket(name, age, Tclass, days));
        printf("Press Enter to continue...");
        getchar();
        system("cls");
        break;
    case 2:
        print();
        printf("Press Enter to continue...");
        getchar();
        system("cls");
        break;
    case 3:
        printf("Enter Ticket ID to delete: ");
        scanf("%s", &id);
        getchar();
        search(id);
        remove(id);
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