#include <stdio.h>
#include <stdlib.h>

int global_var;
int global_initialized_var = 5;

void function()
{
    int stack_var;

    printf("The function's stack_var is at address %p\n", &stack_var);
}

int main()
{
    int stack_var;
    static int static_initialized_var = 5;
    static int static_var;
    int *heap_var_ptr;

    heap_var_ptr = (int *) malloc(4);

    //Data segment
    printf("global_initialized_var is at address %p\n", &global_initialized_var);
    printf("static_initialized_var is at address %p\n\n", &static_initialized_var);

    //BSS segment
    printf("static_var is at address %p\n", &static_var);
    printf("global_var is at address %p\n\n", &global_var);

    //Heap segment
    printf("heap_var is at address %p\n\n", heap_var_ptr);

    //Stack segment
    printf("stack_var is at address %p\n", &stack_var);
    function();

    return 0;
}