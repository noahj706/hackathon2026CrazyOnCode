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
    if (parent == NULL || child == NULL) return;

    parent->numberOfChildren++;
    parent->children = realloc(parent->children, parent->numberOfChildren * sizeof(FolderNode*));
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
    if (root == NULL) return;

    char currentPath[256];
    sprintf(currentPath, "%s/%s", parentPath, root->name);

    if (_mkdir(currentPath) == 0) 
    {
        printf("Created: %s\n", currentPath);
    }
    else {
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
    if (nodes == NULL) return;

    for (int i = 0; i < count; i++) 
    {
        freeFolderTree(nodes[i]);  // This will free the node and its children
    }
    free(nodes);
}

void connectRootToFirstDepth(FolderNode* root, FolderNode* firstDepthNodes[], int numberOfFirstDepthNodes)
{
    if (root == NULL) return;

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
    FolderNode* root = createNode("Project");

    printf("Choose folder structure size:\n");
    printf("1. Small (3 first-depth folders)\n");
    printf("2. Medium (5 first-depth folders)\n");
    printf("3. Large (7 first-depth folders)\n");
    printf("Enter your choice (1-3): ");
    scanf("%d", &userChoice);

    // Determine first depth count based on user choice
    switch (userChoice)
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


    // Create the actual folders on disk
    printf("\nCreating actual folder structure on disk:\n");
    createFolders(root, ".");

    // Clean up memory
    freeFolderTree(root);
    // Note: firstDepthNodes is already freed as part of the tree

    printf("\nFolder structure created successfully!\n");
}



