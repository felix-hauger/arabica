#define NUM_OPERATIONS 28
#include "arabica.h"

int TestOperation(char *functionName) {
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
        "JUMP_IF_TRUE",
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
