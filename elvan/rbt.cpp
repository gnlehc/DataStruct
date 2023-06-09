// Chelsea Ng - 2602057652

#include <stdio.h>
#include <stdlib.h>

// RED BLACK TREE Properties
// 1. Nodes can be either BLACK or RED
// 2. Root is BLACK color by default
// 3. New Node is RED
// 4. Each red node's parent is black
// 5. if a node is RED, than both its children are BLACK
// 6. ALL external nodes are BLACK

#define RED 0
#define BLACK 1

struct RBT
{
    int key;
    int color;
    struct RBT *parent, *left, *right;
};
struct RBT *root;
struct RBT *leaves; // leaf node that are NULL
void RBT_fixup(struct RBT *newNode);
void rightRotate(struct RBT *newNode);
void leftRotate(struct RBT *newNode);

void RBTinsert(int key)
{
    // memory allocation
    struct RBT *roots, *x;
    struct RBT *newNode = (struct RBT *)malloc(sizeof(struct RBT));
    newNode->key = key;
    newNode->color = RED;
    newNode->left = leaves;
    newNode->right = leaves;

    roots = root;
    x = leaves; // track non leaf node that will be newNode's parent

    while (roots != leaves)
    {
        x = roots;
        if (newNode->key <= roots->key)
        {
            roots = roots->left;
        }
        else
        {
            roots = roots->right;
        }
    }

    if (x == leaves)
    {
        root = newNode;
    }
    else if (newNode->key <= x->key)
    {
        x->left = newNode;
    }
    else
    {
        x->right = newNode;
    }

    newNode->parent = x;
    RBT_fixup(newNode);
}

void RBT_fixup(struct RBT *newNode)
{
    while (newNode->parent->color == RED)
    {
        // newNode parent is left child of newNode's grandparent
        if (newNode->parent == newNode->parent->parent->left)
        {
            // newNode's grandparent's right child is RED
            if (newNode->parent->parent->right->color == RED)
            {
                newNode->parent->color = BLACK;
                newNode->parent->parent->right->color = BLACK;
                newNode->parent->parent->color = RED;
                newNode = newNode->parent->parent;
            }
            // if newNode's grandparent's right child is BLACK
            else
            {
                // if newNode is newNode's parent's right child
                if (newNode = newNode->parent->right)
                {
                    newNode = newNode->parent;
                    leftRotate(newNode);
                }
                newNode->parent->color = BLACK;
                newNode->parent->parent->color = RED;
                rightRotate(newNode->parent->parent);
            }
        }

        else
        {
            // newNode's left uncle or newNode's grandparent's left child is also RED
            if (newNode->parent->parent->left->color == RED)
            {
                newNode->parent->color = BLACK;
                newNode->parent->parent->left->color = BLACK;
                newNode->parent->parent->color = RED;
                newNode = newNode->parent->parent;
            }
            else
            {
                if (newNode == newNode->parent->left)
                {
                    newNode = newNode->parent;
                    rightRotate(newNode);
                }
                newNode->parent->color = BLACK;
                newNode->parent->parent->color = RED;
                leftRotate(newNode->parent->parent);
            }
        }
    }
    root->color = BLACK;
}

void leftRotate(struct RBT *newNode)
{
    struct RBT *temp;
    // rotate temp's left child newNode's right child
    temp = newNode->right;
    newNode->right = temp->left;
    if (temp->left != leaves)
    {
        temp->left->parent = newNode;
    }

    // make newNode's parent temp's parent, newNode's parent's child
    temp->parent = newNode->parent;
    if (temp->parent == leaves)
    {
        root = temp;
    }
    // if newNode is newNode's parent's left child
    else if (newNode = newNode->parent->left)
    {
        // assign newNode's parent's left child is temp
        newNode->parent->left = temp;
    }
    else
    {
        // assign newNode's parent's right child is temp
        newNode->parent->right = temp;
    }

    // make newNode, temp's left child and temp, newNode's parent
    temp->left = newNode;
    newNode->parent = temp;
}

void rightRotate(struct RBT *newNode)
{
    struct RBT *temp;
    // rotate temp's right child newNode's left child
    temp = newNode->left;
    newNode->left = temp->right;
    if (temp->right != leaves)
    {
        temp->right->parent = newNode;
    }

    // make newNode's parent temp's parent and temp, newNode's parent's child
    temp->parent = newNode->parent;
    if (temp->parent == leaves)
    {
        root = temp;
    }
    else if (newNode == newNode->parent->left)
    {
        newNode->parent->left = temp;
    }
    else
    {
        newNode->parent->right = temp;
    }

    // make temp, newNode's parent and newNode, temp's child
    temp->right = newNode;
    newNode->parent = temp;
}

void inOrder(struct RBT *curr)
{
    if (curr != leaves)
    {
        inOrder(curr->left);
        if (curr->key == 0)
        {
            printf("RED: ");
        }
        else
        {
            printf("BLACK: ");
        }

        printf("%d ", curr->key);
        // printf("%d", curr->color);
        inOrder(curr->right);
    }
}

int main()
{
    leaves = (struct RBT *)malloc(sizeof(struct RBT));
    leaves->color = BLACK;
    root = leaves;

    RBTinsert(41);
    RBTinsert(22);
    RBTinsert(5);
    RBTinsert(51);
    RBTinsert(48);
    RBTinsert(29);
    RBTinsert(18);
    RBTinsert(21);
    RBTinsert(45);
    RBTinsert(3);
    inOrder(root);
    return 0;
}
