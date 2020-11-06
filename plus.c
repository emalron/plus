#include <stdio.h>
#include <stdlib.h>
#define MAX_SIZE 100

int LA;
int E(), E1(), T();
int stack[MAX_SIZE];
int commands[MAX_SIZE], index=0;
int top = -1;
int IsEmpty() {
    if(top < 0)
        return 1;
    else
        return 0;
}
int IsFull() {
    if(top >= MAX_SIZE)
        return 1;
    else
        return 0;
}
void push(int value) {
    if(IsFull())
        printf("error: stack is full.\n");
    else
        stack[++top] = value;
}
int pop() {
    if(IsEmpty())
        printf("error: stack is empty\n");
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
    for(int i=0; i<index;i++) {
        printf("%d ", commands[i]);
    }
    printf("\n");
    int back[index];
    int j = 0;
    while(j<index) {
        int L = commands[j];
        if(L == 100) {
            if(!IsEmpty()) {
                int t_ = pop();
                push(100);
                back[i] = t_;
            } else {
                push(100);
            }
        } else {
            back[j] = L;
            j++;
        }
    }
    for(int i=0; i<index;i++) {
        printf("%d ", back[i]);
    }
    printf("\n");
    for(int i=0; i<index; i++) {

}
int E() {
    T(); E1();
}
int E1() {
    if(LA == '+') {
        match('+');
        commands[index++] = 100;
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
            commands[index++] = r_;
            printf("T: %c\n", t_);
            return 0;
        }
    }
    error();
}
