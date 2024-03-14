#include "arabica.h"

int main(int argc, char **argv)
{
    printf("Number of args: %d\n", argc);

    int i = 0;

    while (argv[i] != NULL) {
        printf("arg number %d: %s\n", i, argv[i]);
        i++;
    }

    char *programName = "abcdefghijklmnop";

    _Instruction *instructions = parse_abc("example.abc");

    int programSize = get_program_size(instructions);

    // Open file with read / write, create it if it doesn't exist
    int bytecodeFile = open("bytecode", O_CREAT | O_RDWR);

    writeHeader(bytecodeFile, programSize, programName);

    writeInstructionsInBytes(bytecodeFile, instructions);

    return 0;
}