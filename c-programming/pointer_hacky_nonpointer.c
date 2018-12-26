#include <stdio.h>

int main()
{
    // printf("%u \t %u", sizeof(unsigned int), sizeof(int*));
    int i;

    char char_array[5] = {'a', 'b', 'c', 'd', 'e'};
    int int_array[5]   = {1, 2, 3, 4, 5};

    long unsigned int hack_nonpointer;

    hack_nonpointer = (long unsigned int) char_array;

    for (i = 0; i < 5; i++)
    {
        printf("[integer pointer] points to %p, which contains the char %c\n", hack_nonpointer, *((char *) hack_nonpointer));
        hack_nonpointer = hack_nonpointer + sizeof(char);
    }

    hack_nonpointer = (long unsigned int) int_array;

    for (i = 0; i < 5; i++)
    {
        printf("[char pointer] points to %p, which contains the int %d\n", hack_nonpointer, *((int *) hack_nonpointer));
        hack_nonpointer = hack_nonpointer + sizeof(int);
    }

    return 0;
}