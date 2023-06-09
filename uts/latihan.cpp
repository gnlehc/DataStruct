#include<stdio.h>
#include<stdlib.h>

struct pq
{
    int prior;
    pq *next, *prev;
}*head, *tail;

pq *createQueue(int prior){
    pq *node = (pq *)calloc(1, sizeof(pq));
    node->prior = prior;
    return node;
}

void insert(int prior){
    pq *node = createQueue(prior);
    if(!head){
        head = tail = node;
    }else{
        pq *curr = head;
        if(node->prior < curr->prior){
            curr->prev = node;
            node->next = curr;
            head = node;
        }
        while(curr && curr->prior <= node->prior){
            curr = curr->next;
        }

        if(curr){
            pq *before = curr->prev;
            before->next = node;
            node->prev = before;
            node->next = curr;
            curr->prev = node;
        }
    }
}

void removeQueue(pq *curr){
    if(!head){
        return;
    }else if(head = tail){
        free(head);
        head = tail = NULL;
    }else{
        pq *temp = head->next;
        head->next = temp->prev = NULL;
        head = temp;
    }
}
