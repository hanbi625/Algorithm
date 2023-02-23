#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct edge {
	int f, t, w;
}Edges;
typedef struct graph {
	int vertices[6];
	int adjacency[6][6];
	Edges edge[20];
	int size;
}Graph;
void makeGraph(Graph* G);
void insert(Graph* G, int v1, int v2, int w);
void modify(Graph* G, int v1, int v2, int w);
void deleteE(Graph* G, int v1, int v2);
void print(Graph* G, int v);
int main() {
	char order;
	int w, a, b;
	Graph G;
	makeGraph(&G);
	insert(&G, 0, 1, 1);
	insert(&G, 0, 2, 1);
	insert(&G, 0, 3, 1);
	insert(&G, 0, 5, 2);
	insert(&G, 1, 2, 1);
	insert(&G, 2, 4, 4);
	insert(&G, 4, 4, 4);
	insert(&G, 4, 5, 3);
	//간선추가
	while (1) {
		scanf("%c", &order); //명령어 입력받기
		switch (order) {
		case 'a': //a를 입력받았으면
			scanf("%d", &w); //노드번호 입력받기
			getchar();
			print(&G, w - 1); //노드번호 오름차순으로 인쇄하기
			break;
		case 'm': //m으로 입력받기
			scanf("%d %d %d", &a, &b, &w); //간선 a, b의 가중치 w 입력받기
			getchar();
			if (w != 0) modify(&G, a - 1, b - 1, w); //가중치가 0이 아니면 w로 변경하기
			else deleteE(&G, a - 1, b - 1); //w가 0이면 간선 a, b 삭제하기
			break;
		case 'q': //q를 입력받으면 프로그램 종료
			return -1;
		}
	}

	return 0;
}
void makeGraph(Graph* G) { //그래프 만들기
	for (int i = 0; i < 6; i++) {
		G->vertices[i] = i; //i로 노드이름 만들기
		for (int j = 0; j < 6; j++) //-1로 초기화
			G->adjacency[i][j] = -1;
	}
	G->size = 0;
}
void insert(Graph* G, int v1, int v2, int w) { //삽입함수
	Edges* e = G->edge; //edge노드 e 생성
	int idx = -1; //인덱스 -1로 초기화

	for (int i = 0; i < G->size; i++) { //반복문으로 중복검사 및 list 추가
		if (e[i].f == v1 && e[i].t == v2) {
			e[i].w = w;
			idx = i;
			break;
		}
		if (e[i].f == v2 && e[i].t == v1) {
			e[i].w = w;
			idx = i;
			break;
		}
	}
	if (idx == -1)
		idx = G->size;
	e[idx].f = v1;
	e[idx].t = v2;
	e[idx].w = w;

	G->adjacency[v1][v2] = idx;
	G->adjacency[v2][v1] = idx;

	G->size++; //사이즈 증가
}
void modify(Graph* G, int v1, int v2, int w) { //수정함수
	if (v1 < 0 || v1 > 5 || v2 < 0 || v2>5) { //범위를 넘어가면 -1출력후 종료
		printf("-1\n");
		return;
	}
	Edges* e = G->edge; //edge e 생성
	//간선이 존재하지 않으면 새로운 간선 생성
	if (G->adjacency[v1][v2] == -1) insert(G, v1, v2, w);
	else e[G->adjacency[v1][v2]].w = w;
	//존재하면 가중치 변경
}
void deleteE(Graph* G, int v1, int v2) {
	if (v1 < 0 || v1 > 5 || v2 < 0 || v2>5) {//범위를 넘어가면 -1출력후 종료
		printf("-1\n");
		return;
	}
	Edges* e = G->edge;
	G->adjacency[v1][v2] = -1;
	G->adjacency[v2][v1] = -1;
	G->size--;
	//-1로 초기화 후 사이즈 감소
}
void print(Graph* G, int v) {
	Edges* e = G->edge;
	int idx;

	if (v < 0 || v>5) { //존재하지 않으면 -1 출력 후 종료
		printf("-1\n");
		return;
	}
	for (int i = 0; i < 6; i++) {
		idx = G->adjacency[v][i];
		if (idx == -1) continue; //-1이면 continue
		//-1이 아닐경우 출력
		printf(" %d %d", i + 1, e[idx].w);
	}
	printf("\n");
}
