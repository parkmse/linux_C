#include <stdio.h>
int main()
{
        double x = 1; // double형 변수 선언(값이 크기 때문)
        for (int i = 20; i>=1; i--) // i는 20부터 1보다 크거나 같아질때까지 감소
        {
                x *= i; // x에 x*i값 대입
        }

        printf("factorial is\n%.0lf\n",x); // 소숫점 그 이후 자리는 안보이게 출력
        return 0;
}

