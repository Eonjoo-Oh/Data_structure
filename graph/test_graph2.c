#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct Graph {
    int numVertices;
    Node** adjacencyList;
} Graph;

Node* createNode(int v) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = v;
    newNode->next = NULL;
    return newNode;
}

Graph* createGraph(int numVertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = numVertices;

    graph->adjacencyList = (Node**)malloc(numVertices * sizeof(Node*));
    for (int i = 0; i < numVertices; i++) {
        graph->adjacencyList[i] = NULL;
    }

    return graph;
}

void addEdge(Graph* graph, int src, int dest) {
    // 소스 정점에서 목적 정점으로 간선 추가
    Node* newNode = createNode(dest);
    newNode->next = graph->adjacencyList[src];
    graph->adjacencyList[src] = newNode;

    // 목적 정점에서 소스 정점으로 간선 추가
    newNode = createNode(src);
    newNode->next = graph->adjacencyList[dest];
    graph->adjacencyList[dest] = newNode;
}

void printGraph(Graph* graph) {
    for (int i = 0; i < graph->numVertices; i++) {
        Node* currentNode = graph->adjacencyList[i];
        printf("%c: ", 'A' + i);
        while (currentNode) {
            printf("%c ", 'A' + currentNode->vertex);
            currentNode = currentNode->next;
        }
        printf("\n");
    }
}

int main() {
    int numVertices = 5;
    Graph* graph = createGraph(numVertices);

    // 그래프에 간선 추가
    addEdge(graph, 0, 1); // A와 B 연결
    addEdge(graph, 1, 0); // B와 A 연결
    addEdge(graph, 2, 3); // C와 D 연결
    addEdge(graph, 3, 2); // D와 C 연결

    // 그래프 출력
    printGraph(graph);

    return 0;
}