#include <stdio.h>
#include <stdlib.h>
#include <string.h>


struct data{
    int umur;
    struct data *next;
}*head = NULL, *tail = NULL;

struct data *newNode(int umur){
    // 1. reserve
    struct data *node = (struct data*) malloc(sizeof(struct data));
    // 2. inisialisasi
    // strcpy(node->nama, nama);
    node->umur = umur;
    node->next = NULL;
    return node;
}

// 3. connect
void pushHead(int umur){
    struct data *node = newNode(umur);

    if(head == NULL){
        head = tail = node;
    }else{
        node->next = head;
        head = node; 
    }
}

void pushTail(int umur){
    struct data *node = newNode(umur);
    if(head == NULL){
        head = tail = node;
    }else{
        tail->next = node;
        tail = node;
    }
}

void printData(){
    struct data *curr = head;

    while(curr){ // curr != NULL
        printf("%d\n", curr->umur);
        curr = curr->next;
    }
}

// delete
void popHead(){

    if(head){
        struct data *curr = head;

        if(head == tail){
            head == tail == NULL;
        }else{
            head = head->next;
            free(curr);
        }
    }
}

void popTail(){
   if(!head){
    return;
   }
   else if(head == tail){
    free(head);
    head = tail = NULL;
   }else{
    struct data *curr = head;
    while(curr->next != tail){
        curr = curr->next;
    }
    curr->next = NULL;
    free(tail);
    tail = curr;
   }
}

void popNum(int x){
    struct data *curr = head;
    while(curr->next->umur != x ){
        curr = curr->next;
    }
    struct data *del = curr->next;
    curr->next = del->next; // putusin tangan kasi ke tangan
    free(del);
}

// single linked list
// struct tnode{
//     int value;
//     struct tnode *next;
// };
// struct tnode *head = 0; // first element in the linked list


// tnode *createNode(int value){
//     tnode *newnode = (tnode *)malloc(sizeof(tnode));
//     newnode->value = value;
//     newnode->next = head;
//     head = newnode;
//     return newnode;
// }

int main(){
    // dynamic memory allocation
    int *px = (int *)malloc(sizeof(int)); // casting sesuai dengan tipe data
    char *pc = (char *)malloc(sizeof(char));
    *px = 205;
    *pc = 'A';
    printf("%d %c\n", *px, *pc);
    free(px);
    free(pc);


    // pushHead("Andi", 25);
    // pushHead("Itol", 8);
    // pushTail("Chelsea", 18);

    pushHead(15);
    pushHead(30);
    pushHead(28);
    pushHead(150);
    pushHead(23);
    pushHead(17);
    pushHead(8);
    pushHead(71);
    pushHead(90);
    pushHead(89);
    printData();
    printf("==========\n");
    popHead();
    popTail();
    popHead();
    printData();
    printf("==========\n");
    pushTail(19);
    pushTail(7);
    pushTail(5);
    printData();
    printf("==========\n");
    popTail();
    popHead();
    popHead();
    printData();
    printf("==========\n");

    return 0;
}