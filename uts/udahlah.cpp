#include<stdio.h>
#include<stdlib.h>

struct bst
{
    int key;
    bst *left, *right;
}*root;

bst *createNode(int key){
    bst *node = (bst *)calloc(1, sizeof(bst));
    node->key = key;
    return node;
}

bst *insert(bst *curr, int key){
    if(!curr){
        return createNode(key);
    }else if(key < curr->key){
        curr->left = insert(curr->left, key);
    }else if(key > curr->key){
        curr->right = insert(curr->right, key);
    }
    return curr;
}

void inOrder(bst *curr){
    if(curr){
        inOrder(curr->left);
        printf("%d\n", curr->key);
        inOrder(curr->right);
    }
}

int treeHeight(bst *root){
    if(!root){
        return 0;
    }
    int lh = treeHeight(root->left);
    int rh = treeHeight(root->right);
    if(lh >= rh){
        return lh + 1;
    }else{
        return rh + 1;
    }
}

int totalNodes(bst *root){
    if(!root){
        return 0;
    }
    int l = totalNodes(root->left);
    int r = totalNodes(root->right);
    return l + r + 1;
}

int maxValue(bst *root){
    if(root->right){
        maxValue(root->right);
    }else{
        return root->key;
    }
}

int minValue(bst *root){
    if(root->left){
        minValue(root->left);
    }else{
        return root->key;
    }
}

bst *predecessor(bst *curr){
    curr = curr->left;
    if(curr->right){
        curr = curr->right;
    }
    return curr;
}

bst *removeNode(bst *root, int key){
    if(!root){
        return NULL;
    }else if(key < root->key){
        root->left = removeNode(root->left, key);
    }else if(key > root->key){
        root->right = removeNode(root->right, key);
    }else{
        if(!root->left && !root->right){
            free(root);
            root = NULL;
        }
        else if(!root->left && root->right){
            bst *temp = root->right;
            free(root);
            return temp;
        }else if(root->left && !root->right){
            bst *temp = root->left;
            free(root);
            return temp;
        }else{
            bst *pre = predecessor(root);
            root->key = pre->key;
            root->left = removeNode(root->left, pre->key);
        }
    }
    return root;
}

int main(){
    root = insert(root, 19);
    root = insert(root, 9);
    root = insert(root, 20);
    root = insert(root, 5);
    root = insert(root, 2);
    root = insert(root, 4);
    root = insert(root, 17);
    root = removeNode(root, 4);
    inOrder(root);
    printf("Tree Height: %d\n", treeHeight(root));
    printf("Total Nodes: %d\n", totalNodes(root));
    printf("Maximum Value: %d\n", maxValue(root));
    printf("Minimum Value: %d\n", minValue(root));
    return 0;
}