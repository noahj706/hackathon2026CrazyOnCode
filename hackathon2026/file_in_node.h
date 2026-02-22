#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdlib.h>


char* generate_sentence(void);
void write_to_file(FILE* output_fp, char* str);
int Generate_Random_Strings(int count, char* filename);
