#include "arabica.h"

int main(int argc, char **argv)
{
    printf("Number of args: %d\n", argc);

    int i = 0;

    while (argv[i] != NULL) {
        printf("arg number %d: %s\n", i, argv[i]);
        i++;
    }

    
    int result = TestOperation("ADD");
    int reversed = bswap_32(result);

    // Open file with read / write, create it if it doesn't exist
    int filedes = open("bytecode", O_CREAT | O_RDWR);

    write(filedes, "CODE", 4);
    
    printf("Result: %d\n", result);
    //result = bswap_32(result)
    write(filedes, &reversed , 4);
    

    return 0;
}