#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct node {
	int key;
	struct node* next;
}NODE;
NODE* getnode(int k);
int findeElement(NODE *H, int k, int M);
void insertItem(NODE *H, int k, int M);
int removeElement(NODE *H, int k, int M);
void initBucketArray(NODE* H, int M);
void print(NODE* H, int M);
int main() {
	char order;
	int x, M;

	scanf("%d", &M); //크기 M입력받기
	NODE* H = (NODE*)malloc(sizeof(NODE) * M); //크기 H인 배열 동적할당
	initBucketArray(H, M); //크기 H인 해시테이블 만들기

	while (1) {
		scanf("%c", &order); //명령어 입력받기
		if (order == 'e') break; //e를 입력받으면 종료
		switch (order) {
		case 'i' : //i(삽입)를 입력받으면
			scanf("%d", &x); //키 입력받기
			getchar();
			insertItem(H, x, M); //해시테이블에 삽입
			break;
		case 's': //s(탐색)를 입력받으면
			scanf("%d", &x); //탐색할 키 입력받기
			printf("%d\n", findeElement(H, x, M)); //키 x가 해시테이블에 존재하는지 탐색
			break;
		case 'd'://d(삭제)를 입력받으면
			scanf("%d", &x); //삭제할 키 입력받기
			printf("%d\n", removeElement(H, x, M)); //키가 해시테이블에 존재하면 삭제
			break;
		case 'p' : //p(인쇄)를 입력받으면
			print(H, M); //해시테이블에 저장된 키들을 순서대로 인쇄
			break;
		case 'e':
			break;
		}
	}
	
	return 0;
}
NODE* getnode(int k) { //키 k를 가진 노드 만들기
	NODE* node = (NODE*)malloc(sizeof(NODE)); //동적할당
	node->next = NULL; //next를 NULL로 초기화
	node->key = k; //key에 k 넣기
	return node; //node 반환
}
void initBucketArray(NODE* H, int M) { //배열 초기화 함수
	for (int i = 0; i < M; i++) { //M개의 배열을 반복하여
		H[i].key = 0; //key값 초기화
		H[i].next = NULL; //next를 NULL로 초기화
	}
}
int findeElement(NODE *H, int k, int M) {
	int hx = k % M, cnt = 0; //hx는 k를 M으로 나눈 나머지, cnt 0으로 초기화
	NODE* p = H + hx; //p는 H 0번째 인덱스에서 hx만큼 떨어진 인덱스 가리키기
	while (p->next != NULL) { //p의 next가 NULL이 아닐동안 반복
		p = p->next; //p 다음으로 이동
		cnt++; //cnt 1더하기
		if (p->key == k) //p의 key가 k랑 같으면
			return cnt; //cnt 반환
	}
	return 0; //그 외의 경우 0 반환
}
void insertItem(NODE *H, int k, int M) { //해시테이블에 삽입하는 함수
	NODE* node = getnode(k); //k를 key로 가지는 노드 생성
	int hx = k % M; //k를 m으로 나눈 나머지
	NODE* p = H + hx; //p값 조정

	if (p->next == NULL) //비어있으면 node 삽입
		p->next = node;
	else { //그 외의 경우 맨 앞에 새 node 넣기
		node->next = p->next;
		p->next = node;
	}
}
int removeElement(NODE *H, int k, int M) {
	int hx = k % M;
	int res = findeElement(H, k, M); //k를 가진 노드 찾기
	if (res == 0) return 0; //없으면 0반환

	NODE* p = H + hx;
	while (p->next->key != k) //k를 발견할때까지 next로 이동
		p = p->next;
	NODE* q = p->next; //q에 p의 next저장
	p->next = p->next->next; //p의 next 넘기기
	free(q); //q삭제
	q = NULL;
	return res; //res 반환
}
void print(NODE* H, int M) { //전체 출력함수
	NODE* p;
	for (int i = 0; i < M; i++) {
		p = H + i;
		while (p->next != NULL) {
			printf(" %d", p->next->key);
			p = p->next;
		}
	}
	printf("\n");
}
