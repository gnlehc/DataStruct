#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define size 25
struct data
{
    char name[35];
    int dif;
    char probID[7];
    char type[35];
    int submit;
    int solve;
    data *next, *prev;
} *head[size], *tail[size];

data *createNode(char name[], char type[], int dif, int submit)
{
    data *newNode = (data *)malloc(sizeof(data));
    strcpy(newNode->name, name);
    strcpy(newNode->type, type);
    newNode->dif = dif;
    newNode->submit = submit;
    int temp = submit;
    int limit = 0.7 * temp;
    newNode->solve = rand() % limit;
    newNode->next = NULL;
    newNode->prev = NULL;
    char ID[7];
    int a = rand() % 10;
    int b = rand() % 10;
    int c = rand() % 10;
    int len = strlen(type);
    sprintf(ID, "%c%c%d%d%d", type[0], type[1] - 32, a, b, c);
    for (int i = 0; i < len; i++)
    {
        if (type[i] == ' ' && type[i + 1] != ' ')
        {
            ID[1] = type[i + 1];
        }

        // else if(type[i+1] >= 'a' && type[i+1] <= 'z'){
        //     type[i] -= 32;
        // }
    }
    // char typetemp[7];
    // int cond = 0;
    // int len = strlen(type);
    // for (int i = 0; i < len; i++)
    // {
    //     if (type[i] == ' ' && type[i] != ' ')
    //     {
    //         typetemp[i] = type[i + 1];
    //         cond = 1;
    //     }
    // }
    // sprintf(ID, "%c%c%d%d%d", type[0], typetemp - 32, a, b, c);

    strcpy(newNode->probID, ID);
    return newNode;
}

int hash(char probID[])
{
    int hashkey = 0;
    for (int i = 0; i < 5; i++)
    {
        hashkey += probID[i];
    }
    return hashkey % size;
}

// void pushTail(data *newNode)
// {
//     int index = hash(newNode->probID);

//     if (!head[index])
//     {
//         head[index] = tail[index] = newNode;
//     }
//     else
//     {
//         tail[index]->next = newNode;
//         newNode->prev = tail[index];
//         tail[index] = newNode;
//     }
// }

void insert(data *node)
{
    int index = hash(node->probID);
    if (!head[index])
    {
        head[index] = tail[index] = node;
    }
    else
    {
        data *curr = head[index];
        while (curr->next)
        {
            curr = curr->next;
        }
        curr->next = node;
    }
}

void NoDATA(int simpen)
{
    if (simpen == 0)
    {
        puts("+-------------------------------------+");
        puts("| ~There is no Code Problem To Solve~ |");
        puts("+-------------------------------------+");
    }
    else
    {
        return;
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
        data *curr = head[i];
        while (curr)
        {
            puts("============================");
            printf("# ID: %-3s\n", curr->probID);
            printf("# Name: %-3s\n", curr->name);
            printf("# Type: %-3s\n", curr->type);
            printf("# Difficulty: %-3d\n", curr->dif);
            printf("# Total Submission: %-3d\n", curr->submit);
            printf("# Total Solved Case: %-3d\n", curr->solve);
            puts("============================");
            curr = curr->next;
            simpen += 1;
        }
    }
    NoDATA(simpen);
}

// data *search(char ID[])
// {
//     int index = hash(ID);
//     if (head[index])
//     {
//         data *curr = head[index];
//         while (curr && strcmp(curr->probID, ID) != 0)
//         {
//             curr = curr->next;
//         }
//         return curr;
//     }
//     return NULL;
// }

void deleteProb(char ID[])
{
    int index = hash(ID);
    if (!head[index])
    {
        puts("============================================");
        puts("# Fail to delete, there is no code problem #");
        puts("============================================");
    }

    if (head[index] == tail[index] && strcmp(head[index]->probID, ID) == 0)
    {
        free(head[index]);
        head[index] = NULL;
        tail[index] = NULL;
        puts("==============================================");
        printf("# Successfully deleted %s code problem   #\n", ID);
        puts("==============================================");
    }
    else if (strcmp(head[index]->probID, ID) == 0)
    {
        data *temp = head[index];
        head[index] = head[index]->next;
        head[index]->prev = NULL;
        temp->next = NULL;
        free(temp);
        temp = NULL;
        puts("==============================================");
        printf("# Successfully deleted %s code problem   #\n", ID);
        puts("==============================================");
        return;
    }
    else if (strcmp(tail[index]->probID, ID) == 0)
    {
        data *temp = tail[index];
        tail[index] = tail[index]->prev;
        tail[index]->next = NULL;
        temp->prev = NULL;
        free(temp);
        temp = NULL;
        puts("==============================================");
        printf("# Successfully deleted %s code problem   #\n", ID);
        puts("==============================================");
        return;
    }
    else
    {
        data *curr = head[index]->next;
        while (curr && strcmp(curr->probID, ID) != 0)
        {
            curr = curr->next;
        }
        if (curr == NULL)
        {
            puts("============================================");
            puts("# Fail to delete, there is no code problem #");
            puts("============================================");
        }
        else
        {
            data *after = curr->next;
            data *before = curr->prev;
            after->prev = before;
            before->next = after;

            curr->next = NULL;
            curr->prev = NULL;
            free(curr);
            curr = NULL;
            puts("==============================================");
            printf("# Successfully deleted %s code problem   #\n", ID);
            puts("==============================================");
            return;
        }
    }
}

void Menu()
{
    int chs = 0;
    char name[31] = {0};
    int dif = 0;
    int len = 0;
    int submit = -1;
    int solve = 0;
    int limit = 0;
    char type[35] = {0};
    char ID[7];
    puts("codeforJeS");
    puts("---------------");
    puts("1. Add a Code Problem");
    puts("2. View All Code Problem");
    puts("3. Delete a Code Problem");
    puts("4. Exit");
    printf(">>> ");
    scanf("%d", &chs);
    getchar();
    switch (chs)
    {
    case 1:
        // printf("Input problem's name [3..30]: ");
        // scanf("%[^\n]", &name);
        // getchar();
        len = strlen(name);
        while (len < 3 || len > 30)
        {
            printf("Input problem's name [3..30]: ");
            scanf("%[^\n]", &name);
            getchar();
            len = strlen(name);
        }

        while (dif < 800 || dif > 3500)
        {
            printf("Input problem's difficulty [800..3500]: ");
            scanf("%d", &dif);
            getchar();
        }

        while (strcmp(type, "Dynamic Programming") != 0 && strcmp(type, "Math") != 0 && strcmp(type, "Greedy") != 0 && strcmp(type, "Brute Force") != 0)
        {
            printf("Input problem's type [case sensitive]: ");
            scanf("%[^\n]", &type);
            getchar();
        }

        while (submit < 0 || submit > 100)
        {
            printf("Input problem's total of case submissions [0..100]: ");
            scanf("%d", &submit);
            getchar();
        }
        insert(createNode(name, type, dif, submit));
        puts("----------------------------");
        puts("Succesfully inserted!");
        print();
        printf("Press ENTER to continue...");
        getchar();
        system("cls");
        break;
    case 2:
        print();
        break;
    case 3:
        printf("Input Problem ID to be deleted: ");
        scanf("%s", &ID);
        getchar();
        deleteProb(ID);
        puts("Problem Successfully deleted!");

        printf("Press Enter to continue...");
        getchar();
        system("cls");
        break;
    case 4:
        puts("Program Exited...");
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
        Menu();
    }

    return 0;
}