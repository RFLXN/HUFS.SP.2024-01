#include <stdio.h>
#include "constant.h"
#include "args.h"
#include "env.h"
#include "file_name.h"
#include "file_access.h"
#include "file_create.h"
#include "random_string.h"

int main(int argc, char* argv[]) {
    bool is_force = false;
    bool is_with_contents = false;
    char* prefix;
    char* suffix;
    int num = 0;
    int process_num = 0;
    pid_t pid;

    // parse arguments (function from "args.h")
    int is_valid_args = parse_args(
            argc, argv,
            &is_force, &is_with_contents,
            prefix, suffix, &num
    );

    if (num == 0) {
        is_valid_args = false;
    }

    // when arguments are invalid
    if (!is_valid_args) {

        // print usage
        fprintf(stderr, "ERROR: Invalid arguments\n");
        fprintf(stderr, "Usage: ./main [options]\n");
        fprintf(stderr, "Options:\n");
        fprintf(stderr, "\t-n, --num: Number of output [REQUIRED!]\n");
        fprintf(stderr, "\t-f, --force: Force to overwrite the file\n");
        fprintf(stderr, "\t-c, --with-contents: Include contents in the output\n");
        fprintf(stderr, "\t-p, --prefix: Prefix of the output\n");
        fprintf(stderr, "\t-s, --suffix: Suffix of the output\n");
        fprintf(stderr, "Example: ./main.o -n 100 -f -c -p pre -s suf\n");

        return 1; // and exit with code 1
    }

    // parse environment variables (function from "env.h")
    parse_env(&process_num);

    if (process_num == 0) {
        process_num = DEFAULT_PROCESSES;
    }

    // only run multiprocess when process_num is less than num
    if (process_num < num) {
        int range = num / process_num;

        for (int process_idx = 0; process_idx < process_num; process_idx++) {

            // fork child processes for multiprocessing
            pid = fork();
            if (pid < 0) {
                fprintf(stderr, "ERROR: Failed to fork process.\n");
                exit(1);
            } else if (pid == 0) {      // child process (worker)
                // calculate range
                int start = (process_idx * range) + 1;
                int end = (process_idx + 1) * range;
                if (end > num) {
                    end = num;
                }

                // allocate memory for file name
                char* target_file_name = (char*)malloc(MAX_FILE_NAME);

                for (int i = start; i <= end; i++) {
                    // create file name (function from "file_name.h")
                    create_file_name(target_file_name, prefix, suffix, i);

                    // when "-f" option given
                    if (is_force) {
                        if (is_file_exist(target_file_name)) {  // function from "file_access.h"
                            // fork remove worker
                            pid_t remove_pid = fork();
                            if (remove_pid < 0) {
                                fprintf(stderr, "ERROR: Failed to fork process.\n");
                                exit(1);
                            } else if (remove_pid == 0) {
                                // force remove file with exec function
                                execl("/bin/rm", "-rf", target_file_name, NULL);
                                exit(0);
                            } else {
                                // wait until remove worker finishes
                                int status;
                                do {
                                    waitpid(remove_pid, &status, 0);
                                } while(!WIFEXITED(status) && !WIFSIGNALED(status));
                                printf("Remove file for force write: %s\n", target_file_name);
                            }
                        }

                        // when "-c" option given
                        if (is_with_contents) {
                            // create random-generated string (function from "random_string.h")
                            char* random_string = (char*) malloc(24);
                            generate_random_string(random_string, 24);

                            // create file with random-generated string (function from "file_create.h")
                            create_file(target_file_name, random_string);
                            free(random_string);
                        } else {
                            // create empty file
                            create_file(target_file_name, "");
                        }
                    } else { // when "-f" option not given
                        if (!is_file_exist(target_file_name)) {
                            if (is_with_contents) {
                                char* random_string = (char*) malloc(24);
                                generate_random_string(random_string, 24);
                                create_file(target_file_name, random_string);
                                free(random_string);
                            } else {
                                create_file(target_file_name, "");
                            }
                        } else {
                            // just skip when not "-f" and file exists
                            fprintf(stderr, "Skip exist file: %s\n", target_file_name);
                        }
                    }
                }

                free(target_file_name);
                exit(0);
            }
        }

        for (int process_idx = 0; process_idx < process_num; process_idx++) {
            wait(NULL);
        }
    } else {  // single process run when process_num is greater than num
        char* target_file_name = (char*)malloc(MAX_FILE_NAME);

        for (int i = 0; i < num; i++) {
            create_file_name(target_file_name, prefix, suffix, i);

            if (is_force) {
                if (is_file_exist(target_file_name)) {
                    pid_t remove_pid = fork();

                    if (remove_pid < 0) {
                        fprintf(stderr, "ERROR: Failed to fork process.\n");
                    } else if (remove_pid == 0) {
                        execl("/bin/rm", "-rf", target_file_name, NULL);
                        exit(0);
                    } else {
                        int status;
                        do {
                            waitpid(remove_pid, &status, 0);
                        } while(!WIFEXITED(status) && !WIFSIGNALED(status));
                        printf("Remove file for force write: %s\n", target_file_name);
                    }
                }

                if (is_with_contents) {
                    char* random_string = (char*) malloc(24);
                    generate_random_string(random_string, 24);
                    create_file(target_file_name, random_string);
                    free(random_string);
                } else {
                    create_file(target_file_name, "");
                }
            } else {
                if (!is_file_exist(target_file_name)) {
                    if (is_with_contents) {
                        create_file(target_file_name, "x3SrUvfx3Isga2u3577QVAwb");
                    } else {
                        create_file(target_file_name, "");
                    }
                } else {
                    fprintf(stderr, "Skip exist file: %s\n", target_file_name);
                }
            }
        }

        free(target_file_name);
    }



    return 0;
}
