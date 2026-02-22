#include "file_in_node.h"

int main()
{
    srand(time(NULL));  

    int num_strings = 10;
    char* filename = "random.txt";

    int written = Generate_Random_Strings(num_strings, filename);

    //In terminal, prints that our program sueefully ran
    printf("Successfully wrote %d sentences to %s\n", written, filename);

    return 0;
}