#include<stdio.h>
#include<string.h>
#include<stdlib.h>

// BINARY SEARCH TREE
// Root -> parent
// Leaf -> anak paling terakhir yang udah gapunya edge lagi
// kiri root < root
// root > kanan root

struct User{
	int key;
	char name[100];
	struct User *left;
	struct User *right;
};

struct User* createUser(int key, char name[]){
	struct User *node = (User*)malloc(sizeof(struct User));
	node->key = key;
	strcpy(node->name, name);
	node->left = NULL;
	node->right = NULL;
	
	return node;
}

// Inserting
struct User* insert(struct User *root, struct User *node){
	if(root == NULL){
		root = node;
	}else if(node->key < root->key){
		root->left = insert(root->left, node);
	}else if(node->key > root->key){
		root->right = insert(root->right, node);
	}
	
	return root;
}

// Printing
void postOrder(struct User *root){
	if(root != NULL){
		postOrder(root->left);
		postOrder(root->right);
		printf("|%-21s ||           %-12d|\n", root->name, root->key);
	}
}

void inOrder(struct User *root){
	if(root != NULL){
		inOrder(root->left);
		printf("|%-21s ||           %-12d|\n", root->name, root->key);
		inOrder(root->right);
	}
}

void preOrder(struct User *root){
	if(root != NULL){
		printf("|%-21s ||           %-12d|\n", root->name, root->key);
		preOrder(root->left);
		preOrder(root->right);
	}
}

// Updating
struct User* update(struct User *root, int key, char changeName[]){
	if(root == NULL){
		return root;
	}else if(key < root->key){
		root->left = update(root->left, key, changeName);
	}else if(key > root->key){
		root->right = update(root->right, key, changeName);
	}else{
		if(key != root->key){
			return root;
		}
		strcpy(root->name, changeName);
	}
	return root;
}

// Searching Data
int searchingData(struct User *curr, int key){
	if(curr){
		if(curr->key==key){
			return 1;
		}
	
		if(curr->key<key){
			return searchingData(curr->right, key);
		}else{
			return searchingData(curr->left, key);
		}
	}
	return 0;
}

// Predecessor
struct User* predecessor(struct User *root){
	struct User* curr = root->right;
	while(curr->left!=NULL){
		curr = curr->left; // belokin terus ke kiri
	}
	return curr;
}

// Deleting
struct User* deleteData(struct User *root, int key){
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
		}else if(root->left == NULL || root->right == NULL){ // artinya salah satu kosong, minimal pny 1 anak
			struct User* temp;
			if(root->left!=NULL){
				temp = root->left;
			}else{
				temp = root->right;
			}
			free(root);
			root = temp;
		}else{ // kalo punya dua anak
			struct User* pre = predecessor(root);
			
			root->key = pre->key;
			strcpy(root->name, pre->name);
			
			root->right = deleteData(root->right, pre->key);
		}
	}
	return root;
}

struct User* deleteAll(struct User* root){
	while(root!=NULL){
		root = deleteData(root, root->key);
	}
	return NULL;
}

int main(){
	struct User *root = NULL;
	root = insert(root, createUser(5, "Jordy")); // buat nambahin data baru
	root = insert(root, createUser(16, "Budi")); // buat nambahin data baru
	root = insert(root, createUser(4, "Susi")); // buat nambahin data baru
	root = insert(root, createUser(9, "Joko")); // buat nambahin data baru
	root = insert(root, createUser(3, "Andy")); // buat nambahin data baru
	root = insert(root, createUser(20, "Fani")); // buat nambahin data baru
	
	update(root, 9, "Gaby");
	
	int curr;
	curr = searchingData(root, 4);
	curr = searchingData(root, 10);
	if(curr==NULL){
		puts("Data not found!");
	}else{
		printf("%d\n", root->key);
	}
	
	
	puts("=================================================");
	puts("|               Pre Order Print                 |");
	puts("=================================================");
	puts("|        Name          ||          Key          |");
	puts("=================================================");
	preOrder(root);
	puts("=================================================");
	
	puts("=================================================");
	puts("|                In Order Print                 |");
	puts("=================================================");
	puts("|        Name          ||          Key          |");
	puts("=================================================");
	inOrder(root);
	puts("=================================================");
	
	puts("=================================================");
	puts("|               Post Order Print                |");
	puts("=================================================");
	puts("|        Name          ||          Key          |");
	puts("=================================================");
	postOrder(root);
	puts("=================================================");
	
	puts("=================================================");
	puts("|              After Delete Data                |");
	puts("=================================================");
	puts("|        Name          ||          Key          |");
	puts("=================================================");
	root = deleteData(root, 5);
	inOrder(root);
	puts("=================================================");
	
	puts("=================================================");
	puts("|              After Delete Data                |");
	puts("=================================================");
	puts("|        Name          ||          Key          |");
	puts("=================================================");
	root = deleteAll(root);
	inOrder(root);
	puts("| All data have been deleted                    |");
	puts("=================================================");

	return 0;
}
