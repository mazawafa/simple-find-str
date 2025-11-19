#include <malloc.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SZ 1000

#define RED "\e[1;31m"
#define RESET "\e[0m"

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

char* print_range(const char* start, const char* end) {
    char* p;
    for (p = start; p != end; ++p)
        printf("%c", *p);
    return p;
}

int main(int argc, char* argv[]) {
    char* pat = argv[2];
    size_t pat_ln = strlen(pat);

    if (argc < 3) {
        printf("usage: %s FILENAME STRING\n", argv[0]);
        return EXIT_FAILURE;
    }

    /* Open file */
    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        printf("error while opening file \"%s\"\n", argv[1]);
        return EXIT_FAILURE;
    }

    /* Read file line by line */
    char* buf = malloc(BUF_SZ);
    char* ptr_found;
    int num = 1;
    while (fgets(buf, BUF_SZ, fp)) {

        /* Find several matches in the line */
        ptr_found = brute_force_search(pat, buf);
        if (ptr_found) {
            printf("%d: ", num);

            char* p = buf;
            do {
                p = print_range(p, ptr_found);
                printf(RED);
                p = print_range(p, ptr_found + pat_ln);
                printf(RESET);
            } while (ptr_found = brute_force_search(pat, ptr_found + pat_ln));
            printf("%s", p);
        }
        ++num;
    }

    return EXIT_SUCCESS;
}
