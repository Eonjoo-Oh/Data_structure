#include <stdio.h>

#define MAX_VERTICES 5

typedef struct {
    int adjacencyMatrix[MAX_VERTICES][MAX_VERTICES];
} Graph;

void initGraph(Graph* g) {
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            g->adjacencyMatrix[i][j] = 0; // 초기값으로 0으로 설정 (연결되지 않은 상태)
        }
    }
}

void addEdge(Graph* g, int start, int end) {
    g->adjacencyMatrix[start][end] = 1; // 연결 관계 표시 (1로 설정)
    g->adjacencyMatrix[end][start] = 1; // 무방향 그래프인 경우 반대쪽도 연결 표시
}

int main() {
    Graph g;
    initGraph(&g);
    
    // 구역 A, B, C, D, E를 그래프에 추가
    // 예시에서는 A=0, B=1, C=2, D=3, E=4로 인덱스를 지정합니다.
    addEdge(&g, 0, 1); // A와 B 연결
    addEdge(&g, 0, 2); // A와 C 연결
    addEdge(&g, 1, 3); // B와 D 연결
    addEdge(&g, 2, 3); // C와 D 연결
    addEdge(&g, 3, 4); // D와 E 연결
    
    // 그래프 출력
    for (int i = 0; i < MAX_VERTICES; i++) {
        for (int j = 0; j < MAX_VERTICES; j++) {
            printf("%d ", g.adjacencyMatrix[i][j]);
        }
        printf("\n");
    }
    
    return 0;
}
