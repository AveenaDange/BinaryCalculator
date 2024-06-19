#include "linkedList.h"

void initList(list *l){
    *l = NULL;
    return;
}
node* createNode(char data){
    node* nn = (node*) malloc(sizeof(node));
    nn->data = data;
    nn->next = NULL;
    return nn;
}
void insertBeg(list *l, char data){
    if(*l == NULL){
        if(isdigit(data)){
            *l = createNode('1'); //1-positive 0-negative
            insertBeg(l, data);
            return;
        }
        *l = createNode(data);
        return;
    }
    //inserting data but after the sign bit
    node* p = *l;
    node* nn = createNode(data);
    nn->next = p->next;
    p->next = nn;
    return;
}
// void displayList(list l){
//     if(l == NULL){
//         return;
//     }
//     node* p = l;
//     while(p){
//         printf("%c", p->data);
//         p = p->next;
//     }
//     printf("\n");
// }
void displayInReverse(list l){
    if(l == NULL)
        return;
    displayInReverse(l->next);
    printf("%c", l->data);
    return;
}
void displayNumbers(list l){
    if(l == NULL)
        return;
    else    
        if(l->next == NULL)
            displayInReverse(l); //single element in the list
        else{
            if(l->data == '0') //adding negative sign for a negative number
                printf("-");
            displayInReverse(l->next);
        }
    
}
void reverseList(list *l){ //reverse but after the sign bit
    if(*l == NULL)
        return;
    node* current = *l;
    node* previous = NULL;
    node* next = NULL;

    while(current!=NULL){
        next = current->next;
        current->next = previous;
        previous = current;
        current = next;
    }
    *l = previous;
}