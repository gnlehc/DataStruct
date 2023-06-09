#include<stdio.h>
#include<stdlib.h>

struct p
{
    int key;
    p *left, *right, *parent;
}*root;

p *createTree(int key){
    p *node = (p *)calloc(1, sizeof(p));
    node->key = key;
    return node;
}

p *insert(p *curr, int key){
    p *node = createTree(key);
    if(!curr){
        return node;
    }else if(key < curr->key){
        if(!curr->left){
            curr->left = node;
            curr->left->parent = curr;
        }else{
            insert(curr->left, key);
        }
    }else if(key > curr->key){
        if(!curr->right){
            curr->right = node;
            curr->right->parent = curr;
        }else{
            insert(curr->right, key);
        }
    }
    return curr;
}

void inOrder(p *curr){
    if(curr){
        inOrder(curr->left);
        printf("Key: %d\n", curr->key);
        inOrder(curr->right);
    }
}

p *search(p *curr, int key){
    if(curr){
        if(curr->key == key){
            return curr;
        }else if(key < curr->key){
            return search(curr->left, key);
        }else if(key > curr->key){
            return search(curr->right, key);
        }
    }
}

p *rightMostChild(p *curr){
    while (curr->right)
    {
        rightMostChild(curr->right);
    }
    return curr;
}
p *predecessor(p *curr){
    curr = curr->left;
    while (curr->right)
    {
        curr = curr->right;
    }
    return curr;
}

void removeNode(p *curr, int key){
    p *pop = search(curr, key);
    if(pop){
        if(!pop->left && !pop->right){
            if(pop == root){
                root = NULL;
            }else{
                if(pop->parent->left == pop){
                    pop->parent->left = NULL;
                }else{
                    pop->parent->right = NULL;
                }
            }
            free(pop);
        }else if(!pop->left){
            if(pop == root){
                root = pop->right;
                root->parent = NULL;
            }else{
                if(pop->parent->left = pop){
                    pop->parent->left = pop->right;
                }else{
                    pop->parent->right = pop->right;
                }
                pop->right->parent = pop->parent;
            }
            free(pop);
        }else if(!pop->right){
            if(pop == root){
                root = pop->left;
                root->parent = NULL;
            }else{
                if(pop->parent->left = pop){
                    pop->parent->left = pop->left;
                }else{
                    pop->parent->right = pop->left;
                }
                pop->left->parent = pop->parent;
            }
            free(pop);
        }
        else{
            p *pre = rightMostChild(pop->left);
            pop->key = pre->key;
            removeNode(pre, pre->key);
            
        }
    }
    
}

int main(){
    root = insert(root, 19);
    root = insert(root, 13);
    root = insert(root, 9);
    root = insert(root, 5);
    root = insert(root, 15);
    root = insert(root, 21);
    removeNode(root, 19);
    inOrder(root);
    return 0;
}