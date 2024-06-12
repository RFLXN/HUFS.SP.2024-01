#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>
#include <getopt.h>
#include "constant.h"

/*
 * Parse arguments by getopt_long()
 */
bool parse_args(int argc, char* argv[], bool* force, bool* with_contents, char* prefix, char* suffix, int* num) {
    const char *const short_options = "fcp:s:n:";
    const struct option long_options[] = {
        { "force",          0,  NULL,   'f' },
        { "prefix",         1,  NULL,   'p' },
        { "suffix",         1,  NULL,   's' },
        { "with-contents",  0,  NULL,   'c' },
        { "num",            1,  NULL,   'n' },
        { NULL,             0,  NULL,   0 }
    };

    int next_option;

    bool is_force = false;
    bool is_with_contents = false;
    char* pre;
    char* suff;
    int n;

    do {
        next_option = getopt_long(argc, argv, short_options, long_options, NULL);
        switch (next_option) {
            case 'f':
                is_force = true;
                break;
            case 'p':
                pre = strdup(optarg);
                break;
            case 's':
                suff = strdup(optarg);
                break;
            case 'c':
                is_with_contents = true;
                break;
            case 'n':
                n = atoi(optarg);
                break;
            case '?':
                return ARGS_INVALID;
            case -1:
                break;
            default:
                return ARGS_INVALID;
        }
    } while (next_option != -1);

    *force = is_force;
    *with_contents = is_with_contents;
    if (pre == NULL) {
        strcpy(prefix, "");
    } else {
        strcpy(prefix, pre);
    }
    if (suff == NULL) {
        strcpy(suffix, "");
    } else {
        strcpy(suffix, suff);
    }
    *num = n;

    return ARGS_OK;
}
