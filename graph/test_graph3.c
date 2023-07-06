#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FAVORITE 100
#define AREA_NUM 20

typedef struct s_vertex {
    char name[MAX_FAVORITE];
    struct s_vertex* nearest;
    int area_num;
    int cnt;
} t_vertex;

typedef struct s_graph {
    t_vertex** vertex;
} t_graph;

t_graph* init_graph() {
    t_graph* graph = malloc(sizeof(t_graph));
    graph->vertex = malloc(AREA_NUM * sizeof(t_vertex*));
    for (int i = 0; i < AREA_NUM; i++) {
        graph->vertex[i] = NULL;
    }
    return graph;
}

t_vertex* create_vertex(char* name, int area_num) {
    t_vertex* vertex = malloc(sizeof(t_vertex));
    strcpy(vertex->name, name);
    vertex->nearest = NULL;
    vertex->area_num = area_num;
    vertex->cnt = 0;
    return vertex;
}

void insertStore(t_graph* graph, char* name, int area_num, int nearest_area_num) {
    t_vertex* store = create_vertex(name, area_num);
    if (graph->vertex[area_num] == NULL) {
        graph->vertex[area_num] = store;
    } else {
        t_vertex* current = graph->vertex[area_num];
        while (current->nearest != NULL) {
            current = current->nearest;
        }
        current->nearest = store;
    }
    store->nearest = graph->vertex[nearest_area_num];
}

void printGraph(t_graph* graph) {
    for (int i = 0; i < AREA_NUM; i++) {
        t_vertex* current = graph->vertex[i];
        printf("가게 위치: %d\n", i);
        while (current != NULL) {
            printf("  가게 이름: %s\n", current->name);
            printf("  인접 가게: %s\n", current->nearest ? current->nearest->name : "없음");
            current = current->nearest;
        }
    }
}

int main() {
    t_graph* graph = init_graph();

    insertStore(graph, "가게1", 0, 1);
    insertStore(graph, "가게2", 0, 2);
    insertStore(graph, "가게3", 1, 3);
    insertStore(graph, "가게4", 2, 4);

    printGraph(graph);

    return 0;
}
