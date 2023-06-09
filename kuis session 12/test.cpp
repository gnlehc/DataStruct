#include <stdio.h>
#include <stdlib.h>
struct avl
{
    int key, height, bf;
    avl *left, *right;
};

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int getHeight(avl *curr)
{
    return curr ? curr->height : 0;
}

int setHeight(avl *root)
{
    return root ? (max(getHeight(root->left), getHeight(root->right))) + 1 : 0;
}

int setBF(avl *root)
{
    return root ? getHeight(root->left) - getHeight(root->right) : 0;
}

avl *update(avl *curr)
{
    if (!curr)
    {
        return 0;
    }

    curr->height = setHeight(curr);
    curr->bf = setBF(curr);
    return curr;
}

avl *createNode(int key)
{
    avl *node = (avl *)malloc(sizeof(avl));
    node->key = key;
    node->height = 1;
    node->bf = 0;
    node->left = node->right = NULL;
    return node;
}

avl *rightRotation(avl *curr)
{
    avl *pivot = curr->left;
    avl *leftChild = pivot->right;

    pivot->right = curr;
    curr->left = leftChild;
    curr = update(curr);
    pivot = update(pivot);
    return pivot;
}
avl *leftRotation(avl *curr)
{
    avl *pivot = curr->right;
    avl *rightChild = pivot->left;

    pivot->left = curr;
    curr->right = rightChild;
    return pivot;
}

avl *rotate(avl *curr)
{
    if (!curr)
    {
        return curr;
    }

    if (curr->bf > 1 && curr->left->bf >= 0)
    {
        return rightRotation(curr);
    }
    else if (curr->bf > 1 && curr->left->bf < 0)
    {
        curr->left = leftRotation(curr->left);
        return rightRotation(curr);
    }
    else if (curr->bf < -1 && curr->right->bf <= 0){
        return leftRotation(curr);
    }
    else if(curr->bf < -1 && curr->right->bf > 0){
        curr->right = rightRotation(curr->right);
        return leftRotation(curr);
    }
    return curr;
}

avl *insert(avl *root, int key)
{
    if (!root)
    {
        return createNode(key);
    }
    else if (key < root->key)
    {
        root->left = insert(root->left, key);
    }
    else if (key > root->key)
    {
        root->right = insert(root->right, key);
    }
    return rotate(update(root));
}

void inOrder(avl *curr){
    if(curr){
        inOrder(curr->left);
        printf("%d\n", curr->key);
        inOrder(curr->right);
    }
}

avl *deleteNode(avl *curr, int delVal){
    if(!curr){
        return curr;
    }
    else if(delVal < curr->key){
        curr->left = deleteNode(curr->left, delVal);
    }
    else if(delVal > curr->key){
        curr->right = deleteNode(curr->right, delVal);
    }
    else if(delVal == curr->key){
        if(!curr->left && !curr->right){
            free(curr);
            curr = NULL;
        }
    }
}

int main()
{

    avl *root = NULL;
    root = insert(root, 12);
    root = insert(root, 17);
    root = insert(root, 1);
    root = insert(root, 2);
    inOrder(root);
    return 0;
}