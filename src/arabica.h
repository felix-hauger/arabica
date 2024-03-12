#ifndef ARABICA
#define ARABICA

#define PROGRAM_NAME_SIZE 16
#define ARGUMENTS_MAX_NUM 2
#define ARGUMENT_MAX_SIZE 100


// Include C libraries below
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <byteswap.h>
#include <string.h>

// Structures
typedef struct Instruction {
    char *instruction;
    char arguments[ARGUMENTS_MAX_NUM][ARGUMENT_MAX_SIZE];
    int size; // Maybe not needed
}_Instruction;

// Include external C libraries below


// Include project files below
// Write project's functions signatures below
// int TestOperation(char *functionName);
char* getName(int argc, char *argv[]);
int getFunctionIdFromName(char *functionName);
void writeHeader(int filedes, int programSize, char programName[PROGRAM_NAME_SIZE]);
void writeIntegerForCompile(int filedes, int integer);
void writeStringForCompile(int filedes, char *input);
_Instruction *parse_abc(char *file_name);

// Utils
char *my_strcpy(char *dest, char *src);
char **split(char *s, char *delim);

#endif