#include "arabica.h"

int main(int argc, char **argv)
{
    printf("Number of args: %d\n", argc);

    int i = 0;

    while (argv[i] != NULL) {
        printf("arg number %d: %s\n", i, argv[i]);
        i++;
    }

    if (argv[1] == NULL) {
        handle_error("Missing .abc file", "Usage: ./arabica <abcProgramFile>", 1);
    }

    char *abcFileName = argv[1];

    char *programName = "abcdefghidqq";

    if (my_strlen(programName) > PROGRAM_NAME_SIZE) {
        handle_error("Program name too long. Max length: ", my_itoa(PROGRAM_NAME_SIZE), 1);
    }

    _Instruction *instructions = parse_abc(abcFileName);

    int programSize = get_program_size(instructions);

    // Open file with read / write, create it if it doesn't exist
    int bytecodeFile = open("bytecode", O_CREAT | O_RDWR, 0664);

    writeHeader(bytecodeFile, programSize, programName);

    writeInstructionsInBytes(bytecodeFile, instructions);

    close(bytecodeFile);

    i = 0;

    while (instructions[i].instruction != NULL) {
        free(instructions[i].instruction);
        free(instructions[i].arguments[0]);
        free(instructions[i].arguments[1]);
        i++;
    }

    free(instructions);

    return 0;
}