#include<stdio.h>
#include<stdlib.h>

struct data
{
    int key;
    data *left, *right;
}*root;

// alokasi memori
data *createNode(int key){
    data *node = (data *)calloc(1, sizeof(data));
    // pake calloc tidak perlu NULL kan left dan right
    node->key = key; // inisialisasi key
    return node;
}

data *insert(data *curr, int key){
    if(!curr){ // jika tidak ada data sama sekali (no head no tail)
        return createNode(key); // buat data baru
    }else if(key < curr->key){ // jika data yang kita masukan lebih kecil dari data yg sudah ada
        curr->left = insert(curr->left, key); // assign data baru ke bagian kiri tree
    }else if(key > curr->key){ // jika data yang kita masukan lebih besar dari data yg sudah ada
        curr->right = insert(curr->right, key); // assign data baru ke bagian kanan tree
    }
    return curr; // return data keseluruhan
}

void inOrder(data *curr){
    if(curr){ // jika terdapat data
        inOrder(curr->left); // cek paling kiri
        printf("%d\n", curr->key); // lalu print data
        inOrder(curr->right); // lalu cek paling kanan
    }
}

int main(){
    root = insert(root, 18);
    root = insert(root, 8);
    root = insert(root, 3);
    root = insert(root, 1);
    root = insert(root, 7);
    inOrder(root);
    return 0;
}