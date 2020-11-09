#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

int LA;
int E(), E1(), T(), T1(), F();
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
int error(char *msg) {
    printf("Syntax Error: %s\n", msg);
    exit(1);
}
int match(int t) {
    if(LA == t) {
        LA = yylex();
        return 0;
    } else {
        error("match error");
    }
}

int main() {
    LA = getchar();
    E();
    for(int i=0; i<index; i++) {
        int value = queue[i];
        printf("%d ", value);
        if(value == 100) {
            push(pop() + pop());
        }
        else if(value == 101) {
            push(pop() - pop());
        }
        else if(value == 102) {
            push(pop() * pop());
        }
        else {
            push(value);
        }
    }
    printf("\nresult: %d\n", pop());
}

int E() {
    T(); E1();
}
int E1() {
    if(LA == '+') {
        match('+');
        T();
        queue[index++] = 100;
        E1();
    } else if(LA == '-') {
        match('-');
        T();
        queue[index++] = 101;
        E1();
    } else if(LA == EOF) {
        ;
    } else {
        // epsilon
    }
}
int T() {
    F(); T1();
}
int T1() {
    if(LA == '*') {
        match('*');
        F();
        queue[index++] = 102;
        T1();
    } else if(LA == EOF) {
        ;
    } else {
        // epsilon
    }
}
int F() {
    char c = '0';
    for(int i=0; i<100; i++) {
        char t_ = c + i;
        if (LA == t_) {
            match(t_);
            int r_ = t_ - '0';
            queue[index++] = r_;
            return 0;
        }
    }
    error("invalid terminal");
}
