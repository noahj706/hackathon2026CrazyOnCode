/*
	Programmer: Walker Raubuch
	Date Created: 2/22/2026
	Program Title: tree.h

	Description:
	A header file for a library that includes various functions for
	a tree structure. The tree structure contains any number of pointers
	to files and any number of pointers to other trees (in this case directories).
*/

#include "treeminus.h"

/* Creates a new node struct on the heap. */
Node* createNode(const Data* pData)
{
	// Allocate space for node
	Node* pNew = malloc(sizeof(Node));

	// If success
	if (pNew)
	{
		pNew->pNext1 = NULL;
		pNew->pNext2 = NULL;
		pNew->pNext3 = NULL;
		strcpy(pNew->item.dirName, pData->dirName);
		strcpy(pNew->item.fileName1, pData->fileName1);
		strcpy(pNew->item.fileName2, pData->fileName2);
	}

	// Return pointer
	return pNew;
}

// Prints data
void printData(const Data* pData)
{
	printf("Directory name: %s\n", pData->dirName);
	printf("File Name 1: %s\n", pData->fileName1);
	printf("File Name 2: %s\n\n", pData->fileName2);
}

/* Prints out all the contents of a tree. */
void printTree(const Node* pTree, int numIterations)
{
	if (pTree)
	{
		// Print out the initial node
		for (int i = 0; i < numIterations; i++) putchar('\t');
		printData(&(pTree->item));

		// Check each of the branches
		if (pTree->pNext1) printTree(pTree->pNext1, numIterations + 1);
		if (pTree->pNext2) printTree(pTree->pNext2, numIterations + 2);
		if (pTree->pNext3) printTree(pTree->pNext3, numIterations + 3);
	}
}


void generateTree(Node** pHead, const Data* pData, int depth)
{
	// Instantiate booleans
	int numChosen = 0;
	int numSeen = 0;

	// Create an array of chosen pointers
	Node* chosenPointers[3] = { NULL };

	// Create a node if there isn't one already
	if (!*pHead)
	{
		*pHead = createNode(pData);
	}

	// Check if the list is empty, if so add a node
	if (depth > 0) // If the head node is not null
	{
		do // Validate these datums until at least one is active
		{
			// Create nodes for up to three of the pointers
			if (rand() % 2)
			{
				(*pHead)->pNext1 = createNode(pData);
				chosenPointers[numChosen] = (*pHead)->pNext1;
				numChosen++;
			}
			if (rand() % 2)
			{
				(*pHead)->pNext2 = createNode(pData);
				chosenPointers[numChosen] = (*pHead)->pNext2;
				numChosen++;
			}
			if (rand() % 2)
			{
				(*pHead)->pNext3 = createNode(pData);
				chosenPointers[numChosen] = (*pHead)->pNext3;
				numChosen++;
			}
		} while (numChosen == 0);
		
		// Check which of the branches are available
		int chosen = rand() % numChosen;

		// Randomly pick which of the chosen pointers will be added
		Node** chosenPointer = &chosenPointers[chosen];

		// Advance to the next tree
		generateTree(chosenPointer, pData, depth - 1);
	}

}


