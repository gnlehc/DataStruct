#include <stdio.h>
#include <string.h>
#include <stdlib.h>

struct Book{
    char title[50];
    int stock;
    int price;
};

int main(){
    // pointer
    int a = 10;
    printf("%d\n", a);
    int *p = &a;
    *p = 9; // value changes
    printf("%d\n", p); // alamat var a
    printf("%d\n", *p); // 9

    char b = 'b';
    char *pb = &b;

    printf("%d\n", pb); // alamat var b
    printf("%c\n", *pb); // b

    int nums[10] = {1,2,3,4};
    printf("%d\n", &nums[0]);
    printf("%d\n", &nums[1]);

    printf("%d\n", *nums);
    printf("%d\n", *(nums+1));

    // ===================================
    Book book1;
    book1.price = 10000;
    printf("%d\n", book1.price);
    strcpy(book1.title,"Narnia");

    // Array of struct
    Book books[10];
    // books[0].price = 10000;
    // strcpy(books[0].title, "narnia");
    // books[0].stock = 5;
    // int i;
    // while(true){
    //     char titleInput[50];
    //     int stockInput;
    //     int priceInput;
    //     printf("Stock: ");
    //     scanf("%d", &stockInput); getchar();
    //     printf("Price: ");
    //     scanf("%d", &priceInput); getchar();
    //     printf("Title: ");
    //     scanf("&[^\n]", &titleInput); getchar();

    //     i = 0;
    //     books[i].price = priceInput;
    //     books[i].stock = stockInput;
    //     strcpy(books[i].title, titleInput);
        
    //      strcpy(books[0].title, "Updated");
    //       for(int j = 0 ; j <= i ; j++){
    //             printf("Name: %s\n", books[j].title);
    //             printf("Price: %d\n", books[j].price);
    //             printf("Stock: %d\n", books[j].stock);
    //         }
    // }

    Book *bookTemp = (Book *)malloc(sizeof(Book));
    bookTemp->price = 10;
    printf("%d", bookTemp->price);

   

    






    return 0;
}