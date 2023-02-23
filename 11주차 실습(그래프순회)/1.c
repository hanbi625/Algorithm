#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct vertices { //정점
	int n;
	int lab;
	struct incidence* incidence;
}Vertices;
typedef struct edge { //간선
	int lab;
	int ver1;
	int ver2;
}Edges;
typedef struct incidence { //리스트
	struct incidence* next;
	int edge;
}Incidence;
typedef struct graph {
	Vertices* vert;
	Edges* edge;
	int size;
	int esize;
}Graph;
Incidence* getincidence(int edge);
void makeGraph(Graph* G, int n, int m);
void insertIncidence(Graph* G, int v1, int v2, Incidence* incidence);
void insertEdge(Graph* G, int v1, int v2);
void DFS(Graph* G, int s);
void rDFS(Graph* G, int s);
int main() {
	int n, m, s, u, v;
	Graph G;
	//정점의 개수 n, 간선의 개수 m, 순회 시작 정점 번호 s 입력하기
	scanf("%d %d %d", &n, &m, &s);
	makeGraph(&G, n, m);
	for (int i = 0; i < m; i++) {
		scanf("%d %d", &u, &v); //간선 u, v 입력받기
		insertEdge(&G, u, v); //간선 추가하기
	}
	DFS(&G, s);
	return 0;
}
void makeGraph(Graph* G, int n, int m) { //그래프 만들기
	G->size = n; //그래프 크기 0으로 초기화
	G->esize = 0; //edge 사이즈 0으로 초기화
	G->vert = (Vertices*)malloc(sizeof(Vertices) * (n+1));
	G->edge = (Edges*)malloc(sizeof(Edges) * m);
	for (int i = 1; i <= G->size; i++) { //편의를 위해 배열 인덱스 1로 시작
		G->vert[i].incidence = NULL;
		G->vert[i].n = i;
	}
}
Incidence* getincidence(int edge) { //노드 생성 함수
	Incidence* node = (Incidence*)malloc(sizeof(Incidence));
	node->next = NULL;
	node->edge = edge;
	return node; //새노드 incidence 할당 후 반환
}
//리스트 삽입 함수
void insertIncidence(Graph* G, int v1, int v2, Incidence* incidence) {
	Vertices* ver = G->vert;
	Incidence* i;
	int tmp;

	i = ver[v1].incidence;
	if (i == NULL) ver[v1].incidence = incidence; //첫노드일때
	else { //첫노드가 아니면 오름차순 삽입
		if (G->edge[i->edge].ver1 == v1) //head와 비교하기
			tmp = G->edge[i->edge].ver2;
		else tmp = G->edge[i->edge].ver1;

		if (tmp > v2) { //head에서 교환하기
			incidence->next = i;
			ver[v1].incidence = incidence;
		}
		else {
			while (i->next != NULL) {
				if (G->edge[i->next->edge].ver1 == v1)
					tmp = G->edge[i->next->edge].ver2;
				else tmp = G->edge[i->next->edge].ver1;

				if (tmp > v2)
					break;
				i = i->next;
			}
			if (i->next == NULL) i->next = incidence;
			else {
				incidence->next = i->next;
				i->next = incidence;
			}
		}
	}
}
void insertEdge(Graph* G, int v1, int v2) { //edge삽입
	Incidence* i1, * i2;
	int tmp, idx = -1;

	//리스트에 중복 검사하고 추가하기
	for (int i = 0; i < G->esize; i++) {
		if (G->edge[i].ver1 == v1 && G->edge[i].ver2 == v2) {
			idx = i;
			break;
		}
		if (G->edge[i].ver1 == v2 && G->edge[i].ver2 == v1) {
			idx = i;
			break;
		}
	}
	if (idx == -1) idx = G->esize;
	G->edge[idx].ver1 = v1;
	G->edge[idx].ver2 = v2;

	//incidence node 생성 한 후 추가하기
	i1 = getincidence(idx);
	i2 = getincidence(idx);

	insertIncidence(G, v1, v2, i1);
	if (v1 != v2) insertIncidence(G, v2, v1, i2);
	G->esize++;
}
void DFS(Graph* G, int s) { //인접 정점들을 번호가 작은 정점부터 큰 순서대로 조사하기
	for (int i = 1; i <= G->size; i++)
		G->vert[i].lab = 0; //정점의 label을 0으로 초기화
	for (int i = 0; i < G->esize; i++)
		G->edge[i].lab = 0; //간선의 label을 0으로 초기화
	//방문하지 않았으면 : 0
	rDFS(G, s);
}
void rDFS(Graph* G, int s) {
	Incidence* i = NULL;
	int idx = s;
	int tmp;

	printf("%d\n", idx);//출발정점 s에서 출발하는 DFS의 방문 순서대로 정점번호 출력하기
	G->vert[idx].lab = -1; //방문하였다면 -1로 바꾸기
	i = G->vert[idx].incidence;

	while (i != NULL) {
		if (G->edge[i->edge].lab == 0) { //lab이 0이면 방문하지 않았음
			if (G->edge[i->edge].ver1 == G->vert[idx].n)
				tmp = G->edge[i->edge].ver2;
			else tmp = G->edge[i->edge].ver1; //방문했을 경우

			if (G->vert[tmp].lab == 0) {
				G->edge[i->edge].lab = -1;
				rDFS(G, tmp);
			}
		}
		i = i->next;
	}

}
