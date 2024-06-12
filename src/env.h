#include <stdlib.h>
#include <stdbool.h>

/**
 * Parse the environment variable "PROCESS_NUMS"
 * @param process_num
 */
void parse_env(int* process_num) {
    char* pn = getenv("PROCESS_NUMS");
    if (pn == NULL) {
        *process_num = 0;
    } else {
        *process_num = atoi(pn);
    }
}
