#include<stdio.h>
#include<stdlib.h>

struct data
{
    int key;
    data *left, *right;
}*root;

data *createNode(int key){
    data *node = (data *)calloc(1, sizeof(data));
    node->key = key;
    return node;
}

data *insert(data *curr, int key){
    if(!curr){
        return createNode(key);
    }else if(key < curr->key){
        curr->left = insert(curr->left, key);
    }else if(key > curr->key){
        curr->right = insert(curr->right, key);
    }
    return curr;
}

data *successor(data *curr){
    curr = curr->right;
    while (curr->left)
    {
        curr = curr->left;
    }
    return curr;
}

data *remove(data *curr, int key){
    if(!curr){
        return curr;
    }else if(key < curr->key){
        curr->left = remove(curr->left, key);
    }else if(key > curr->key){
        curr->right = remove(curr->right, key);
    }else{
        if(!curr->left && !curr->right){
            free(curr);
            curr = NULL;
        }else if(!curr->left || !curr->right){
            data *temp;
            if(curr->left){
                temp = curr->left;
            }else{
                temp = curr->right;
            }
            free(curr);
            curr = temp;
        }else{
            data *suc = successor(curr);
            curr->key = suc->key;
            curr->right = remove(curr->right, suc->key);
        }
    }
    return curr;
}

void inOrder(data *curr){
    if(curr){
        inOrder(curr->left);
        printf("%d\n", curr->key);
        inOrder(curr->right);
    }
}

int main(){
    root = insert(root, 12);
    root = insert(root, 1);
    root = insert(root, 5);
    root = insert(root, 9);
    root = insert(root, 3);
    root = remove(root, 3);
    inOrder(root);
    return 0;
}