#include<stdio.h>
#include<stdlib.h>

struct node
{
    int key;
    node *left, *right;
};

node *newNode(int key){
    node *node = (struct node *)calloc(1, sizeof(node));
    node->key = key;
    return node;
}


void inOrder(node *node){
    if(node){
        inOrder(node->left);
        printf("%d\n", node->key);
        inOrder(node->right);
    }
}