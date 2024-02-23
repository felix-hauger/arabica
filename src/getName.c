#include "arabica.h"

char* getName(int argc, char *argv[]) {
    if (argc > 0) {
        // Find the position of the last '/' character
        char *base_name = strrchr(argv[0], '/');
        if (base_name != NULL) {
            // Move one position ahead to get rid of '/'
            base_name++;
        } else {
            // If '/' is not found, just use the full name
            base_name = argv[0];
        }
        return base_name;
    }
    else {
        return NULL;
    }
}