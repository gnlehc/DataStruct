#include <stdio.h>
#include <stdlib.h>

struct avl
{
    int key, height, bf;
    avl *left, *right;
};

avl *createNode(int key)
{
    avl *node = (avl *)malloc(sizeof(avl));
    node->key = key;
    node->height = 1;
    node->bf = 0;
    node->left = node->right = NULL;
    return node;
}

int max(int a, int b)
{
    return (a > b) ? a : b;
}
int getHeight(avl *curr)
{
    return curr ? curr->height : 0;
}

int setHeight(avl *curr)
{
    return curr ? max(getHeight(curr->left), getHeight(curr->right)) + 1 : 0;
}

int setBF(avl *curr)
{
    return curr ? (getHeight(curr->left) - getHeight(curr->right)) : 0;
}

avl *update(avl *curr)
{
    if (!curr)
    {
        return 0;
    }

    curr->height = setHeight(curr);
    curr->bf = setBF(curr);
}

avl *rightRotate(avl *curr)
{
    avl *pivot = curr->left;
    avl *rightChild = pivot->right;
    pivot->right = curr;
    curr->left = rightChild;
    curr = update(curr);
    pivot = update(pivot);
    return pivot;
}

avl *leftRotate(avl *curr)
{
    avl *pivot = curr->right;
    avl *leftChild = pivot->left;

    pivot->left = curr;
    curr->right = leftChild;
    curr = update(curr);
    pivot = update(pivot);
    return pivot;
}

avl *rotate(avl *root)
{
    if (!root)
    {
        return root;
    }
    else if (root->bf > 1 && root->left->bf >= 0)
    {
        return rightRotate(root);
    }
    else if (root->bf < -1 && root->right->bf <= 0)
    {
        return leftRotate(root);
    }
    else if (root->bf > 1 && root->left->bf < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }
    else if (root->bf < -1 && root->right->bf > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }
    return root;
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

avl *delNode(avl *root, int val)
{
    if (!root)
    {
        return NULL;
    }
    else if (val < root->key)
    {
        root->left = delNode(root->left, val);
    }
    else if (val > root->key)
    {
        root->right = delNode(root->right, val);
    }
    else if (val == root->key)
    {
        if (!root->right && !root->left)
        {
            free(root);
            root = NULL;
        }
        else if (!root->left && root->right)
        {
            avl *temp = root->right;
            free(root);
            root = temp;
        }
        else if (root->left && !root->right)
        {
            avl *temp = root->left;
            free(root);
            root = temp;
        }
        else if (root->left && root->right)
        {
            avl *curr = root->left;
            while (curr->right)
            {
                curr = curr->right;
            }
            root->key = curr->key;
            root->left = delNode(root->left, curr->key);
        }
    }
    return rotate(root);
}
void inOrder(avl *curr)
{
    if (curr)
    {
        inOrder(curr->left);
        printf("%d\n", curr->key);
        inOrder(curr->right);
    }
}

int main()
{
    avl *root = NULL;
    root = insert(root, 12);
    root = insert(root, 2);
    root = insert(root, 1);
    root = delNode(root, 2);
    inOrder(root);
    return 0;
}