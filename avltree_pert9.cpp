#include <stdio.h>
#include <stdlib.h>

struct Node
{
    int value, height, bf;
    Node *left;
    Node *right;
} *root = NULL;

int max(int a, int b)
{
    if (a > b)
    {
        return a;
    }
    else
    {
        return b;
    }
}

int getHeight(Node *curr)
{
    if (curr == NULL)
    {
        return 0;
    }
    return curr->height;
}

int setBalanceFactor(Node *curr)
{
    // -1 0 1 is not violation
    if (curr == NULL)
    {
        return 0;
    }
    return getHeight(curr->left) - getHeight(curr->right);
}

int setHeight(Node *curr)
{
    if (curr == NULL)
    {
        return 0;
    }
    return max(getHeight(curr->left), getHeight(curr->right)) + 1;
}

Node *updateNode(Node *curr)
{
    if (curr == NULL)
    {
        return 0;
    }
    curr->height = setHeight(curr);
    curr->bf = setBalanceFactor(curr);

    return curr;
}

Node *createNode(int value)
{
    Node *newNode = (Node *)malloc(sizeof(Node));
    newNode->value = value;
    newNode->height = 1;
    newNode->bf = 0;
    newNode->left = newNode->right = NULL;
    return newNode;
}

Node *leftRotation(Node *curr)
{
    Node *pivot = curr->right;
    Node *childleft = pivot->left;
    pivot->left = curr;
    curr->right = childleft;
    curr = updateNode(curr);
    pivot = updateNode(pivot);
    return pivot;
}

Node *rightRotation(Node *curr)
{
    Node *pivot = curr->left;
    Node *childright = pivot->right;
    pivot->right = curr;
    curr->left = childright;
    curr = updateNode(curr);
    pivot = updateNode(pivot);
    return pivot;
}

Node *rotation(Node *curr)
{
    if (curr == NULL)
    {
        return curr;
    }

    // LL
    if (curr->bf > 1 && curr->left->bf >= 0)
    {
        return rightRotation(curr);
    }

    // RR
    else if (curr->bf < -1 && curr->right->bf <= 0)
    {
        return leftRotation(curr);
    }

    // LR
    else if (curr->bf > 1 && curr->left->bf < 0)
    {
        curr->left = leftRotation(curr->left);
        return rightRotation(curr);
    }

    // RL
    else if (curr->bf < -1 && curr->right->bf > 0)
    {
        curr->right = rightRotation(curr->right);
        return leftRotation(curr);
    }

    return curr;
}

Node *insertNode(Node *root, int value)
{
    if (root == NULL)
    {
        return createNode(value);
    }
    else if (value < root->value)
    {
        root->left = insertNode(root->left, value);
    }
    else if (value > root->value)
    {
        root->right = insertNode(root->right, value);
    }
    return rotation(updateNode(root));
}

Node *popNode(Node *root, int deletedValue)
{
    if (root == NULL)
    {
        return root;
    }
    else if (deletedValue < root->value)
    {
        root->left = popNode(root->left, deletedValue);
    }
    else if (deletedValue > root->value)
    {
        root->right = popNode(root->right, deletedValue);
    }
    else if (deletedValue == root->value)
    {
        if (root->left == NULL && root->right == NULL)
        {
            // tidak punya 2 anak
            free(root);
            root = NULL;
        }
        else if (root->left != NULL && root->right == NULL)
        {
            // tidak punya anak kanan
            // punya anak kiri
            Node *temp = root->left;
            free(root);
            root = temp;
        }
        else if (root->left == NULL && root->right != NULL)
        {
            // tidak punya anak kiri
            // punya anak kanan
            Node *temp = root->right;
            free(root);
            root = temp;
        }
        else if (root->left != NULL && root->right != NULL)
        {
            // anak dua
            Node *temp = root->left;
            while (temp->right)
            {
                temp = temp->right;
            }
            root->value = temp->value;
            root->left = popNode(root->left, temp->value);
        }
    }

    return rotation(updateNode(root));
}

Node *inOrder(Node *root)
{
    if (root)
    {
        inOrder(root->left);
        // printf("%d, bf : %d, h : %d\n",
        // root->value, root->bf, root->height);
        printf("%d ", root->value);
        inOrder(root->right);
    }
}

Node *deleteAll(Node *curr)
{
    if (curr == NULL)
    {
        return NULL;
    }
    else
    {
        curr->left = deleteAll(curr->left);
        curr->right = deleteAll(curr->right);
        curr->left = curr->right = NULL;
        free(curr);
        curr = NULL;
    }
}

bool searchNode(Node *curr, int key)
{
    if (curr == NULL)
    {
        printf("Not Found!\n");
        return false;
    }
    else if (key < curr->value)
    {
        return searchNode(curr->left, key);
    }
    else if (key > curr->value)
    {
        return searchNode(curr->right, key);
    }
    else if (key == curr->value)
    {
        printf("Found!\n");
        return true;
    }
}

int main()
{
    Node *root = NULL;
    root = insertNode(root, 10);
    root = insertNode(root, 20);
    root = insertNode(root, 30);
    // inOrder(root);
    // searchNode(root, 50);
    root = popNode(root, 20);
    // root = deleteAll(root);
    inOrder(root);

    return 0;
}
