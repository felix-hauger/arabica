#include <stdio.h>
#define NUM_OPERATIONS 28
#include "arabica.h"

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
        if(strcmp(functionName,operations[i]) == 0){
            return ++i;
        }
    }

    return 0;
}

void writeHeader(int filedes, int programSize, char programName[PROGRAM_NAME_SIZE])
{
    write(filedes, "CODE", 4);

    writeIntegerForCompile(filedes, programSize);

    write(filedes, programName, PROGRAM_NAME_SIZE);
}

void writeIntegerForCompile(int filedes, int integer)
{
    // Switch the endianness
    int reversed = bswap_32(integer);

    write(filedes, &reversed, sizeof(reversed));
}

void writeStringForCompile(int filedes, char *input)
{
    write(filedes, input, strlen(input));
}

void writeInstructionsInBytes(int filedes, _Instruction *instructions)
{
    for (int i = 0; instructions[i].instruction != NULL; i++) {
        _Instruction* instruction = &instructions[i];

        //write to file the code for the instruction
        write(filedes, &instruction->code, 1);

        // if the args are declared ( not "No arg" ) write them to the file
        if (instruction->arguments[0] != NULL) {
            if (str_is_digit(instruction->arguments[0])) {  //check if it is a integer
                writeIntegerForCompile(filedes, atoi(instruction->arguments[0])); 
            } else {
                writeStringForCompile(filedes, instruction->arguments[0]);//else its an string
            }
            //if arg 2 is declared write it to the file
            if (instruction->arguments[1] != NULL) {
                if (str_is_digit(instruction->arguments[1])) {
                    writeIntegerForCompile(filedes, atoi(instruction->arguments[1]));
                } else {
                    writeStringForCompile(filedes, instruction->arguments[1]);
                }
            }
        }
    }
}

void display_error(char *error_message)
{
    printf("Error: %s\n", error_message);
}

void display_help()
{
    printf("Usage: ./arabica <abcProgramFile> <destinationFile>\n");
}