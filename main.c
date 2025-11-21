#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SZ 1000

#define RED "\033[1;31m"
#define RESET "\033[0m"

const char* brute_force_search(const char* sub, const char* str) {
    size_t i, j;
    for (i = 0; str[i] != '\0'; ++i) {
        for (j = 0; str[i + j] == sub[j]; ++j) {
            if (sub[j + 1] == '\0')
                return str + i;
        }
    }
    return NULL;
}

const char* print_range(const char* start, const char* end) {
    const char* p;
    for (p = start; p != end; ++p)
        printf("%c", *p);
    return p;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        printf("usage: %s FILENAME STRING\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char* pat = argv[2];
    size_t pat_ln = strlen(pat);

    /* Open file */
    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        printf("error while opening file \"%s\"\n", argv[1]);
        return EXIT_FAILURE;
    }

    /* Read file line by line */
    char* buf = malloc(BUF_SZ); // Buffer to keep line characters
    if (!buf) {
        fprintf(stderr, "memory allocation failed\n");
        fclose(fp);
        return EXIT_FAILURE;
    }

    const char* ptr_found; // Pointer to current match
    int num = 1;     // Current line number
    while (fgets(buf, BUF_SZ, fp)) {

        /* FIND MATCHES */
        ptr_found = brute_force_search(pat, buf);
        if (ptr_found) {
            printf("%d: ", num);

            const char* p = buf; // Pointer to print
            do {
                /* Print match */
                p = print_range(p, ptr_found);
                printf(RED);
                p = print_range(p, ptr_found + pat_ln);
                printf(RESET);
                /* Find next match if any */
            } while ((ptr_found = brute_force_search(pat, p)) != NULL);
            /* Print last characters */
            printf("%s", p);
        }
        ++num;
    }

    free(buf);
    fclose(fp);
    return EXIT_SUCCESS;
}
