//stack header file
//programmer: Noah Julius

#ifndef STACK_H
#define STACK_H

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include <string.h>

//stackNode that'll hold a pathdata string for the directory making stuff
typedef struct stackData
{
	char* path;
	Node* treePos;
}StackData;
typedef struct stackNode
{
	StackData stackItem;
	struct stackNode* pNext;
}StackNode;
//stack node
typedef struct stackStack
{
	StackNode* pHead;
	int count;
}StackStack;

bool isStackEmpty(StackStack* stack);
StackNode* createStackNode(char* pathData);
bool push(StackStack* stack, char* pathData);
bool pop(StackStack* stack);
char* peek(StackStack* stack);



#endif