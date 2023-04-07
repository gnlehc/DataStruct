#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct data
{
    int value;
    char name[255];
    data *left = NULL, *right = NULL;
}*root;

data *createNode(int value, char name[]) {
    data *temp = (data *)malloc(sizeof(data));
    // data *temp = (data *)calloc(1, sizeof(data)); // gausah nullin left right
    temp->value = value;
    temp->left = NULL;
    temp->right = NULL;
    strcpy(temp->name, name);
    return temp;
}
// insert
data *pushNode(data *curr, int value, char name[]) {
    if(!curr) {
        return(createNode(value, name));
    }
    else if(value < curr->value) { // if value in data are lesser than our current inserted value
        // recursive
        curr->left = pushNode(curr->left, value, name); // push current value to left
    }else if(value > curr->value) { // if value in data are greater than our current inserted value
        curr->right = pushNode(curr->right, value, name); // push current value to the right
    }
    return curr;
}

data *updateAtributte( data *curr, int key, char newName[]) {
    if(curr == NULL) {
        return curr;
    }else if(key < curr->value) {
        curr->left = updateAtributte(curr->left, key, newName);
    }else if(key > curr->value) {
        curr->right = updateAtributte(curr->right, key, newName);
    }else{
        strcpy(curr->name, newName);
        return curr;
    }
}

void inOrder(data *curr) {
    if(curr != NULL) {
        inOrder(curr->left); // cek paling kiri
        printf("%d %s\n", curr->value, curr->name); // print kiri
        inOrder(curr->right); // cek yang kanannya
    }
}

void postOrder(data *curr) {
    if(curr != NULL){
        postOrder(curr->left); // cek ke paling kiri
        postOrder(curr->right); // terus cek kanannya tiap node
        printf("%d %s\n", curr->value, curr->name); // print valuenya
    }
}
void preOrder(data *curr) {
    if(curr != NULL) {
        // print root dluan
        printf("%d %s\n", curr->value, curr->name);
        preOrder(curr->left); // print yg kiri
        preOrder(curr->right); // print yg kanan
    }
}


int main(){
    root = pushNode(root, 5, "amanda");
    pushNode(root, 3, "michelle");
    pushNode(root, 2, "verrel");
    pushNode(root, 4, "chelsea");
    pushNode(root, 6, "yoko");
    pushNode(root, 12, "test");
    // inOrder(root);
    // postOrder(root);
    preOrder(root);
    // updateAtributte(root, 6, "vanessa");
    // inOrder(root);
}