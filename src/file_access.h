#include <unistd.h>

/**
 * Check is file exist
 * @param file_name name of file
 * @return
 */
bool is_file_exist(char* file_name) {
    return access(file_name, F_OK) == 0;
}
