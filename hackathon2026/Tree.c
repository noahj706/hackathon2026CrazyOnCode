#include "gui.h"
#include "parent.h"
#include "treeminus.h"

FolderNode* createFolderNode(char* name)
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
        nodes[i] = createFolderNode(folderName);
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
    int firstDepthCount;
    FolderNode* root = createFolderNode("Projekt");

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
        return;
    default:
        printf("Invalid choice. Defaulting to Small.\n");
        firstDepthCount = 3;
    }

    printf("\nCreating %d first-depth folders...\n", firstDepthCount);

    // Create first depth nodes
    FolderNode** firstDepthNodes = createFirstDepthNodes(firstDepthCount);
    if (firstDepthNodes == NULL)
    {
        freeFolderTree(root);
        return;
    }

    // Connect them to root
    connectRootToFirstDepth(root, firstDepthNodes, firstDepthCount);

    // Create the folders on disk
    printf("\nCreating folder structure on disk:\n");
    createFolders(root, ".");

    // Process each first-depth folder with the tree generator
    processEachFolderWithTree(firstDepthNodes, firstDepthCount, "./Projekt");

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

void processEachFolderWithTree(FolderNode** folders, int count, char* basePath)
{
    printf("\n=== Creating Tree Structures for Each First-Depth Folder ===\n");

    // Seed the random number generator if not already done
    srand((unsigned int)time(NULL));

    // Allocate array to store tree pointers for each folder
    Tree** folderTrees = (Tree**)malloc(count * sizeof(Tree*));
    if (folderTrees == NULL)
    {
        printf("Failed to allocate memory for tree pointers\n");
        return;
    }

    // Initialize all tree pointers to NULL
    for (int i = 0; i < count; i++)
    {
        folderTrees[i] = NULL;
    }

    for (int i = 0; i < count; i++)
    {
        char folderPath[256];
        sprintf(folderPath, "%s/%s", basePath, folders[i]->name);

        printf("\n[Folder %d: %s]\n", i + 1, folders[i]->name);
        printf("  Path: %s\n", folderPath);

        // Create a Tree structure for this folder
        folderTrees[i] = (Tree*)malloc(sizeof(Tree));
        if (folderTrees[i] == NULL)
        {
            printf("  Failed to allocate memory for tree\n");
            continue;
        }
        folderTrees[i]->pHead = NULL;

        // Prepare the data for the root node
        Data rootData;
        strcpy(rootData.dirName, folders[i]->name);

        // Generate random filenames
        char filename1[50], filename2[50];
        generateRandomFilename(filename1, sizeof(filename1));
        generateRandomFilename(filename2, sizeof(filename2));
        strcpy(rootData.fileName1, filename1);
        strcpy(rootData.fileName2, filename2);

        printf("  Creating tree for %s with depth ", folders[i]->name);

        // Generate tree with random depth (1-3 levels deep)
        int treeDepth = (rand() % 3) + 1;  // Random depth between 1 and 3
        printf("%d\n", treeDepth);

        // Call generateTree to create the tree structure
        generateTree(&(folderTrees[i]->pHead), &rootData, treeDepth);

        if (folderTrees[i]->pHead != NULL)
        {
            printf("  Tree created successfully for %s\n", folders[i]->name);
            printf("  Tree contents:\n");
            printTree(folderTrees[i]->pHead, 1);  // Print with 1 tab indentation
        }
        else
        {
            printf("  Failed to create tree for %s\n", folders[i]->name);
        }

        // If this folder has subfolders, we could add them to the tree too
        if (folders[i]->numberOfChildren > 0)
        {
            printf("  This folder has %d subfolders\n", folders[i]->numberOfChildren);

            // You could extend this to add the subfolders to the tree
            // This would require modifications to the generateTree function
            // to accept multiple Data structures
        }

        printf("  ----------------------------------------\n");
    }

    // Print summary of created trees
    printf("\n=== Summary of Created Trees ===\n");
    for (int i = 0; i < count; i++)
    {
        if (folderTrees[i] != NULL && folderTrees[i]->pHead != NULL)
        {
            printf("Folder %d: %s - Tree created\n", i + 1, folders[i]->name);
        }
        else
        {
            printf("Folder %d: %s - No tree created\n", i + 1, folders[i]->name);
        }
    }

    // Clean up
    printf("\n=== Cleaning Up Trees ===\n");
    for (int i = 0; i < count; i++)
    {
        if (folderTrees[i] != NULL)
        {
            // Note: You might want to add a freeTree function in treeminus.h
            // For now, we'll just free the Tree structure
            // The nodes themselves would need proper freeing
            free(folderTrees[i]);
            printf("Freed tree structure for Folder %d\n", i + 1);
        }
    }

    free(folderTrees);
}

void freeTree(Node* pNode)
{
    if (pNode == NULL)
        return;

    // Recursively free all children
    if (pNode->pNext1) freeTree(pNode->pNext1);
    if (pNode->pNext2) freeTree(pNode->pNext2);
    if (pNode->pNext3) freeTree(pNode->pNext3);

    // Free the current node
    free(pNode);
}

