// binary search tree
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
struct node
{
    char phn[40];
    char name[40];
    char email[40];
    int point;
    node *left = NULL, *right = NULL;
}*root;

node *createNode(char phn[], char name[], char email[]){
    node *edon = (node *)malloc(sizeof(node));
    strcpy(edon->phn, phn);
    strcpy(edon->name, name);
    strcpy(edon->email, email);
    // int p = 0;
    // edon->point = p;
    // if(name != NULL && email != NULL){
    //     p+=10;
    // }
    return edon;
}

int hash(char phn[]){
    int hashkey = 0;
    for(int i = 0; i < strlen(phn); i++){
        hashkey += phn[i];
    }

    return hashkey % 100;
}

node *insert(node *curr, char phn[], char name[], char email[]){
    int key = hash(phn);
    if(!curr)
    {
        return (createNode(phn, name, email));
    }
    else if(strcmp(name, curr->phn) < 0){
        curr->left = insert(curr->left, phn, name, email);
    }
    else if(strcmp(name, curr->phn) > 0){
        curr->right = insert(curr->right, phn, name, email);
    }
    return curr;
}   

void inOrder(node *curr){
    if(curr){
        inOrder(curr->left);
        printf("%s %s %d\n", curr->name, curr->email, curr->point);
        inOrder(curr->right);
    }
}

void menu(){
    char phn[40] = {0};
    int chs = 0;
    char name[40] = {0};
    char email[40] = {0};
    puts("BlueBucks");
    puts("==============");
    puts("1. Process Order");
    puts("2. View All Customer");
    puts("3. Remove Customer");
    printf(">> ");
    scanf("%d", &chs);
    getchar();
    switch (chs)
    {
    case 1:
        printf("Enter your Phone Number: ");
        scanf("%s", &phn);
        getchar();
        printf("Enter Your Name: ");
        scanf("%[^\n]", &name);
        getchar();
        printf("Enter Your Email: ");
        scanf("%[^\n]", &email);
        getchar();
        root = insert(root, phn, name, email);
        inOrder(root);
        break;
    case 2:
        inOrder(root);
    break;
    
    default:
        break;
    }
}

int main(){
    while (true)
    {
        menu();
    }
    
    return 0;
}