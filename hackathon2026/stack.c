//stack defintions
//programmer: Noah Julius

#include "stack.h"

bool isStackEmpty(StackStack* stack)
{
	assert(stack);//confirms stack exists
	return !stack->pHead;
}
StackNode* createStackNode(StackData item)
{
	StackNode* newNode = (StackNode*)malloc(sizeof(StackNode));
	assert(newNode);//confirm node exists

	strcpy(newNode->path, item.path);
	newNode->pNext = NULL;

	return newNode;
}
bool push(StackStack* stack, char* item)
{
	StackNode* newNode = createStackNode(item);

	if (!stack->pHead)
	{
		stack->pHead = newNode;
		return true;
	}
	newNode->pNext = stack->pHead;
	stack->pHead = newNode;
	stack->count++;
	return true;
}
bool pop(StackStack* stack)
{
	StackNode* next = stack->pHead->pNext;
	free(stack->pHead);
	stack->pHead = next;
	stack->count--;
	return true;
}
char* peek(StackStack* stack)
{
	return stack->pHead->path;
}