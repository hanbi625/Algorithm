#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct vertices {
	int n, ck;
}Vertices;
typedef struct edge {
	int ver1, ver2, ck;
}Edges;
typedef struct graph {
	Vertices* ver;
	Edges* edge;
	int** adjacency;
	int esize;
	int size;
}Graph;
void makeGraph(Graph* G, int n, int m);
void insert(Graph* G, int v1, int v2);
void BFS(Graph* G, int n, int s);
int main() {
	int n, m, s, u, v;
	Graph G;

	//정점의 개수 n, 간선의 개수 m, 순회 시작 정점 번호 s 입력하기
	scanf("%d %d %d", &n, &m, &s);
	makeGraph(&G, n, m);
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &u, &v); //간선 u, v 입력받기
		insert(&G, u, v); //간선 추가하기
	}
	BFS(&G, n, s);

	return 0;
}
void makeGraph(Graph* G, int n, int m) { //그래프 만들기
	G->ver = (Vertices*)malloc(sizeof(Vertices) * n); //ver 동적할당
	G->edge = (Edges*)malloc(sizeof(Edges) * m); //edge 동적할당
	G->adjacency = (int**)malloc(sizeof(int*) * n); //adjancey 동적할당 (이차원배열)
	
	for (int i = 0; i < n; i++) {
		G->ver[i].n = (i + 1); //노드 이름 만들기
		G->ver[i].ck = 0; //0으로 초기화
		G->adjacency[i] = (int*)malloc(sizeof(int) * n);
		for (int j = 0; j < n; j++) //-1로 초기화
			G->adjacency[i][j] = -1;
	}
	for (int i = 0; i < m; i++) //ck 0으로 초기화
		G->edge[i].ck = 0;
	G->size = n; //그래프 사이즈 초기화 
	G->esize = 0;
}
void insert(Graph* G, int v1, int v2) { //삽입함수
	int idx = -1; //인덱스 -1로 초기화

	for (int i = 0; i < G->esize; i++) { //반복문으로 중복검사 및 list 추가
		if (G->edge[i].ver1 == v1 && G->edge[i].ver2 == v2) {
			idx = i;
			break;
		}
		if (G->edge[i].ver1 == v2 && G->edge[i].ver2 == v1) {
			idx = i;
			break;
		}
	}
	if (idx == -1) //idx가 -1이면 esize값 넣어주기
		idx = G->esize;
	G->edge[idx].ver1 = v1;
	G->edge[idx].ver2 = v2;
	G->edge[idx].ck = 1;

	G->adjacency[v1 - 1][v2 - 1] = idx;
	G->adjacency[v2 - 1][v1 - 1] = idx;

	G->esize++; //사이즈 증가
}
void BFS(Graph* G, int n, int s) {
	int* tmp = (int*)malloc(sizeof(int) * n); //tmp 동적할당
	int N = 1, cnt = 0;
	
	printf("%d\n", s); //정점 번호 출력
	for (int i = 0; i < n; i++)
		tmp[i] = 0;
	tmp[0] = s;
	G->ver[s - 1].ck = 1;

	while (cnt < n) { //cnt가 n보다 작을 동안 반복
		for (int i = 0; i < n; i++) { //n번 반복하기
			if (tmp[cnt] != 0) {
				if (G->adjacency[tmp[cnt] - 1][i] != -1 && G->ver[i].ck == 0) {
					printf("%d\n", G->ver[i].n);
					G->ver[i].ck = 1;
					tmp[N] = i + 1;
					N++;
				}
			}
		}
		cnt++; //cnt 증가
	}
}
