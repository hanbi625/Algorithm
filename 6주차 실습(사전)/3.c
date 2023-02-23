#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int findKey(int, int, char*);
int main() {
	int a, b, n;
	char str[101] = { 0 };

	scanf("%d %d %d", &a, &b, &n); //a와 b, Y/N의 개수 입력받기
	scanf("%s", str); //Y/N 입력받기
	printf("%d", findKey(a, b, str)); //k 출력

	return 0;
}
int findKey(int a, int b, char* str) {
	int m = (a + b) / 2; //m은 a와 b사이의 중간값
	int i = 0;
	while (a != b) {
		if (a == b) break; //a와 b가 같을 때 까지 반복
		m = (a + b) / 2;//m은 a와 b사이의 중간값
		if (str[i] == 'Y') //답이 Y인 경우
			a = m + 1; //a의 값을 m+1로 바꿔준다.
		if (str[i] == 'N') //답이 N인 경우
			b = m; //b의 값을 m으로 바꾼다.
		i++;
	}
	return a;
}
