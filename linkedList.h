#include<stdio.h>
#include<stdlib.h>
#include<ctype.h>

#define true 1
#define false 0

typedef struct node{
    char data;
    struct node* next;
}node;

typedef node* list;

void initList(list *l);
node* createNode(char data);
void insertBeg(list *l, char data);
void reverseList(list *l);
void displayInReverse(list l); 
void displayNumbers(list l);

