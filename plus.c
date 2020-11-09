#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

int LA;
int E(), E1(), T(), T1(), F();
int queue[MAX_SIZE], index=0;
int stack[MAX_SIZE], top=-1;
char error_msg[256];
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
    printf("%s\n", msg);
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
    int t = T();
    t = E1();
    if(t < 0) {
        error(error_msg);
    }
}
int E1() {
    if(LA == EOF || LA == '\n') {
        return 0;
    }
    if(LA != '+' && LA != '-') {
        sprintf(error_msg, "invalid operator: %c", LA);
        return -1;
    }
    int t = 0;
    if(LA == '+') {
        match('+');
        t = T();
        queue[index++] = 100;
        t = E1();
        return t;
    } else if(LA == '-') {
        match('-');
        t = T();
        queue[index++] = 101;
        t = E1();
        return t;
    } else {
        ;
    }
}
int T() {
    int t = F();
    t = T1();
    return t;
}
int T1() {
    if(LA == EOF || LA == '\n') {
        return 0;
    }
    if(LA != '*') {
        sprintf(error_msg, "invalid operator: %c", LA);
        return -1;
    }
    if(LA == '*') {
        int t = 0;
        match('*');
        t = F();
        queue[index++] = 102;
        t = T1();
        return t;
    } else if(LA == EOF) {
        ;
    } else {
        error("T1");
    }
}
int F() {
    char c = '0';
    for(int i=0; i<10; i++) {
        char t_ = c + i;
        if (LA == t_) {
            match(t_);
            int r_ = t_ - '0';
            queue[index++] = r_;
            return 1;
        }
    }
    sprintf(error_msg, "invalid terminal: %c", LA);
    error(error_msg);
}
