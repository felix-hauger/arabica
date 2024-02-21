#include "arabica.h"

int main(int argc, char **argv)
{
    printf("Number of args: %d\n", argc);

    int i = 0;

    while (argv[i] != NULL) {
        printf("arg number %d: %s\n", i, argv[i]);
        i++;
    }

    int num = 42;

    int reversed = bswap_32(num);

    // Open file with read / write, create it if it doesn't exist
    int filedes = open("bytecode", O_CREAT | O_RDWR);

    write(filedes, "CODE", 4);

    write(filedes, "coucou", 6);

    write(filedes, &num, 4);
    write(filedes, "AAAAAA", 6);
    write(filedes, &reversed, 4);

    return 0;
}