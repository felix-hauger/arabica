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
    writeHeader(filedes, 24, programName);

    char load_val = getFunctionCodeFromName("LOAD_VAL");
    char add = getFunctionCodeFromName("ADD");
    char print_val = getFunctionCodeFromName("PRINT_VAL");

    parse_abc("test.abc");

    write(filedes, &load_val, 1);
    writeIntegerForCompile(filedes, 42);
    write(filedes, &load_val, 1);
    writeIntegerForCompile(filedes, 69);
    write(filedes, &add, 1);
    write(filedes, &print_val, 1);

    //missing the total number of bytes in the file

    // printf("Process name: %s\n", processName);
    
    // write(filedes, processName, strlen(processName)); 
    
    // char buffer[11] = {0}; // Initialize buffer with 11 zero bytes
    // write(1, buffer, 11);   // Write 11 bytes of zero to stdout

    return 0;
}