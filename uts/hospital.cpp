#include <stdio.h>
#include <string.h>
#include <stdlib.h>
struct data
{
    char name[40];
    char desc[40];
    char code[40];
    int age;
    int prior;
    data *next, *prev;
} *head, *tail;

data *createNode(char name[], int age, char desc[], char code[])
{
    data *newNode = (data *)calloc(1, sizeof(data));
    newNode->age = age;
    strcpy(newNode->name, name);
    strcpy(newNode->desc, desc);
    strcpy(newNode->code, code);
    int p = 0;
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
    newNode->prior = p;
    return newNode;
}

// void pushHead(data *node)
// {
//     if (!head)
//     {
//         head = tail = node;
//     }
//     else
//     {
//         head->prev = node;
//         node->next = head;
//         head = node;
//     }
// }

// void pushTail(data *node)
// {
//     if (!head)
//     {
//         head = tail = node;
//     }
//     else
//     {
//         tail->next = node;
//         node->prev = tail;
//         tail = node;
//     }
// }

// void pushMid(data *node)
// {
//     if (!head)
//     {
//         pushHead(node);
//     }
//     else if (node->prior < tail->prior)
//     {
//         pushTail(node);
//     }
//     else
//     {
//         data *curr = head;
//         data *temp = node;
//         while (curr && curr->prior <= node->prior)
//         {
//             curr = curr->next;
//         }

//         temp->prev = curr;
//         temp->next = curr->next;
//         curr->next->prev = temp;
//         curr->next = temp;
//     }
// }

void pushPriority(char name[], int age, char desc[], char code[]){
    data *node = createNode(name, age, desc, code);
    if(!head){
        head = tail = node;
    }else{
        data *curr = head;

        if(curr->prior > node->prior){
            // ketika data harus di depannya
            // 2 3
            // mau insert 1, maka bandingkan dengan head
            // pushhead
            curr->prev = node;
            node->next = curr;
            head = node;
            return;
        }

        while(curr && curr->prior <= node->prior){
            // 1 1 2 2 3
            // mau insert 2, maka harus diiterasi sampai value 3
            curr = curr->next;
        }
        
        if(curr){
            // curr adalah value 3, maka harus dimasukkin 2 pada value sebelumnya
            data *before = curr->prev;
            before->next = node;
            node->prev = before;
            node->next = curr;
            curr->prev = node;
        }else{
            // contoh situasi
            // 1 1 2 2
            // mau masukin 3, dimana curr adalah value NULL, sehingga dia
            // posisinya tail->next
            tail->next = node;
            node->prev = tail;
            tail = node;
        }
    }
}

void removeQueue(){
    if(!head){
        return;
    }else if(head = tail){
        head = tail = NULL;
        free(head);
        puts("Next Queue Please!");
    }else{
        data *temp = head->next;
        head->next = temp->prev = NULL;
        head = temp;
        puts("Next Queue Please!");
    }
}

void printQueue()
{
    data *curr;
    curr = head;
    puts("Prior List");
    while (curr)
    {
        puts("===============================");
        printf("# Name: %-10s\n", curr->name);
        printf("# Age: %-10d\n", curr->age);
        printf("# Description: %-10s\n", curr->desc);
        printf("# Code: %-10s\n", curr->code);
        printf("# Prior: %-10d\n", curr->prior);
        curr = curr->next;
        puts("===============================");
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
        pushPriority(name, age, syntp, code);
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
        removeQueue();
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