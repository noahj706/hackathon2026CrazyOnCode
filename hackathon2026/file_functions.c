#include "file_in_node.h"

char* generate_sentence(void) {
    //Array groups containing strings that will be put into buffer for the random sentances
    char* nouns[] = { "file", "data", "node", "feature", "project", "system",
        "algorithm", "database", "function", "variable", "pointer", "array",
        "stack", "queue", "tree", "graph", "thread", "process",
        "server", "client", "protocol", "interface", "module", "component" };

    char* verbs[] = { "creates", "reads", "writes", "deletes", "processes", "generates",
        "compiles", "executes", "allocates", "initializes", "validates", "encrypts",
        "compresses", "serializes", "parses", "queries", "caches", "synchronizes" };

    char* adjectives[] = { "random", "small", "large", "new", "old", "fast",
        "recursive", "iterative", "asynchronous", "synchronous", "distributed", "parallel",
        "dynamic", "static", "encrypted", "compressed", "optimized", "scalable",
        "persistent", "transient", "atomic", "volatile", "virtual", "binary" };

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
    strcat(sentence, " data");

    return sentence;
}

void write_to_file(FILE* output_fp, char* str) {
    fprintf(output_fp, "%s\n", str);
}

int Generate_Random_Strings(int count, char* filename) {
    FILE* file = fopen(filename, "w");

    if (file == NULL) {
        printf("Error opening file!\n");
        return 0;
    }

    for (int i = 0; i < count; i++) {
        char* sentence = generate_sentence();
        write_to_file(file, sentence);
    }

    fclose(file);
    return count;
}

