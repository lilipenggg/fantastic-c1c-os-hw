#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

stackT *NewStack(void)
{
    stackT *newStackPtr = malloc(sizeof(stackT));
    newStackPtr->head = NULL;
    return newStackPtr;
}

void Push(stackT *stack, valueT value)
{
    nodeT *newNode = malloc(sizeof(nodeT));
    newNode->value = value;
    if (stack->head == NULL)
    {
        stack->head = newNode;
        newNode->next = NULL;
    }
    else
    {
        newNode->next = stack->head;
        stack->head = newNode;
    }
}

valueT Pop(stackT *stack)
{
    if (stack->head == NULL)
    {
        printf("Error: Nothing can be popped because this is an empty stack.\n");
        return 0;
    }
    else
    {
        valueT tempVal = stack->head->value;
        nodeT *tempNode = stack->head;
        stack->head = stack->head->next;
        free(tempNode);
        return tempVal;
    }
}

void EmptyStack(stackT *stack)
{
    if (stack->head == NULL)
    {
        printf("Error: The stack is empty.\n");
    }
    else
    {
        nodeT *currNode = stack->head;
        while (currNode->next != NULL)
        {
            nodeT *tempNode = currNode;
            currNode = currNode->next;
            free(tempNode);
        }
        free(currNode); // delete the last node in the stack
        stack->head = NULL;
    }
}

void FreeStack(stackT *stack)
{
    if (stack->head != NULL)
    {
        printf("Error: The stack cannot be free because it is not an empty stack.\n");
    }
    else
    {
        free(stack);
    }
}

bool IsEmpty(stackT *stack)
{
    bool flag = true;
    if(stack->head != NULL)
    {
        flag = false;
        return flag;
    }
    return flag;
}
