// BINARY SEARCH TREE
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct node
{
    int val;
    node *left, *right;
} *root;

node *createNode(int val)
{
    node *newNode = (node *)calloc(1, sizeof(node)); // gausah NULL in left dan right
    // (node *)malloc(sizeof(node)); harus NULL in left dan right
    newNode->left = NULL;
    newNode->right = NULL;
    newNode->val = val;
    return newNode;
}

node *insert(node *curr, int val)
{
    // if there is no data
    if (!curr)
    {
        return createNode(val); // create and add the value
    }
    // inserted value are lesser than current value
    else if (curr->val > val)
    {
        curr->left = insert(curr->left, val);
    }
    // inserted value are greater than current value
    else if (curr->val < val)
    {
        curr->right = insert(curr->right, val);
    }

    return curr; // butuh return value yang sebelumnya
    // kalo dalam list ad 12 mau masukin 5, abis insert 5 harus return 12 lagi
}

void inOrder(node *curr)
{
    if (curr)
    {
        inOrder(curr->left);       // cek kiri
        printf("%d\n", curr->val); // print
        inOrder(curr->right);      // cek kanan
    }
}

void preOrder(node *curr)
{
    if (curr)
    {
        printf("%d\n", curr->val);
        preOrder(curr->left);
        preOrder(curr->right);
    }
}

void postOrder(node *curr)
{
    if (curr)
    {
        postOrder(curr->left);
        postOrder(curr->right);
        printf("%d\n", curr->val);
    }
}

node *search(node *current, int val)
{
    if (current)
    {
        if (current->val == val)
        {
            return current;
        }
        else if (val < current->val)
        {
            return search(current->left, val);
        }
        else if (val > current->val)
        {
            return search(current->right, val);
        }
    }
    return NULL;
}
// left most tree right most child
node *predecessor(node *current)
{
    current = current->left;
    while (current->right)
    {
        current = current->right;
    }

    return current;
}
// right most tree left most child
node *successor(node *current)
{
    current = current->right;
    while (current->left)
    {
        current = current->left;
    }

    return current;
}

node *pop(node *current, int val)
{
    if (!current)
        return NULL;
    else if (val < current->val)
    {
        current->left = pop(current->left, val);
    }
    else if (val > current->val)
    {
        current->right = pop(current->right, val);
    }
    else
    {
        // val == current->val
        // 1. leaf node (gda child)
        if (!current->left && !current->right)
        {
            free(current);
        }
        // 2. hanya left child
        else if (current->left && !current->right)
        {
            node *temp = current->left;
            free(current);
            return temp;
        }
        // 3. hanya right child
        else if (!current->left && current->right)
        {
            node *temp = current->right;
            free(current);
            return temp;
        }
        // 4. punya 2 cild
        else
        {
            node *replaced = predecessor(current);
            // copy datanya ke currentnya
            current->val = replaced->val;
            // pop replaced
            current->left = pop(current->left, current->val);
        }
    }
    return current;
}

node *popAll(node *current)
{
    if (!current)
        return NULL;
    current->left = popAll(current->left);
    current->right = popAll(current->right);
    free(current);
    current = NULL;
    return current;
}

int TotalNode(node *root)
{
    if (!root)
    {
        return 0;
    }
    int leftNode = TotalNode(root->left);
    int rightNode = TotalNode(root->right);
    return 1 + leftNode + rightNode;
}

int treeHeight(node *root)
{
    if (!root)
    {
        return 0;
    }
    int lh = treeHeight(root->left);
    int rh = treeHeight(root->right);
    // if (lh >= rh)
    // {
    //     return lh + 1;
    // }
    // else
    // {
    //     return rh + 1;
    // }

    return (lh >= rh) ? lh + 1 : rh + 1;
}

int maxValue(node *root)
{
    if (root->right)
    {
        maxValue(root->right);
    }
    else
    {
        return root->val;
    }
}

int minvalue(node *root)
{
    if (root->left)
    {
        minvalue(root->left);
    }
    else
    {
        return root->val;
    }
}

int main()
{
    // node *root = NULL;
    root = insert(root, 12);
    root = insert(root, 5);
    root = insert(root, 3);
    root = insert(root, 10);
    root = insert(root, 17);
    root = insert(root, 7);
    root = insert(root, 81);
    root = insert(root, 18);
    root = insert(root, 35);
    // root = insert(root, 90);
    // successor(root);
    root = pop(root, 12);
    // popAll(root);
    puts("");
    inOrder(root);
    printf("Total Node: %d\n", TotalNode(root));
    printf("Maximum Node Value: %d\n", maxValue(root));
    printf("Minimum Node Value: %d\n", minvalue(root));
    printf("Tree Height: %d\n", treeHeight(root));

    // node *searchNode = search(root, 11);
    // if(searchNode){
    //     puts("Founded");
    // }else{
    //     puts("Not Found");
    // }
    return 0;
}
