#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <malloc.h>
#define SIZE 26
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


    // apabila table index di key kosong
    if(table[key] == NULL){
        table[key] = createItem(name, price);
    }
    //apabila table index di key ada data
    else{
        item *current = table[key];

        // cari tail
        while(current->next){
            current = current->next;
        }
        // assign di nextnya
        current->next = createItem(name, price);
    }
}

void view(){
    for(int i = 0 ; i < SIZE ; i++){
        if(table[i]){
            printf("%d | (%s - %d)", i, table[i]->name, table[i]->price);
            item *current = table[i]->next;

            while(current){
                printf("->(%s - %d)", current->name, current->price);
                current = current->next;
            }
            puts("");
        }else{
            printf("%d | ~\n", i);
        }
    }
}

item *search(char name[]){
    int key = hash(name);

    // kalo misalnya ada data
    if(table[key]){
        item *current = table[key];
        while(current && strcmp(current->name, name) != 0){
            current = current->next;
        }
         return current;
    }
    return NULL; 
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
    insert("Ayang", 12500);
    insert("A", 12500);
    insert("Mouse", 12500);
    view();

    item *searchedItem = search("Ayam");
    if(search){
        puts("Found!");
        printf("%s\n", searchedItem->name);
    }else{
        puts("Not found!");
    }

    pop("Ayam");

    pop("A");
    view();


}