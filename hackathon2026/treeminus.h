/*
	Programmer: Walker Raubuch
	Date Created: 2/22/2026
	Program Title: treeminus.h

	Description:
	A header file for a library that includes various functions for
	a tree structure. The tree structure contains any number of pointers
	to files and any number of pointers to other trees (in this case directories).
*/

// ------- IMPLEMENT GUARD CODE -------
#ifndef TREEMINUS_H
#define TREEMINUS_H

// ------- DEFINE WARNINGS -------
#define _CRT_SECURE_NO_WARNINGS

// ------- INCLUDE LIBRARIES -------
#include <stdio.h>
#include <stdlib.h>
#include <direct.h>
#include <time.h>

// ------- DEFINE STRUCTS -------

typedef struct data
{
	char dirName[500];
	char fileName1[50];
	char fileName2[50];
}Data;

typedef struct node
{
	struct node* pNext1;
	struct node* pNext2;
	struct node* pNext3;
	Data item;
}Node;

typedef struct tree
{
	Node* pHead;
} Tree;

// ------- DEFINE FUNCTIONS -------

/* Creates a new node struct on the heap. */
Node* createNode(const Data* pData);

// Prints data
void printData(const Data* pData);

/* Prints out all the contents of a tree. */
void printTree(const Node* pTree, int numIterations);

void generateTree(Node** pHead, const Data* pData, int depth);

// ------- END GUARD CODE -------
#endif
