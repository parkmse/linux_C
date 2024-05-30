#include <stdio.h>

void deciToBin(int decimalNum) {
    int binaryNum[32];
    int i = 0;
    while (decimalNum > 0) {
        binaryNum[i] = decimalNum % 2; //입력한 2진수에 10진수 %2 대입
        decimalNum = decimalNum / 2;
        i++; 
    }
    for (int j = i - 1; j >= 0; j--) {
        printf("%d", binaryNum[j]);
    }
}

int main() {
    int decimalNum;
    printf("십진수를 입력하세요: ");
    scanf("%d", &decimalNum);
   // printf("%d", decimalNum);
    if(decimalNum == 0)
    {
	    printf("%d",decimalNum); //decimalNum이 0일때 0 미출력 방지 코드
    }
    deciToBin(decimalNum);
    printf("\n");
    return 0;
}

