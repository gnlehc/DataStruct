#include<stdio.h>
#include<string.h>
#include<stdlib.h>

#define SIZE 20

struct pica
{
    char id[7];
    char name[20];
    char type[20];
    double price;
    pica *next, *prev;
}*head[SIZE], *tail[SIZE];

pica *createPica(char name[], char type[], double price){
    pica *node = (pica *)malloc(sizeof(pica));
    strcpy(node->name, name);
    strcpy(node->type, type);
    node->price = price;

    char getID[7];
    sprintf(getID, "%c%c%d%d%d", type[0], type[1], rand() % 10, rand() % 10, rand() % 10);
    strcpy(node->id, getID);
    node->next = NULL;
    node->prev = NULL;
    return node;
}

int hash(char id[]){
    int hashkey = 0;
    for(int i = 0; i < 5; i++){
        hashkey += id[i];
    }
    return hashkey % SIZE;
}


void insert(pica *node){
    int i = hash(node->id);
    if(!head[i]){
        head[i] = tail[i] = node;
    }
    else{
        pica *curr = head[i];
        while(curr->next){
            curr = curr->next;
        }
        curr->next = node;
    }
}

void NODATA(int simpen){
    if(simpen == 0){
        printf("NO DATA");
        return;
    }
}

void print(){
    int simpen = 0;
    for(int i = 0; i < SIZE; i++){
        if(!head[i]){
            simpen += 0;
        }
        pica *curr = head[i];
        while(curr){
            printf("Id: %s\n", curr->id);
            printf("Name: %s\n", curr->name);
            printf("Type: %s\n", curr->type);
            printf("Price: %.0lf\n", curr->price);
            curr = curr->next;
            simpen += 1;
            return;
        }
    }
    NODATA(simpen);
}

void Remove(char id[]){
    int key = hash(id);
    if(!head[key]){
        puts("There is no data to remove");
    }

    if(head[key] == tail[key] && strcmp(head[key]->id, id) == 0){
        free(head[key]);
        head[key] = NULL;
        tail[key] = NULL;
    }else if(strcmp(head[key]->id, id) == 0){
        pica *temp = head[key];
        head[key] = head[key]->next;
        head[key]->prev = NULL;
        temp->next = NULL;
        free(temp);
        temp = NULL;
        printf("Success to delete\n");
        return;

    }else if(strcmp(tail[key]->id, id) == 0){
        pica *temp = tail[key];
        tail[key] = tail[key]->prev;
        tail[key]->next = NULL;
        temp->prev = NULL;
        free(temp);
        temp = NULL;
        printf("Success to delete\n");
        return;
    }
    else{
        pica *curr = head[key]->next;
        // iterasi buat cari data nya
        while(curr && strcmp(curr->id, id) != 0){
            curr = curr->next;
        }

        if(!curr){
            puts("Id not match anything in data list");
        }
        else{
            pica *after = curr->next;
            pica *before = curr->prev;

            after->prev = before;
            before->next = after;
            curr->next = NULL;
            curr->prev = NULL;
            free(curr);
            curr = NULL;
            puts("Successfully deleted");
            return;
        }
    }
}



int main(){

}