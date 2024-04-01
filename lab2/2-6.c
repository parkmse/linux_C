#include <stdio.h>

int htoi(char s[])
{
	int i, n = 0;
	
	for (i = 0; s[i] != '\0'; ++i) // '\0'이 나오기까지 반복
	{
		if (s[i] >= '0' && s[i] <= '9')
		{
			n = n*16 + (s[i] - '0'); 
		}
		else if (s[i] >= 'a' && s[i] <= 'f')
	       	{
		       	n = n*16 + (s[i] - 'a' + 10); // 소문자에 10을 더해 소문자 a를 10으로 인식
	       	}
	       	else if (s[i] >= 'A' && s[i] <= 'F')
	       	{
		       	n = n*16 + (s[i] - 'A' + 10); // 대문자 동일
		}
	       	else
		{
			return -1; // 잘못된 문자가 입력되면 -1 반환
		}
    }
    return n; // n값을 return
}

int main(void)
{
	char h[] = "12AF";

	printf("%s\n", h);
	printf("%x\n", htoi(h)); // 16진수 대문자를 소문자로 출력
	printf("%d\n", htoi(h)); // integer 형태로 변환

	return 0;
}

