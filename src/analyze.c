#include "arabica.h"

#define MAX_LINE_SIZE 150
#define NUM_OPERATIONS 28

_Instruction *parse_abc(char *filename)
{
    FILE *filedes = fopen(filename , "r");

    if (filedes == NULL) {
        handle_error(".abc file not found", filename, 1);
    }

    _Instruction *result = malloc(sizeof(_Instruction) * 100);

    char *line = (char*)malloc(sizeof(char) * MAX_LINE_SIZE);

    int current_result_index = 0;

    while (fgets(line, MAX_LINE_SIZE, filedes)) {
        struct Instruction current_instruction;

        current_instruction.arguments[0] = NULL;
        current_instruction.arguments[1] = NULL;

        // Test if line is empty
        if (my_strlen(trim(line)) > 0) {
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

            free(splitted_line);
            
            current_result_index++;
        }
    }

    free(line);

    return result;
}

int getFunctionCodeFromName(char *functionName) {
    const char *operations[NUM_OPERATIONS] = {
        "LOAD_VAL",
        "READ_VAR",
        "STORE_VAR",
        "ADD",
        "SUB",
        "MUL",
        "DIV",
        "MOD",
        "JMP",
        "JMP_IF_ZERO",
        "JMP_IF_TRUE",
        "EQ",
        "NEQ",
        "GT",
        "LT",
        "GTE",
        "LTE",
        "PRINT_VAL",
        "INPUT_VAL",
        "HALT",
        "LOAD_STR",
        "PRINT_STR",
        "INPUT_STR",
        "STR_LEN",
        "CONCAT",
        "GET_CHAR",
        "SET_CHAR",
        "STR_CMP"
    };

    for (int i = 0; i < NUM_OPERATIONS; ++i) {
        if(strcmp(functionName, operations[i]) == 0) {
            return ++i;
        }
    }

    // If the function name is not found, display an error message and exit
    handle_error("Invalid function name", functionName, 1);

    return 0;
}

size_t get_argument_size(char *arg)
{
    size_t result;

    if (str_is_digit(arg)) {
        // Need to test if the value is too high for an int.
        // If the value is too high for a standard int, the
        // arabica vm will not be able to handle it correctly.
        if (atoll(arg) > 2147483647) {
            handle_error("One of your integer arguments has a too high value", "Max value: 2147483647", 1);
        } else {
            result = 4;
        }
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

        if (instructions[i].arguments[0] != NULL) {
            // if the instruction is LOAD_STR, we need to add the length of the string minus the quotes that will be deleted later, we should remove  bytes ,
            // but since we also print the size of the string in one byte, it would cause problems, to make it simpler we only remove 1
            if (instructions[i].arguments[0][0] == '"' && instructions[i].arguments[0][strlen(instructions[i].arguments[0])-1] == '"' ) { // if first and last element of the string is "
                result += (get_argument_size(instructions[i].arguments[0]))-1;
            } else {
                result += get_argument_size(instructions[i].arguments[0]);
            }

            if (instructions[i].arguments[1] != NULL) {
                if (instructions[i].arguments[1][0] == '"' && instructions[i].arguments[1][strlen(instructions[i].arguments[1])-1] == '"' ) { // if first and last element of the string is "
                    result += (get_argument_size(instructions[i].arguments[1]))-1;
                } else {
                    result += get_argument_size(instructions[i].arguments[1]);
                }
            }
        }

        i++;
    }
    return result;
}