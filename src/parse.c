#include "arabica.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_SIZE 150

_Instruction *parse_abc(char *filename)
{
    FILE *filedes = fopen(filename , "r");

    if (filedes == NULL) {
        printf("Error: file not found\n");
        return NULL;
    }

    _Instruction *result = malloc(sizeof(_Instruction) * 100);

    if (result == NULL) {
        printf("Error: memory allocation failed\n");
        return NULL;
    }

    char *line = (char*)malloc(sizeof(char) * MAX_LINE_SIZE);

    int current_result_index = 0;

    while (!feof(filedes)) {
        struct Instruction current_instruction = {.arguments = {{"No arg"}, {"No arg"}}, .instruction = NULL, .size = 0};

        fgets(line, MAX_LINE_SIZE, filedes);

        printf("  %s\n", line);
        char **splitted_line = split(line, " ");

        current_instruction.instruction = my_strdup(trim(splitted_line[0]));
        if (splitted_line[1] != NULL) {
            my_strcpy(current_instruction.arguments[0], trim(splitted_line[1]));
            if (splitted_line[2] != NULL) {
                my_strcpy(current_instruction.arguments[1], trim(splitted_line[2]));
            }
        }

        result[current_result_index] = current_instruction;
        
        current_result_index++;
    }

    int i = 0;

    while (result[i].instruction != NULL) {
        printf("Instruction: %s\n", result[i].instruction);
        printf("Argument 1: %s\n", result[i].arguments[0]);
        printf("Argument 2: %s\n", result[i].arguments[1]);
        i++;
    }

    return result;
}