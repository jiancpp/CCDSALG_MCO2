#include <stdbool.h>
#include <string.h>

#include "stack.h"

/**
 * This function clears a stack by setting the top (last index) to -1.
 * @param stack the stack to be cleared
 */
void
clearStack (Stack *stack)
{
    stack->top = -1;
}

/**
 * This function checks if the stack is full based on the maximum capacity.
 * @param stack the stack to be checked if full
 * @return (a) true if stack is full;
 *         (b) false if stack is not full.
 */
bool
isFullStack (Stack *stack)
{
    if (stack->top == MAX_CAPACITY - 2) {
        return true;
    } else return false;
}

/**
 * This function checks if the stack is empty.
 * @param stack the stack to be checked if empty
 * @return (a) true if stack is empty;
 *         (b) false if stack has at least one element.
 */
bool
isEmptyStack (Stack *stack)
{
    if (stack->top == -1) {
        return true;
    } else return false;
}

/**
 * This function pops (removes) the element at the top of the stack and returns it.
 * @param stack the stack to be popped
 * @return popped element 
 */
char*
popStack (Stack *stack)
{
    char *temp = stack->collection[stack->top];
    (stack->top)--;
    
    return temp;
}

/**
 * This function pushes (inserts) an item to the stack.
 * @param stack stack to be added on
 * @param item element to be pushed to the stack
 */
void
pushStack (Stack *stack, char* item)
{
    (stack->top)++;
    strcpy(stack->collection[stack->top], item);
}

/**
 * This function returns the element at the top of the stack.
 * @param stack stack to be peeked
 * @return element at the top of the stack
 */
char*
peekStack (Stack *stack)
{
    return stack->collection[stack->top];
}
