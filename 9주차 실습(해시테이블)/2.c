#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int findElement(int *H, int k, int M);
int insertItem(int *H, int k, int M);
void initBucketArray(int* H, int M);
int main() {
	char order;
	int x, M, n;

	scanf("%d %d", &M, &n); //해시테이블의 크기 M과 입력 데이터의 크기 n입력받기
	int* H = (int*)malloc(sizeof(int) * M); //크기 H인 배열 동적할당
	initBucketArray(H, M); //초기화하기

	while (1) {
		scanf("%c", &order); //명령어 입력받기
		if (order == 'e') break; //e를 입력받으면 종료
		switch (order) {
		case 'i' : //i(삽입)를 입력받으면
			scanf("%d", &x); //키 입력받기
			getchar();
			printf("%d\n", insertItem(H, x, M)); //해시테이블에 삽입 후 인덱스 출력
			break;
		case 's': //s(탐색)를 입력받으면
			scanf("%d", &x); //탐색할 키 입력받기
			int f = findElement(H, x, M);//키 x가 해시테이블에 존재하는지 탐색
			if (f == -1) printf("%d\n", f); //없으면 -1 출력
			else 
				printf("%d %d\n", f, x);//있으면 인덱스와 원소 출력
			break;
		case 'e':
			break;
		}
	}
	
	return 0;
}
void initBucketArray(int* H, int M) { //배열 초기화 함수
	for (int i = 0; i < M; i++)
		H[i] = 0;
}
int findElement(int *H, int k, int M) { //원소 찾는 함수
	for (int i = 0; i < M; i++) //해시테이블 속 원소 찾기
		if (H[i] == k) //i번째 원소가 k랑 같으면
			return i; //인덱스 i 반환
	return -1; //없으면 -1 반환
}
int insertItem(int *H, int k, int M) { //해시테이블에 삽입하는 함수
	int hx = k % M; //hx에 k를 M으로 나눈 나머지 저장
	while (H[hx] != 0) { //H 속 원소가 0이 아닐동안 반복하기
		printf("C"); //C 출력
		hx = (hx + 1) % M;
	}
	H[hx] = k; //hx 값 정한 후 hx번째에 k 넣기
	return hx; //hx(인덱스) 반환
}

