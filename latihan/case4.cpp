#include <stdio.h>
#include <string.h>
#include <stdlib.h>
// hash table chaining

#define SIZE 1007
struct library
{
    char name[35];
}*head[SIZE], *tail[SIZE];
int chs = 0;

int simpen = 0;
void print()
{
    for(int i = 0; i < SIZE; i++){
        if(!head[i]){
            simpen += 0;
        }

        library *curr = head[i];
        while(curr) {
            printf("%s\n", curr->name);
        }
    }
}

void Menu()
{
    puts("Bluejack Library");
    puts("===================");
    puts("1. View Book");
    puts("2. Insert Book");
    puts("3. Remove Book");
    puts("4. Exit");
    printf(">>> ");
    scanf("%d", &chs);
    switch (chs)
    {
    case 1:

        break;

    default:
        break;
    }
}

int main()
{
    return 0;
}