#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct tree { //트리 노드 만들기
	int data;
	struct tree* left;
	struct tree* right;
}TREE;
void search(TREE*); //탐색 함수
void insert(TREE*, char, int); //삽입 함수
TREE* leftChild(TREE*); //왼쪽 자식 노드
TREE* rightChild(TREE*); //오른쪽 자식 노드
TREE* findid(TREE*, int); //id 찾기 함수
int main() {
	TREE root; //루트 만들기
	int N, id, lid, rid;
	//원소 개수, id 입력, 왼쪽 id, 오른쪽 id 선언

	root.left = NULL; //루트의 왼쪽에 NULL
	root.right = NULL; //루트의 오른쪽에 NULL
	scanf("%d", &N); //노드 개수 입력받기
	for (int i = 0; i < N; i++) { //반복문
		scanf("%d %d %d", &id, &lid, &rid);
		if (i == 0) { //처음 노드 일 경우
			root.data = id; //노드에 id 입력
			if (lid != 0) insert(&root, 'L', lid); //왼쪽 id가 0이 아닐 경우 삽입
			if (rid != 0) insert(&root, 'R', rid); //오른쪽 id가 0이 아닐 경우 삽입
		}
		else { //처음 노드가 아닐 경우
			TREE* p = findid(&root, id); //id 찾기
			if (lid != 0) insert(p, 'L', lid); //왼쪽 id가 0이 아닐 경우 삽입
			if (rid != 0) insert(p, 'R', rid); //오른쪽 id가 0이 아닐 경우 삽입
		}
	}
	search(&root); //트리 탐색
	return 0;
}
void search(TREE* root) {
	char ch[101] = { 0 }; 
	int N;

	scanf("%d", &N); //탐색 횟수 입력받기
	for (int i = 0; i < N; i++) {
		getchar();
		scanf("%s", ch); //탐색 문자열 입력받기
		TREE* v = root;
		printf(" %d", v->data);
		for (int j = 0; j < strlen(ch); j++) { //문자열 길이만큼 반복
			if (ch[j] == 'R') v = rightChild(v); //R이면 오른쪽 노드 방문
			if (ch[j] == 'L') v = leftChild(v); //L이면 왼쪽 노드 방문
			printf(" %d", v->data); //트리 정보 출력
		}
		printf("\n"); //개행문자 출력
	}
}
void insert(TREE* v, char ch, int id) { //삽입함수
	TREE* tree = (TREE*)malloc(sizeof(TREE));
	tree->data = id;
	tree->left = NULL;
	tree->right = NULL; //트리 노드 생성
	if (ch == 'R') v->right = tree;	//트리 오른쪽에 새 노드 연결
	if (ch == 'L') v->left = tree; //트리 왼쪽에 새 노드 연결
}
TREE* leftChild(TREE* v) {
	return v->left; //왼쪽 노드 반환
}
TREE* rightChild(TREE* v) {
	return v->right; //오른쪽 노드 반환
}
TREE* findid(TREE* v, int id) { //id 찾기 함수
	if (v != NULL) { //NULL이 아닐 동안
		if (v->data == id)
			return v;//찾는 id와 트리 노드의 id가 같을 경우 노드 반환
		else {
			TREE* p = findid(leftChild(v), id); //재귀함수 이용하여 왼쪽 노드 반복 탐색
			if (p != NULL) return p; //p가 NULL이 아니면 반환
			p = findid(rightChild(v), id); //재귀함수 이용하여 오른쪽 노드 반복
			if (p != NULL) return p; //p가 NULL이 아니면 반환
		}
	}
	return NULL; //id 못 찾으면 NULL반환-> p로 들어감
}
