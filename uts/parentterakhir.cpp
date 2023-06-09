#include<stdio.h>
#include<stdlib.h>

struct p
{
    int key;
    p *left, *right, *parent;
}*root;

p *createNode(int key){
    p *node = (p *)calloc(1, sizeof(p));
    node->key = key;
    return node;
}

p *insert(p *curr, int key){
    p *node = createNode(key);
    if(!curr){
        return node;
    }
    else if(key < curr->key){
        if(!curr->left){
            curr->left = node;
            curr->left->parent = curr;
        }else{
            insert(curr->left, key);
        }
    }else if(key > curr->key){
        if(!curr->right){
            curr->right = node;
            curr->right->parent = curr;
        }else{
            insert(curr->right, key);
        }
    }
    return curr;
}

void inOrder(p *root){
    if(root){
        inOrder(root->left);
        printf("Key: %d\n", root->key);
        inOrder(root->right);
    }
}

int main(){
    root = insert(root, 12);
    root = insert(root, 10);
    root = insert(root, 11);
    root = insert(root, 20);
    root = insert(root, 3);
    root = insert(root, 2);
    inOrder(root);
    return 0;
}