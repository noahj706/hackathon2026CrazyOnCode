/*
	Programmer: Walker Raubuch
	Date Created: 2/21/2026
	Program Title: tree.h

	Description:
	A header file for a library that includes various functions for
	a tree structure. The tree structure contains any number of pointers
	to files and any number of pointers to other trees (in this case directories).
*/

// ------- INCLUDE LIBRARIES -------
#include "tree.h"

// ------- INCLUDE FUNCTIONS -------

/* Creates a node with the specified number of files and folders.
Precondition: numFiles and numFolders are both > 0, size of filenames is equal to or greater than numFiles in size */
Node* createNode(const char* filenames[], const int numFiles, const int numFolders)
{
	// Allocate space on the heap for a new node
	Node* pNew = malloc(sizeof(Node));

	// Check if space allocated successfully
	if (pNew)
	{
		// Save the number of files and folders
		pNew->numFiles = numFiles;
		pNew->numFolders = numFolders;

		// Allocate space for the number of files and folders specified
		pNew->pFiles = calloc(numFiles, sizeof(FILE*));
		pNew->pFolders = calloc(numFolders,sizeof(Node*));

		// Check to see if space was successfully allocated for the number of files and folders
		if (pNew->pFiles && pNew->pFolders)
		{
			for (int i = 0; i < numFiles; i++)
			{
				pNew->pFiles[i] = fopen(filenames[i], "w");
			}
		}
		else
		{
			// Free the other array
			if (pNew->pFiles) free(pNew->pFiles);
			if (pNew->pFolders) free(pNew->pFolders);

			// Free the node
			free(pNew);

			// Set pNew to be null
			pNew = NULL;
		}
	}

	// Return a pointer to pNew
	return pNew;
}

/* Inserts a node at the front of the tree with the specified number of
files and folders. Which folder in the new node directs to the rest of the tree
will be determined by the position inputted into the function. If insertion is
successful, then TRUE is returned, and FALSE otherwise. 
Precondition: numFiles and numFolders > 0 and 0 <= position < numFolders 
And size of filenames is equal to or greater than numFiles in size */
int insertAtFront(Node** pTree, const char* filenames[], const int numFiles, const int numFolders, const int position)
{
	// Create a new node
	Node* pNew = createNode(filenames,numFiles, numFolders);

	// Check if space allocated successfully
	if (!pNew) return FALSE;

	// 
	pNew->pFolders[position] = *pTree;
	*pTree = pNew;

	// Space allocated successfully
	return TRUE;

}

/* Checks to see if there are folders in the node. Returns TRUE if folders are present. Returns FALSE otherwise. */
int hasFolders(const Node* pNode)
{
	// If the node is null, it has no folders, return true
	if (!pNode) return FALSE;
	
	// Loop through all of the node's folders
	for (int i = 0; i < pNode->numFolders; i++)
	{
		// If a folder has been spotted from this node, it is not at the end
		if (pNode->pFolders[i])return TRUE;
	}

	// At the end
	return FALSE;
}

/* Checks to see if there are no folders in the node. Returns TRUE if files are present. Returns FALSE otherwise. */
int hasFiles(const Node* pNode)
{
	// If the node is null, it has no folders, return true
	if (!pNode) return FALSE;

	// Loop through all of the node's folders
	for (int i = 0; i < pNode->numFiles; i++)
	{
		// If a folder has been spotted from this node, it is not at the end
		if (pNode->pFiles[i])return TRUE;
	}

	// At the end
	return FALSE;
}

/* Prints out all the contents of a tree. */
void printTree(const Node* pNode, int numIterations)
{
	// Declare variables
	int numFilesFound = 0;
	int numFoldersFound = 0;

	if (pNode)
	{
		// Go through each file in the node.
		for (int i = 0; i < pNode->numFiles; i++)
		{
			// If the file is not null, print it to the console
			if (pNode->pFiles[i])
			{
				for (int j = 0; j < numIterations; j++) putchar('\t');
				printf("File %d: %p\n", i, pNode->pFiles[i]);
				numFilesFound++;
			}
		}

		// Go through each folder in the node.
		for (int i = 0; i < pNode->numFolders; i++)
		{
			if (pNode->pFolders[i])
			{
				for (int j = 0; j < numIterations; j++) putchar('\t');
				printf("Folder:\n");
				printTree(pNode->pFolders[i], numIterations + 1);
				numFoldersFound++;
			}
		}
	}
	if (numFilesFound == 0 && numFoldersFound == 0)
	{
		for (int j = 0; j < numIterations; j++) putchar('\t');
		printf("Empty\n");
	}
}