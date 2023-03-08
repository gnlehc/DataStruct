#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#define SIZE 10
// hash table chaining
struct item{
    char name[50];
    int price;
    item *next;
}*table[SIZE];

item *createItem(char name[], int price){
    item *newItem = (item *)malloc(sizeof(item));
    strcpy(newItem->name, name);
    newItem->price = price;
    newItem->next = NULL;
    return newItem;
}

// Hash Function
int hash(char name[]){
    return (name[0] - 65) % SIZE;
}

void insert(char name[], int price){
    int key = hash(name);
    int pos = key;

    do{
        // data di index key kosong
        if(!table[pos]){
            table[pos] = createItem(name,price);
            return ;
        }
        // data di index key tidak kosong
        else{
            pos = (pos+1) % SIZE;
        }
    }while(key != pos);
}

void view(){
    for(int i = 0 ; i < SIZE ; i++){
        if(table[i]){
            printf("%d | %s  - %d\n", i, table[i]->name, table[i]->price);
        }else{
            printf("%d | ~\n", i);
        }
    }
    
}

item *search(char name[]){
    

}

void pop(char name[]){
    int key = hash(name);

    // apabila ada data di depan ( pop head )
    if(table[key]){
        if(strcmp(name, table[key]->name) == 0){
            // pop head
            item *temp = table[key];
            table[key] = table[key]->next;
            free(temp);
        }
    // data ada di tengah atau akhir
    else{
        item *current = table[key];

        // selama next node masih ada dan tidak sama dengan yang kita cari, NEXT
        while(current->next && strcmp(current->next->name, name) != 0){
            current = current->next;
        }
        item *temp = current->next;
        current->next = temp->next;
        free(temp);
    }
    }
}
int main(){
    insert("Ayam", 12500);
    insert("Air", 13000);
    insert("Boba", 13000);
    view();
}