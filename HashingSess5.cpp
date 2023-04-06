#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 5

struct item{
    char name[50];
    item *next;
}*table[SIZE];

item *createItem(char name[]){
    item *newNode = (item *)malloc(sizeof(item));
    strcpy(newNode->name, name);
    return newNode;
}

int hash(char name[]){
    int len = strlen(name);
    return len % SIZE;
}

void insert(char name[]){
    int key = hash(name);
    if(table[key] == NULL){
        table[key] = createItem(name);
    }
    else{
        item *current = table[key];

        // cari tail
        while(current->next){
            current = current->next;
        }
        // assign di nextnya
        current->next = createItem(name);
    }
}

void view(){
    for(int i = 0 ; i < SIZE ; i++){
        if(table[i]){
            printf("%d | %s", i, table[i]->name);
            item *current = table[i]->next;

            while(current){
                printf("->%s ", current->name);
                current = current->next;
            }
            puts("");
        }else{
            printf("%d | ~\n", i);
        }
    }
}
int main(){
    insert("Hemnes");
    insert("Sprutt");
    insert("Hodde");
    insert("Dvala");
    insert("Godmorgon");
    insert("Aina");
    insert("Sannolikt");
    view();
    return 0;
}