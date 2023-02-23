#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
void insertItem(int);
void inPlaceHeapSort();
void downHeap(int);
void upHeap(int);
void rBuildHeap(int);
void buildHeap();
void printArray();
int H[100] = { 0 }, n = 0, N;
int main() {
	scanf("%d", &n); //키 개수 입력
	N = n;
	for (int i = 1; i <= n; i++) {
		scanf("%d", &H[i]);
	}//n개의 키 입력받기
	inPlaceHeapSort();
	printArray();
	return 0;
}
void insertItem(int k) {
	n++; //n 갱신
	H[n] = k; //n위치에 k 삽입
	upHeap(n); //힙 조정
}
void upHeap(int i) {
	if (i == 1) return; //루트면 종료
	if (H[i] <= H[i / 2]) //부모 노드보다 키 크기가 작으면 종료
		return;
	//그렇지 않으면 부모 노드랑 키 바꾸기
	int tmp = H[i];
	H[i] = H[i / 2];
	H[i / 2] = tmp;
	upHeap(i / 2); //부모노드로 upHeap 실행
}
void inPlaceHeapSort() { //무순배열을 제자리 힙 정렬
	int tmp;
	buildHeap(); //힙정렬 1기작업
	for (int i = n; i > 1; i--) { //힙정렬 2기작업
		tmp = H[1];
		H[1] = H[i];
		H[i] = tmp;
		N--;
		downHeap(1);
	}
}
void printArray() {
	for (int i = 1; i <= n; i++) //힙에 저장된 n개의 원소 출력
		printf(" %d", H[i]);
	printf("\n");
}
void downHeap(int i) { //최대힙만들기
	int big;
	if (i * 2 > N)
		return; //자식이 없으면 종료
	big = 2 * i; //왼쪽 자식이 내부노드이면 big에 저장
	if (2 * i + 1 <= N) { //오른쪽 자식이 N보다 작은 동안
		if (H[i * 2 + 1] > H[big]) {//오른쪽 자식 노드가 크면 big에 오른쪽 자식 저장
			big = i * 2 + 1;
		}
	}
	if (H[i] >= H[big]) //현재 노드가 자식 노드보다 크면 종료
		return;
	//그 외의 경우 현재노드랑 big이랑 바꾸기
	int tmp = H[i];
	H[i] = H[big];
	H[big] = tmp;
	downHeap(big); //big에 대한 downHeap 실행 
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
