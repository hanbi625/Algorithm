#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct NODE { //이중연결리스트 노드 만들기
	struct NODE* pre;
	struct NODE* next;
	char e;
}NODE;
typedef struct List { //헤더랑 트레일러 만들기
	struct NODE* header;
	struct NODE* tail;
}LIST;
NODE* getnode(); //노드 만드는 함수
void mlist(LIST*); //리스트 만드는 함수
void add(LIST*, int, char); //원소 추가(add) 함수
void delete(LIST*, int); //원소 삭제(delete) 함수
char get(LIST*, int); //원소 반환(get) 함수
void print(LIST*); //원소 출력(print) 함수
int main() {
	LIST list;
	char ch, e;
	int r, n = 0; //순위 r, 원소 개수 n 선언
	int N; //연산 개수 N 선언

	mlist(&list); //리스트 만들기

	scanf("%d", &N); //연산 개수 입력
	for (int i = 0; i < N; i++) {
		getchar();
		scanf("%c", &ch); //연산 종류 입력
		switch (ch) {
		case 'A': //연산 종류가 'A'일때
			scanf("%d %c", &r, &e); //저장 순위와 원소 입력
			if (r < 1 || r > n + 1) {
				printf("invalid position\n");
				break; //순위 정보가 유효하지 않으면 에러 메시지 출력 후 종료
			}
			add(&list, r, e); //add 함수 실행
			n++; //원소 개수 증가
			break;
		case 'D': //연산 종류가 'D'일때
			scanf("%d", &r); //삭제할 순위 입력
			if (r <1 || r > n) {
				printf("invalid position\n");
				break;
			}//순위 정보가 유효하지 않으면 에러 메시지 출력 후 종료
			delete(&list, r); //delete 함수 실행
			n--; //원소 개수 감소
			break;
		case 'G': //연산 종류가 'G'일때
			scanf("%d", &r);//반환할 원소 순위 입력
			if (r < 1 || r > n) {
				printf("invalid position\n");
				break;
			}//순위 정보가 유효하지 않으면 에러 메시지 출력 후 종료
			printf("%c\n", get(&list, r)); //get 함수 실행
			break;
		case 'P': //연산 종류가 'P'일때
			print(&list); //print 함수 실행
			break;
		}
	}
	return 0;
}
NODE* getnode() { //노드 만들기
	NODE* node;
	node = (NODE*)malloc(sizeof(NODE));
	node->next = NULL;
	node->pre = NULL;
	return node;
}
void mlist(LIST* list) { //리스트 만들기
	list->header = getnode();
	list->tail = getnode();
	list->header->next = list->tail;
	list->tail->pre = list->header;
}
void add(LIST* list, int r, char e) {
	NODE* node, *p;
	node = getnode();
	node->e = e;
	p = list->header;
	for (int i = 0; i < r; i++)
		p = p->next; //p가 저장할 노드 순위일때까지 반복
	node->pre = p->pre;
	node->next = p;
	p->pre->next = node;
	p->pre = node; //지정 순위에 노드 넣기
}
void delete(LIST* list, int r) {
	NODE* p;
	p = list->header;
	for (int i = 0; i < r; i++)
		p = p->next; //삭제할 순위까지 반복문
	p->pre->next = p->next;
	p->next->pre = p->pre;
	free(p); //r순위 노드 삭제
}
char get(LIST* list, int r) {
	NODE* p;
	p = list->header;
	for (int i = 0; i < r; i++)
		p = p->next; //지정 순위까지 반복문 돌기
	return p->e; //반환
}
void print(LIST* list) {
	NODE* p;
	for (p = list->header->next; p != list->tail; p = p->next)
		printf("%c", p->e); //헤더 다음부터 트레일러 전까지 반복
	printf("\n");
}
