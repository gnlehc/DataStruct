#include<stdio.h>
#include<stdlib.h>


struct bst
{
    int key;
    bst *left, *right;
}*root;

bst *createTree(int key){
    bst *node = (bst *)calloc(1, sizeof(bst));
    node->key = key;
    return node;
}

bst *insert(bst *curr, int key){
    if(!curr){
        return createTree(key);
    }else if(key < curr->key){
        curr->left = insert(curr->left, key);
    }else if(key > curr->key){
        curr->right = insert(curr->right, key);
    }
    return curr;
}

bst *predecessor(bst *curr){
    curr = curr->left;
    while (curr->right)
    {
        curr = curr->right;
    }
    return curr;
}

bst *removeNode(bst *curr, int key){
    if(!curr){
        return curr;
    }else if(key < curr->key){
        curr->left = insert(curr->left, key);
    }else if(key > curr->key){
        curr->right = insert(curr->right, key);
    }else{
        if(!curr->left && !curr->right){
            free(curr);
        }
        else if(!curr->left && curr->right){
            bst *temp = curr->right;
            free(curr);
            return temp;
        }else if(!curr->right && curr->left){
            bst *temp = curr->left;
            free(curr);
            return temp;
        }else{
            bst *pre = predecessor(curr);
            curr->key = pre->key;
            curr->left = removeNode(curr->left, pre->key);
        }
    }
}