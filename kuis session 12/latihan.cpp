#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct itol
{
    char title[255];
    char genre[255];
    int stock;
    int height, bf;
    int key;
    itol *left, *right;
};

int max(int a, int b)
{
    return (a > b) ? a : b;
}

int treeHeight(itol *root)
{
    return root ? root->height : 0;
}

int setHeight(itol *root)
{
    return root ? (max(treeHeight(root->left), treeHeight(root->right)) + 1) : 0;
}

int setBalanceFactor(itol *root)
{
    return root ? (treeHeight(root->left) - treeHeight(root->right)) : 0;
}

itol *update(itol *root)
{
    if (!root)
    {
        return root;
    }
    root->height = setHeight(root);
    root->bf = setBalanceFactor(root);
    return root;
}

itol *rightRotation(itol *curr)
{
    itol *pivot = curr->left;
    itol *rightChild = pivot->right;

    pivot->right = curr;
    curr->left = rightChild;
    curr = update(curr);
    pivot = update(pivot);
    return pivot;
}

itol *leftRotation(itol *curr)
{
    itol *pivot = curr->right;
    itol *leftChild = pivot->left;

    pivot->left = curr;
    curr->left = leftChild;
    curr = update(curr);
    pivot = update(pivot);
    return pivot;
}

itol *rotate(itol *curr)
{
    if (!curr)
    {
        return curr;
    }
    else if (curr->bf > 1 && curr->left->bf >= 0)
    {
        return rightRotation(curr);
    }
    else if (curr->bf < -1 && curr->right->bf <= 0)
    {
        return leftRotation(curr);
    }
    else if (curr->bf < -1 && curr->right->bf > 0)
    {
        curr->right = rightRotation(curr->right);
        return leftRotation(curr);
    }
    else if (curr->bf > 1 && curr->left->bf < 0)
    {
        curr->left = leftRotation(curr->left);
        return rightRotation(curr);
    }

    return curr;
}

itol *createNode(char title[], char genre[], int stock)
{
    itol *node = (itol *)malloc(sizeof(itol));
    strcpy(node->title, title);
    strcpy(node->genre, genre);
    node->stock = stock;
    node->height = 1;
    node->bf = 0;
    int temp = 0;
    int temp2 = 0;
    // for(int i = 0 ; i < strlen(root->title); i++){
    //     temp += root->title[i];
    // }
    for (int j = 0; j < strlen(title); j++)
    {
        temp2 += title[j];
    }

    node->key = temp2;

    node->right = node->left = NULL;
    return node;
}

itol *insert(itol *root, itol *data)
{
    // if (!root)
    // {
    //     return createNode(data->title, data->genre, data->stock);
    // }
    // else if (data->stock < root->stock)
    // {
    //     root->left = insert(root->left, createNode(data->title, data->genre, data->stock));
    // }
    // else if (data->stock > root->stock)
    // {
    //     root->right = insert(root->right, createNode(data->title, data->genre, data->stock));
    // }
    // int newtitle = strlen(data->title);
    // int roottitle = strlen(root->title);
    // int temp1 = 0;
    // int temp2 = 0;

    // for (int i = 0; i < roottitle; i++)
    // {
    //     temp1 += root->title[i];
    // }
    // for (int j = 0; j < newtitle; j++)
    // {
    //     temp2 += data->title[j];
    // }
    if (!root)
    {
        return createNode(data->title, data->genre, data->stock);
    }
    else if (strcmp(root->title, data->title) < 0)
    {
        root->left = insert(root->left, createNode(data->title, data->genre, data->stock));
    }
    else if (strcmp(root->title, data->title) > 0)
    {
        root->right = insert(root->right, createNode(data->title, data->genre, data->stock));
    }

    // if (!root)
    // {
    //     return createNode(data->title, data->genre, data->stock);
    // }
    // else if (data->key < root->key)
    // {
    //     root->left = insert(root->left, createNode(data->title, data->genre, data->stock));
    // }
    // else if (data->key > root->key)
    // {
    //     root->right = insert(root->right, createNode(data->title, data->genre, data->stock));
    // }
    // return rotate(update(root));
    // return root;
}

itol *updateNode(itol *root, itol *data)
{
    
}

bool search(itol *root, char title[])
{
    if (!root)
    {
        return false;
    }
    else if (strcmp(root->title, title) < 0)
    {
        return search(root->left, title);
    }
    else if (strcmp(root->title, title) > 0)
    {
        return search(root->right, title);
    }
    else if (strcmp(root->title, title) == 0)
    {
        return true;
    }
    return false;
}


void case1();
void case2();
void case3();
void inOrder(itol *root)
{
    if (root)
    {
        inOrder(root->left);
        printf("Title: %-20s\n", root->title);
        printf("Genre: %-20s\n", root->genre);
        printf("Stock: %-20d\n", root->stock);
        inOrder(root->right);
    }
}
void postOrder(itol *root)
{
    if (root)
    {
        postOrder(root->left);
        postOrder(root->right);
        printf("Title: %-20s\n", root->title);
        printf("Genre: %-20s\n", root->genre);
        printf("Stock: %-20d\n", root->stock);
    }
}
void preOrder(itol *root)
{
    if (root)
    {
        printf("Title: %-20s\n", root->title);
        printf("Genre: %-20s\n", root->genre);
        printf("Stock: %-20d\n", root->stock);
        preOrder(root->left);
        preOrder(root->right);
    }
}

itol *root = NULL;
void Menu()
{
    int chs;
    puts("BlueJack GShop");
    puts("===============");
    puts("1. Insert Game");
    puts("2. View Game");
    puts("3. Update Stock");
    puts("4. Exit");
    printf(">> ");
    scanf("%d", &chs);
    getchar();
    switch (chs)
    {
    case 1:
        case1();
        break;
    case 2:
        case2();
        break;
    case 3:
        case3();
        break;
    case 4:
        exit;
        break;
    default:
        break;
    }
}

void case3()
{
    char title[255];
    int stock = 0;
    int chs = 0;
    printf("Input game title: ");
    scanf("%[^\n]", &title);
    getchar();
    if (search(root, title) == false)
    {
        puts("Data not found");
    }

    printf("Press enter to continue...");
    getchar();
    system("cls");
    puts("1. Add new game");
    puts("2. Update game");
    printf("Choose between 2 options");
    scanf("%d", &chs);
    getchar();

    switch (chs)
    {
    case 1:
        case1();
        break;
    case 2:
        printf("Enter the new stock: ");
        scanf("%d", &stock);
        getchar();
        // root = insert(root)
        break;
    default:
        break;
    }
    Menu();
}

void case2()
{
    inOrder(root);
    // postOrder(root);
    // preOrder(root);
    Menu();
}
void case1()
{

    char title[255] = {};
    char type[255] = {};
    int stock = 0;
    int lenType = strlen(type);
    int skipspace = 0;
    bool isntunique = search(root, title);

    while (skipspace < 5 || skipspace > 25 || search(root, title))
    {
        title[255] = {0};
        printf("Input Game title[5-25][unique]: ");
        scanf("%[^\n]", &title);
        skipspace = 0;
        getchar();
        int len = strlen(title);
        for (int i = 0; i < len; i++)
        {
            if ((title[i] >= 'a' && title[i] <= 'z') || (title[i] >= 'A' && title[i] <= 'Z' || (title[i] >= '0' && title[i] <= '9')))
            {
                skipspace++;
            }
        }
        // printf("skipspace: %d\n", skipspace);
    }
    while (strcmp(type, "Action") != 0 && strcmp(type, "RPG") != 0 && strcmp(type, "Adventure") != 0 && strcmp(type, "Card Game") != 0)
    {
        printf("Input Game Type[Action|RPG|Adventure|Card Game]: ");
        scanf("%[^\n]", &type);
        getchar();
    }
    while (stock < 1)
    {
        printf("Input Game Stock[>=1]: ");
        scanf("%d", &stock);
        getchar();
    }

    root = insert(root, createNode(title, type, stock));
    puts("Insert Success!");
    Menu();
}

int main()
{
    Menu();
    return 0;
}