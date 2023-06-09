#include<stdio.h>
#include<stdlib.h>

struct kiwi
{
    int prior;
    kiwi *next, *prev;
}*first, *last;

kiwi *createNode(int prior){
    kiwi *node = (kiwi *)calloc(1, sizeof(kiwi));
    node->prior = prior;
    return node;
}

kiwi *insert(int prior){
    kiwi *node = createNode(prior);
    if(!first){
        first = last = node;
    }
    else{
        kiwi *curr = first;
        if(curr->prior > node->prior){
            // pushHead
            curr->prev = node;
            node->next = curr;
            first = node;
        }
        while(curr->prior <= node->prior){
            curr = curr->next;
        }
        if(curr){
            kiwi *before = curr->prev;
            curr->prev = node;
            node->next = curr;
            before->next = node;
            node->prev = before;
        }else{
            last->next = node;
            node->prev = last;
            last = node;
        }
    }
}

void display(){
    kiwi *curr = first;
    while(curr){
        printf("Prior: %d\n", curr->prior);
        curr = curr->next;
    }
}

void removePrior(){
    if(!first){
        return;
    }else if(first == last){
        free(first);
        first = last = NULL;
    }else{
        kiwi *temp = first->next;
        temp->prev = first->next = NULL;
        first = temp;
    }
}

void removeALL(){
    while(first){
        removePrior();
    }
}

int main(){
    insert(3);
    display();
    return 0;
}