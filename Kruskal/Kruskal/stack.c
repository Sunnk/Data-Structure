#include "stack.h"

Stack *stack_create(void)
{
    Stack *stack = (Stack *)malloc(sizeof(Stack));
    return_val_if_fail(stack != NULL, NULL);

    stack->slist = slist_create();
    if(stack->slist == NULL){
        free(stack);
        return_val_if_fail(stack->slist != NULL, NULL);
    }

    return stack;
}

Ret stack_push(Stack *stack, void *data)
{
    return_val_if_fail(stack != NULL, RET_INVALID_ARGUMENT);

    return slist_prepend(stack->slist, data);
}

Ret stack_pop(Stack *stack, void **data)
{
    return_val_if_fail(stack != NULL, RET_INVALID_ARGUMENT);

    return slist_delete(stack->slist, 0, data);
}

Ret stack_get_top(Stack *stack, void **data)
{
    return_val_if_fail(stack != NULL, RET_INVALID_ARGUMENT);
    return_val_if_fail(data != NULL, RET_INVALID_ARGUMENT);

    return slist_get_nth_data(stack->slist, 0, data);
}

int32_t stack_count_depth(Stack *stack)
{
    return_val_if_fail(stack != NULL, -1);

    return slist_count_length(stack->slist);
}

void stack_destroy(Stack *stack)
{
    return_if_fail(stack != NULL);

    slist_destroy(stack->slist);
    free(stack);
}

