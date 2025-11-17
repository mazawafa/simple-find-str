#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#define BUF_SZ 1000

char* brute_force_search(char* sub, char* str) {
    size_t i, j;
    for (i = 0; str[i] != '\0'; ++i) {
        for (j = 0; str[i + j] == sub[j]; ++j) {
            if (sub[j + 1] == '\0')
                return str + i; 
        }
    }
    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("usage: %s FILENAME STRING\n", argv[0]); 
        return EXIT_FAILURE;
    }

    /* Open file */
    FILE *fp = fopen(argv[1], "r");
    if (!fp) {
        printf("error while opening file \"%s\"\n", argv[1]);
        return EXIT_FAILURE;
    }
    printf("%s", argv[2]);

    /* Read file line by line */
    char* buf = malloc(BUF_SZ);
    while (fgets(buf, BUF_SZ, fp)) {
        printf("brute_force_search(buf, argv[2]))
            printf("1");
    }

    return EXIT_SUCCESS;
}
