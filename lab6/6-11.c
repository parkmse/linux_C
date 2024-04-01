#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int main(void)
{
	struct point{
		int x;
		int y;
	};
	struct point pt1 = { 10, 20 }; // 구조체 변수 pr1
	struct point pt2 = { 30, 40 };

	int dist_x = pt2.x - pt1.x;
	int dist_y = pt2.y - pt1.y; // 좌표를 선정하여 pt2 - pt1을 통해 거리 계산.
	double dist = sqrt(dist_x * dist_x + dist_y * dist_y); // 피타고라스 정리

	printf("두 점 간의 거리: %.2lf\n", dist);

	int z = fabs(dist_x);
	int h = fabs(dist_y); // 절댓값으로 z와 h 계산

	double area = z * h;// 가로 * 세로

	printf("사각형의 넓이: %.2lf\n", area);

	return 0;
}
