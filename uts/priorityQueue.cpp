#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct p
{
    char name[40];
    int age;
    int prior;
    p *next, *prev;
}*first, *last;

p *createNode(char name[], int age, int prior){
    p *node = (p *)calloc(1, sizeof(p));
    node->age = age;
    node->prior = prior;
    strcpy(node->name, name);
    return node;
}

p *insert(p *node){
    if(!first){
        first = last = node;
    }else{
        p *curr = first;
        while (curr && curr->prior <= node->prior) // selama dia masih ada data dan lebih kecil sama dengan
        {
            curr = curr->next; // iterasi
        }
        if(curr){
            p *before = curr->prev; // assign ke angka yg lbh kecil dari node (buat variable baru)
            before->next = node; // sambungin pointer angka lbh kecil ke node (kanannya)
            node->prev = before; // sambungin pointer node ke angka lbh kecil (kirinya)
            node->next = curr; // sambungin pointer node ke angka lebih besar (kanannya)
            curr->prev = node; // sambungin pointer angka lbh besar ke node (kirinya)
        }else{ // pushTail
            last->next = node;
            node->prev = last;
            last = node;
        }
    }
}

p *remove(){
    if(!first){
        return;
    }else if(first = last){
        free(first);
        first = last = NULL;
    }else{
        p *temp = first->next;
        first->next = temp->prev = NULL;
        free(first);
        first = temp;
    }
}

p *popAll(){
    while (first)
    {
        remove();
    }
    
}




int main(){
    return 0;
}