#ifndef LINKEDLIST_H
#define LINKEDLIST_H

#include "linkedList.h"

#endif
typedef struct StackLL{
    list *arr;
    int top;
    int size;
    int count;
}StackLL;

void initStackLL(StackLL *s, int size);
void pushToStackLL(StackLL *s, list l);
int isEmptyStackOfList(StackLL s);
list popFromStackLL(StackLL *s);
list peekFromStackLL(StackLL s);

