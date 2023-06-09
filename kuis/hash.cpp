#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#define size 10
struct data{
    char key[40];
    data *next, *prev;
}*head[size], *tail[size];

data *createNode(char key[]){
    data *node = (data *)calloc(1, sizeof(data));
    // pake calloc gausah nullin prev dan next
    strcpy(node->key, key);
    return node;
}

int hash(char key[]){
    int hashkey = strlen(key);
    int hkey = hashkey * hashkey;
    return hkey % size;
}

data *push(data *node){
    int hkey = hash(node->key);
    if(!head[hkey]){
        head[hkey] = tail[hkey] = node;
    }else{
        tail[hkey]->next = node;
        node->prev = tail[hkey];
        tail[hkey] = node;
    }
}

void print(){
    for(int i = 0; i < size; i++){
        data *curr = head[i];
        while (curr)
        {
            printf("%s\n", curr->key);
            curr = curr->next;
        }
    }
}
int main(){
    char rnd[40] = {0};
    printf("Enter Your Name: ");
    scanf("%s", &rnd);
    push(createNode(rnd));
    // push(createNode("Alexandra"));
    print();
    return 0;
}