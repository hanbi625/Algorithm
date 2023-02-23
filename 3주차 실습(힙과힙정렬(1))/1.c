#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void insertItem(int);
int removeMax();
void printHeap();
void upHeap(int);
void downHeap(int);
int H[100] = { 0 }, n = 0; //순차힙 생성, 원소개수 n
int main() {
	int k;
	char order;

	while (1) {
		scanf("%c", &order);

		switch (order) {
		case 'i': //i를 입력받으면
			scanf("%d", &k); //키 입력받기
			insertItem(k); //n위치에 k 삽입 함수 실행
			printf("0\n"); //0출력하기
			break;
		case 'd': //d를 입력받으면
			printf("%d\n", removeMax()); //키 삭제 함수 실행
			break;
		case 'p': //p를 입력받으면
			printHeap(); //힙에 저장된 키들을 레벨 순서로 인쇄
			break;
		case 'q':
			return 0;
		}
	}
	return 0;
}
void insertItem(int k) {
	n++; //n 갱신
	H[n] = k; //n위치에 k 삽입
	upHeap(n); //힙 조정
}
void upHeap(int i) {
	if (i == 1) return; //루트이면 종료
	if (H[i] <= H[i / 2]) //부모 노드보다 키 크기가 작으면 종료
		return;
	//그렇지 않으면 부모 노드랑 키 바꾸기
	int tmp = H[i];
	H[i] = H[i / 2];
	H[i / 2] = tmp;
	upHeap(i / 2); //부모노드로 upHeap 실행
}
int removeMax() {
	int key = H[1]; //루트 키 보관
	H[1] = H[n]; //힙의 마지막 키를 루트로 이동
	n--; //n 갱신
	downHeap(1); //힙 조정
	return key; //삭제 키 반환
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
