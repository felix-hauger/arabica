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
        struct Instruction current_instruction;

        current_instruction.arguments[0] = NULL;
        current_instruction.arguments[1] = NULL;

        fgets(line, MAX_LINE_SIZE, filedes);

        printf("  %s\n", line);
        char **splitted_line = split(line, " ");

        current_instruction.instruction = my_strdup(trim(splitted_line[0]));
        current_instruction.code = getFunctionCodeFromName(current_instruction.instruction);
        if (splitted_line[1] != NULL) {
            current_instruction.arguments[0] = my_strdup(trim(splitted_line[1]));
            if (splitted_line[2] != NULL) {
                current_instruction.arguments[1] = my_strdup(trim(splitted_line[2]));
            }
        }

        result[current_result_index] = current_instruction;
        
        current_result_index++;
    }

    // int i = 0;

    // while (result[i].instruction != NULL) {
    //     printf("Instruction: %s\n", result[i].instruction);
    //     printf("Code: %d\n", result[i].code);
    //     printf("Argument 1: %s\n", result[i].arguments[0]);
    //     printf("Argument 2: %s\n", result[i].arguments[1]);
    //     i++;
    // }

    return result;
}


size_t get_argument_size(char *arg)
{
    size_t result;

    if (str_is_digit(arg)) {
        //! Might need to test if the value is too high for an int
        result = 4;
    } else {
        result = my_strlen(arg);
    }

    return result;
}

size_t get_program_size(_Instruction *instructions)
{
    size_t result = 0;
    int i = 0;

    while (instructions[i].instruction != NULL) {
        result++;
        printf("Program size: %ld\n", result);
        if (instructions[i].arguments[0] != NULL) {
                result += get_argument_size(instructions[i].arguments[0]);
            if (instructions[i].arguments[1] != NULL) {
                result += get_argument_size(instructions[i].arguments[0]);
            }
        }
        i++;
        printf("Program size: %ld\n\n", result);
    }
    return result;
}