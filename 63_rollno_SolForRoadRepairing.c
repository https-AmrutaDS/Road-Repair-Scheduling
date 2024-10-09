#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// Define the structure of a road repair job
typedef struct {
    int id;          // Road ID or Name
    int priority;    // Priority of repair (higher means more urgent)
} Road;

// Priority Queue structure
typedef struct {
    Road heap[MAX];
    int size;
} PriorityQueue;

// Function to swap two roads
void swap(Road *a, Road *b) {
    Road temp = *a;
    *a = *b;
    *b = temp;
}

// Function to heapify (for max-heap property)
void heapify(PriorityQueue *pq, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < pq->size && pq->heap[left].priority > pq->heap[largest].priority)
        largest = left;

    if (right < pq->size && pq->heap[right].priority > pq->heap[largest].priority)
        largest = right;

    if (largest != i) {
        swap(&pq->heap[i], &pq->heap[largest]);
        heapify(pq, largest);
    }
}

// Function to insert a road into the priority queue
void insert(PriorityQueue *pq, int id, int priority) {
    if (pq->size >= MAX) {
        printf("Priority Queue is full!\n");
        return;
    }

    // Insert the new road at the end
    int i = pq->size++;
    pq->heap[i].id = id;
    pq->heap[i].priority = priority;

    // Fix the max-heap property if violated
    while (i != 0 && pq->heap[(i - 1) / 2].priority < pq->heap[i].priority) {
        swap(&pq->heap[i], &pq->heap[(i - 1) / 2]);
        i = (i - 1) / 2;
    }
}

// Function to extract the highest priority road from the queue
Road extractMax(PriorityQueue *pq) {
    if (pq->size <= 0) {
        printf("Priority Queue is empty!\n");
        return (Road){-1, -1};  // Return a dummy road
    }

    if (pq->size == 1) {
        pq->size--;
        return pq->heap[0];
    }

    // Store the root road, and replace it with the last road
    Road root = pq->heap[0];
    pq->heap[0] = pq->heap[--pq->size];

    // Restore the max-heap property
    heapify(pq, 0);

    return root;
}

// Function to display the current priority queue (for visualization)
void display(PriorityQueue *pq) {
    if (pq->size == 0) {
        printf("The priority queue is empty.\n");
        return;
    }
    
    printf("Current Roads in Priority Queue (ID, Priority):\n");
    for (int i = 0; i < pq->size; i++) {
        printf("Road %d: Priority %d\n", pq->heap[i].id, pq->heap[i].priority);
    }
}

int main() {
    PriorityQueue pq;
    pq.size = 0;

    int numRoads, id, priority;

    // Take input for the number of roads
    printf("Enter the number of road repair jobs: ");
    scanf("%d", &numRoads);

    // Input each road repair job
    for (int i = 0; i < numRoads; i++) {
        printf("Enter Road ID and Priority for road %d:\n", i + 1);
        printf("Road ID: ");
        scanf("%d", &id);
        printf("Priority (higher value means more urgent): ");
        scanf("%d", &priority);
        insert(&pq, id, priority);
    }

    display(&pq);

    // Extract roads in priority order and simulate repair
    printf("\nRepairing roads in priority order:\n");
    while (pq.size > 0) {
        Road nextRoad = extractMax(&pq);
        printf("Repairing Road %d with Priority %d\n", nextRoad.id, nextRoad.priority);
    }

    return 0;
}