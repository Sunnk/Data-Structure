#ifndef _STACK_H_
#define _STACK_H_

#include "slist.h"

typedef struct{
    SList *slist;
}Stack;

Stack *stack_create(void);
Ret stack_push(Stack *stack, void *data);
Ret stack_pop(Stack *stack, void **data);
Ret stack_get_top(Stack *stack, void **data);
int32_t stack_count_depth(Stack *stack);
void stack_destroy(Stack *stack);

#endif // _STACK_H_
