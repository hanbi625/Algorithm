#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
int getNextBucket(int hx, int i, int x, int M, int q);
int findElement(int* H, int k, int M, int q);
int insertItem(int* H, int k, int M, int q);
void initBucketArray(int* H, int M);
void print(int* H, int M);
int main() {
	char order;
	int x, M, n, q;

	scanf("%d %d %d", &M, &n, &q); //해시테이블의 크기 M과 입력 데이터의 크기 n입력받기, 두번째 해싱함수 q입력
	int* H = (int*)malloc(sizeof(int) * M); //크기 H인 배열 동적할당
	initBucketArray(H, M); //초기화하기

	while (1) {
		scanf("%c", &order); //명령어 입력받기
		switch (order) {
		case 'i': //i(삽입)를 입력받으면
			scanf("%d", &x); //키 입력받기
			getchar();
			printf("%d\n", insertItem(H, x, M, q)); //해시테이블에 삽입 후 인덱스 출력
			break;
		case 's': //s(탐색)를 입력받으면
			scanf("%d", &x); //탐색할 키 입력받기
			int f = findElement(H, x, M, q);//키 x가 해시테이블에 존재하는지 탐색
			if (f == -1) printf("%d\n", f); //없으면 -1 출력
			else
				printf("%d %d\n", f, x);//있으면 인덱스와 원소 출력
			break;
		case 'p': //p(출력)를 입력받으면
			print(H, M); //현재의 해시테이블 입력
			break;
		case 'e': //e를 입력받으면 
			print(H, M); //해시테이블 인쇄후 종료
			return 0;
		}
	}

	return 0;
}
void initBucketArray(int* H, int M) { //배열 초기화 함수
	for (int i = 0; i < M; i++)
		H[i] = 0;
}
int getNextBucket(int hx, int i, int x, int M, int q) {
	return (hx + i * (q - (x % q))) % M; //이중해싱
}
int findElement(int* H, int k, int M, int q) { //원소 찾는 함수
	int hx = k % M; //hx 설정
	int i = 0, b;
	while (i < M) {
		b = getNextBucket(hx, i, k, M, q); //인덱스 설정
		if (H[b] == 0) //비어있으면 -1 반환
			return -1;
		else if (k == H[b]) //k 찾으면 인덱스 반환
			return b;
		else i++; //그 외의 경우 i 증가
	}
	return -1;
}
int insertItem(int* H, int k, int M, int q) { //해시테이블에 삽입하는 함수
	int hx = k % M; //hx 설정
	int b, i = 0;
	while (i < M) {
		b = getNextBucket(hx, i, k, M, q); //인덱스 설정
		if (H[b] == 0) { //비어있으면 삽입 후 인덱스 반환
			H[b] = k;
			return b;
		}
		else i++; //그 외의 경우 i 증가
		printf("C"); //충돌시 C 출력
	}
	return b; //인덱스 반환
}
void print(int* H, int M) { //해시테이블 출력 함수
	for (int i = 0; i < M; i++) //모든 원소 출력
		printf(" %d", H[i]);
	printf("\n");
}

