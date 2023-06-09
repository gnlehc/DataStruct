#include<stdio.h>
#include<malloc.h>
#include<string.h>
// session 8 9 may 23
struct item{
	int price;
	char name[25];
	item *left, *right;
	int height;
}*root;

item *createItem(int price, char name[]){
	item *newItem = (item*)malloc(sizeof(item));
	newItem->price = price;
	strcpy(newItem->name, name);
	newItem->right = newItem->left = NULL;
	newItem->height = 1;
	
	return newItem;
}

int max(int a, int b){
	return (a > b) ? a : b;
}

int getHeight(item *current){
	return (current) ? current->height : 0;
}

item *rightRotation(item *current){
	item *child = current->left;
	item *child_right = child->right;
	
	child->right = current;
	current->left = child_right;
	
	current->height = 1 + max(getHeight(current->left), getHeight(current->right));
	child->height = 1 + max(getHeight(child->left), getHeight(child->right));
	
	return child;
}

item *leftRotation(item *current){
	item *child = current->right;
	item *child_left = child->left;
	
	child->left = current;
	current->right = child_left;
	
	current->height = 1 + max(getHeight(current->left), getHeight(current->right));
	child->height = 1 + max(getHeight(child->left), getHeight(child->right));
	
	return child;
}

int balance_factor(item *current){
	return getHeight(current->left) - getHeight(current->right);
}

item *insert(item *current, item *newItem){
	if(!current){
		return newItem;
	}
	else if(current->price > newItem->price){
		current->left = insert(current->left, newItem);
	}
	else if(current->price < newItem->price){
		current->right = insert(current->right, newItem);
	}
	
	current->height = 1 + max(getHeight(current->left), getHeight(current->right));
	
	//check balance factor
	int bf = balance_factor(current);
	
	//left left case
	if(bf > 1 && current->left->price > newItem->price){
		return rightRotation(current);
	}
	//right right case
	else if(bf < -1 && current->right->price < newItem->price){
		return leftRotation(current);
	}
	//left right case
	//lakuin left rotation
	//right rotation
	else if(bf > 1 && current->left->price < newItem->price){
		current->left = leftRotation(current->left);
		return rightRotation(current);
	}
	//right left case
	else if(bf < -1 && current->right->price > newItem->price){
		current->right = rightRotation(current->right);
		return leftRotation(current);
	}
	
	//return unchanged pointer
	return current;
}

void preOrder(item *current){
	if(!current){
		return;
	}
	
	printf("%s %d - Level %d\n", current->name, current->price, current->height);
	preOrder(current->left);
	preOrder(current->right);
}

int main(){
	
	//kalau di bagian insert, harus pakai return kalau currentnya kosong
	
	//untuk cobain LR case
//	root = insert(root, createItem(50, "A"));
//	root = insert(root, createItem(20, "B"));
//	root = insert(root, createItem(30, "C"));

//	root = insert(root, createItem(60, "D"));

	//untuk cobain RL case
	root = insert(root, createItem(50, "A"));
	root = insert(root, createItem(60, "B"));
	root = insert(root, createItem(55, "C"));
	
	
	preOrder(root);
	
	return 0;
}
