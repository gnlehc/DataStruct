#include<stdio.h>
#include<stdlib.h>
#include<string.h>
struct item
{
    int price;
    char name[25];
    item *left, *right;
    int height;
}*root;

item *createNode(int price, char name[]){
    item *newNode = (item *)calloc(1, sizeof(item));
    newNode->price = price;
    strcpy(newNode->name, name);
    newNode->height = 1;
    return newNode;
}

item *insert(item *current, item *newItem){
    if(!current){
        return newItem;
    }else if(current->price > newItem->price){
        current->left = insert(current->left, newItem);
    }else if(current->price < newItem->price){
        current->right = insert(current->right, newItem);
    }
    current->height = 1 + max(getHeight(current->left), getHeight(current->right));
    return current;
}

void inOrder(item *current){
    if(current){
        inOrder(current->left);
        printf("%d\n", current->price);
        inOrder(current->right);
    }
}

void preOrder(item *current){
    if(current){
        printf("%s %d : %d\n", current->name, current->price, current->height);
        preOrder(current->left);
        preOrder(current->right);
    }
}

int max(int a, int b){
    return (a > b) ? a : b;
}

int getHeight(item *current){
    return (current) ? current->height : 0;
}

int main(){
    root = insert(root, createNode(50, "Amanda"));
    root = insert(root, createNode(20, "test"));
    root = insert(root, createNode(10, "1"));
    root = insert(root, createNode(60, "2"));
    root = insert(root, createNode(30, "3"));
    preOrder(root);
}