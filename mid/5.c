#include <stdio.h>

int main(int argc, char *argv[]) {
    FILE *fp;
    int lines = 0, words = 0, bytes = 0;
    char c;

    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }

    fp = fopen(argv[1], "r");
    if (fp == NULL) {
        printf("Could not open file: %s\n", argv[1]);
        return 1;
    }

    while ((c = fgetc(fp)) != EOF) {
        bytes++;
        if (c == '\n') lines++;
        if (c == ' ' || c == '\n' || c == '\t') words++;
    }

    // words를 증가시키는 것은 마지막 단어는 공백 없이 문자가 있기 때문에 
    // 파일의 끝에 NULL 문자를 삽입하여 마지막 단어도 세주어야 함.
    words++;

    fclose(fp);

    printf("%d %d %d %s\n", lines, words, bytes, argv[1]);

    return 0;
}

