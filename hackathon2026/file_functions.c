#include "file_in_node.h"

char* generate_sentence(void) {
    //Array groups containing strings that will be put into buffer for the random sentances
    char* nouns[] = { "-file", "-data", "-node", "-feature", "-project", "-system",
        "-algorithm", "-database", "-function", "-variable", "-pointer", "-array",
        "-stack", "-queue", "-tree", "-graph", "-thread", "-process",
        "-server", "-client", "-protocol", "-interface", "-module", "-component" };

    char* verbs[] = { "creates", "reads", "writes", "deletes", "processes", "generates",
        "compiles", "executes", "allocates", "initializes", "validates", "encrypts",
        "compresses", "serializes", "parses", "queries", "caches", "synchronizes" };

    char* adjectives[] = { "(random)", "(small)", "(large)", "(new)", "(old)", "(fast)",
        "(recursive", "(iterative", "(asynchronous)", "(synchronous)", "(distributed)", "(parallel)",
        "(dynamic)", "(static)", "(encrypted)", "(compressed)", "(optimized)", "(scalable)",
        "(persistent)", "(transient)", "(atomic)", "(volatile)", "(virtual)", "(binary)" };

    char* prefixes[] = { "The", "A", "This", "Each", "Every",
        "Our", "That", "Any", "Some", "Another" };

    //Maximum number of values in the string will be 200 values 
    static char sentence[200];
    //This will start
    sentence[0] = '\0';

    strcat(sentence, prefixes[rand() % 5]);
    strcat(sentence, " ");
    strcat(sentence, adjectives[rand() % 6]);
    strcat(sentence, " ");
    strcat(sentence, nouns[rand() % 6]);
    strcat(sentence, " ");
    strcat(sentence, verbs[rand() % 6]);
    strcat(sentence, " data;");

    return sentence;
}

void write_to_file(FILE* output_fp, char* str) {
    fprintf(output_fp, "%s\n", str);
}

//takes in respective names, creates a file path with them, create rand file to that path
//pragrammed by noah at 5am so idk if thisll be coherent LOL!!!
bool genRanFile(const char* curPath, const char* fileName)
{
    //path creation in buffer, txt file is then created at path location
    char pathBuffer[256] = { '\0' };
    sprintf(pathBuffer, "%s/%s.txt", curPath, fileName);
    FILE* newFile = fopen(pathBuffer, "w");

    assert(newFile != NULL); //error check

    //fill the txt file with some bs
    for (int i = 0; i <= 100; ++i) 
    {
        write_to_file(newFile, generate_sentence());
    }

    //close file stream
    fclose(newFile);
    return true;
    //FUCK YEAH THIS LOOKS LIKE ITLL WORK!!!
}


/*
ADD NODE PARAMETERS WHEN WALKER IS DONE!!!!
*/

//reads data from current node and then passes it into genRanFile();
bool readNode()
{
    return;
}

//uses a stack to navigate the tree, steps back when at end of branch
//enters node -> calls readNode() to push stack->path info and genRanFile(peek(), nameFile) -> move to next node left2right priority
//IF no nodes left to move UP list, make sure data is read and THEN free the node, pop stock, should land one node backwards
void traverseTree()
{
    StackStack stack = { .count = 0, .pHead = NULL };

}



