#include <stdio.h>
#include <stdlib.h>

struct tree
{
    int key, height, bf;
    tree *left, *right;
};

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int getHeight(tree *root)
{
    return root ? root->height : 0;
}

int setHeight(tree *root)
{
    // + 1 -> include root itself
    return max(getHeight(root->left), getHeight(root->right)) + 1;
}

int setBalanceFactor(tree *root)
{
    return getHeight(root->left) - getHeight(root->right);
}

tree *update(tree *root)
{
    // validasi wajib
    if (!root)
    {
        return 0;
    }
    root->height = setHeight(root);
    root->bf = setBalanceFactor(root);
    return root;
}

// Single right rotation
tree *rightRotation(tree *curr)
{
    // single right rotation tree example
    //       12 -> curr
    //      /  -> curr left child
    //     9 -> pivot
    //    / \ -> pivot right child
    //   3
    // assign pivot is curr->left child
    tree *pivot = curr->left;
    // assign right child of the pivot
    tree *rightChild = pivot->right;
    // assign and fill pivot right child with curr
    pivot->right = curr;
    // empty curr left child
    curr->left = rightChild;
    // update position
    curr = update(curr);
    pivot = update(pivot);
    // return pivot as a new curr (curr / parent)
    return pivot;
}
// Single left rotation
tree *leftRotation(tree *curr)
{
    // single left roation tree example:
    //                    12 -> curr
    //                      \ -> curr right child
    //                       19 -> pivot
    // pivot left child  -> /  \
    //                          21

    // assign pivot is the right child of curr
    tree *pivot = curr->right;
    // assign left child is pivot's left child
    tree *leftChild = pivot->left;
    // assign pivot's left child is curr
    pivot->left = curr;
    // empty curr's right child
    // because on the first condition, curr have a right child = 19
    // if we move 12 to be left child, the right pointer on 12 should be empty
    curr->right = leftChild;
    // update attribute
    curr = update(curr);
    pivot = update(pivot);
    // return pivot as new curr (root / parent)
    return pivot;
}

// if balance factor is positive means is in the right side
// if balance factor is negative means is in the left side
// balance factor is around -1 0 1 -> balanced tree (no violation)
// tree *rotate(tree *root)
// {
//     if(!root){
//         return root;
//     }
//     // left subtree child from root is heavier (has a higher height)
//     if (root->bf > 1)
//     {
//         // if the root left subtree has more or equal to zero balance factor
//         if (root->left->bf >= 0)
//         {
//             // right rotation on root
//             return rightRotation(root);
//         }
//         else
//         {
//             // left right rotation
//             // do left rotation on root->left child
//             root->left = leftRotation(root->left);
//             // and right rotation on root
//             return rightRotation(root);
//         }
//     }
//     // right subtree child from root is heavier (has a higher height)
//     else if (root->bf < -1)
//     {
//         // if root right child balance factor are more or equal to 0
//         if (root->right->bf <= 0)
//         {
//             // do left rotation on root
//             return leftRotation(root);
//         }
//         else
//         {
//             // right left rotation
//             // right rotation on root->right child
//             root->right = rightRotation(root->right);
//             // and left rotation on root
//             return leftRotation(root);
//         }
//     }
//     // return root so after rotate, the previous node still there
//     return root;
// }

tree *Rotation(tree *curr)
{
    // if there is no data
    if (!curr)
    {
        return curr;
    }

    // Right rotation
    // left subtree heavier and curr's left child bf >= 0
    // left - right : 4 - 2 = 2
    // if left heavier -> right rotation
    if (curr->bf > 1 && curr->left->bf >= 0)
    {
        return rightRotation(curr);
    }

    // Left Rotation
    // right subtree heavier
    // left - right = 2 - 4 = -2
    // if right heavier -> left rotation
    else if (curr->bf < -1 && curr->right->bf <= 0)
    {
        return leftRotation(curr);
    }

    // LR
    // if left subtree heavier and left subtree's right child is heavier
    else if (curr->bf > 1 && curr->left->bf < 0)
    {
        curr->left = leftRotation(curr->left);
        return rightRotation(curr);
    }

    // RL
    // if right subtree heavier and right subtree's left child is heavier
    else if (curr->bf < -1 && curr->right->bf > 0)
    {
        curr->right = rightRotation(curr->right);
        return leftRotation(curr);
    }
    // return curr so after rotation, previous node return back
    return curr;
}

tree *createNode(int key)
{
    tree *newNode = (tree *)malloc(sizeof(tree));
    newNode->key = key;
    newNode->bf = 0;
    newNode->height = 1;
    newNode->left = newNode->right = NULL;
    return newNode;
}

tree *insert(tree *root, int key)
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

    return Rotation(update(root));
}

// left subtree right most child
tree *predecessor(tree *curr)
{
    curr = curr->left;
    while (curr->right)
    {
        curr = curr->right;
    }
    return curr;
}

// right subtree left most child
tree *successor(tree *curr)
{
    curr = curr->right;
    while (curr->left)
    {
        curr = curr->left;
    }
    return curr;
}

tree *deletion(tree *root, int deletedValue)
{
    if (!root)
    {
        return root;
    }
    else if (deletedValue < root->key)
    {
        root->left = deletion(root->left, deletedValue);
    }
    else if (deletedValue > root->key)
    {
        root->right = deletion(root->right, deletedValue);
    }
    else if (deletedValue == root->key)
    {
        // kalo gak punya anak sama sekali kiri kanan
        if (!root->left && !root->right)
        {
            // lansung delete aja
            free(root);
            root = NULL;
        }
        // kalo ada anak kanan
        else if (!root->left && root->right)
        {
            tree *temp = root->right;
            free(root);
            root = temp;
        }
        // kalo ada anak kiri
        else if (root->left && !root->right)
        {
            tree *temp = root->left;
            free(root);
            root = temp;
        }
        // ada anak kiri kanan
        else if (root->left && root->right)
        {
            // left subtree right most child
            // predecessor
            tree *replaced = root->left;
            while (replaced->right)
            {
                replaced = replaced->right;
            }

            // tree *replaced = predecessor(root);
            root->key = replaced->key;
            root->left = deletion(root->left, replaced->key);
        }
    }
    return Rotation(update(root));
}

// preOrder print dlu baru left right
void preOrder(tree *curr){
    if(curr){
        printf("%d ", curr->key);
        preOrder(curr->left);
        preOrder(curr->right);
    }
}

// left print right
void inOrder(tree *curr)
{
    if (curr)
    {
        inOrder(curr->left);
        printf("%d ", curr->key);
        // puts("");
        // printf("Height: %d ", curr->height);
        // puts("");
        // printf("Balance Factor: %d\n", curr->bf);
        inOrder(curr->right);
    }
}

// left right print
void postOrder(tree *curr){
    if(curr){
        postOrder(curr->left);
        postOrder(curr->right);
        printf("%d ", curr->key);
    }
}


tree *deleteALL(tree *curr){
    if(!curr){
        return NULL;
    }else{
        curr->left = deleteALL(curr->left);
        curr->right = deleteALL(curr->right);
        curr->left = curr->right = NULL;
        free(curr);
        curr = NULL;
    }
}


int main()
{
    tree *root = NULL;
    root = insert(root, 2);
    root = insert(root, 12);
    root = insert(root, 24);
    root = insert(root, 6);
    inOrder(root);
    root = deletion(root, 24);
    root = deletion(root, 12);
    puts("");
    inOrder(root);
    return 0;
}