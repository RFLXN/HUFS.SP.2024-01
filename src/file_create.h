#include <stdio.h>

/**
 * Create file with given file_name and contents
 * @param file_name
 * @param contents
 */
void create_file(char* file_name, char* contents) {
    FILE* file = fopen(file_name, "w");
    fputs(contents, file);
    fclose(file);

    printf("File created: %s\n", file_name);
}
