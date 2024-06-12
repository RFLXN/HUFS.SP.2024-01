#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>

/**
 * Generate random string of given size.
 * @param str
 * @param size
 */
void generate_random_string(char* str, size_t size) {
    const char charset[] = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    struct timeval t;

    // set time-based seed
    gettimeofday(&t, NULL);
    srand(t.tv_usec);

    for (size_t n = 0; n < size; n++) {
        int key = rand() % (int) (sizeof charset - 1);
        str[n] = charset[key];
    }
    str[size] = '\0';
}
