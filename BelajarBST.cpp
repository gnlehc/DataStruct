#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

struct binaryTree{
	int value;
	
	struct binaryTree *left;
	struct binaryTree *right;
}*root = NULL; 

struct binaryTree *newNode (int value){
	struct binaryTree *node = (struct binaryTree*)malloc(sizeof(struct binaryTree));
	
	node->value = value;
	node->left = NULL;
	node->right = NULL;
	
	return node;
}

void insertData(struct binaryTree *curr, int value){
	if(root==NULL){
		root = newNode(value);
	}else if(value > curr->value){
		if(curr->right == NULL){
			curr->right = newNode(value);
		}else{
			insertData(curr->right, value);
		}
	}else if(value < curr->value){
		if(curr->left == NULL){
			curr->left = newNode(value);
		}else{
			insertData(curr->left, value);
		}
	}else{
		puts("Sorry, this data already exists!");
	}
}

void printData(struct binaryTree *curr){ // Pre-Order
	if(curr){
		printf("%d ", curr->value);
		printData(curr->left);
		printData(curr->right);
	}
}

int searchingData(struct binaryTree *curr, int value){
	if(curr!=NULL){
		if(value == curr->value){
			return 1;
		}else{
			if(value < curr->value){
				searchingData(curr->left, value);
			}else if(value > curr->value){
				searchingData(curr->right, value);
			}
		}
	}else{
		return 0;
	}
}

struct binaryTree* predecessor (struct binaryTree *root){
	struct binaryTree *curr = root->right;
	while(curr!=NULL){
		curr = curr->left;
	}
	return curr;
}

struct binaryTree* deleteData(struct binaryTree *root, int value){
	if(root == NULL){
		return root;
	}else if(value < root->value){
		root->left = deleteData(root->left, value);
	}else if(value > root->value){
		root->right = deleteData(root->right, value);
	}else{
		if(root->left == NULL && root->right == NULL){
			free(root);
			root = NULL;
		}else if(root->left == NULL || root->right == NULL){
			struct binaryTree *temp;
			
			if(root->left!=NULL){
				temp = root->left;
			}else{
				temp = root->right;
			}
			
			free(temp);
			temp = NULL;
		}else{
			struct binaryTree *pre = predecessor(root);
			
			root->value = pre->value;
			root->right = deleteData(root->right, pre->value);
		}
	}
	return root;
}

void mainMenu();
void firstMenu();
void secondMenu();
void thirdMenu();
void fourthMenu();

int main(){
	mainMenu();

	return 0;
}

void mainMenu(){
	int input;
	
	puts("+====================+");
	puts("| Binary Search Tree |");
	puts("+====================+");
	puts("| 1. Insert Data     |");
	puts("| 2. Search Data     |");
	puts("| 3. Delete Data     |");
	puts("| 4. Exit            |");
	puts("+====================+");
	printf(">> ");
	scanf("%d", &input); getchar();
	
	while(input<1 || input>4){
		printf(">> ");
		scanf("%d", &input); getchar();
	}
	
	switch(input){
		case 1:
			firstMenu();
			break;
		case 2:
			secondMenu();
			break;
		case 3:
			thirdMenu();
			break;
		case 4:
			fourthMenu();
			break;
	}
}

void firstMenu(){
	int value;
	printf("Input a value: ");
	scanf("%d", &value); getchar();
	insertData(root, value);
	
	puts("Our data now: ");
	printData(root);
	puts(" ");
	
	printf("Press ENTER to continue..."); getchar();
	system("cls");
	mainMenu();
	return;
}

void secondMenu(){
	int value;
	int search;
	printf("Input a value to be search: ");
	scanf("%d", &value); getchar();
	
	search = searchingData(root, value);
	if(search == 0){
		printf("The %d value does not exist\n", value);
	}else{
		printf("The %d value does exist\n", value);
	}
	
	printf("Press ENTER to continue..."); getchar();
	system("cls");
	mainMenu();
	return;
}

void thirdMenu(){
	int value;
	printf("Input a value to be delete: ");
	scanf("%d", &value); getchar();
	root = deleteData(root, value);
	
	puts("Our data now: ");
	printData(root);
	puts(" ");
	
	printf("Press ENTER to continue..."); getchar();
	system("cls");
	mainMenu();
	return;
}

void fourthMenu(){
	system("cls");
	puts("Slayage");
	
	return;
}
