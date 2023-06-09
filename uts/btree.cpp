// #include<string.h>
// #include<stdio.h>
// #include<stdlib.h>

// struct bst
// {
//     int value;
//     bst *left, *right;
// }*root;

// bst *createNode(int value){
//     bst *node = (bst *)calloc(1, sizeof(bst));
//     node->value = value;
//     return node;
// }

// bst *insert(bst *curr, int value){
//     if(!curr){
//         return createNode(value);
//     }else if(value < curr->value){
//         curr->left = insert(curr->left, value);
//     }else if(value > curr->value){
//         curr->right = insert(curr->right, value);
//     }
//     return curr;
// }

// bst *predecessor(bst *root){
//     bst *curr = root->right;
//     while(curr->left){
//         curr = curr->left;
//     }
//     return curr;
// }

// bst *remove(bst *root, int value){
//     if(!root){ // gda data yg bisa di delete
//         return root; // return data yg ada
//     }else if(value < root->value){ // value yg di masukin lbh kecil
//         root->left = remove(root->left, value); // cari ke samping kiri
//     }else if(value > root->value){ // value yg dimasukin lebih besar
//         root->right = remove(root->right, value); // cari ke samping kanan
//     }else{
//         if(!root->left && !root->right){ // kalo kiri kanan kosong
//             free(root);
//             root = NULL; // free dan NULL in data
//         }else if(!root->left || !root->right){ // kalo salah satu anak kiri kanan gda
//             bst *temp;
//             if(root->left){ // kalo yg ada cm anak kiri
//                 temp = root->left; // tampung anak kiri di temp
//             }else{
//                 temp = root->right; // tampung anak kanan di temp
//             }
//             free(root); // free root dan assign root = temp;
//             root = temp;
//         }else{
//             bst *pre = predecessor(root);
//             root->value = pre->value;
//             root->right = remove(root->right, pre->value);
//         }
//     }
//     return root; // jangan lupa return root biar kalo dihapus bawahnya masih ke return
// }

// void inOrder(bst *curr){
//     if(curr){
//         inOrder(curr->left);
//         printf("Value: %d\n", curr->value);
//         inOrder(curr->right);
//     }
// }

// bst *search(bst *curr, int value){
//     if(curr){
//         if(curr->value == value){
//             printf("%d is here!\n", value);
//         }else if(value < curr->value){
//             curr->left = search(curr->left, value);
//         }else if(value > curr->value){
//             curr->right = search(curr->right, value);
//         }
//     }
//     return curr; // jangan lupa return curr biar data gada yg kepotong pas udh ketemu yg kita cari
// }

// int main(){
//     root = insert(root, 3);
//     root = insert(root, 1);
//     root = insert(root, 6);
//     root = insert(root, 7);
//     root = insert(root, 13);
//     root = insert(root, 10);
//     root = insert(root, 12);
//     root = insert(root, 9);
//     // inOrder(root);
//     root = remove(root, 12);
//     // root = search(root, 12);
//     inOrder(root);

//     return 0;
// }

#include <stdio.h>
#include <stdlib.h>

struct bst
{
    int key;
    bst *left, *right;
} *root;

bst *createNode(int key)
{
    bst *node = (bst *)calloc(1, sizeof(bst));
    node->key = key;
    return node;
}

bst *insert(bst *curr, int key)
{
    if (!curr)
    {
        return createNode(key);
    }
    else if (key < curr->key)
    {
        curr->left = insert(curr->left, key);
    }
    else if (key > curr->key)
    {
        curr->right = insert(curr->right, key);
    }
    return curr;
}

void inOrder(bst *curr)
{
    if (curr)
    {
        inOrder(curr->left);
        printf("InORder: %d\n", curr->key);
        inOrder(curr->right);
    }
}

void postOrder(bst *curr)
{
    if (curr)
    {
        postOrder(curr->left);
        postOrder(curr->right);
        printf("PostOrder: %d\n", curr->key);
    }
}

void preOrder(bst *curr)
{
    if (curr)
    {
        printf("PreOrder: %d\n", curr->key);
        preOrder(curr->left);
        preOrder(curr->right);
    }
}

bst *successor(bst *root)
{
    bst *curr = root->right;
    while (curr->left)
    {
        curr = curr->left;
    }
    return curr;
}

bst *remove(bst *curr, int key)
{
    if (!curr)
    {
        return curr;
    }
    else if (key < curr->key)
    {
        curr->left = remove(curr->left, key);
    }
    else if (key > curr->key)
    {
        curr->right = remove(curr->right, key);
    }
    else
    {
        if (!curr->left && !curr->right)
        {
            free(curr);
            curr = NULL;
        }
        else if (!curr->left || !curr->right)
        {
            bst *temp;
            if (curr->left)
            {
                temp = curr->left;
            }
            else
            {
                temp = curr->right;
            }
            free(curr); // hapus data yg kita masukin
            curr = temp; // isi tre eulang dgn value yg udh dihapus
        }
        else
        {
            // pilih cara hapus -> direction tree
            bst *suc = successor(curr);
            curr->key = suc->key;
            curr->right = remove(curr->right, suc->key);
        }
    }
    return curr;
}

bst *search(bst *root, int value)
{
    if (root)
    {
        if (root->key == value)
        {
            printf("%d is here\n", value);
        }
        else if (root->key > value)
        {
            root->left = search(root->left, value);
        }
        else if (root->key < value)
        {
            root->right = search(root->right, value);
        }
    }
    return root;
}

int main()
{
    root = insert(root, 7);
    root = insert(root, 6);
    root = insert(root, 2);
    root = insert(root, 11);
    root = insert(root, 14);
    root = insert(root, 9);
    // postOrder(root);
    root = remove(root, 2);
    root = search(root, 6);
    inOrder(root);
    // preOrder(root);
    return 0;
}