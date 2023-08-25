#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

// To Run:
// gcc BreadthFirstSearch.c -o bfs
// ./bfs

// Queue data structure for BFS
typedef struct {
    int *arr;
    int front, rear;
    unsigned capacity;
} Queue;

Queue* createQueue(unsigned capacity) {
    Queue* queue = (Queue*)malloc(sizeof(Queue));
    queue->capacity = capacity;
    queue->front = queue->rear = -1;
    queue->arr = (int*)malloc(queue->capacity * sizeof(int));
    return queue;
}

bool isEmpty(Queue* queue) {
    return queue->front == -1;
}

void enqueue(Queue* queue, int item) {
    if (queue->rear == queue->capacity - 1)
        return; // Queue is full
    if (isEmpty(queue))
        queue->front = 0;
    queue->rear++;
    queue->arr[queue->rear] = item;
}

int dequeue(Queue* queue) {
    if (isEmpty(queue))
        return -1; // Queue is empty
    int item = queue->arr[queue->front];
    if (queue->front == queue->rear)
        queue->front = queue->rear = -1; // Last element
    else
        queue->front++;
    return item;
}

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

void bfs(Graph* graph, int startVertex) {
    bool* visited = (bool*)malloc(graph->numVertices * sizeof(bool));
    for (unsigned i = 0; i < graph->numVertices; ++i)
        visited[i] = false;

    Queue* queue = createQueue(graph->numVertices);
    visited[startVertex] = true;
    enqueue(queue, startVertex);

    while (!isEmpty(queue)) {
        int currentVertex = dequeue(queue);
        printf("%d ", currentVertex);

        Node* temp = graph->adjList[currentVertex];
        while (temp) {
            int adjVertex = temp->vertex;
            if (!visited[adjVertex]) {
                visited[adjVertex] = true;
                enqueue(queue, adjVertex);
            }
            temp = temp->next;
        }
    }

    free(visited);
    free(queue->arr);
    free(queue);
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

    printf("Breadth-First Traversal (starting from vertex 0): ");
    bfs(graph, 0);

    return 0;
}
