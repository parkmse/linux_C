#include <stdio.h>
#include <string.h>

#define MAX_LEN 100

int main(int argc, char *argv[]) {
    int reverse = 0;

    // -r 옵션이 있는지 확인
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "-r") == 0) { // -r 옵션이 주어졌을 때
            reverse = 1; // reverse에 1 대입
        }
    }

    // 입력된 문자열을 출력
    if (reverse) {
        for (int i = argc - 1; i > 1; i--) {
            printf("%s ", argv[i]);
        }
    } else {
        for (int i = 1; i < argc; i++) {
            printf("%s ", argv[i]);
        }
    }
    putchar('\n');

    return 0;
}

