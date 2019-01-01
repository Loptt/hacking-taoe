#include <stdio.h>

int func_one()
{
    printf("This is function one\n");
    return 1;
}

int func_two()
{
    printf("This is function two\n");
    return 2;
}

int main(int argc, char const *argv[])
{
    int value;
    int (*function_ptr) ();

    function_ptr = func_one;
    printf("function_ptr is %p\n", function_ptr);
    value = function_ptr();
    printf("value returned was %d\n", value);

    function_ptr = func_two;
    printf("function_ptr is %p\n", function_ptr);
    value = function_ptr();
    printf("value returned was %d\n", value);

    return 0;
}