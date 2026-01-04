#include<stdio.h>
#define SIZE 50
int queue[SIZE];
int front =-1,rear=-1;

void enqueue(int value){
    if(rear==SIZE-1){
        printf("Queue OverFlow\n");
    }
    else{
        if(front==-1)front=0;
        rear++;
        queue[rear]=value;
        printf("%d is inserted to the queue\n",value);
    }
}
void dequeue(){
    if(front==-1||front>rear){
        printf("Queue Underflow\n");
    }
    else{
        printf("%d is deleted\n",queue[front]);
        front++;
    }
}
void display(){
    if(front==-1||front>rear){
        printf("Queue is Empty\n");
    }
    else{
        printf("Queue Elements are:");
        for(int i=front;i<=rear;i++){
            printf("%d",queue[i]);
        }
        printf("\n");
    }
}
int main(){
    int value,choice;
    while(1){
        printf("Queue Operations are:\n");
        printf("1.Enqueue\n2.Dequeue\n3.Display\n4.Exit\n");
        printf("Enter your choice:");
        scanf("%d",&choice);
        switch(choice){
            case 1:
                printf("Enter the value to insert:");
                scanf("%d",&value);
                enqueue(value);
                break;
            case 2:
                dequeue();
                break;
            case 3:
                display();
                break;
            case 4:
                printf("Exiting..");
                return 0;
            default:
                printf("Invalid choice..");
        }
        
    }
}