#include"stack.h"

typedef struct Infix{
    list* next; //char data and next pointer
    int count;
}Infix;

void initInfix(Infix *infix, int size);
void createInfix(Infix *infix, list l);
void displayInfix(Infix infix);

typedef struct Postfix{
    list* next;
    int count;
}Postfix;

void initPostFix(Postfix *postfix, int size);
Postfix createPostfix(Infix infix);
void displayPostfix(Postfix postfix);
list evaluatePostfix(Postfix postfix);
int priority(char ch);
int isOperator(char ch);