#include <stdio.h>

/*
 * Create a file name from a prefix, suffix, and id.
 */
void create_file_name(char* file_name, char* prefix, char* suffix, int id) {
    sprintf(file_name, "%s%d%s", prefix, id, suffix);
}
