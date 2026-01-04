#include<stdio.h>
#define SIZE 20
int stack[SIZE];
int top=-1;

void push(int value){
    if(top>=SIZE-1){
        printf("Stack Overflow,Insertion is not possible:\n");
    }
    else{
        top++;
        stack[top]=value;
        printf("%d is inserted to the stack\n",value);
    }
}
void pop(){
    if(top==-1){
        printf("Stack Underflow!Nothing to pop");
    }
    else{
        printf("%d is popped from the stack\n",stack[top]);
        top--;
    }
}
void display(){
    if(top==-1){
        printf("Stack Underflow!\n");
    }
    else{
        printf("Stack elements are:");
        for(int i=top;i>=0;i--){
            printf("%d",stack[i]);
        }
        printf("\n");
    }
}
int main(){
    int value,choice;
    while(1){
        printf("Stack operations are:\n");
        printf("1.Push \n 2.Pop \n 3.Display \n 4.Exit \n");
        printf("Enter your choice:");
        scanf("%d",&choice);
        switch(choice){
            case 1:
                printf("Enter the value to insert:");
                scanf("%d",&value);
                push(value);
                break;
            case 2:
                pop();
                break;
            case 3:
                display();
                break;
            case 4:
                printf("Exiting..\n");
                return 0;
            default:
                printf("Invalid Choice..\n");
        }
    }
}