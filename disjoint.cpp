#include <stdio.h>

// hindarin looping
// tiap index array mewakili valuenya sendiri
// jadi kalo index 0 valuenya jg 0 berarti parent 0 masih nunjuk diri nya sendiri
// setiap node itu parentnya nunjuk diri sendiri
// nanti parent bakal diubah ubah sesuai root
// union (gabungin) butuh operasi find

int parent[100];

void makeSet(int size)
{
    for (int i = 0; i < size; i++)
    {
        parent[i] = i;
    }
}

int findParent(int x)
{
    if (parent[x] != x)
    {
        parent[x] = findParent(parent[x]);
    }
    return parent[x];
}

void unionSet(int x, int y)
{
    int rootX = findParent(x);
    int rootY = findParent(y);

    if (rootX != rootY)
    {
        parent[y] = rootX;
    }
    else
    {
        puts("Cyclick");
    }
}

int main()
{
    makeSet(5);

    unionSet(1, 2);
    unionSet(2, 3);
    unionSet(1 , 3);
    printf("Parent 3: %d\n", parent[3]);

    return 0;
}