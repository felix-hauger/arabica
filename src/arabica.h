#ifndef ARABICA
#define ARABICA

#define PROGRAM_NAME_SIZE 16


// Include C libraries below
#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <byteswap.h>
#include <string.h>

// Include external C libraries below


// Include project files below
// Write project's functions signatures below
// int TestOperation(char *functionName);
char* getName(int argc, char *argv[]);
int getFunctionIdFromName(char *functionName);
void writeHeader(int filedes, int programSize, char programName[PROGRAM_NAME_SIZE]);
void writeIntegerForCompile(int filedes, int integer);
void writeStringForCompile(int filedes, char *input);

#endif