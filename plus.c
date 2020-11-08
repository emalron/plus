#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

int LA;
int E(), E1(), T();
int queue[MAX_SIZE], index=0;
int stack[MAX_SIZE], top=-1;
int isEmpty() {
    if(top < 0)
        return 1;
    else
        return 0;
}
int isFull() {
    if(top >= MAX_SIZE) 
        return 1;
    else
        return 0;
}
void push(int t) {
    if(!isFull()) 
        stack[++top] = t;
    else
        printf("stack is full\n");
}
int pop() {
    if(isEmpty())
        printf("stack is empty\n");
    else
        return stack[top--];
}
int yylex() {
    return getchar();
}
int error() {
    printf("Syntax Error\n");
    exit(1);
}
int match(int t) {
    if(LA == t) {
        LA = yylex();
        return 0;
    } else {
        error();
    }
}

int main() {
    LA = getchar();
    E();
    int command[MAX_SIZE], len = 0;
    for(int i=0; i<index; i++) {
        int value = queue[i];
        if(value != 100) {
            command[len++] = value;
        }
        else {
            if(isEmpty()) {
                push(value);
            }
            else {
                int op = pop();
                command[len++] = op;
                push(value);
            }
        }
    }
    while(!isEmpty()) {
        command[len++] = pop();
    }
    top = -1;
    for(int i=0; i<len; i++) {
        int ahead = command[i];
        if(ahead != 100) {
            push(ahead);
        } else {
            int a_ = pop();
            int b_ = pop();
            int result = a_ + b_;
            push(result);
        }
    }
    printf("result: %d\n", pop());
}

int E() {
    T(); E1();
}
int E1() {
    if(LA == '+') {
        match('+');
        queue[index++] = 100;
        T(); E1();
    } else if(LA = EOF) {
        ;
    } else {
        error();
    }
}
int T() {
    char c = '0';
    for(int i=0; i<100; i++) {
        char t_ = c + i;
        if (LA == t_) {
            match(t_);
            int r_ = t_ - '0';
            queue[index++] = r_;
            printf("T: %c\n", t_);
            return 0;
        }
    }
    error();
}
