#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct data
{
    char rnd;
    data *next;
} *head, *tail;

data *createNode(char rnd)
{
    data *node = (data *)malloc(sizeof(data));
    node->rnd = rnd;
    node->next = NULL;
    return node;
}

void pushHead(char rnd)
{
    data *node = createNode(rnd);
    if (!head)
    {
        head = tail = node;
    }
    else
    {
        node->next = head;
        head = node;
    }
}

void print()
{
    data *curr = head;
    while (curr)
    {
        printf("%c", curr->rnd);
        curr = curr->next;
    }
    puts("");
}

int main()
{
    char rnd[255] = {0};
    int simpen = 0;
    int size = 0;
    while (simpen < 4)
    {
        printf("Input Sentence [minimum 5 words]: ");
        scanf("%[^\n]", &rnd);
        getchar();
        size = strlen(rnd);
        for (int i = 0; i < size; i++)
        {
            if (rnd[i] == ' ')
            {
                simpen ++;
            }
            else
            {
                simpen += 0;
            }
        }
    }
        for (int j = 0; j < size; j++)
        {
            pushHead(rnd[j]);
        }
        print();
        char chs[25];
        printf("Do You Want to Continue[yes|no]? ");
        scanf("%[^\n]", &chs);
        if(strcmp(chs, "yes") == 0 || strcmp(chs, "y") == 0){
        while (simpen < 4)
    {
        printf("Input Sentence [minimum 5 words]: ");
        scanf("%[^\n]", &rnd);
        getchar();
        size = strlen(rnd);
        for (int i = 0; i < size; i++)
        {
            if (rnd[i] == ' ')
            {
                simpen ++;
            }
            else
            {
                simpen += 0;
            }
        }
    }
        for (int j = 0; j < size; j++)
        {
            pushHead(rnd[j]);
        }
        print();
        }

    return 0;
}