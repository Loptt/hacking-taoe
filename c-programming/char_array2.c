#include <stdio.h>
#include <string.h>

int sum(int a, int b)
{
    return a + b;
}

int main()
{
    char str_a[20];

    strcpy(str_a, "Hello, world!\n");
    printf(str_a);
    printf("%d", sum(1,2));
    return 0;
}