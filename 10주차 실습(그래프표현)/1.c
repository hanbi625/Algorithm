#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct vertices { //정점
	int n;
	struct incidence* incidence;
}Vertices;
typedef struct edge { //간선
	int w;
	int ver1;
	int ver2;
}Edges;
typedef struct incidence { //리스트
	struct incidence* next;
	int edge;
}Incidence;
typedef struct graph {
	Vertices vert[6];
	Edges edge[21];
	int size;
}Graph;
Incidence* getincidence(int edge);
void makeGraph(Graph* G);
void insertIncidence(Graph* G, int v1, int v2, Incidence* incidence);
void deleteIncidence(Graph* G, int v1, int v2);
void insertEdge(Graph* G, int v1, int v2, int w);
void modifyEdge(Graph* G, int v1, int v2, int w);
void deleteEdge(Graph* G, int v1, int v2);
void printEdge(Graph* G, int v);
int main() {
	char order;
	int w, a, b;
	Graph G;
	makeGraph(&G);
	insertEdge(&G, 0, 1, 1);
	insertEdge(&G, 0, 2, 1);
	insertEdge(&G, 0, 3, 1);
	insertEdge(&G, 0, 5, 2);
	insertEdge(&G, 1, 2, 1);
	insertEdge(&G, 2, 4, 4);
	insertEdge(&G, 4, 4, 4);
	insertEdge(&G, 4, 5, 3);
	//간선추가
	while (1) {
		scanf("%c", &order); //명령어 입력받기
		switch (order) {
		case 'a': //a를 입력받았으면
			scanf("%d", &w); //노드번호 입력받기
			getchar();
			printEdge(&G, w - 1); //노드번호 오름차순으로 인쇄하기
			break;
		case 'm': //m으로 입력받기
			scanf("%d %d %d", &a, &b, &w); //간선 a, b의 가중치 w 입력받기
			getchar();
			if (w != 0) modifyEdge(&G, a - 1, b - 1, w); //가중치가 0이 아니면 w로 변경하기
			else deleteEdge(&G, a - 1, b - 1); //w가 0이면 간선 a, b 삭제하기
			break;
		case 'q': //q를 입력받으면 프로그램 종료
			return -1;
		}
	}

	return 0;
}
void makeGraph(Graph* G) { //그래프 만들기
	for (int i = 0; i < 6; i++) { //초기화하기
		G->vert[i].incidence = NULL;
		G->vert[i].n = i + 1;
	}
	G->size = 0; //그래프 크기 0으로 초기화
	//간선 추가
}
Incidence* getincidence(int edge) { //노드 생성 함수
	Incidence* node = (Incidence*)malloc(sizeof(Incidence));
	node->next = NULL;
	node->edge = edge;
	return node; //새노드 incidence 할당 후 반환
}
//리스트 삽입 함수
void insertIncidence(Graph* G, int v1, int v2, Incidence* incidence) {
	Edges* e = G->edge;
	Vertices* ver = G->vert;
	Incidence* i;
	int tmp;

	i = ver[v1].incidence;
	if (i == NULL) ver[v1].incidence = incidence; //첫노드일때
	else { //첫노드가 아니면 오름차순 삽입
		if (e[i->edge].ver1 == v1) //head와 비교하기
			tmp = e[i->edge].ver2;
		else tmp = e[i->edge].ver1;

		if (tmp > v2) { //head에서 교환하기
			incidence->next = i;
			ver[v1].incidence = incidence;
		}
		else {
			while (i->next != NULL) {
				if (e[i->next->edge].ver1 == v1)
					tmp = e[i->next->edge].ver2;
				else tmp = e[i->next->edge].ver1;

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
void deleteIncidence(Graph* G, int v1, int v2) { //incidence 삭제
	Edges* e = G->edge;
	Vertices* ver = G->vert;
	Incidence* i;
	int tmp;

	i = ver[v1].incidence;
	if (i == NULL) return;
	//head와 비교하여
	if (e[i->edge].ver1 == v1) tmp = e[i->edge].ver2;
	else tmp = e[i->edge].ver1;

	if (tmp == v2) { //head에서 삭제
		ver[v1].incidence = i->next;
		free(i);
		i = NULL;
	}
	else {
		while (i->next != NULL) {
			if (e[i->next->edge].ver1 == v1)
				tmp = e[i->next->edge].ver2;
			else tmp = e[i->next->edge].ver1;

			if (tmp == v2) break;
			i = i->next;
		}
		if (i->next == NULL) return;
		else //다시 연결하기
			i->next = i->next->next;
	}
}
void insertEdge(Graph* G, int v1, int v2, int w) { //edge삽입
	Edges* e = G->edge;
	Incidence* i1, * i2;
	int tmp, idx = -1;

	//리스트에 중복 검사하고 추가하기
	for (int i = 0; i < G->size; i++) {
		if (e[i].ver1 == v1 && e[i].ver2 == v2) {
			e[i].w = w;
			idx = i;
			break;
		}
		if (e[i].ver1 == v2 && e[i].ver2 == v1) {
			e[i].w = w;
			idx = i;
			break;
		}
	}
	if (idx == -1) idx = G->size;
	e[idx].ver1 = v1;
	e[idx].ver2 = v2;
	e[idx].w = w;

	//incidence node 생성 한 후 추가하기
	i1 = getincidence(idx);
	i2 = getincidence(idx);

	insertIncidence(G, v1, v2, i1);
	if (v1 != v2) insertIncidence(G, v2, v1, i2);
	G->size++;
}
void modifyEdge(Graph* G, int v1, int v2, int w) { //edge 수정
	if (v1 < 0 || v1 > 5 || v2 < 0 || v2 >5) { //범위 넘어가면 -1출력후 종료
		printf("-1\n");
		return;
	}
	Edges* e = G->edge;
	Incidence* i = G->vert[v1].incidence;
	int tmp, cnt = 0;
	if (i == NULL) insertEdge(G, v1, v2, w);
	else {
		while (i != NULL) {
			if (e[i->edge].ver1 == v1) tmp = e[i->edge].ver2;
			else tmp = e[i->edge].ver1;

			if (tmp == v2) { //가중치 변경하기
				e[i->edge].w = w;
				cnt++;
				break;
			}
			i = i->next;
		}
		if (cnt == 0) insertEdge(G, v1, v2, w); //새로운 간선 생성하기
	}
}
void deleteEdge(Graph* G, int v1, int v2) { //edge 삭제 함수
	if (v1 < 0 || v1 > 5 || v2 < 0 || v2 >5) {//범위 넘어가면 -1출력후 종료
		printf("-1\n");
		return;
	}
	Edges* e = G->edge;
	Vertices* ver = G->vert;
	Incidence* i;
	int tmp, idx = 0;
	//node 삭제
	deleteIncidence(G, v1, v2);
	if (v1 != v2) deleteIncidence(G, v2, v1);
	G->size--;
}
void printEdge(Graph* G, int v) { //출력 함수
	if (v < 0 || v>5) { //노드번호가 존재하지 않으면 -1 출력 후 종료
		printf("-1\n");
		return;
	}
	Vertices* ver = G->vert;
	Edges* e = G->edge;
	Incidence* i = ver[v].incidence;
	int tmp;

	if (i == NULL) return;
	while (i != NULL) {
		if (e[i->edge].ver1 == v) tmp = e[i->edge].ver2;
		else tmp = e[i->edge].ver1;
		//노드 출력
		printf(" %d %d", tmp + 1, e[i->edge].w);
		i = i->next;
	}
	printf("\n");

}
