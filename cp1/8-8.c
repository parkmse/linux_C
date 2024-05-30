#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_WORDS 100
#define MAX_WORD_LEN 50

int compare_strings(const void* a, const void* b) {
    const char* pa = *(const char**)a;
    const char* pb = *(const char**)b;
    return strcmp(pa, pb);
}

int main(int argc, char* argv[]) {
    char* words[MAX_WORDS];
    int num_words = 0;
    int i, reverse = 0;

    if (argc < 2) {
        printf("Usage: %s [-r] word1 word2 ...\n", argv[0]);
        return 1;
    }

    if (strcmp(argv[1], "-r") == 0) {
        reverse = 1;
        argc--;
        argv++;
    }

    if (argc - 1 > MAX_WORDS) {
        printf("Too many words! Maximum is %d.\n", MAX_WORDS);
        return 1;
    }

    for (i = 1; i < argc; i++) {
        if (strlen(argv[i]) > MAX_WORD_LEN) {
            printf("Word '%s' is too long! Maximum is %d characters.\n",
                   argv[i], MAX_WORD_LEN);
            return 1;
        }
        words[num_words++] = argv[i];
    }

    qsort(words, num_words, sizeof(char*), compare_strings);

    if (reverse) {
        for (i = num_words-1; i >= 0; i--) {
            printf("%s\n", words[i]);
        }
    } else {
        for (i = 0; i < num_words; i++) {
            printf("%s\n", words[i]);
        }
    }

    return 0;
}

