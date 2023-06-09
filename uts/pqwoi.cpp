#include <stdio.h>
#include <stdlib.h>

struct data
{
    int prior;
    data *next, *prev;
} *first, *last;

data *createNode(int prior)
{
    data *node = (data *)calloc(1, sizeof(data));
    node->prior = prior;
    return node;
}

data *insert(data *node)
{
    if (!first)
    {
        first = last = node;
    }
    else
    {
        data *curr = first;
        while (curr && curr->prior <= node->prior)
        {
            curr = curr->next;
        }
        if (curr)
        {
            data *before = curr->prev;
            before->next = node;
            node->next = curr;
            node->prev = before;
            curr->prev = node;
        }
        else{
            last->next = node;
            node->prev = last;
            last = node;
        }
    }
}

void removeQueue(){
    if(!first){
        return;
    }else if(first = last){
        free(first);
        first = last = NULL;
        puts("Successfully deleted!");
    }else{
        data *temp = first->next;
        first->next = temp->prev = NULL;
        first = temp;
        puts("Successfully deleted!");
    }
}

void display(){
    data *curr = first;
    while (curr)
    {
        printf("Prior: %d\n", curr->prior);
        curr = curr->next;
    }
    
}

int main()
{
    insert(createNode(3));
    insert(createNode(9));
    insert(createNode(11));
    // insert(createNode(12));
    // insert(createNode(9));
    // insert(createNode(5));
    display();
    // removeQueue();
    // display();
    return 0;
}