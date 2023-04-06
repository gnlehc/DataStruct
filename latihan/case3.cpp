#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<conio.h>

struct hospital
{
    char name[26];
    int age;
    char desc[255];
    
}*head, *tail;

void menu(){
    puts("Bluejack Hospital");
    puts("===================");
    puts("1. Insert");
    puts("2. View");
    puts("3. Next Queue");
    puts("4. Exit");
    printf(">>> ");
}

int main(){
    menu();
    int chs;
    scanf("%d", &chs);
    switch (chs)
    {
    case 1:
        break;
    
    default:
        break;
    }
    return 0;
}