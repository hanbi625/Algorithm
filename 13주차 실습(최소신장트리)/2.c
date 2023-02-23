#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
typedef struct incident { //인접리스트
    int edge;
    struct incident* next;
}Incidence;
typedef struct edge {//간선구조체
    int ver1, ver2, w; //양끝 정점 번호와 가중치
}Edges;

typedef struct vertex { //정점 구조체
    int name;
}Vertices;
typedef struct seperate {
    int size;
    Incidence* head;
}Seperate;
typedef struct G { //그래프 구조체
    Vertices* ver;
    Edges* edge;
    int n, m;
}GRAPH;
typedef struct heap { //힙을 이용한 우선순위 큐
    int key;
    int w;
}Heap;
GRAPH G;

void makeGraph();
void insertIncidence(int v1, int v2, int w, int idx);
void addFirst(Incidence** head, int idx);
int deleteFirst(Incidence** head);
void kruskalMST();
Seperate* setbuild();
Heap* buildHeap();
int findSet(Seperate* S, int v);
void unionSet(Seperate* S, int v1, int v2);
void downHeap(Heap* H, int idx, int size);
void swap(Heap* x, Heap* y);
int removeMin(Heap* H, int idx);
void freeSet(Seperate* S);
void freeG();
int main(void) {

    makeGraph(); //그래프 만들기
    kruskalMST(); //알고리즘
    freeG();

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
        G.ver[i].name = i; //정점 이름에 번호 저장
    }

    for (int i = 0; i < G.m; i++) {
        scanf("%d %d %d", &v1, &v2, &w);//간선의 개수 m만큼 반복하여 간선 정보 입력받기
        insertIncidence(v1, v2, w, i);
    }
}
void insertIncidence(int v1, int v2, int w, int idx) {
    //간선의 양끝 정점 번호와 무게 저장하기
    G.edge[idx].w = w;
    G.edge[idx].ver1 = v1;
    G.edge[idx].ver2 = v2;
}
void addFirst(Incidence** head, int idx) {//인접리스트 노드 삽입
    Incidence* node = (Incidence*)malloc(sizeof(Incidence));
    node->edge = idx;
    node->next = (*head);
    (*head) = node;
}
int deleteFirst(Incidence** head) {
    int r;
    if (*head == NULL) return -1; //NULL이면 -1반환
    r = (*head)->edge;
    *head = (*head)->next; //다음 포인터로 이동
    return r;
}
Seperate* setbuild() {
    Seperate* S = (Seperate*)malloc(sizeof(Seperate) * G.n); //집합 동적할당
    for (int i = 0; i < G.n; i++) { //집합 초기화
        S[i].size = 0;
        S[i].head = (Incidence*)malloc(sizeof(Incidence));
        S[i].head->edge = G.ver[i + 1].name;
        S[i].head->next = NULL;
    }
    return S;
}
Heap* buildHeap() {
    Heap* H = (Heap*)malloc(sizeof(Heap) * (G.m + 1));
    for (int i = 1; i <= G.m; i++) { //정보 초기화
        H[i].key = i;
        H[i].w = G.edge[i-1].w;
    }
    for (int i = G.m / 2; i >= 1; i--) { //상향식 힙생성
        downHeap(H, i, G.m);
    }
    return H;
}
void downHeap(Heap* H, int idx, int size) {
    int l = 2 * idx;
    int r = 2 * idx + 1;
    int smaller;

    if (l > size) return;
    //왼쪽 자식을 더 작은 키 값을 가진 정점으로 초기화
    smaller = l;
    if (r <= size) { //오른쪽 자식 노드가 존재하고 왼쪽보다 작을 경우 더 작은 값으로 초기화
        if (H[r].w < H[l].w)
            smaller = r;
    }

    if (H[idx].w <= H[smaller].w) return;

    swap(H + idx, H + smaller); //자리 바꾸기
    downHeap(H, smaller, size); //재귀호출
}
void swap(Heap* x, Heap* y) { //바꾸기
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
void kruskalMST() {
    Seperate* S = setbuild(); //집합 생성
    Heap* H = buildHeap(); //힙 생성
    int sum = 0, u, v1, v2;
    int s = G.m;//s에 간선 개수 저장

    while (s > 0) { //s가 0보다 클 동안 반복
        u = removeMin(H, s); //삭제 후 u에 저장
        v1 = findSet(S, G.edge[u - 1].ver1);
        v2 = findSet(S, G.edge[u - 1].ver2);
        if (v1 != v2) { //v1과 v2가 같지 않으면
            printf(" %d", G.edge[u - 1].w); //간선 무게 출력
            sum += G.edge[u - 1].w; //간선 무게 총합 구하기
            unionSet(S, v1, v2);
        }
        s--;
    }
    printf("\n%d", sum); //총합 출력
    freeSet(S);
    free(H);
}
int findSet(Seperate* S, int v) {
    Incidence* p;
    for (int i = 0; i < G.n; i++) { //정점 개수만큼 반복
        p = S[i].head;
        while (p != NULL) { //p가 NULL이 될 때 까지 반복
            if (G.ver[p->edge].name == v) return i;
            p = p->next;
        }
    }
    return -1;
}
void unionSet(Seperate* S, int v1, int v2) {
    int tmp, cnt;
    if (S[v1].size < S[v2].size) { //자리 바꾸기
        tmp = v1;
        v1 = v2;
        v2 = tmp;
    }
    while (1) { //무한 반복
        cnt = deleteFirst(&(S[v2].head));
        if (cnt == -1) break; //cnt -1반환되었으면 종료
        addFirst(&(S[v1].head), cnt); //맨 앞 삽입
    }
    S[v2].head = NULL;
    S[v2].size = 0;
}
void freeSet(Seperate* S) { //해제하기
    Incidence* p, * q;
    for (int i = 0; i < G.n; i++) {
        p = S[i].head;
        while (p != NULL) {
            q = p->next;
            free(p);
            p = q;
        }
    }
    free(S);
}
void freeG() {
    free(G.ver);
    free(G.edge);
}
/*
6 9
 
1 2 3
 
1 3 20
 
2 4 25
 
2 5 17
 
3 4 34
 
3 5 1
 
3 6 12
 
4 5 5
 
5 6 37
*/
