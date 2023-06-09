#include <stdio.h>
#include <stdlib.h>

struct bst
{
    int key;
    bst *left, *right;
} *root;

struct pq
{
    int prior;
    pq *next, *prev;
} *first, *last;

bst *createTree(int key)
{
    bst *node = (bst *)calloc(1, sizeof(bst));
    node->key = key;
    return node;
}

pq *createQueue(int prior)
{
    pq *node = (pq *)calloc(1, sizeof(pq));
    node->prior = prior;
    return node;
}

// BST
// insert
bst *insert(bst *node, int key)
{
    if (!node)
    {
        return createTree(key);
    }
    else if (key < node->key)
    {
        node->left = insert(node->left, key);
    }
    else if (key > node->key)
    {
        node->right = insert(node->right, key);
    }
    return node;
}
// predecessor
bst *predecessor(bst *curr)
{
    curr = curr->left;
    while (curr)
    {
        curr = curr->right;
    }
    return curr;
}
// delete
bst *removeNode(bst *root, int key)
{
    if (!root)
        return;
    else if (key < root->key)
    {
        root->left = removeNode(root->left, key);
    }
    else if (key > root->key)
    {
        root->right = removeNode(root->right, key);
    }
    else
    {
        if (!root->left && !root->right)
        {
            free(root);
        }
        else if (!root->left && root->right)
        {
            bst *temp = root->right;
        }
        else if (root->left && !root->right)
        {
            bst *temp = root->left;
        }
        else
        {
            bst *pre = predecessor(root);
            root->key = pre->key;
            root->left = removeNode(root->left, pre->key);
        }
    }
}
// search
bst *Search(bst *curr, int key)
{
    if (curr)
    {
        if (curr->key == key)
        {
            printf("%d Found\n", curr->key);
        }
        else if (key < curr->key)
        {
            curr->left = Search(curr->left, key);
        }
        else if (key > curr->key)
        {
            curr->right = Search(curr->right, key);
        }
    }
}

pq *insert(pq *node)
{
    if (!first)
    {
        first = last = node;
    }
    else
    {
        pq *curr = first;
        if (curr->prior > node->prior)
        {
            curr->prev = node;
            node->next = curr;
            first = node;
        }
        while (curr && curr->prior <= node->prior)
        {
            curr = curr->next;
        }

        if (curr)
        {
            pq *before = curr->prev;
            node->next = curr;
            curr->prev = node;
            node->prev = before;
            before->next = node;
        }
        else
        {
            last->next = node;
            node->prev = last;
            last = node;
        }
    }
}

void removeQueue(){
    if(!first){
        return;
    }else if(first = last){
        first = last = NULL;
    }else{
        pq *curr = first->next;
        curr->prev = first->next = NULL;
        first = curr;
    }
}

int main()
{
    return 0;
}