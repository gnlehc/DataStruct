#include<stdio.h>
#include<stdlib.h>

struct data
{
    int key;
    data *left, *right;
}*head, *tail;

data *createNode(int key){
    data *node = (data *)calloc(1, sizeof(data));
    node->key = key;
    return node;
}

data *insert(data *node, int key){
    if(!head){
        head = tail = node;
    }else if(key < node->key){
        node->left = insert(node->left, key);
    }else if(key > node->key){
        node->right = insert(node->right, key);
    }
    return node;
}

int main(){
    return 0;
}