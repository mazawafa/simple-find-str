#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUF_SZ 1000

#define RED "\033[1;31m"
#define RESET "\033[0m"

const char* brute_force_search(const char* haystack, const char* needle) {
    size_t i, j;
    for (i = 0; haystack[i] != '\0'; ++i) {
        for (j = 0; haystack[i + j] == needle[j]; ++j) {
            if (needle[j + 1] == '\0')
                return haystack + i;
        }
    }
    return NULL;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        fprintf(stderr, "usage: %s FILENAME STRING\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char* pat = argv[2];

    /* Open file */
    FILE* fp = fopen(argv[1], "r");
    if (!fp) {
        fprintf(stderr, "error while opening file \"%s\"\n", argv[1]);
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
    while (fgets(buf, BUF_SZ, fp) != NULL) {
        /* FIND MATCHES */
        ptr_found = brute_force_search(buf, pat);
        if (ptr_found) {
            printf("%d: ", num);

            const char* p = buf; // Pointer to print
            size_t len = (size_t)(ptr_found - p);
            do {
                /* Print match */
                p = p + fwrite(p, 1, len, stdout);
                printf(RED);
                len = (size_t)(ptr_found + strlen(pat) - p);
                p = p + fwrite(p, 1, len, stdout);
                printf(RESET);
                /* Find next match if any */
            } while ((ptr_found = brute_force_search(p, pat)) != NULL);
            /* Print last characters */
            printf("%s", p);
        }
        ++num;
    }

    free(buf);
    fclose(fp);
    return EXIT_SUCCESS;
}
