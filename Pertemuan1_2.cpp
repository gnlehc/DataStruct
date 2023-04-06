#include <stdio.h>
#include <string.h>

struct tdata{
    int age;
    char name[100];
    float score;
}a,b;

struct profile{
    int age;
    char name[100];
};

struct student{
    struct profile p;
    int score;
    int grade;
};

int main(){
    tdata x;
    x.age = 17;
    strcpy(x.name,"andi");
    x.score = 82.5;
    return 0;
}