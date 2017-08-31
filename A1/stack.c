#include <studio.h>
#include "stack.h"

stackT *NewStack(void)
{
	struct stackT *newStackPtr = new stackT;
	newStackPtr->head = NULL;
	return newStackPtr;
}

void Push(stackT *stack, valueT value)
{
	struct nodeT *newNode = new nodeT;
	newNode->value = value;
	if (stack->head == NULL)
	{
		stack->head = newNode;
		newNode->next = NULL;
	}
	else
	{
		newNode->next = head;
		head = newNode;
	}
}

valueT Pop(stackT *stack)
{
	if (stack->head == NULL)
	{
		printf("Error: Nothing can be popped because this is an empty stack.")
			return '0';
	}
	else
	{
		tempNode = stack->head;
		stack->head = head->next;
		delete tempNode;
	}
}

void EmptyStack(stackT *stack)
{
	if (stack->head == NULL)
	{
		printf("Error: The stack is empty.")
		return 0;
	}
	else
	{
		struct nodeT *currNode = stack->head;
		while (currNode->next != NULL)
		{
			struct nodeT *tempNode = currNode;
			currNode = currNode->next;
			delete tempNode;
		}
		delete currNode; // delete the last node in the stack
		stack->head = NULL;
	}
}

void FreeStack(stackT *stack)
{
	if (stack->head != NULL)
	{
		printf("Error: The stack cannot be free because it is not an empty stack.");
		return 0;
	}
	else
	{
		stack->head = NULL;
		delete stack;
	}
}

bool IsEmpty(stackT *stack)
{
	return (stack->head != NULL);
}
