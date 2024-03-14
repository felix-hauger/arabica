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

    // Open file with read / write, create it if it doesn't exist
    int filedes = open("bytecode", O_CREAT | O_RDWR);

    // char *processName = getName(argc, argv); // get the name of the process
    writeHeader(filedes, 20, programName);

    /*
    char load_val = getFunctionCodeFromName("LOAD_VAL");
    char add = getFunctionCodeFromName("ADD");
    char print_val = getFunctionCodeFromName("PRINT_VAL");

    _Instruction *instructions = parse_abc("test.abc");

    size_t program_size = get_program_size(instructions);

    printf("Program size: %ld\n", program_size);

    write(filedes, &load_val, 1);
    writeIntegerForCompile(filedes, 42);
    write(filedes, &load_val, 1);
    writeIntegerForCompile(filedes, 69);
    write(filedes, &add, 1);
    write(filedes, &print_val, 1);
    */

    //missing the total number of bytes in the file

    // printf("Process name: %s\n", processName);
    
    // write(filedes, processName, strlen(processName)); 
    
    // char buffer[11] = {0}; // Initialize buffer with 11 zero bytes
    // write(1, buffer, 11);   // Write 11 bytes of zero to stdout

    //get instruction from file
    _Instruction* result = parse_abc("test.abc");

    for (int i = 0; result[i].instruction != NULL; i++) {
        _Instruction* instruction = &result[i];
        
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
    
    return 0;
}