#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>

struct cake
{
    char name[255];
    double price;
    int avail;
    char code[5];
    cake *next,
        *prev;
} *head = NULL, *tail = NULL;

cake *createCake(char name[], double price, int avail)
{
    cake *newCake = (cake *)malloc(sizeof(cake));
    newCake->price = price;
    strcpy(newCake->name, name);
    newCake->avail = avail;

    char genID[7];
    int a = rand()%10;
    int b = rand()%10;
    int c = rand()%10;
    sprintf(genID, "CK0%d%d%d", a, b, c);

    // int random = rand()%100;
    // char num[5];
    // itoa(random, num, 10);
    // strcpy(newCake->code, strcat("CK0", num));
    
    strcpy(newCake->code, genID);
    newCake->next = NULL;
    newCake->prev = NULL;
    return newCake;
}

void pushTail(char name[], double price, int avail)
{
    cake *Cakes = createCake(name, price, avail);
    if (!head)
    {
        head = tail = Cakes;
    }
    else
    {
        tail->next = Cakes;
        Cakes->prev = tail;
        tail = Cakes;
    }
}

void popHead()
{
    if (head == tail)
    {
        free(head);
        head = tail = NULL;
    }
    else
    {
        cake *curr = head;
        head = curr->next;
        head->prev = NULL;
        free(curr);
    }
}

void popTail()
{
    if (head == tail)
    {
        free(head);
        head = tail = NULL;
    }
    else
    {
        cake *curr = tail;
        tail = curr->prev;
        tail->next = NULL;
        free(curr);
    }
}
bool search(char name[])
{
    // int key = hash(id)
    if (!head) // !head[key]
    {
        return false;
    }
    else if (strcmp(head->name, name) == 0) // head[key]->id, id
    {
        return true;
    }
    else if (strcmp(tail->name, name) == 0) // tail[key]->id, id
    {
        return true;
    }
    else
    {
        cake *curr = head; // curr = head[key]
        while (curr)
        {
            if (strcmp(curr->name, name) == 0) // curr->id == id
            {
                return true;
            }
            curr = curr->next;
        }
    }
    return false;
}

void popMid(char name[])
{
    if (!head)
    {
        return;
    }
    else if (strcmp(head->name, name) == 0)
    {
        popHead();
    }
    else if (strcmp(tail->name, name) == 0)
    {
        popTail();
    }
    else
    {
        cake *curr = head;
        if (search(name) == true)
        {
            while (curr)
            {
                if (strcmp(curr->name, name) == 0)
                {
                    break;
                }
                curr = curr->next;
            }

            cake *before = curr->prev;
            cake *after = curr->prev;
            before->next = after;
            after->prev = before;
            free(curr);
        }
    }
}

void printCake()
{
    // srand(time(0));
    // int random = (rand());
    int i = 1;
    cake *curr = head;
    // if (!head)
    // {
    //     puts("There is no cake available");
    // }

    puts("No.   | Cake Code  | Cake Name   | Price   | Avaiable   ");
    puts("--------------------------------------------------------");
    while (curr != NULL)
    {
        // int random = (rand());
        printf("%-5d | %s | %-8s | %-5.3lf | %-5d |\n", i, curr->code, curr->name, curr->price, curr->avail);
        curr = curr->next;
        i++;
    }
}

int chs = 0;
void Menu()
{
    int avail;
    double price;
    char name[255] = {0};
    cake *temp;
    int jumlah;
    puts("BLUE CAKE SHOP CASHIER");
    puts("=======================");
    puts("");

    puts("1. Sell Cake");
    puts("2. Add Stock");
    puts("3. Exit");
    printf("Choose between 1-3 >> ");
    scanf("%d", &chs);
    getchar();
    puts(" ");
    // puts("No.  | Cake Code  | Cake Name     | Available     | Price     ");
    // puts("----------------------------------------------------------------");

    switch (chs)
    {
    case 1:
        puts("Enter Name of a Cake You Want To Buy");
        printf(">>> ");
        scanf("%s", &name);
        getchar();
        puts("Jumlah Yang Mau Di Beli");
        printf(">>> ");
        scanf("%d", &jumlah);
        getchar();

        break;
    case 2:
        puts("Enter Cake Name, Price, availablity");
        printf(">> ");
        scanf("%s", &name);
        getchar();
        scanf("%lf", &price);
        getchar();
        scanf("%d", &avail);
        getchar();

        pushTail(name, price, avail);
        printCake();
        
        break;
    case 3:
        puts("Bye Bye!");
        exit(0);

        // break;
    default:
        break;
    }
}

void sellCake(char name[], double price, int avail)
{
    cake *temp = createCake(name, price, avail);
    cake *curr = head;
    while (curr != NULL && strcmp(temp->name, name) != 0)
    {
        curr = curr->next;
    }
    if (curr != NULL)
    {
        curr->avail = temp->avail;
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

// #include<stdio.h>
// #include<string.h>
// #include<stdlib.h>

// struct cake
// {
//    char name[255];
//    double price;
//    int avail;
//    char code[5];
//    cake *next, *prev;
// }*head = NULL, *tail = NULL;

// int chs = 0;

// void Menu(){

//     puts("BLUE CAKE SHOP CASHIER");
//     puts("=======================");
//     puts("");

//     puts("1. Sell Cake");
//     puts("2. Add Stock");
//     puts("3. Exit");
//     printf("Choose between 1-3 >> ");
//     scanf("%d", &chs);
//     printf(" ");
//     // puts("No.  | Cake Code  | Cake Name     | Available     | Price     ");
//     // puts("----------------------------------------------------------------");
// }

// cake *createCake(char name[], double price, int avail){
//     cake *newCake = (cake *)malloc(sizeof(cake));
//     newCake->avail = avail;
//     newCake->price = price;
//     strcpy(newCake->name, name);

//     int num = rand()%100;
//     char nums[5];
//     itoa(num, nums, 10);
//     strcpy(newCake->code, strcat("CK0", nums));
//     newCake->next = NULL;
//     newCake->prev = NULL;
//     return newCake;
// }

// // void pushHead(cake *node){
// //     if(!head){
// //         head = tail = node;
// //     }else{
// //         head->prev = node;
// //         node->next = head;
// //         node->prev = NULL;
// //         head = node;
// //     }
// // }

// bool search(char code[]){
//     if(!head){
//         return false;
//     }else if(strcmp(head->code, code) == 0){
//         return true;
//     }else if(strcmp(tail->code, code) == 0){
//         return true;
//     }else{
//         cake *curr = head;
//         while(curr){
//             if(strcmp(curr->code, code) == 0){
//                 return true;
//             }
//             curr = curr->next;
//         }
//     }
//     return false;
// }

// void edit(char code[], int avail){
//     cake *temp;
//     if(search(code)){
//         temp->avail = avail;
//     }
// }

// void pushHead(char name[], double price, int avail){
//     cake *node = createCake(name, price, avail);
//     if(!head){
//         head = tail = node;
//     }else{
//         head->prev = node;
//         node->next = head;
//         node->prev = NULL;
//         head = node;
//     }
// }

// void printCake(){
//     // srand(time(0));
//     // int random = (rand());
//     int i = 1;
//     cake *curr = head;
//     if(!head){
//         puts("There is no cake available");
//     }
//     puts("No.   | Cake Code  | Cake Name   | Price   | Avaiable   ");
//     puts("--------------------------------------------------------");
//     while(curr){
//         // int random = (rand());
//         printf("%-5d | %s | %-8s | %-5.3lf | %-5d |\n", i, curr->code, curr->name, curr->price, curr->avail);
//         curr = curr->next;
//         i++;
//     }
// }

// int main(){
//     Menu();
//     switch (chs)
//     {
//     case 1:

//         break;
//     case 2:
//     char name[255];
//     double price;
//     int avail;
//     printf("Enter cake Name, Price, Avail: ");
//     scanf("%s %lf %d", &name, &price, &avail);
//     getchar();
//     pushHead(name, price, avail);
//     printCake();
//     break;
//     default:
//         break;
//     }
//     return 0;
// }