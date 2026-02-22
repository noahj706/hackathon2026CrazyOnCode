#define _CRT_SECURE_NO_WARNINGS
#ifndef PARENT_H
#define PARENT_H
#include <direct.h>
#include <stdio.h>
#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include <time.h> 
#define ZERO 0
#define SMALL 1
#define MEDIUM 2
#define LARGE 3

typedef struct FolderNode
{
    char name[100];
    struct FolderNode** children;
    int numberOfChildren;
} FolderNode;

// Function prototypes
FolderNode* createNode(char* name);
void addChild(struct FolderNode* parent, struct FolderNode* child);
void createFolders(struct FolderNode* root, char* parentPath);
void freeFolderTree(FolderNode* node);
FolderNode** createFirstDepthNodes(int count);
void destroyFirstDepthNodes(FolderNode** nodes, int count);
void connectRootToFirstDepth(FolderNode* root, FolderNode* firstDepthNodes[], int numberOfFirstDepthNodes);
void test_folders();
//void processEachFolderWithTree(FolderNode** folders, int count, char* basePath);
#endif
