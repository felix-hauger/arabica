#ifndef ARABICA
#define ARABICA

// Define constants below
#define PROGRAM_NAME_SIZE 16
#define ARGUMENTS_MAX_NUM 2

// Include C libraries below
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <byteswap.h>
#include <string.h>
#include <ctype.h>

// Structures
typedef struct Instruction {
    char *instruction;
    char code; // Instruction code stored on 1 byte
    char *arguments[ARGUMENTS_MAX_NUM];
    int size; // Maybe not needed
}_Instruction;

// Include external C libraries below

// Write project's functions signatures below
char* getName(int argc, char *argv[]);
int getFunctionCodeFromName(char *functionName);
void writeHeader(int filedes, int programSize, char programName[PROGRAM_NAME_SIZE]);
void writeIntegerForCompile(int filedes, int integer);
void writeStringForCompile(int filedes, char *input);
_Instruction *parse_abc(char *file_name);
size_t get_program_size(_Instruction *instructions);

// Utils
char *my_strcpy(char *dest, char *src);
char *my_strdup(char *src);
char **split(char *s, char *delim);
char *trim(char *s);
int str_is_digit(char *s);
int my_strlen(char *s);

#endif