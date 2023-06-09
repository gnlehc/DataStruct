#include<stdio.h>
#include<string.h>
#include<stdlib.h>

// BST
// sisi kiri < tengah < sisi kanan

// Deleting :
// 1. if the key is in a leaf, just delete that node
// 2. if the key is in a node which has one child, delete that node and connect its child to its parent.
// 3. if the key is the parent with 2 children, find the right most child of its left sub tree, replace/switch its key with
//    right most child, and remove it recursively (the right most child). 
// 

struct data{
	int key;
	struct data *left, *right, *parent;
}*root = NULL;

struct data* newNode(int key){
	struct data *node = (struct data*)malloc(sizeof(struct data));
	node->key = key;
	node->left = node->right = node->parent = NULL;
	
	return node;
}

void pushBST(struct data *curr, int key){
	if(!root){
		root = newNode(key);
	}
	else if(key > curr->key){
		if(curr->right == NULL){
			curr->right = newNode(key);	
			curr->right->parent = curr;
		}
		else{
			pushBST(curr->right, key);
		}
	}
	else if(key < curr->key){
		if(curr->left == NULL){
			curr->left = newNode(key);
			curr->left->parent = curr;
		}
		else{
			pushBST(curr->left, key);
		}
	}
	else{
		printf("ERROR 404. Double Data\n");
	}
}

void preOrder(struct data *curr){
	if(curr){
		printf("%d ",curr->key);
		preOrder(curr->left);
		preOrder(curr->right);
	}
}

void inOrder(struct data *curr){
	if(curr != NULL){
		inOrder(curr->left);
		printf("%d ", curr->key);
		inOrder(curr->right);
	}
}

void postOrder(struct data *curr){
	if(curr != NULL){
		postOrder(curr->left);
		postOrder(curr->right);
		printf("%d ", curr->key);
	}
}

struct data* successor(struct data *root){
	struct data *curr = root->right;
	
	while(curr->left != NULL){
		curr = curr->left;
	}
	
	return curr;
}

struct data* deleteData(struct data *root, int key){
	if(root == NULL){
		return root;
	}else if(key < root->key){
		root->left = deleteData(root->left, key);
	}else if(key > root->key){
		root->right = deleteData(root->right, key);
	}else{
		if(root->left == NULL && root->right == NULL){
			free(root);
			root = NULL;
			puts("succeed");
		}else if(root->right == NULL || root->left == NULL){
			struct data *temp;
			
			if(root->left!=NULL){
				temp = root->left;
			}else{
				temp = root->right;
			}
			
			free(root);
			root = temp;
			puts("succeed");
		}else{
			struct data *suc = successor(root);
			
			root->key = suc->key;
			root->right = deleteData(root->right, suc->key);
			puts("succeed");
		}
	}
	return root;
}

struct data *search(struct data *root, int key){
	if(root!=NULL){
		if(root->key == key){
			return root;
		}
		
		if(key < root->key){
			search(root->left, key);
		}else if(key > root->key){
			search(root->right, key);
		}
	}
	return root;
}

struct data* rightMost(struct data *curr){ // right MOST CHILD from the left SUB-TREE
	if(curr->right!=NULL){
		rightMost(curr->right);
	}
	
	return curr;
}

void popData(struct data *curr, int key){
	struct data *pop = search(curr, key);
	if(pop!=NULL){
		if(pop->left == NULL && pop->right == NULL){ // has no child / leaf
			if(pop == root){
				root = NULL;
			}else{
				if(pop->parent->left == pop){ // node is a left child
					pop->parent->left = NULL;
				}else{ // node is a right child
					pop->parent->right = NULL;
				}
			}
			free(pop);
		}else if(pop->left == NULL){ // punya 1 anak, anak kanan
			if(pop == root){
				root = pop->right;
				root->parent = NULL;
			}else{
				if(pop->parent->left == pop){ // node is a left child
					pop->parent->left = pop->right;
				}else{ // node is a right child
					pop->parent->right = pop->right;
				}
				pop->right->parent = pop->parent;
			}
			free(pop);
		}else if(pop->right == NULL){
			if(pop == root){
				root = pop->left;
				root->parent == NULL;
			}else{
				if(pop->parent->left == pop){
					pop->parent->left = pop->left;
				}else{
					pop->parent->right = pop->left;
				}
				pop->left->parent = pop->parent;
			}
			free(pop);
		}else{ // kalo pny dua anak
			struct data *replace = rightMost(pop->left);
			pop->key = replace->key;
			popData(replace, replace->key);
		}
	}
	return;
}

void popAll(struct data *curr){
	if(curr!=NULL){
		popAll(curr->left);
		popAll(curr->right);
		if(root == curr){
			root = NULL;
		}else if(curr->parent->left == curr){
			curr->parent->left = NULL;
		}else{
			curr->parent->right = NULL;
		}
		free(curr);
	}
}

int main(){
//	root = insertData(root, newNode(10));
//	root = insertData(root, newNode(5));
//	root = insertData(root, newNode(15));
//	root = insertData(root, newNode(2));
//	root = insertData(root, newNode(7));
//	root = insertData(root, newNode(11));
//	root = insertData(root, newNode(17));
//	root = insertData(root, newNode(12));
	pushBST(root, 10);
	pushBST(root, 5);
	pushBST(root, 15);
	pushBST(root, 2);
	pushBST(root, 7);
	pushBST(root, 11);
	pushBST(root, 17);
	pushBST(root, 12);
	
	preOrder(root);
	puts("");
	inOrder(root);
	puts("");
	postOrder(root);
	puts("");
	
//	root = deleteData(root, 10);
	popData(root, 10);
	inOrder(root);
	puts("");
	
//	root = deleteData(root, 12);
	popData(root, 12);
	inOrder(root);
	puts("");
	
//	root = deleteData(root, 5);
	popData(root, 5);
	inOrder(root);
	puts("");
	
	popAll(root);
	inOrder(root);
	puts("");
	
	return 0;
}

