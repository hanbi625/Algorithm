#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
typedef struct incident { //인접리스트
    int edge;
    struct incident* next;
}Incidence;
typedef struct edge {//간선구조체
    int ver1, ver2, weight; //양끝 정점 번호와 가중치
}Edges;

typedef struct vertex { //정점 구조체
    int name, d;
    Incidence* head;
}Vertices;
typedef struct G { //그래프 구조체
    Vertices* ver;
    Edges* edge;
    int n, m;
}GRAPH;
typedef struct heap { //힙을 이용한 우선순위 큐
    int key;
    int d;
}Heap;
GRAPH G;

void makeGraph();
void insertVer(int idx);
void insertIncidence(int v1, int v2, int w, int idx);
void addFirst(Incidence* head, int idx);

void primJarnikMST();

Heap* buildHeap();
void upHeap(Heap* H, int idx);
void downHeap(Heap* H, int idx, int size);
void swap(Heap* x, Heap* y);
int removeMin(Heap* H, int idx);
int opposite(int u, int e);
int isInclude(Heap* H, int idx, int z);
void replaceKey(Heap* H, int idx, int z, int w);

void freeGraph();

int main(void) {

    makeGraph(); //그래프 만들기
    primJarnikMST();//prim-Jarnik 알고리즘
    freeGraph();

    return 0;
}
void makeGraph() {
    int n, m;
    int v1, v2, w;

    scanf("%d %d", &n, &m); //정점과 간선의 개수 입력받기
    G.n = n, G.m = m;
    G.ver = (Vertices*)malloc(sizeof(Vertices) * (n + 1)); //1부터 시작
    G.edge = (Edges*)malloc(sizeof(Edges) * m);

    for (int i = 1; i <= n; i++) {//정점의 개수 n만큼 반복하여 정점 정보 초기화
        insertVer(i);
    }

    for (int i = 0; i < G.m; i++) {
        scanf("%d %d %d", &v1, &v2, &w);//간선의 개수 m만큼 반복하여 간선 정보 입력받기
        insertIncidence(v1, v2, w, i);
    }
}
void insertVer(int idx) {
    G.ver[idx].name = idx; //정점의 name에 번호 저장
    G.ver[idx].head = (Incidence*)malloc(sizeof(Incidence));
    G.ver[idx].head->next = NULL;
}
void insertIncidence(int v1, int v2, int w, int idx) {
    //간선의 양끝 정점 번호와 무게 저장하기
    G.edge[idx].weight = w;
    G.edge[idx].ver1 = v1;
    G.edge[idx].ver2 = v2;

    //간선 정보를 정점에 입력
    addFirst(G.ver[v1].head, idx);
    addFirst(G.ver[v2].head, idx);
}
void addFirst(Incidence* head, int idx) {//인접리스트 노드 삽입
    Incidence* node = (Incidence*)malloc(sizeof(Incidence));
    node->edge = idx;
    node->next = head->next;
    head->next = node;
}
Heap* buildHeap() {
    Heap* H = (Heap*)malloc(sizeof(Heap) * (G.n + 1));
    for (int i = 1; i <= G.n; i++) { //초기화
        H[i].d = G.ver[i].d;
        H[i].key = G.ver[i].name;
    }
    for (int i = G.n / 2; i >= 1; i--) { //상향식 힙생성
        downHeap(H, i, G.n);
    }
    return H;
}
void upHeap(Heap* H, int idx) {
    if (idx == 1)return;
    if (H[idx].d >= H[idx / 2].d) return;
    //루트거나 부모보다 크면 종료
    swap(H + idx, H + idx / 2); //자리 바꾸기
    upHeap(H, idx / 2); //재귀호출
}
void downHeap(Heap* H, int idx, int size) {
    int left = 2 * idx;
    int right = 2 * idx + 1;
    int smaller;

    if (left > size) return;
    //왼쪽 자식을 더 작은 키 값을 가진 정점으로 초기화
    smaller = left;
    if (right <= size) { //오른쪽 자식 노드가 존재하고 왼쪽보다 작을 경우 더 작은 값으로 초기화
        if (H[right].d < H[left].d)
            smaller = right;
    }

    if (H[idx].d <= H[smaller].d) return;

    swap(H + idx, H + smaller); //자리 바꾸기
    downHeap(H, smaller, size); //재귀호출
}
void swap(Heap* x, Heap* y) {
    Heap temp;
    temp = *x;
    *x = *y;
    *y = temp;
}
int removeMin(Heap* H, int idx) {//최단거리의 정점 삭제하여 반환하기
    Heap r;
    if (idx == 0) return -1;
    r = H[1]; //삭제할 정점 저장
    swap(H + 1, H + idx);//자리 바꾸기
    downHeap(H, 1, --idx);//정점 위치 이동

    return r.key; //삭제된 값 반환
}
void replaceKey(Heap* H, int idx, int z, int w) {
    int i;
    for (i = 1; i < idx; i++) {
        if (H[i].key == z) {
            H[i].d = w;
            break;
        }
    }
    upHeap(H, i); //upHeap 함수 실행
}
void primJarnikMST() {
    Heap* H;
    Incidence* p;
    int sum, u, z, i;

    for (i = 1; i <= G.n; i++) { // 초기화
        G.ver[i].d = 99999;
    }
    G.ver[1].d = 0;//1번 정점의 d 0으로 초기화

    H = buildHeap();//heap을 이용한 우선순위 큐 만들기
    i = G.n;
    sum = 0;
    while (i > 0) { //힙의 모든 정점이 삭제될 때까지 반복하기
        u = removeMin(H, i);//최단거리 경로의 정점 삭제 후 u에 저장하기
        printf(" %d", G.ver[u].name);//추가된 정점 이름 출력받기

        sum += G.ver[u].d;
        p = G.ver[u].head->next;
        while (p != NULL) { //정점의 모든 간선 탐색
            z = opposite(u, p->edge); //반대편 정점 저장
            if (isInclude(H, i, z) && G.edge[p->edge].weight < G.ver[z].d) {
                G.ver[z].d = G.edge[p->edge].weight;
                replaceKey(H, i, z, G.ver[z].d);//힙 위치 변경하기
            }
            p = p->next; //다음 노드로 이동
        }
        i--;
    }
    printf("\n%d", sum);
    free(H);
}
int opposite(int u, int e) {
    if (G.edge[e].ver1 == u) return G.edge[e].ver2;
    else return G.edge[e].ver1;
}
int isInclude(Heap* H, int idx, int z) {
    for (int i = 1; i < idx; i++) {
        if (H[i].key == z) return 1; //z와 같으면 1반환 하고 종료 그렇지 않으면 0반환
    }
    return 0;
}
void freeGraph() { //해제하기
    Incidence* node, * next;

    for (int i = 1; i <= G.n; i++) {
        node = G.ver[i].head;
        while (node != NULL) {
            next = node->next;
            free(node);
            node = next;
        }
    }

    free(G.ver);
    free(G.edge);
}
