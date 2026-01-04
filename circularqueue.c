#include <stdio.h>
#define SIZE 5  // maximum size of the circular queue
int queue[SIZE];
int front = -1, rear = -1;

int isFull() {
    return (front == (rear + 1) % SIZE);
}

int isEmpty() {
    return (front == -1);
}

void enqueue(int value) {
    if (isFull()) {
        printf("Queue is full (Overflow)\n");
    } else {
        if (front == -1) // first element
            front = 0;
        rear = (rear + 1) % SIZE;
        queue[rear] = value;
        printf("Inserted %d\n", value);
    }
}

void dequeue() {
    if (isEmpty()) {
        printf("Queue is empty (Underflow)\n");
    } else {
        printf("Deleted %d\n", queue[front]);
        if (front == rear) { // only one element was present
            front = rear = -1;
        } else {
            front = (front + 1) % SIZE;
        }
    }
}

void display() {
    if (isEmpty()) {
        printf("Queue is empty\n");
    } else {
        printf("Queue elements: ");
        int i = front;
        while (1) {
            printf("%d ", queue[i]);
            if (i == rear)
                break;
            i = (i + 1) % SIZE;
        }
        printf("\n");
    }
}

int main() {
    enqueue(10);
    enqueue(20);
    enqueue(30);
    display();
    dequeue();
    dequeue();
    display();

    enqueue(60);
    enqueue(70);
    display();

    return 0;
}
