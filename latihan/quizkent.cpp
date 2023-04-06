#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define SIZE 100
struct accessory
{
    char name[40];
    char aID[7];
    char type[40];
    double price;
    char goldType[255];
    accessory *next, *prev;
} *head[SIZE], *tail[SIZE];

accessory *createNewItem(char name[], char type[], char goldType[], double price)
{
    accessory *newAcc = (accessory *)malloc(sizeof(accessory));
    strcpy(newAcc->name, name);
    strcpy(newAcc->type, type);
    strcpy(newAcc->goldType, goldType);
    char ID[7];
    int a = rand() % 10;
    int b = rand() % 10;
    int c = rand() % 10;
    // coba pake double
    double w = 50000 * 0.5;
    double r = 75000 * 0.5;
    double y = 100000 * 0.5;
    if (strcmp(goldType, "White") == 0)
    {
        price = price + w;
    }
    if (strcmp(goldType, "Rose") == 0)
    {
        price = price + r;
    }
    if (strcmp(goldType, "Yellow") == 0)
    {
        price = price + y;
    }
    newAcc->price = price;
    sprintf(ID, "%c%c%d%d%d", type[0], type[1] - 32, a, b, c);
    strcpy(newAcc->aID, ID);
    newAcc->next = NULL;
    newAcc->prev = NULL;
    return newAcc;
}

int hash(char ID[])
{
    int hashkey = 0;
    for (int i = 0; i < 5; i++)
    {
        hashkey += ID[i];
    }

    return hashkey % SIZE;
}

// hash chaining
void insert(accessory *node)
{
    int index = hash(node->aID);
    if (!head[index])
    {
        head[index] = tail[index] = node;
    }
    else
    {
        // tail[index]->next = node;
        // node->prev = tail[index];
        // tail[index] = node;
        accessory *curr = head[index];
        while (curr->next)
        {
            curr = curr->next;
        }
        curr->next = node;
    }
}

void currentData(accessory *curr)
{
    int index = hash(curr->aID);
    insert(curr);
    puts(" ");
    puts("Successfully Inserted");
    puts("----------------------");
    puts("---------------------------------------------------------------------------");
    puts("| Accessory ID | Accessory Name   | Type      | Gold Type     | Price     |");
    puts("---------------------------------------------------------------------------");
    printf("| %-12s | %-15s | %-10s | %-12s | %-10.0lf |\n", curr->aID, curr->name, curr->type, curr->goldType, curr->price);
    puts("---------------------------------------------------------------------------");
    puts(" ");
}

void Remove(char ID[])
{
    int index = hash(ID);
    if (!head[index])
    {
        puts("----------------------------------------------------------------------------");
        puts("|                 Fail to delete, There is nothing to delete               |");
        puts("----------------------------------------------------------------------------");
        return;
    }
    if (head[index] == tail[index] && strcmp(head[index]->aID, ID) == 0)
    {
        free(head[index]);
        head[index] = NULL;
        tail[index] = NULL;
        puts("----------------------------------------------------------------------------");
        puts("|                            Delete Successfull                            |");
        puts("----------------------------------------------------------------------------");
        return;
    }
    else if (strcmp(head[index]->aID, ID) == 0)
    {
    }
}
void NoDATA(int simpen)
{
    if (simpen == 0)
    {
        puts("----------------------------------------------------------------------------");
        puts("| Accessory ID | Accessory Name   | Type      | Gold Type     | Price     |");
        puts("----------------------------------------------------------------------------");
        puts("|                         There Is No Accessories Available               |");
        puts("----------------------------------------------------------------------------");
    }
}

void print()
{
    int simpen = 0;
    for (int i = 0; i < SIZE; i++)
    {
        if (!head[i])
        {
            simpen += 0;
        }
        // accessory *curr = head[i]->next;
        accessory *curr = head[i];
        // if(head[i]){
        //     printf("| %-12s | %-15s | %-12s | %-15s | %-10lld |", curr->aID, curr->name, curr->type, curr->goldType, curr->price);
        // }
        while (curr)
        {
            puts(" ");
            puts("----------------------------------------------------------------------------");
            puts("| Accessory ID | Accessory Name   | Type      | Gold Type     | Price     |");
            puts("----------------------------------------------------------------------------");
            printf("| %-12s | %-15s | %-10s | %-12s | %-10.0lf |\n", curr->aID, curr->name, curr->type, curr->goldType, curr->price);
            puts("----------------------------------------------------------------------------");
            curr = curr->next;
            simpen += 1;
        }
    }
    puts(" ");
    NoDATA(simpen);
}

void Search(char ID[])
{
    int index = hash(ID);
    if (!head[index])
    {
        // puts("----------------------------------------------------------------------------");
        // puts("|                     Fail to delete, ID wasn't Found                      |");
        // puts("----------------------------------------------------------------------------");
        return;
    }
    if (head[index] == tail[index] && strcmp(head[index]->aID, ID) == 0)
    {
        accessory *curr = head[index];
        puts(" ");
        puts("----------------------------------------------------------------------------");
        puts("| Accessory ID | Accessory Name   | Type      | Gold Type     | Price      |");
        puts("----------------------------------------------------------------------------");
        printf("| %-12s | %-15s | %-10s | %-12s | %-10.0lf |", curr->aID, curr->name, curr->type, curr->goldType, curr->price);
        puts("----------------------------------------------------------------------------");
        puts(" ");
        return;
    }
}

void MENU()
{
    char ID[7] = {0};
    int chs = 0;
    int len = 0;
    char name[40] = {0};
    char type[25] = {0};
    char goldType[30] = {0};
    double price = 0;
    char ans[1] = {0};
    puts("GOld Accessory");
    puts("------------------");
    puts("1. Add New Accessory");
    puts("2. View Accessory");
    puts("3. Delete Accessory");
    puts("4. Exit");
    printf(">>> ");
    scanf("%d", &chs);
    getchar();
    switch (chs)
    {
    case 1:
        while (len < 5 || len > 20)
        {
            printf("Insert Accessory Name [5..20]: ");
            scanf("%[^\n]", &name);
            getchar();
            len = strlen(name);
        }

        printf("Insert Accessory Type [Watch | Rose | Bracelet](Case Sensitive): ");
        scanf("%s", &type);
        getchar();
        printf("Input Accessory Gold Type [White | Rose | Yellow]: ");
        scanf("%s", &goldType);
        getchar();
        while (price < 50000 || price > 100000)
        {
            printf("Input Accessory Price [50000-100000]: ");
            scanf("%lf", &price);
            getchar();
        }

        // insert(createNewItem(name, type, goldType, price));
        // print();
        currentData(createNewItem(name, type, goldType, price));
        puts("Press Enter to continue...");
        getchar();
        system("cls");
        break;
    case 2:
        print();
        puts("Press Enter to continue...");
        getchar();
        system("cls");
        break;
    case 3:
        printf("Enter ID to be deleted: ");
        scanf("%s", &ID);
        getchar();
        Search(ID);
        printf("Are You Sure to delete selected accessory [y/n]? ");
        scanf("%c", &ans);
        getchar();
        if (strcmp(ans, "y") == 0)
        {
            Remove(ID);
        }
        else if (strcmp(ans, "n") == 0)
        {
            system("cls");
            return;
        }

        puts("Press Enter to continue...");
        getchar();
        system("cls");
        break;
    case 4:
        puts("Program Exited...");
        exit(0);
    default:
        break;
    }
}

int main()
{
    while (true)
    {
        MENU();
    }
}