#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
typedef struct node {
	struct node* lChild;
	struct node* rChild;
	struct node* parent;
	int key;
	int height;
}NODE;
NODE* root; //전역변수 선언
NODE* getnode();
int findElement(NODE*, int);
void insertItem(NODE*, int);
void expandExternal(NODE*);
NODE* treeSearch(NODE*, int);
int isExternal(NODE*);
int isInternal(NODE*);
NODE* sibling(NODE*);
NODE* inOrderSucc(NODE*);
void searchAndFixAfterInsertion(NODE*);
int updateHeight(NODE*);
int isBalanced(NODE*);
NODE* restructure(NODE*, NODE*, NODE*);
void print(NODE*);
int removeElement(NODE**, int);
NODE* reduceExternal(NODE**, NODE*);
void searchAndFixAfterRemoval(NODE*, NODE*);
int main() {
	char ch;
	int k, e;
	root = getnode(); //노드 생성
	while (1) { //q가 입력될때까지 무한 반복
		scanf("%c", &ch);
		switch (ch) { //ch의 값이
		case 'i': //i이면
			scanf("%d", &k); //k값 입력받기
			getchar();
			insertItem(root, k); //키에 대한 노드 생성 및 트리에 삽입
			break;
		case 'd': //d를 입력받으면
			scanf("%d", &k); //k입력받기
			getchar();
			e = removeElement(&root, k); //e에 삭제할 노드의 키 저장
			if (e == -1) //k 값이 없으면 X출력
				printf("X\n");
			else //있으면 해당 노드 삭제 후 삭제된 키 출력받기
				printf("%d\n", e);
			break;
		case 's': //s를 입력받으면
			scanf("%d", &k); //k 입력받기
			getchar();
			e = findElement(root, k); //e에 찾을 키의 값 저장
			if (e == -1) //없으면 X 출력
				printf("X\n");
			else //있으면 해당 키 출력
				printf("%d\n", e);
			break;
		case 'p': //p를 입력받으면
			print(root); //현재 트리를 전위순회로 인쇄
			printf("\n");
			break;
		case 'q': //q면 프로그램 종료
			return -1;
		}
	}

	return 0;
}
NODE* getnode() {
	NODE* node = (NODE*)malloc(sizeof(NODE)); //node 동적할당받기
	node->parent = NULL; //node의 부모 NULL로 초기화
	node->lChild = NULL; //node의 왼쪽자식 NULL로 초기화
	node->rChild = NULL; //node의 오른쪽자식 NULL로 초기화
	return node; //node 반환
}
int findElement(NODE* root, int k) {
	NODE* w = treeSearch(root, k); //k를 저장한 노드 찾기
	if (isExternal(w)) //외부노드이면 종료
		return -1;
	else return w->key; //그 노드에 저장된 원소 반환
}
void insertItem(NODE* root, int k) {
	NODE* w = treeSearch(root, k);
	if (isInternal(w)) return; //외부노드이면 종료
	else { //그 외의경우
		w->key = k; //w에 k저장
		expandExternal(w); //k를 저장한 노드 삽입
		searchAndFixAfterInsertion(w);
	}
}
void expandExternal(NODE* w) {
	NODE* l = getnode();
	NODE* r = getnode();
	l->lChild = NULL;
	l->rChild = NULL;
	l->parent = w;
	l->height = 0;

	r->lChild = NULL;
	r->rChild = NULL;
	r->parent = w;
	r->height = 0;

	w->lChild = l;
	w->rChild = r;
	w->height = 1;
}
NODE* treeSearch(NODE* root, int k) {
	if (isExternal(root))
		return root; //외부노드이면 노드가 위치할 외부노드 반환
	if (k == root->key) //키 k를 저장한 내부 노드 반환
		return root;
	else if (k < root->key)
		return treeSearch(root->lChild, k);
	else //k가 key보다 클경우
		return treeSearch(root->rChild, k);
}
void print(NODE* root) { //트리 출력 함수
	if (isInternal(root)) {
		printf(" %d", root->key);
		print(root->lChild); //왼쪽 자식에 대하여 함수 실행
		print(root->rChild); //오른쪽 자식에 대하여 함수 실행
	}
}
int isExternal(NODE* w) {
	if (w->lChild == NULL && w->rChild == NULL)
		return 1; //자식노드가 없으면 1반환
	else return 0; //그외의 경우 외부노드가 아님
}
int isInternal(NODE* w) {
	if (w->lChild != NULL || w->rChild != NULL)
		return 1; //외부노드가 아니면 1반환
	else return 0; //그외의 경우 내부노드가 아님
}
NODE* sibling(NODE* w) {
	if (w->parent == NULL) //루트이면 종료
		return NULL;
	if (w->parent->lChild == w) //부모의 왼쪽 자식이 w이면 오른쪽 자식 반환
		return w->parent->rChild;
	else return w->parent->lChild; //그외의 경우 오른쪽 자식 반환
}
NODE* inOrderSucc(NODE* w) {
	w = w->rChild; //현재 노드의 오른쪽 으로 이동
	if (isExternal(w)) //외부노드면 종료
		return NULL;
	while (isInternal(w->lChild))
		w = w->lChild; //왼쪽 자식이 내부노드일 동안 반복하여 왼쪽 자식으로 이동
	return w; //w반환
}
void searchAndFixAfterInsertion(NODE* w) {
	NODE* x, * y, * z;
	//w에서 루트를 향해 올라가다가 처음 만나는 불균형 노드 z로 설정
	//그게 없으면 return
	if (w->parent == NULL) return;
	z = w->parent;
	while (updateHeight(z) && isBalanced(z)) {
		if (z->parent == NULL) return;
		z = z->parent;
	}
	if (isBalanced(z)) return;
	//z의 높은 자식을 y로 설정
	if (z->lChild->height > z->rChild->height)
		y = z->lChild;
	else y = z->rChild;
	//y의 높은 자식을 x로 설정
	if (y->lChild->height > y->rChild->height)
		x = y->lChild;
	else x = y->rChild;
	//restructure (x, y, z) 실행
	restructure(x, y, z);
}
int updateHeight(NODE* w) { //높이 갱신 함수
	int h;
	NODE* l, * r;
	l = w->lChild;
	r = w->rChild;
	h = (l->height > r->height) ? l->height + 1 : r->height + 1;
	if (h != w->height) {
		w->height = h;
		return 1;
	}
	return 0;
}
int isBalanced(NODE* w) { //균형인지 아닌지 확인하는 함수
	int bal = w->lChild->height - w->rChild->height;
	if (bal >= -1 && bal <= 1) return 1; //높이 차이가 1이하면 1반환
	return 0; //그외의 경우 0반환
}
NODE* restructure(NODE* x, NODE* y, NODE* z) {
	NODE* a, * b, * c; //x, y, z의 중위순회 방문순서의 나열을 a, b, c라고 하자
	NODE* T0, * T1, * T2, * T3;
	//x, y, z의 부트리들 가운데 x, y, z을 루트로 하는 부트리를 제외한 4개의 부트리의 중위순회 방문순서의 나열을 T0, t1, t2, t3라 하자.
	if (x->key < y->key && y->key < z->key) { //x<y<z일때
		a = x; b = y; c = z;
		T0 = a->lChild; T1 = a->rChild;
		T2 = b->rChild; T3 = c->rChild;
	}
	else if (z->key < y->key && y->key < x->key) { //z<y<x일때
		a = z; b = y; c = x;
		T0 = a->lChild; T1 = b->lChild;
		T2 = c->lChild; T3 = c->rChild;
	}
	else if (y->key < x->key && x->key < z->key) { //y<x<z일때
		a = y; b = x; c = z;
		T0 = a->lChild; T1 = b->lChild;
		T2 = b->rChild; T3 = c->rChild;
	}
	else { //z<x<y일때
		a = z; b = x; c = y;
		T0 = a->lChild; T1 = b->lChild;
		T2 = b->rChild; T3 = c->rChild;
	}
	//z을 루트로 하는 부트리를 b를 루트로 하는 부트리로 대체한다.
	if (z->parent == NULL) {
		root = b;
		b->parent = NULL;
	}
	else if (z->parent->lChild == z) {
		z->parent->lChild = b;
		b->parent = z->parent;
	}
	else { //z->parent->rchild == z일때
		z->parent->rChild = b;
		b->parent = z->parent;
	}
	//T0과 T1을 각각 a의 왼쪽 및 오른쪽 부트리로 만든다
	a->lChild = T0;
	a->rChild = T1;
	T0->parent = a;
	T1->parent = a;
	updateHeight(a);
	//T2와 T3를 각각 c의 왼쪽 및 오른쪽 부트리로 만든다
	c->lChild = T2;
	c->rChild = T3;
	T2->parent = c;
	T3->parent = c;
	updateHeight(c);

	//a와 c를 각각 b의 왼쪽 및 오른쪽 자식으로 만든다
	b->lChild = a;
	b->rChild = c;
	a->parent = b;
	c->parent = b;
	updateHeight(b);

	return b;
}
int removeElement(NODE** root, int k) {
	NODE* w = treeSearch(*root, k); //w에 k위치 노드 저장
	NODE* z, * y, * zs = NULL;
	int e;
	if (isExternal(w)) return -1; //w가 외부노드이면 종료
	e = w->key; //e에 w의 key 저장
	z = w->lChild; //노드 z에 w의 왼쪽 자식 저장
	if (!isExternal(z)) z = w->rChild; //z가 외부노드가 아니면 w의 오른쪽 자식 저장
	if (isExternal(z)) zs = reduceExternal(root, z); //z의 외부노드이면 reduceExternal 함수 실행
	else {//그외의 경우
		y = inOrderSucc(w);
		z = y->lChild;
		w->key = y->key; //w의 원소에 y의 원소 저장
		zs = reduceExternal(root, z);
	}
	searchAndFixAfterRemoval(*root, zs->parent);
	return e; //원소 반환
}
NODE* reduceExternal(NODE** root, NODE* z) {
	NODE* g;
	NODE* w = z->parent;
	NODE* zs = sibling(z);

	if (w == *root) { //z의 부모노드가 루트이면
		*root = zs;
		zs->parent = NULL; //zs의 부모 NULL로 초기화
	}
	else { // 그외의 경우
		g = w->parent; //g에 w의 부모 저장
		zs->parent = g; //zs의 부모에 g 저장
		if (w == g->lChild) //g의 왼쪽 자식이 w이면
			g->lChild = zs; //g의 왼쪽 자식에 zs 저장
		else //그외의 경우 오른쪽 자식에 저장
			g->rChild = zs;
	}
	free(z); //z와 w 동적해제
	z = NULL;
	free(w);
	w = NULL;
	return zs;
}
void searchAndFixAfterRemoval(NODE* root, NODE* z) {
	NODE* x, * y, * b;
	//w에서 루트를 향해 올라가다가 처음 만나는 불균형 노드 설정
	while (updateHeight(z) && isBalanced(z)) {
		if (z->parent == NULL) return;
		z = z->parent;
	}
	//불균형 노드 없으면 종료
	if (isBalanced(z)) return;

	//z의 가장높은 자식을 y로 설정
	if (z->lChild->height > z->rChild->height)
		y = z->lChild;
	else y = z->rChild;
	//y의 자식 중 높은 자식을 x라고 하고 자식 높이가 같으면 y와 같은 쪽 자식 x로 설정
	if (y->lChild->height > y->rChild->height)
		x = y->lChild;
	else if (y->lChild->height < y->rChild->height)
		x = y->rChild;
	else {
		if (z->lChild == y) x = y->lChild;
		else x = y->rChild;
	}
	//restructure함수 실행
	b = restructure(x, y, z);
	if (b->parent == NULL) return;
	//균형 잃은 노드 고치는 것 계속 반복하기
	searchAndFixAfterRemoval(root, b->parent);
}
