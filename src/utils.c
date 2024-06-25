#include "arabica.h"

void handle_error(char *error_message, char *hint, int exit_code)
{
    printf("\033[1;31mError: %s (%s)\033[0m\n", error_message, hint);

    exit(exit_code);
}

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

int char_is_digit(char c)
{
    return (c >= '0' && c <= '9') ? 1 : 0;
}

int str_is_digit(char *string)
{
    int i = 0;

    while (string[i] != 0) {
        if (!char_is_digit(string[i])) return 0;

        i++;
    }

    return 1;
}

int my_strcmp(char *s1, char *s2)
{
    int i = 0;

    while (s1[i] || s2[i]) {
        if (s1[i] > s2[i]) return 1;
        else if (s2[i] > s1[i]) return -1;
        i++;
    }

    return 0;
}

int count_digits(int n)
{
    int count = 0;

    while (n != 0) {
        n = n / 10;
        count++;
    }

    return count;
}

/*
Find the nb of digits
from the left
get the first digit
add equivalent from char to result string
get the next digit:
    to do so multiply the previous digit by the nb of 10^nb_digits
    remove the digit from the left (n = n - nb_digits * last_digit)
    reduce the nb of digits by 1
continue for nb of digits
*/
char *my_itoa(int n)
{
    // Get number of digits (eg: 7851 = 4)
    int nb_digits = count_digits(n);

    // Allocate from the number of digits
    char *result = (char*)malloc(sizeof(char) * nb_digits + 1);

    // To calculate the digits
    int digits = 1;

    int i = 0;

    // 10^(n-1) (eg: 3 digits = 100, 7 digits = 1 000 000)
    // To make calculations
    while (i < nb_digits - 1) {
        digits = digits * 10;
        i++;
    }

    // To insert the char at the right index of the result string
    int result_index = 0;

    while (n > 0) {
        // Get the current digit
        int current_digit = n / digits;

        // Insert the digit character from the ASCII table ('0' == 48)
        result[result_index] = current_digit + '0';

        result_index++;

        // Remove the current first digit of the original number
        n = n - current_digit * digits;

        // Reduce the number of digits
        digits = digits / 10;
    }

    // Insert 0 to flag the end of the string
    result[result_index] = 0;

    return result;
}