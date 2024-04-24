#define STACK_SIZE 1000
#include <stdbool.h>

void dfs_backtrack(int max_length, char* symbols, char* starting_candidate, char** output, int outputSize) {
    char** stack = (char**)malloc(sizeof(char*) * STACK_SIZE);
    stack[0] = malloc(sizeof(char)*(strlen(starting_candidate)+1));
    strcpy(stack[0], starting_candidate);
    int esp = 0;
    while(esp > -1){
        char* candidate = stack[esp--];

        if (true) {
            //add to output
            break;
        }
        // Test the candidate's children if applicable
        if (strlen(candidate) < max_length) {
            int candidate_length = strlen(candidate);
            for (int i = 0; i < strlen(symbols); i++) {
                stack[++esp] = malloc((candidate_length + 2) * sizeof(char));  // Allocate memory for child candidate on the stack
                sprintf(stack[esp], "%s%c", candidate, symbols[i]);  // Create child candidate and null terminates
            }
        }
        free(candidate);
    }
    free_stack(stack);
}

int main(int argc, char *argv[]) {
    int max_length = 4;
    int outputSize = 100;

    // alloc arr of strings
    char** output = (char**)malloc(sizeof(char*)*outputSize);
    for(int i = 0; i < outputSize; i++){
        output[i] = (char*)malloc(sizeof(char)*(max_length+1));
        output[i][max_length] = '\0';
    }

    // populate output
    dfs_backtrack(max_length, "0123456789", "", output, outputSize);  

    // print and free output strings
    for(int i = 0; i < outputSize; i++){
        printf("%s, ");
        free(output[i]);
    }
    printf("\n");
    free(output);
    return 0;
}