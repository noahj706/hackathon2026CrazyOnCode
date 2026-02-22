
#ifndef FILENODE_H
#define FILENODE_H

#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <stdbool.h>
#include "stack.h"


char* generate_sentence(void);
void write_to_file(FILE* output_fp, char* str);

//takes in respective names, creates a file path with them, create rand file to that path
bool genRanFile(char* curPath, char* fileName);

//reads data from current node and then passes it into genRanFile();
bool readNode();

//uses a stack to navigate the tree, steps back when at end of branch
//when stepping back from a branch end the node is popped behind it bcs data is written out
void traverseTree();

#endif