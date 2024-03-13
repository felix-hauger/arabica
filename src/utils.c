#include "arabica.h"

int my_strlen(char *str)
{
    int len = 0;

    while (str[len] != 0) len++;

    return len;
}

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

char *my_strdup(char *src)
{
    int str_length = my_strlen(src);

    char *str = (char*)malloc(sizeof(char*) * str_length);

    my_strcpy(str, src);

    return str;
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

char *ltrim(char *s)
{
    while (isspace(*s)) s++; // Move pointer to the right until it's not a space

    return s;
}

char *rtrim(char *s)
{
    char *back = s + strlen(s); // Create a pointer to the end of the string

    while (isspace(*--back)); // Decrement the pointer and dereference it until it's not a space

    *(back + 1) = '\0'; // Set the null terminator

    return s;
}

char *trim(char *s)
{
    return rtrim(ltrim(s));
}