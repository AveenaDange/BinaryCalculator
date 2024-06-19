#include "stack.h"

void initStackLL(StackLL *s, int size){
    s->size = size;
    s->arr = (list *)malloc(sizeof(list *)*size);
    s->top = -1;
    return;
}
void pushToStackLL(StackLL *s, list l){
    if(s->top < s->size-1){
        s->arr[++s->top] = l;
    }
    return;
}
int isEmptyStackOfList(StackLL s){
    return s.top == -1 ? true : false;
}
list popFromStackLL(StackLL *s){
    if(s == NULL)   
        return NULL;

    if(s->top == -1)  
        return NULL;

    return s->arr[s->top--];    
}

list peekFromStackLL(StackLL s){
    if(s.top == -1)
        return NULL;
    else
        return s.arr[s.top];
}
