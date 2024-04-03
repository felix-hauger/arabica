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
    char *instruction; // Probably not needed anymore
    char code; // Instruction code stored on 1 byte
    char *arguments[ARGUMENTS_MAX_NUM];
    int size; // Maybe not needed
}_Instruction;

// Include external C libraries below

// Write project's functions signatures below

// Analyze
int getFunctionCodeFromName(char *functionName);
_Instruction *parse_abc(char *file_name);
size_t get_program_size(_Instruction *instructions);

// Compile
void writeHeader(int filedes, int programSize, char *programName);
void writeIntegerForCompile(int filedes, int integer);
void writeStringForCompile(int filedes, char *input);
void writeInstructionsInBytes(int filedes, _Instruction *instructions);

// Utils
void handle_error(char *error_message, char *hint, int exit_code);
char *my_strcpy(char *dest, char *src);
char *my_strdup(char *src);
char **split(char *s, char *delim);
char *trim(char *s);
int str_is_digit(char *s);
int my_strlen(char *s);
int my_strcmp(char *s1, char *s2);
char *my_itoa(int n);

#endif