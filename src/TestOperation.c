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

void writeHeader(int filedes, int programSize, char *programName)
{
    write(filedes, "CODE", 4); // WRITE CODE
   
    writeIntegerForCompile(filedes, programSize); // WRITE Size of the program

    int len = strlen(programName);

    if (len < PROGRAM_NAME_SIZE){
        writeStringForCompile(filedes, programName); // WRITE Program name
        for (int i = 0; i < PROGRAM_NAME_SIZE - len; i++){
            write(filedes, "\0", 1);    // WRITE 0 bytes to fill the rest of the space
        }
    } else if (len == PROGRAM_NAME_SIZE){
        writeStringForCompile(filedes, programName); // WRITE Program name if the length of the program name is = 16
    } else{
        printf("ERROR : Program name is too long\n");
        exit(1);
    }
   
    
    
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