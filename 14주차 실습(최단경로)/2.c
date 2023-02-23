#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct edge {//간선구조체
    int ver1, ver2, weight; //양끝 정점 번호와 가중치
}Edges;
typedef struct vertex { //정점 구조체
    int name, d;
}Vertices;
typedef struct G { //그래프 구조체
    Vertices ver[101];
    Edges edge[1001];
}Graph;
Graph G;
int n, m, s;
void makeGraph();
void BellmanFordShortestPaths();
int selectMin(int a, int b);
int main()
{
    makeGraph(); //그래프 만들기
    BellmanFordShortestPaths();
    for (int i = 1; i <= n; i++) {
        //출발정점 s에서 다른 모든 정점으로의 최단거리를 출력한다.
        if (i == s || G.ver[i].d == 30000)
            continue;
        printf("%d %d\n", G.ver[i].name, G.ver[i].d);
        //정점과 그 정점까지의 거리를 출력하되, 도달할 수 없는 정점은 출력하지 않는다. 
    }

    return 0;
}
void makeGraph() {
    int u, v, w;
    scanf("%d %d %d", &n, &m, &s); //정점과 간선의 개수, 출발정점 번호 s 입력받기
    for (int i = 1; i <= n; i++) //정점의 개수 n만큼 반복하여 정점 정보 초기화
        G.ver[i].name = i;
    for (int i = 0; i < m; i++) { //간선의 개수 m만큼 반복하여 간선의 정보 입력받기
        scanf("%d %d %d", &u, &v, &w); //간선의 양 끝 정점 번호, 무게 입력받기
        G.edge[i].ver1 = u;
        G.edge[i].ver2 = v;
        G.edge[i].weight = w;
    }
}
int selectMin(int a, int b) {
    if (a >= b) return b; //작은 수 반환하는 함수
    return a;
}
void BellmanFordShortestPaths() {
    int u, z;
    for (int i = 1; i <= n; i++)
        G.ver[i].d = 30000;//무한대값은 최대가중치X최대간선수를 초과하는 충분히 큰 값 30000으로 초기화
    G.ver[s].d = 0;
    for (int i = 2; i <= n; i++) {
        for (int j = 0; j < m; j++) { //모든 간선에 대하여
            u = G.edge[j].ver1;
            z = G.edge[j].ver2;
            if (G.ver[u].d == 30000) continue;
            G.ver[z].d = selectMin(G.ver[z].d, G.ver[u].d + G.edge[j].weight);
        }
    }
}
