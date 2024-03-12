#include "arabica.h"

char *my_strcpy(char *dest, char *src)
{
    int i = 0;

    while (src[i] != 0) {
        dest[i] = src[i];

        i++;
    }

    dest[i] = 0;

    return dest;
}

char **split(char *s, char *delim)
{
    char **result = malloc(sizeof(char*) * 100);
    char *token;
    int token_index = 0;

    token = strtok(s, delim);

    while (token != NULL) {
        result[token_index] = token;
        token = strtok(NULL, delim);
        token_index++;
    }

    return result;
}