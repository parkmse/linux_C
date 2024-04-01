#include <stdio.h>
#include <string.h>
#define ELEMENTS 7
#define NAMELEN 10

// 문자열 위치를 변경해주는 swap()함수
void swap(char v[][NAMELEN], int i, int j)
{
    char temp[NAMELEN];
    strcpy(temp, v[i]); // 문자열 변경을 위한 strcpy함수 사용
    strcpy(v[i], v[j]);
    strcpy(v[j], temp);
}

// 문자열 배열을 정렬하는 sort() 함수
void sort(char v[][NAMELEN], int left, int right)
{
    int i, last;
    if (left >= right)
	    return; // 정렬 값이 1개 이하면 정렬 중지

    last = left;
    for (i = left + 1; i <= right; i++)
        if (strcmp(v[i], v[left]) < 0) //strcmp 사용하여 v[i] v[left] 비교
            swap(v, ++last, i); // 두개의 값 swap
    // 피벗을 제자리에, 왼쪽 오른쪽 정렬
    swap(v, left, last);
    sort(v, left, last - 1);
    sort(v, last + 1, right);
}

int main(void)
{
    char array[ELEMENTS][NAMELEN] = {"kin", "lee", "park", "choi", "jung", "kang", "cho"};

    for (int i = 0; i < ELEMENTS; i++)
        printf("%s ", array[i]);
    printf("\n");

    // 문자열 배열을 정렬하는 sort() 함수 호출
    sort(array, 0, ELEMENTS - 1);

    for (int i = 0; i < ELEMENTS; i++)
        printf("%s ", array[i]);
    printf("\n");

    return 0;
}
