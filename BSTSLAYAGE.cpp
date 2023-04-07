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


struct data
{
	int key;
	struct data *left, *right, *parent;
}*root = NULL;

struct data* newNode(int key)
{
	struct data *node = (struct data*)malloc(sizeof(struct data));
	node->key = key;
	node->left = node->right = node->parent = NULL;
	
	return node;
}

void pushBST(struct data *curr, int key)
{
	if(!root)
	{
		root = newNode(key);
	}
	else if(key > curr->key)
	{
		if(curr->right == NULL)
		{
			curr->right = newNode(key);	
		}
		else
		{
			pushBST(curr->right, key);
		}
	}
	else if(key < curr->key)
	{
		if(curr->left == NULL)
		{
			curr->left = newNode(key);
		}
		else
		{
			pushBST(curr->left, key);
		}
	}
	else
	{
		printf("ERROR 404. Double Data\n");
	}
}

void preOrder(struct data *curr)
{
	if(curr)
	{
		printf("%d ",curr->key);
		preOrder(curr->left);
		preOrder(curr->right);
	}
}

void inOrder(struct data *curr)
{
	if(curr != NULL)
	{
		inOrder(curr->left);
		printf("%d ", curr->key);
		inOrder(curr->right);
	}
}

void postOrder(struct data *curr)
{
	if(curr != NULL)
	{
		postOrder(curr->left);
		postOrder(curr->right);
		printf("%d ", curr->key);
	}
}

int main()
{
	pushBST(root, 55);
	pushBST(root, 1);
	pushBST(root, 15);
	pushBST(root, 20);
	pushBST(root, 28);
	pushBST(root, 7);
	pushBST(root, 60);
	
	preOrder(root);
	puts("");
	inOrder(root);
	puts("");
	postOrder(root);
	puts("");
	return 0;
}

