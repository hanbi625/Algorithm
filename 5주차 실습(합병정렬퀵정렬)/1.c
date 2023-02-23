#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct node {
	int x;
	struct node* next;
	int n;
}NODE;
typedef struct list {
	NODE* L;
	int n;
}LIST;
NODE* getnode();
LIST* mlist();
int isEmpty(LIST*);
LIST* mergeSort(LIST*);
LIST* merge(LIST*, LIST*);
LIST* partition(LIST*, int);
void addLast(LIST*, int);
int removeFirst(LIST*);
int get(LIST*);
void print(LIST*);
int main() {
	LIST* list;
	int n, e;

	list = mlist();
	scanf("%d", &n); //리스트 크기 입력받기
	for (int i = 0; i < n; i++) { //n번 반복
		scanf("%d", &e);
		addLast(list, e); //리스트에 원소 삽입
	}
	
	list = mergeSort(list); //합병정렬 함수 실행
	print(list); //리스트 출력하기

	return 0;
}
NODE* getnode() { //동적할당 이용하여 node 만들기
	NODE* node = NULL;
	node = (NODE*)malloc(sizeof(NODE));
	node->next = NULL; //next를 NULL로 초기화
	return node;
}
LIST* mlist() {
	LIST* list;
	list = (LIST*)malloc(sizeof(LIST)); //리스트 생성
	list->L = getnode();
	list->n = 0; //리스트 원소 개수 0으로 초기화
	return list;
}
void addLast(LIST* list, int e) { //리스트 끝에 원소 삽입
	NODE* p = getnode(); //노드 생성
	NODE* q;
	if (list->n == 0) //리스트가 비어있으면
		list->L->x = e; //리스트 처음에 저장
	else { //그렇지않은경우
		p->x = e;
		q = list->L;
		for (; q->next != NULL; q = q->next); //리스트 맨끝으로 이동
		q->next = p; //리스트 맨끝에 노드 삽입
	}
	list->n++; //원소 개수 증가
}
int removeFirst(LIST* list) { //첫번째 원소 삭제 함수
	NODE* p = list->L; //노드 p는 리스트의 첫 원소 가리킴
	int e = list->L->x; //e에 리스트 첫번째 원소 저장
	list->L = list->L->next; //다음노드로 이동
	p->next = NULL;
	free(p); //첫 원소 삭제
	p = NULL;
	list->n--; //리스트 원소 개수 감소
	return e; //첫 원소 반환
}
int isEmpty(LIST* list) { //만약 리스트가 비었으면
	if (list->n == 0) return 1; //1 반환
	return 0; //리스트가 비어있지 않으면 0반환
}
int get(LIST* list) { //리스트의 첫번째 원소 반환
	return list->L->x;
}
LIST* mergeSort(LIST* list) {
	LIST* L1, * L2;
	if (list->n > 1) { //리스트 원소 개수가 1보다 많으면 (베이스케이스)
		L1 = list;
		L2 = partition(list, list->n / 2);//L을 L1과 L2로 분할
		L1 = mergeSort(L1); //L1 재귀적으로 정렬
		L2 = mergeSort(L2); //L2 재귀적으로 정렬
		list = merge(L1, L2); //L1과 L2 합병
	}
	return list;
}
LIST* merge(LIST* L1, LIST* L2) {
	LIST* L;
	L = mlist(); //리스트 생성
	while (!isEmpty(L1) && !isEmpty(L2)) { //L1과 L2가 비어있지 않을때
		if (get(L1) <= get(L2)) //L1의 첫번째 원소가 L2의 첫번쨰 원소보다 작거나 같으면
			addLast(L, removeFirst(L1)); //리스트 L에 L1의 첫번째 원소 저장
		else //그 외의 경우
			addLast(L, removeFirst(L2)); //L에 L2의 첫번째 원소 저장
	}
	while (!isEmpty(L1)) { //L1이 비어있지 않으면
		addLast(L, removeFirst(L1)); //L1의 원소 리스트 L에 저장
	}
	while (!isEmpty(L2)) { //L2가 비어있지 않으면
		addLast(L, removeFirst(L2)); //L2의 원소 리스트 L에 저장
	}
	return L;//리스트 L 반환
}
LIST* partition(LIST* L1, int k) { //분할 함수
	LIST* L2 = NULL;
	NODE* p = L1->L; //p는 L1 가리킴
	L2 = mlist(); //L2 리스트 만들기
	for (int i = 0; i < k -1; i++)
		p = p->next; //k-1번동안 반복하여 다음노드로 이동
	if (p != NULL) { //p가 NULL이 아니면
		L2->L = p->next; //L2리스트에 저장
		p->next = NULL;
	}
	L2->n = L1->n - k; //크기가|L|-k인 부리스트 만들기
	L1->n = k; //크키가 k인 부리스트 만들기
	return L2; //L2반환
}
void print(LIST *list) {
	NODE* p;
	p = list->L;
	for (; p != NULL; p = p->next) //리스트의 원소 출력
		printf(" %d", p->x);
	printf("\n");
}
