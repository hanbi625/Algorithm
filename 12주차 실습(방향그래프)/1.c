#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct incident {
	int e;
	struct incident* next;
}Incidence;
typedef struct edge {
	int origin, destination;
}Edges;
typedef struct vertex {
	char name;
	Incidence* inE;
	Incidence* outE;
	int inDegree;
}Vertices;
typedef struct graph {
	Vertices* ver;
	Edges* edge;
}Graph;
typedef struct que {
	int* q;
	int f, r;
}Que;
Graph G; //방향 그래프 전역 변수
int n, m; //정점수 n, 간선 수 m
int in[100]; //정점 i의 진입차수
int topOrder[101]; //정점들의 위상순서
Que Q; //정점들의 대기열
void buildGraph();
void insertVertex(char vName, int i);
void insertDirectedEdge(char uName, char wName, int i);
int index(char vName);
void addFirst(Incidence* H, int i);
void topologicalSort();
int isEmpty();
void enqueue(int v);
int dequeue();
int main() {
	buildGraph(); //입력으로부터 G구축
	topologicalSort(); //G를 위상 정렬

	if (topOrder[0] == 0) //G는 non-DAG 즉, 방향싸이클 존재
		printf("0\n");
	else //G는 DAG
		for (int i = 1; i <= n; i++)
			printf("%c ", G.ver[topOrder[i]].name);

	return 0;
}
void buildGraph() { //표준입력으로부터 방향 그래프 정보를 읽어 들여 그래프 G에 저장
	char vName, uName, wName;
	G.ver = (Vertices*)malloc(sizeof(Vertices) * 100); //ver 동적할당
	G.edge = (Edges*)malloc(sizeof(Edges) * 1000); //edge 동적할당

	scanf("%d", &n); //정점 수 입력받기
	getchar();
	for (int i = 0; i < n; i++) { //정점들의 이름 입력받기
		scanf("%c", &vName); //정점 이름
		getchar();
		insertVertex(vName, i); //정점 삽입
	}

	scanf("%d", &m); //방향 간선 수 입력받기
	getchar();
	for (int i = 0; i < m; i++) { //방향 간선 정보 입력받기
		scanf("%c %c", &uName, &wName);
		getchar();
		insertDirectedEdge(uName, wName, i); //방향간선 그래프에 삽입하기
	}
}
void insertVertex(char vName, int i) {
	//vName 정점 i를 G의 정점리스트에 삽입하고 i의 진입차수를 초기화
	G.ver[i].name = vName;//정점 i의 이름 저장
	G.ver[i].outE = (Incidence*)malloc(sizeof(Incidence));//진출부착간선리스트 초기화
	G.ver[i].inE = (Incidence*)malloc(sizeof(Incidence));//진입부착간선리스트 초기화
	G.ver[i].outE->next = NULL;
	G.ver[i].inE->next = NULL;
	G.ver[i].inDegree = 0;//정점 i의 진입차수 초기화
}
void insertDirectedEdge(char uName, char wName, int i) {
	/*uName 정점 u를 시점으로, wName정점 w를 종점으로 하는 방향간선 i를 G의 간선리스트,
	u의 진출 간선리스트, w의 진입간선리스트에 각각 삽입하고, w의 진입차수를 갱신*/
	int u, w;
	u = index(uName);//uName정점의 배열 인덱스를 u에 저장
	w = index(wName);//wName정점의 배열 인덱스를 w에 저장

	G.edge[i].origin = u;//간선 i의 시점으로 u를 저장
	G.edge[i].destination = w;//간선 i의 종점으로 w를 저장
	addFirst(G.ver[u].outE, i);//정점 u의 진출부착간선리스트에 i삽입
	addFirst(G.ver[w].inE, i);//정점 w의 진입부착간선리스트에 i삽입
	G.ver[w].inDegree++;//정점 w의 진입차수 갱신
}
int index(char vName) { //vName에 해당하는 정점의 인덱스를 찾아 반환
	for (int i = 0; i < n; i++)
		if (G.ver[i].name == vName)
			return i;
}
void addFirst(Incidence* H, int i) { //H의 첫 노드 위치에 정수 i를 원소로 하는 노드를 삽입
	Incidence* node = (Incidence*)malloc(sizeof(Incidence));//node 할당
	node->e = i;//node원소로 i를 저장
	node->next = H->next;//기존 연결리스트를 node뒤에 연결
	H->next = node;//node를 H의 첫 노드로 설정
}
void topologicalSort() {//G로부터 위상순서를 구하거나 방향싸이클이 존재함을 보고
	int t, u, w;
	Incidence* e;
	Q.q = (int*)malloc(sizeof(int) * 100);
	Q.f = 0;
	Q.r = 0;
	for (int i = 0; i < 100; i++) //Q 초기화
		Q.q[i] = 0;

	for (int i = 0; i < n; i++) {//G의 모든 정점에 정점번호순으로 반복
		in[i] = G.ver[i].inDegree;//정점i의 진입차수를 in[i]에 저장
		if (in[i] == 0)//진입차수가 0인 정점들을 Q에 삽입
			enqueue(i);
	}
	t = 1; //위상순위 t
	while (!isEmpty()) { //Q가 비지 않은동안 반복
		u = dequeue();//Q 삭제
		topOrder[t] = u;//위상순위 t 정점 저장
		t++; //위상순위 t 증가

		e = G.ver[u].outE;
		e = e->next;
		while (e != NULL) { //u의 모든 진출간선 e에 대해 반복
			w = G.edge[e->e].destination;//w는 간선 e의 종점
			in[w]--; //in[w] 감소
			if (in[w] == 0) enqueue(w);//정점 w의 진입차수가 0이면 Q에 삽입
			e = e->next;
		}
	}
	if (t <= n) topOrder[0] = 0;//위상순위가 매겨지지않은 정점이 존재하면 G는 non-DAG(방향사이클존재)
	else topOrder[0] = 1;
	//G는 dag

}
int isEmpty() { //Q가 비어있으면 1 아니면 0반환
	if (Q.r==Q.f) return 1;
	else return 0;
}
void enqueue(int v) { //v를 Q에 삽입
	Q.q[Q.r] = v;
	Q.r = (Q.r + 1) % 100;
}
int dequeue() { //Q로부터 정점을 삭제하여 반환
	int v;
	v = Q.q[Q.f];
	Q.f = (Q.f + 1) % 100;
	return v;
}
