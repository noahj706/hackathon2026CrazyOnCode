/*
	Programmer: Walker Raubuch
	Date Created: 2/21/2026
	Program Title: tree.h

	Description:
	A header file for a library that includes various functions for
	a tree structure. The tree structure contains any number of pointers
	to files and any number of pointers to other trees (in this case directories).
#include "gui.h"
#include "parent.h"
FolderNode* createNode(char* name)
{
    struct FolderNode* newNode = (struct FolderNode*)malloc(sizeof(struct FolderNode));
    if (newNode == NULL) 
    {
        printf("Memory allocation failed\n");
        return NULL;
    }
    strcpy(newNode->name, name);
    newNode->children = NULL; 
    newNode->numberOfChildren = 0;
    return newNode;
}

void addChild(struct FolderNode* parent, struct FolderNode* child)
{
    if (parent == NULL || child == NULL)
    {
        return;
    }

    parent->numberOfChildren++;
    parent->children = (struct FolderNode*)realloc(parent->children, parent->numberOfChildren * sizeof(FolderNode*));
    if (parent->children == NULL) 
    {
        printf("Memory reallocation failed\n");
        parent->numberOfChildren--;
        return;
    }
    parent->children[parent->numberOfChildren - 1] = child;
}

void createFolders(struct FolderNode* root, char* parentPath)
{
    if (root == NULL)
    {
        return;
    }

    char currentPath[256];
    sprintf(currentPath, "%s/%s", parentPath, root->name);

    if (_mkdir(currentPath) == 0) 
    {
        printf("Created: %s\n", currentPath);
    }
    else 
    {
        printf("Failed to create or already exists: %s\n", currentPath);
    }

    for (int i = 0; i < root->numberOfChildren; i++)
    {
        createFolders(root->children[i], currentPath);
    }
}

// Create an array of first depth nodes
FolderNode** createFirstDepthNodes(int count) 
{
    FolderNode** nodes = (FolderNode**)malloc(count * sizeof(FolderNode*));
    if (nodes == NULL) 
    {
        printf("Memory allocation failed\n");
        return NULL;
    }

    char folderName[50];
    for (int i = 0; i < count; i++) 
    {
        sprintf(folderName, "Feature_%d", i + 1);
        nodes[i] = createNode(folderName);
    }

    return nodes;
}

// Clean up first depth nodes
void destroyFirstDepthNodes(FolderNode** nodes, int count) 
{
    if (nodes == NULL)
    {
        return;
    }

    for (int i = 0; i < count; i++) 
    {
        freeFolderTree(nodes[i]);  // This will free the node and its children
    }
    free(nodes);
}

void connectRootToFirstDepth(FolderNode* root, FolderNode* firstDepthNodes[], int numberOfFirstDepthNodes)
{
    if (root == NULL)
    {
        return 1;
    }

    // Clear existing children if any
    if (root->children != NULL)
    {
        free(root->children);
        root->children = NULL;
    }
    root->numberOfChildren = 0;

    // Add each first depth node as a child of root
    for (int i = 0; i < numberOfFirstDepthNodes; i++)
    {
        addChild(root, firstDepthNodes[i]);
    }
}

void freeFolderTree(FolderNode* node) 
{
    if (node == NULL) return;

    for (int i = 0; i < node->numberOfChildren; i++) 
    {
        freeFolderTree(node->children[i]);
    }

    free(node->children);
    free(node);
}

void test_folders()
{
    int userChoice;
    int firstDepthCount;
    FolderNode* root = createNode("Projekt");

    /*printf("Choose folder structure size:\n");
    printf("1. Small (3 first-depth folders)\n");
    printf("2. Medium (5 first-depth folders)\n");
    printf("3. Large (7 first-depth folders)\n");
    printf("Enter your choice (1-3): ");
    scanf("%d", &userChoice);*/

    // Determine first depth count based on user choice
    switch (buttonMenu())
    {
    case SMALL:
        firstDepthCount = 5;
        break;
    case MEDIUM:
        firstDepthCount = 10;
        break;
    case LARGE:
        firstDepthCount = 15;
        break;
    case ZERO:
        freeFolderTree(root);
        return 0;
        break;
    default:
        printf("Invalid choice. Defaulting to Small.\n");
        firstDepthCount = 3;
        userChoice = SMALL;
    }

    printf("\nCreating %d first-depth folders...\n", firstDepthCount);

    // Create first depth nodes
    FolderNode** firstDepthNodes = createFirstDepthNodes(firstDepthCount);
    if (firstDepthNodes == NULL)
    {
        freeFolderTree(root);
        return 1;
    }

    // Connect them to root
    connectRootToFirstDepth(root, firstDepthNodes, firstDepthCount);

    //processEachFolderWithTree(firstDepthNodes, firstDepthCount, "./Root");
    // Create the folders on disk
    printf("\nCreating folder structure on disk:\n");
    createFolders(root, ".");

    // Clean up memory
    freeFolderTree(root);


    printf("\nFolder structure created successfully!\n");
}

void generateRandomFilename(char* buffer, int bufferSize)
{
    const char* prefixes[] = { "doc", "notes", "list", "data", "info", "license", "readme" };
    int numPrefixes = sizeof(prefixes) / sizeof(prefixes[0]);

    // Generate a random number between 1 and 999
    int randomNum = (rand() % 999) + 1;

    // Picks a random prefix
    const char* prefix = prefixes[rand() % numPrefixes];

    // Create the filename: prefix_randomNumber.txt
    snprintf(buffer, bufferSize, "%s_%d.txt", prefix, randomNum);
}

/*void processEachFolderWithTree(FolderNode** folders, int count, char* basePath)
{
    printf("\n=== Creating Tree Structures for Each First-Depth Folder ===\n");

    // Allocate array to store tree pointers for each folder
    Tree** folderTrees = (Tree**)malloc(count * sizeof(Tree*));
    if (folderTrees == NULL) {
        printf("Failed to allocate memory for tree pointers\n");
        return;
    }

    for (int i = 0; i < count; i++) 
    {
        char folderPath[256];
        sprintf(folderPath, "%s/%s", basePath, folders[i]->name);

        printf("\n[Folder %d: %s]\n", i + 1, folders[i]->name);
        printf("  Path: %s\n", folderPath);

        // OPTION 1: If they have a function that creates a tree from a path
        // This assumes their function returns a Tree* pointer
        folderTrees[i] = OtherTree_CreateFromPath(folderPath);

        if (folderTrees[i] != NULL) 
        {
            printf("Tree created successfully for %s\n", folders[i]->name);
            printf("Tree pointer (pTree): %p\n", (void*)folderTrees[i]);

            // OPTION 2: If they need to add data to their tree
            // OtherTree_AddFolderData(folderTrees[i], folders[i]);

            // OPTION 3: If they need to process subfolders
            if (folders[i]->numberOfChildren > 0) 
            {
                printf("  This folder has %d subfolders that can be added to the tree\n",
                    folders[i]->numberOfChildren);

                // Example of adding subfolders to their tree
                for (int j = 0; j < folders[i]->numberOfChildren; j++) 
                {
                    char subPath[256];
                    sprintf(subPath, "%s/%s", folderPath, folders[i]->children[j]->name);
                    printf("    Adding subfolder: %s\n", folders[i]->children[j]->name);

                    // Call their function to add a child to the tree
                    // OtherTree_AddChild(folderTrees[i], folders[i]->children[j]->name, subPath);
                }
            }

            // OPTION 4: If they have a function to process the entire tree
            // OtherTree_Process(folderTrees[i]);

        }
        else 
        {
            printf("Failed to create tree for %s\n", folders[i]->name);
        }

        printf("  ----------------------------------------\n");
    }

    // Now all trees are created, you can work with them

    // Example: Access each folder's tree
    printf("\n=== Summary of Created Trees ===\n");
    for (int i = 0; i < count; i++) 
    {
        if (folderTrees[i] != NULL) 
        {
            printf("Folder %d: %s - Tree at %p\n",
                i + 1, folders[i]->name, (void*)folderTrees[i]);
        }
    }
    //
    printf("\n=== Cleaning Up Trees ===\n");
    for (int i = 0; i < count; i++) 
    {
        if (folderTrees[i] != NULL) 
        {
            // Call their free function
            // OtherTree_Free(folderTrees[i]);
            printf("Freed tree for Folder %d\n", i + 1);
        }
    }

    free(folderTrees);
}
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