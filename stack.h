#ifndef STACK_H
#define STACK_H

#define CAPACITY (256);

#include "shared.h"
#include "linkedListGraph.h"

typedef struct {
    Vertex collection[256];
    int top; // index of last added element
} Stack;

void        clearStack      (Stack *stack);
bool        isFullStack     (Stack *stack);
bool        isEmptyStack    (Stack *stack);
char*       popStack        (Stack *stack);
void        pushStack       (Stack *stack, char* item);
char*       peekStack       (Stack *stack);

#endif
