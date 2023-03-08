#include <stdio.h>
// hello iseng
int main(){
    int x;
    int *px;
    px = &x;
    x = 10;
    *px = 20;
    printf("%d\n", x);
    printf("%d\n", px); 
    printf("%d\n", *px); 
    printf("%d\n", &x); 

    int y = 10;
    int *py, **ppy;
    py = &y;
    ppy = &py;

    int z = 10;
    int *pz = &z;
    int **ppz = &pz;
    printf("z = %d\n", z);
    printf("&z = %d\n", &z);
    printf("pz = %d\n", pz);
    printf("*pz = %d\n", *pz);
    printf("&pz = %d\n", &pz);
    printf("ppz = %d\n", ppz);
    printf("*ppz = %d\n", *ppz);
    printf("**ppz = %d\n", **ppz);

    int arr[5] = {80,90,30,40,50};
    printf("%d\n",*(arr+1)); // cetak index ke 1
    // constant pointer itu index 0 -> *arr bakal cetak index ke 0 yaitu 80
    printf("%d\n",*arr); //80
    printf("%d\n", arr); // address index ke 0
    printf("%d\n", (arr+1)); // address index ke 1
    return 0;
}

