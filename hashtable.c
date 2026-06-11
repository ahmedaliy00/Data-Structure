#include<stdio.h>
#include<stdlib.h>
void insert(int table[], int size, int key)
{
    int index = key % size;

    while(table[index] != -1)
    {
        index = (index + 1) % size;
    }

    table[index] = key;
}
int search(int table[], int size, int key)
{
    int index = key % size;
    int start = index;

    while(table[index] != -1)
    {
        if(table[index] == key)
            return index;
        index = (index + 1) % size;
        if (index == start)
            break; // We've looped through the entire table
    }

    return -1; // Not found
}
int main ()
{
    int size = 10;
    int table[10];
    for (int i = 0; i < size; i++) {
        table[i] = -1;
    }

    insert(table, size, 5);
    insert(table, size, 15);
    insert(table, size, 25);

    printf("Search for 15: %d\n", search(table, size, 15));
    printf("Search for 20: %d\n", search(table, size, 20));

    return 0;
}