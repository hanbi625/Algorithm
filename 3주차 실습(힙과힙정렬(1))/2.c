#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void rBuildHeap(int);
void buildHeap();
void printHeap();
void downHeap(int);
int H[100] = { 0 }, n; //순차힙 생성, 원소개수 n
int main() {

	scanf("%d", &n); //키 개수 입력받기
	for (int i = 1; i <= n; i++) {
		scanf("%d", &H[i]); //N개의 k 입력받기
	}
	buildHeap();
	printHeap();

	return 0;
}
void rBuildHeap(int i) { //재귀방식으로 상향식 힙 생성
	if (i > n)
		return;
	rBuildHeap(2 * i); //왼쪽 자식 힙 생성
	rBuildHeap(2 * i + 1); //오른쪽 자식 힙 생성
	downHeap(i); //현재 노드와 왼쪽 자식, 오른쪽 자식 합친 힙 생성
}
void buildHeap() { //비재귀 방식으로 상향식 힙 생성
	for (int i = n / 2; i >= 1; i--)
		downHeap(i);
	//마지막 내부노드부터 루트까지 역방향으로 반복하여 downHeap 실행
}
void downHeap(int i) { //최대힙만들기
	int big;
	if (i * 2 > n)
		return; //자식이 없으면 종료
	big = 2 * i; //왼쪽 자식이 내부노드이면 big에 저장
	if (H[i * 2 + 1] > H[big]) {//오른쪽 자식 노드가 크면 big에 젖ㅇ
		big = i * 2 + 1;
	}
	if (H[i] >= H[big]) //현재 노드가 자식 노드보다 크면 종료
		return;
	//그 외의 경우 현재노드랑 big이랑 바꾸기
	int tmp = H[i];
	H[i] = H[big];
	H[big] = tmp;
	downHeap(big); //big에 대한 downHeap 실행 
}
void printHeap() {
	for (int i = 1; i <= n; i++)
		printf(" %d", H[i]);
	//레벨 순서로 힙의 내용을 인쇄
	printf("\n");
}
