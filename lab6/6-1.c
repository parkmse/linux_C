#include <stdio.h>
#include <math.h> 
#include <stdlib.h>

// point 구조체 정의
struct point {
    int x;
    int y;
};

// 두 점 사이 거리 계산 함수
double distance(struct point pt1, struct point pt2) {
    int dist_x = pt2.x - pt1.x;
    int dist_y = pt2.y - pt1.y;

    // 피타고라스 정리 이용
    return sqrt(dist_x * dist_x + dist_y * dist_y);
}

// 두 점에 의한 사각형의 넓이 계산 함수
double area(struct point pt1, struct point pt2) {
    int dist_x = pt2.x - pt1.x;
    int dist_y = pt2.y - pt1.y;

    // 가로와 세로의 길이를 구하여 넓이 계산
    return abs(dist_x) * abs(dist_y);
}

int main(void) {
    struct point pt1 = {10, 20};
    struct point pt2 = {30, 40};

    // 두 점 사이의 거리와 사각형의 넓이를 계산하고 출력
    double dist = distance(pt1, pt2);
    printf("두 점 간의 거리: %.2f\n", dist);

    double a = area(pt1, pt2);
    printf("사각형의 넓이: %.2f\n", a);

    return 0;
}
