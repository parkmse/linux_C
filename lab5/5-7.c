#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_LINES 5000
#define MAX_LENGTH 1000

char *line_ptr[MAX_LINES]; // 문자열 포인터 배열 선언

int read_lines(char *line_ptr[], int max_lines);
void write_lines(char *line_ptr[], int num_lines);
void quick_sort(void *line_ptr[], int left, int right, int (*comp)(void *, void *));
int string_cmp(const char *s1, const char *s2);
int num_cmp(const char *s1, const char *s2);

int main(int argc, char *argv[]) {
    int num_lines, numeric;
    numeric = 0;
    if (argc > 1 && strcmp(argv[1], "-n") == 0) { // -n옵션이 있으면 
        numeric = 1; // numeric에 1 대입

    }
// 입력된 문자열을 읽고 정렬 후 출력
    if ((num_lines = read_lines(line_ptr, MAX_LINES)) >= 0) {
        quick_sort((void **) line_ptr, 0, num_lines - 1,
            (int (*)(void *, void *))(numeric ? num_cmp : string_cmp));
        write_lines(line_ptr, num_lines);
        return 0;
    }
    else {
        printf("Error: input too big to sort\n");
        return 1;
    }
}

int read_lines(char *line_ptr[], int max_lines) {
    int num_lines = 0;
    char line[MAX_LENGTH];
    char *p;

    while (fgets(line, MAX_LENGTH, stdin) != NULL) {
        if (num_lines >= max_lines || (p = malloc(strlen(line) + 1)) == NULL) {
            return -1;
        } else { // line_ptr 배열에 문자열 저장 공간이 있고, 메모리 할당도 성공했을 때
            strcpy(p, line); // 문자열을 복사해서 p에 저장
            line_ptr[num_lines++] = p; // p가 가리키는 문자열의 시작 주소를 대입하고 num_lines증가
        }
    }
    return num_lines;
}
// 문자열 출력 함수
void write_lines(char *line_ptr[], int num_lines) {
    for (int i = 0; i < num_lines; i++) {
        printf("%s", line_ptr[i]);

    }
}
// quick 정렬 알고리즘을 사용해 문자열을 정렬하는 함수
void quick_sort(void *line_ptr[], int left, int right, int (*comp)(void *, void *)) {
    if (left >= right) {
        return;
    }

    int i, j;
    char *temp;
    void *pivot = line_ptr[(left + right) / 2];

    i = left;
    j = right;

    while (i <= j) {
        while (comp(line_ptr[i], pivot) < 0) { // 피벗보다 작을 시
            i++; // 인덱스 증가
        }
        while (comp(line_ptr[j], pivot) > 0) { // 크면
            j--; // 감소
        }
        if (i <= j) {
            temp = line_ptr[i];
            line_ptr[i] = line_ptr[j];
            line_ptr[j] = temp;
            i++;
            j--;
        }
    }

    quick_sort(line_ptr, left, j, comp); // 피벗보다 작은쪽을 재귀적으로 호출
    quick_sort(line_ptr, i, right, comp); // 큰쪽을 호출
}

// 두 문자열을 사전순으로 비교
int string_cmp(const char *s1, const char *s2) {
    return strcmp(s1, s2);
}

// 숫자를 기준으로 정렬하는 함수
int num_cmp(const char *s1, const char *s2) {
    double v1, v2;
    v1 = atof(s1);
    v2 = atof(s2);
    if (v1 < v2) { // 첫번째 숫자가 더 작으면 
        return -1; // -1반환
    } else if (v1 > v2) {
        return 1;
    } else { // 두 숫자가 같으면 
        return 0; // 0반환
    }
}

