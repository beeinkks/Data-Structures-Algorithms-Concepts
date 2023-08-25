#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// Graph data structure
typedef struct Node {
    int vertex;
    struct Node* next;
} Node;

typedef struct {
    Node** adjList;
    unsigned numVertices;
} Graph;

Graph* createGraph(unsigned numVertices) {
    Graph* graph = (Graph*)malloc(sizeof(Graph));
    graph->numVertices = numVertices;
    graph->adjList = (Node**)malloc(numVertices * sizeof(Node*));
    for (unsigned i = 0; i < numVertices; ++i)
        graph->adjList[i] = NULL;
    return graph;
}

void addEdge(Graph* graph, int src, int dest) {
    Node* newNode = (Node*)malloc(sizeof(Node));
    newNode->vertex = dest;
    newNode->next = graph->adjList[src];
    graph->adjList[src] = newNode;
}

void dfsVisit(Graph* graph, int vertex, bool* visited) {
    visited[vertex] = true;
    printf("%d ", vertex);

    Node* temp = graph->adjList[vertex];
    while (temp) {
        int adjVertex = temp->vertex;
        if (!visited[adjVertex]) {
            dfsVisit(graph, adjVertex, visited);
        }
        temp = temp->next;
    }
}

void dfs(Graph* graph, int startVertex) {
    bool* visited = (bool*)malloc(graph->numVertices * sizeof(bool));
    for (unsigned i = 0; i < graph->numVertices; ++i)
        visited[i] = false;

    dfsVisit(graph, startVertex, visited);

    free(visited);
}

int main() {
    unsigned numVertices = 7;
    Graph* graph = createGraph(numVertices);

    addEdge(graph, 0, 1);
    addEdge(graph, 0, 2);
    addEdge(graph, 1, 3);
    addEdge(graph, 1, 4);
    addEdge(graph, 2, 5);
    addEdge(graph, 2, 6);

    printf("Depth-First Traversal (starting from vertex 0): ");
    dfs(graph, 0);

    return 0;
}
