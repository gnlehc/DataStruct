#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct Food{
    char name[255];
    int price;

    Food *next;
    Food *prev;
}*head, *tail;

Food * createNode(char name[], int price){
    Food *temp = (Food *)malloc(sizeof(Food));
    temp->price = price;
    strcpy(temp->name, name);
    temp->next = NULL;
    temp->prev = NULL;

    return temp;
}

void pushHead(char name[], int price){
    Food *node = createNode(name, price);

    if(!head){
        head = tail = node;
    }else{
        node->next = head;
        head->prev = node;
        node->prev = NULL;
        head = node;
    }
}

void pushTail(char name[], int price){
    Food *node = createNode(name, price);

    if(!head){
        head = tail = node;
    }else{
        node->prev = tail;
        tail->next = node;
        node->next = NULL;
        tail = node;
    }
}   

void pushMid(char name[], int price){
    Food *node = createNode(name, price);

    if(head == NULL){
        head = tail = node;
    }else{
        if(strcmp(node->name, head->name) < 0){
            pushHead(name, price);
        }else if(strcmp(node->name, tail->name) > 0){
            pushTail(name,price);
        }else{
            Food *curr = head;
            while(curr != tail && strcmp(node->name, curr->name) > 0){
                curr = curr->next;
            }

            Food *before = curr->prev;
            before->next = node;
            node->prev = before;
            node->next = curr;
            curr->prev = node;
        }
    }
}

void popHead(){
    if(head == tail){
        free(head);
        head = tail = NULL;
    }else{
        Food *node = head;
        head = node->next;
        head->prev = NULL;
        free(node);
    }
}

void popTail(){
    if(head == tail){
        free(head);
        head = tail = NULL;
    }else{
        Food *node = tail;
        tail = node->prev;
        tail->next = NULL;
        free(node);
    }
}

bool search(char name[]){
    if(head == NULL){
        return false;
    }else if(strcmp(head->name, name) == 0){
        return true;
    }else if(strcmp(tail->name, name) == 0){
        return true;
    }else{
        Food *curr = head;
        while(curr){
            if(strcmp(curr->name,name) == 0){
                return true;
            }
            curr = curr->next;
        }
    }
    return false;
}

void popMid(char name[]){
    if(head==NULL){
        return;
    }else if(strcmp(head->name, name) == 0){
        popHead();
    }else if(strcmp(tail->name, name) == 0){
        popTail();
    }else{
        Food *curr = head;

        if(search(name) == true){
            while(curr){
                if(strcmp(curr->name, name) == 0){
                    break;
                }
                curr = curr->next;
            }

            Food *before = curr->prev;
            Food *after = curr->next;
            before->next = after;
            after ->prev = before;
            free(curr);
        }
    }
}

void Enqueue(char name[], int price){
    pushTail(name, price);
}

void Dequeue(){
    popHead();
}

void printAllBackward(){
    Food *curr = tail;
    while(curr){
        printf("%s %d\n", curr->name, curr->price);
        curr = curr->prev;
    }
}
void printAll(){
    Food *curr = head;
    while(curr){
        printf("%s %d\n", curr->name, curr->price);
        curr = curr->next;
    }
}

int main(){
    pushHead("Sate", 150);
    pushHead("Sate", 150);
    pushHead("Sate", 150);
    pushHead("Sate", 150);
    pushTail("Ss", 190);
    printAll();

    return 0;
}