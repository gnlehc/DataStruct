#include<stdio.h>
#include<stdlib.h>

struct pq
{
    int prior;
    pq *next, *prev;
}*head, *tail;

pq *createNode(int prior){
    pq *node = (pq *)calloc(1, sizeof(pq));
    node->prior = prior;
    return node;
}

void insert(pq *node){
    if(!head){
        head = tail = node;
    }else{
        
    }
}

int main(){
    return 0;
}