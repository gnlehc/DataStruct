#include <stdio.h>
#include <limits.h>

int heap[100] = {INT_MIN};
int size = 0;

int parentIndex(int index)
{
    return index / 2;
}

void swap(int index_1, int index_2)
{
    int val = heap[index_1];
    heap[index_1] = heap[index_2];
    heap[index_2] = val;
}

void insert(int value)
{
    size++;
    heap[size] = value;
    int curr = size;
    // selama anaknya lebih kacil kita swap ke atas
    while (heap[curr] < heap[parentIndex(curr)])
    {
        swap(curr, parentIndex(curr));
        curr = parentIndex(curr);
    }
}

void printHeap()
{
    for (int i = 1; i <= size / 2; i++)
    {
        int leftIndex = i * 2;
        int rightIndex = i * 2 + 1;
        if (rightIndex > size)
        {

            printf("Current: %d, Left Child: %d", heap[i], heap[leftIndex]);
        }
        else
        {
            printf("Current: %d, Left Child: %d, Right Child: %d\n", heap[i], heap[leftIndex], heap[rightIndex]);
        }
    }
}

int GET_MIN()
{
    return heap[1];
}

int left_value(int index)
{
    int left_index = index * 2;
    // karena left child itu ada setiap +2, jadi mulai dari index 1, 1 + 2 = 3 -> left
    if (left_index > size)
    {
        // left child doesnt exists
        return INT_MAX;
    }
    else
    {
        // left child exists
        return heap[index * 2];
    }
}

int right_value(int index)
{
    int right_index = index * 2 + 1;
    // karena right child itu ada setiap +1 dari left child
    if (right_index > size)
    {
        // left child doesnt exists
        return INT_MAX;
    }
    else
    {
        // left child exists
        return heap[right_index];
    }
}

void heapify(int curr)
{
    int val = heap[curr];
    int left_val = left_value(curr);
    int right_val = right_value(curr);
    if (val > left_val || val > right_val)
    {
        if (left_val < right_val)
        {
            swap(curr, curr * 2);
            heapify(curr * 2);
            // tuker anak kiri
            // swap sm bagian kirinya
        }
        else
        {
            // swap sm bagian kananya
            swap(curr, curr * 2 + 1);
            heapify(curr * 2 + 1);

            // tuker anak kanan
        }
    }
}

int extract()
{
    // ambil root dari tree
    int value = heap[1];
    heap[1] = heap[size];
    size--;
    heapify(1);
    return value;
}

int main()
{
    insert(10);
    insert(5);
    insert(12);
    insert(20);
    insert(7);
    // GET_MIN();
    printHeap();
    puts("");
    printf("ROOT: %d\n", extract());
    puts("");
    printHeap();
    puts("");
    puts("");
    printf("ROOT: %d\n", extract());
}