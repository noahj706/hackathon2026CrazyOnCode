/*
	Programmer: Walker Raubuch
	Date Created: 2/21/2026
	Program Title: tree.h
	
	Description:
	A header file for a library that includes various functions for
	a tree structure. The tree structure contains any number of pointers
	to files and any number of pointers to other trees (in this case directories).
*/

// ------- IMPLEMENT GUARD CODE -------
#ifndef TREE_H
#define TREE_H

// ------- DEFINE WARNINGS -------
#define _CRT_SECURE_NO_WARNINGS

// ------- INCLUDE LIBRARIES -------
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

// ------- DEFINE STRUCTS -------

/* Defines a node struct. */
typedef struct node
{
	int numFiles; // The number of files in the node.
	int numFolders; // The number of folders in the node.
	FILE** pFiles; // An array of pointers to files of the node.
	struct node** pFolders; // An array of pointers to folders of the node.
} Node;

// ------- DEFINE FUNCTIONS -------

/* Creates a node with the specified number of files and folders.
Precondition: numFiles and numFolders are both > 0 */
Node* createNode(const char* filenames[], const int numFiles, const int numFolders);

/* Inserts a node at the front of the tree with the specified number of
files and folders. Which folder in the new node directs to the rest of the tree
will be determined by the position inputted into the function. If insertion is
successful, then TRUE is returned, and FALSE otherwise.
Precondition: numFiles and numFolders > 0 and 0 <= position < numFolders */
int insertAtFront(Node** pTree, const char* filenames[], const int numFiles, const int numFolders, const int position);

/* Checks to see if there are no folders in the node. Returns TRUE if
no folders are present. Returns FALSE otherwise. */
int hasFolders(const Node* pNode);

/* Prints out all the contents of a tree. */
void printTree(const Node* pNode, int numIterations);

// ------- END GUARD CODE -------
#endif