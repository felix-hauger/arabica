#include "arabica.h"

void writeHeader(int filedes, int programSize, char *programName)
{
    write(filedes, "CODE", 4); // WRITE CODE
   
    writeIntegerForCompile(filedes, programSize); // WRITE Size of the program

    int len = strlen(programName);

    if (len < PROGRAM_NAME_SIZE) {
        writeStringForCompile(filedes, programName); // WRITE Program name
        for (int i = 0; i < PROGRAM_NAME_SIZE - len; i++){
            write(filedes, "\0", 1);    // WRITE 0 bytes to fill the rest of the space
        }
    } else if (len == PROGRAM_NAME_SIZE) {
        writeStringForCompile(filedes, programName); // WRITE Program name if the length of the program name is = 16
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

void writeInstructionsInBytes(int filedes, _Instruction *instructions)
{
    for (int i = 0; instructions[i].instruction != NULL; i++) {
        _Instruction* instruction = &instructions[i];

        // write to file the code for the instruction
        write(filedes, &instruction->code, 1);

        // if the args are declared write them to the file
        if (instruction->arguments[0] != NULL) {

            if (my_strcmp(instruction->instruction, "LOAD_STR") == 0) {
                char length = (my_strlen(instruction->arguments[0])-2);  // get the length of the string
                write(filedes, &length, 1);  // write the length of the string

                if (instruction->arguments[0][0]== '"' && instruction->arguments[0][strlen(instruction->arguments[0])-1] == '"' ) { // if first and last element of the string is "
                    instruction->arguments[0][strlen(instruction->arguments[0])-1] = '\0'; // remove the last "
                    writeStringForCompile(filedes, instruction->arguments[0]+1);  // write the string to the file without the first "

                } else {
                    handle_error("Invalid string format", "Quotes (\") expected", 1);
                }
            } else if (str_is_digit(instruction->arguments[0])) {  //check if it is a integer
                writeIntegerForCompile(filedes, atoi(instruction->arguments[0]));   //write the integer to the file
            } else {
                handle_error("Invalid arg format", "Integer or string expected", 1);  // if the arg is not a integer or a string is format is invalid
            }

            //if arg 2 is declared write it to the file
            if (instruction->arguments[1] != NULL) {
               if(instruction->arguments[1][0] == '"' && instruction->arguments[0][strlen(instruction->arguments[1])-1] == '"' ){ // if first and last element of the string is "
                    instruction->arguments[1][strlen(instruction->arguments[1])-1] = '\0'; // remove the last "
                    writeStringForCompile(filedes, instruction->arguments[1]+1);  // write the string to the file without the first "
                } else {
                    handle_error("Invalid string format", "Quotes (\") expected", 1);
                }

                if (str_is_digit(instruction->arguments[1])) {  //check if it is a integer
                    writeIntegerForCompile(filedes, atoi(instruction->arguments[1]));   //write the integer to the file
                } else {
                    handle_error("Invalid arg format", "Integer or string expected", 1);  // if the arg is not a integer or a string is format is invalid
                }
            }
        }
    }
}
