#include "InfixToPostfix.h"
#include "functions.h"

void initInfix(Infix *infix, int size){
    infix->next = (list*)malloc(sizeof(list* )*size);
    infix->count = 0;
}
void createInfix(Infix *infix, list l){
    infix->next[infix->count++] = l;
}
void displayInfix(Infix infix){
    for(int i=0; i<infix.count; i++){
        displayNumbers(infix.next[i]);
    }
}
void initPostFix(Postfix *postfix, int size){
    postfix->next = (list*)malloc(sizeof(list*)*size);
    postfix->count = 0;
}
int isOperator(char ch){
    if(ch == '+' || ch == '-' || ch == '*' || ch == '/' || ch == '^' || ch == '%' || ch == '>' || ch == '<')
        return true;
    return false;
}
int priority(char ch){
    if(ch == '^')
        return 4;
    else if(ch == '*' || ch == '/' || ch == '%')
        return 3;
    else if(ch == '+' || ch == '-')
        return 2;
    else if(ch == '>' || ch == '<')
        return 1;
    return 0;
}
void insertIntoPostfix(Postfix *postfix,list l){
    postfix->next[postfix->count++] = l;
    return;
}
Postfix createPostfix(Infix infix){
    StackLL temp;
    initStackLL(&temp, infix.count);

    Postfix postfix;
    initPostFix(&postfix, infix.count);

    for(int i=0; i<infix.count; i++){
        if(isdigit(infix.next[i]->data)){
            insertIntoPostfix(&postfix, infix.next[i]);
        }
        else if(infix.next[i]->data == '('){
            pushToStackLL(&temp, infix.next[i]); //store into stack
        }
        else if(infix.next[i]->data == ')'){ //pop from stack
            list tempList = popFromStackLL(&temp);
            while(tempList && tempList->data != '('){
                insertIntoPostfix(&postfix, tempList);
                tempList = popFromStackLL(&temp); //temp has the previously added operators here
            }
        }
        else if(isOperator(infix.next[i]->data)){ //if it is an operator push to stack by checking priority, pop accordingly
            if(isEmptyStackOfList(temp)){
                pushToStackLL(&temp, infix.next[i]); //if stack is empty, push the first opeartor to temp(stack)
            }
            else{
                if(priority(infix.next[i]->data) > priority(peekFromStackLL(temp)->data)){ //priority of infix data is greater than that of stack top then push the opr onthe stack
                    pushToStackLL(&temp, infix.next[i]);
                }
                else if(priority(infix.next[i]->data) == priority(peekFromStackLL(temp)->data) && infix.next[i]->data == '^'){ //priority of infix data is equal to that of stack top then push the opr onthe stack
                    pushToStackLL(&temp, infix.next[i]);
                }
                else{
                    while(!isEmptyStackOfList(temp) && priority(infix.next[i]->data) <= priority(peekFromStackLL(temp)->data)){ //priority on stack is less than or equal to infix operator, then pop from stack and push into postfix
                        insertIntoPostfix(&postfix, popFromStackLL(&temp));
                    }
                    pushToStackLL(&temp, infix.next[i]); //push the operator on stack
                }
            }
        }    
    }
    while(!isEmptyStackOfList(temp)){
        insertIntoPostfix(&postfix, popFromStackLL(&temp)); //inserting the remaining elements in the stack into postfix
    }
    return postfix;
}

void displayPostfix(Postfix postfix){
    for(int i=0; i<postfix.count; i++){
        displayNumbers(postfix.next[i]);
        printf(" ");
    }
}

list evaluatePostfix(Postfix postfix){
    list answer, temp;
    initList(&answer);
    initList(&temp);

    StackLL numbers;
    initStackLL(&numbers, postfix.count);

    for(int i=0; i<postfix.count; i++){
        if(isdigit(postfix.next[i]->data)){
            pushToStackLL(&numbers, postfix.next[i]); //if the char is a digit, push it on the stack
        }
        else{
            list num1 = popFromStackLL(&numbers);
            list num2 = popFromStackLL(&numbers);

            switch(postfix.next[i]->data){
                case '*':
                    temp = multiply(num2, num1);
                    break;
                case '/':
                    temp = divide(num2, num1);
                    break;  
                case '+':
                    temp = add(num2, num1);
                    break;
                case '-':
                    temp = subtract(num2, num1);
                    break;
                default :
                    printf("Incorrect operator error!");
                    return NULL;
                    break;
            }
            pushToStackLL(&numbers, temp);
        }
    }
    return temp;
}