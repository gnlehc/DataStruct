#include <stdio.h>
#include <malloc.h>
#include <string.h>

struct item{
    char name[50];
    int qty;
    struct item *next;
}*head, *tail;

item *createItem(char name[], int qty){
    // alokasi
    item *newItem = (item *)malloc(sizeof(item));
    // assign
    strcpy(newItem->name, name);
    newItem->qty = qty;
    newItem->next = NULL;
    // return
    return newItem;
}

void pushHead(char name[], int qty){
    // saat single linked list kosong
    if(!head){
        head = tail = createItem(name,qty);
    }else{
        item *newItem = createItem(name,qty);
        newItem->next = head;
        head = newItem;
    }
}



void view(){
    item *curr = head;
    while(curr){
        printf("%s - %d ->", curr->name, curr->qty);
        curr = curr->next;
    }
}

void popHead(){
    if(head){
        if(head == tail){
            free(head);
            head = tail = NULL;
        }else{
            item *temp = head;
            head = head->next;
            free(temp);
        }
    }else{
        return;
    }
}

void popTail(){
    if(head){
        if(head==tail){
            free(tail);
            head = tail = NULL;
        }else{
            item *curr = head;
            while(curr->next != tail){
                curr  = curr->next;
            }
            item *temp = tail;
            tail = curr;
            curr->next = NULL;
            free(temp);
        }
    }else{
        return;
    }
}

void popMid(char name[]){
    if(head){
        // apakah namanya sama kayak di head
        if(strcmp(name, head->name)==0){
            popHead();
        }else if(strcmp(name, tail->name) == 0){
            popTail();
        }else{
            item *curr = head;
            item *temp;
            while(strcmp(name, curr->name) != 0 && curr->next){
                temp = curr;
                curr = curr->next;
            }

            if(strcmp(curr->name, name) == 0){
                // validasi dia ada yang sama gak
                temp->next = curr->next;
                free(curr);
            }
            
           
        }
    }
}

void pushTail(char name[], int qty){
    item *temp = createItem(name, qty);

    if(!head){
        head = tail = temp;
    }else{
        tail->next = temp;
        tail = temp;
    }
}

void pushMid(char name[], int qty){
    if(!head){
        head = tail = createItem(name, qty);
    }
    else{
        // newItem valuenya lebih kecil dari headnya
        // key = quantity
        if(head->qty > qty){
            pushHead(name, qty);
        }else if(tail->qty < qty){
            pushTail(name, qty);
        }else{
            item *curr = head;
            item *temp = createItem(name, qty);
            while(qty > curr->next->qty){
                curr = curr->next;
            }
            temp->next = curr->next;
            curr->next = temp;
        }
    }
}

item *search(char name[]){
    item *curr = head;
    while(curr && strcmp(curr->name, name) != 0){
        curr = curr->next;
    }
    return curr;
}

int main(){
    pushHead("hehe", 10);
    pushHead("hehe", 9);
    pushTail("C", 13);
    pushMid("D", 11);
    popHead();
  

    if(search("haha")){
        puts("Found!");
    }else{
        puts("Not Found!");
    }


 
    view();

    return 0;
}