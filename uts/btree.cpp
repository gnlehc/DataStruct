#include<stdio.h>
#include<stdlib.h>

struct btree
{
    int value;
    btree *left, *right;
}*root;

btree *createNode(int value){
    btree *node = (btree *)calloc(1, sizeof(btree));
    node->value = value;
    return node;
}

btree *insert(btree *curr, int val){
    if(!curr){
        return createNode(val);
    }else if(val < curr->value){
        curr->left = insert(curr->left, val);
    }else if(val > curr->value){
        curr->right = insert(curr->right, val);
    }
    return curr;
}

void inOrder(btree *curr){
    if(curr){
        inOrder(curr->left);
        printf("%d\n", curr->value);
        inOrder(curr->right);
    }
}
btree *remove(btree *curr, int val){
    if(!curr){
        return curr;
    }
    else if(val < curr->value){
        curr->left = remove(curr->left, val);
    }
    else if(val > curr->value){
        curr->right = remove(curr->right, val);
    }
    else{
        if(!curr->left || !curr->right){
            btree *newNode = curr->left ? curr->left : curr->right;
            curr->left = curr->right = NULL;
            free(curr);
            curr = NULL;
            return newNode;
        }
    }
}


int main(){
    root = insert(root, 3);
    root = insert(root, 6);
    root = insert(root, 2);
    root = insert(root, 1);
    inOrder(root);
    return 0;
}