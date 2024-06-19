#include "functions.h"
#include<math.h>

#define POSITIVE 1
#define NEGATIVE 0

int scale = 0;

void deleteZeroes(list *l){
    reverseList(&(*l)->next);
    node* p = (*l)->next;
    node* q = (*l);
    node* temp;
    while(p->data == '0' && p->next){
        temp = p;
        p = p->next;
        free(temp);
        q->next = p;
    }
    reverseList(&(*l)->next);
    return;
}

int isZero(list l){
    if(l == NULL)
        return true;
    if(l->next == NULL)
        return true;
    node* p = l->next;
    while(p){
        if(p->data != '0')
            return false;
        p = p->next;
    }
    return true;
}
// void comp(list l1, list l2, int * greater){
//     if(l1 == NULL)
//         return;
        
//     comp(l1->next,l2->next,greater);
//     if(*greater == 0)
//         if(l1->data > l2->data)
//             *greater = 1;
//         else if( l2->data > l1 -> data)
//             *greater = -1;
// }
void comp(list l1, list l2, int * greater) {
    list temp1 = l1, temp2 = l2;
    while(temp1 != NULL && temp2 != NULL){
        if(*greater == 0) {
            if(temp1->data > temp2->data)
                *greater = 1;
            else if(temp2->data > temp1->data)
                *greater = -1;
        }

        temp1 = temp1->next;
        temp2 = temp2->next;
    }
}
int compareNumbers(list l1,list l2){
    int greater = 0;
    node *p = l1;
    node *q = l2;
    while(p && q){
        p = p->next;
        q = q->next;
    }
    if(p)
        return 1;
    if(q)
        return -1;
    comp(l1->next,l2->next,&greater);
    return greater;
}
void negateSigns(list *l){
    if((*l)->data == 0){
        (*l)->data = 1;
    }
    else    
        (*l)->data = 0;
}

node* add(list l1, list l2){
    list ans;
    initList(&ans);

    if(l1 == NULL && l2 == NULL) //if both lists are empty then we cannot perfom addition
        return NULL;
    
    if(l1 == NULL){ //is num1 is empty then we add num2 to the result
        node* p = l2->next; //sets to sign bit
        while(p){
            insertBeg(&ans, p->data);
            p = p->next;
        }
        reverseList(&ans->next);
        ans->data = l2->data;
        return ans;
    }
    else if(l2 == NULL){
        node* p = l1->next;
        while(p){
            insertBeg(&ans, p->data);
            p = p->next;
        }
        reverseList(&ans->next);
        ans->data = p->data; 
        return ans;
    }

    if(l1->next == NULL && l2->next == NULL){
        return NULL;
    }
    if(l1->next == NULL){
        return l2;
    }
    else if(l2->next == NULL){
        return l1;
    }
    if(l1->data != l2->data){ //
        if(l1->data == '0')
            return subtract(l2, l1);
        else    
            return subtract(l1, l2);
    }

    node* p = l1->next;
    node* q = l2->next;
    int carry = 0, a, b;
    
    while(p && q){
        // int sum = 0;
        a = p->data - '0';
        b = q->data - '0';
        //sum = a+b+carry;
        insertBeg(&ans, ((a+b+carry) % 10) + '0');  
        if(a+b+carry > 9)
            carry = 1;
        else    
            carry = 0;

        p = p->next;
        q = q->next;
    }
    while(p){
        a = p->data - '0';

        insertBeg(&ans, ((a + carry) % 10) + '0');
        if(a + carry > 9)
            carry = 1;
        else     
            carry = 0;
        p = p->next;
    }

    while(q){
        a = q->data - '0';

        insertBeg(&ans, ((a + carry) % 10) + '0');
        if(a + carry > 9)
            carry = 1;
        else
            carry = 0;
        q = q->next;     
    }

    q = ans->next;
    if(carry == 1){
        insertBeg(&ans, carry + '0');
    }                                

    reverseList(&ans->next);
    return ans;                                                                                                                                                                                                                                                                                          
}


node* multiply(list l1, list l2){ //add multiple times
    list ans;
    initList(&ans);
    list temp;

    if(l1 == NULL || l2 == NULL) //when both numbers are NULL, there is nothing to multiply
        return NULL;

    if(isZero(l1) || isZero(l2)) { // if either of the numbers are zero then answer is 0
        initList(&ans);
        insertBeg(&ans, '0');
        return ans;
    }

    node* p = l2->next;
    int count = 0;
    while(p){
        initList(&temp);
        int n = p->data - '0';
        for(int i=0; i<n; i++){
            temp = add(temp, l1);
        }
        for(int i=0; i<count; i++)
            if(count > 0)
                insertBeg(&temp, '0');

        count++;
        ans = add(ans, temp);
        p = p->next;
        free(temp);
    }

    if(l1->data != l2->data) //negating the signs
        //result->data = result->data == '1' ? '0' : '1';
        if(ans->data == '1')
            ans->data = '0';
        else
            ans->data = '1';
    return ans;
}


node* subtract(list l1, list l2){
    if(l1 == NULL && l2 == NULL) //if both the numbers are null there is nothing to subtract
        return NULL;
// for below snippet: 
// - -11 => +11
// - 11 => -11
    if(l1 == NULL || isZero(l1)){  //negating the signs
        if(l2->data == '0')
            l2->data = '1';
        else    
            l2->data = '0';

        return l2;
    }
    list ans;
    initList(&ans);
// 00 - - 23
// 00 - 23
    node* p = l1->next; //to access the number, skipping the sign bit
    node* q = l2->next;
    int borrow = 0, a, b, current;
    int comparison = compareNumbers(l1, l2);
    //if num1 > num2
    if(comparison == 1){ //if l1 is greater than l2
        while(p && q){ 
            a = p->data - '0'; 
            b = q->data - '0';
            current = (a - b - borrow); 
            //printf("current: %d\n", current);
            if(a-b-borrow < 0)
                borrow = 1;
            else    
                borrow = 0;

            if(borrow == 1)
                current += 10;
            insertBeg(&ans, (current) + '0');
            p = p->next;
            q = q->next;
        }
        while(p){ 
            a = p->data - '0';
            current = ((a - borrow));
            if((a - borrow) < 0)
                borrow = 1;
            else    
                borrow = 0;

            if(borrow == 1)
                current += 10;
            insertBeg(&ans, current + '0');
            p = p->next;
        }
        reverseList(&ans->next);
        //negateSigns(&ans);
        deleteZeroes(&ans);
        //printf("sign: %d", ans->data);
        return ans;
    }

    else if(comparison == -1){ //if l2 is greater than l1
        ans = subtract(l2, l1);
        if(ans->data == '1') //negating signs
            ans->data = '0'; //ans->data = l2->data;
        else    
            ans->data = '1';
        //printf("sign: %d", ans->data);
        return ans;
    }

    else{
        insertBeg(&ans, '0'); //if both numbers are equal then the answer is only 0
        //printf("sign: %d", ans->data);
        return ans;
    }
}

node* divide(list l1, list l2){
    list ans;
    initList(&ans);

    if(l1 == NULL && l2 == NULL) //both operators are NULL
        return NULL;

    if(l1 == NULL || isZero(l1)){ // 0 divided by anything would be zero
        insertBeg(&ans, '0');
        return ans;
    }
    else if(l2 == NULL || isZero(l2)){ //cannot divide by 0
        printf("Divide by zero error!");
        exit(0);
    }

    char temp = l1->data == '0' ? '1' : '0';
    // char temp;
    // if(l1->data == '0')
    //     temp = '1';
    // else
    //     temp = '0';

    int sign = 1;
    if(l1->data != l2->data) //if the signs are different for both the operands, then the result would be negative
        sign = 0; // - + = -

    // if(l1->data == '1')
    //     sign = 0;

    list addOne;
    initList(&addOne);
    insertBeg(&addOne, '1'); 
    

    int comparison = compareNumbers(l1, l2);
    if(comparison == 1){ //l1 is greater than l2
        while(l1->data != temp){ //repeatedly subtracting l2 from l1 until l1 becomes less than temp
            l1 = subtract(l1, l2);
            ans = add(ans, addOne);
        }
        ans = subtract(ans, addOne);
        ans->data = sign;
        return ans;
    }
    else if(comparison == -1){ //if l2 is greater than l1 then ans is 0
        insertBeg(&ans, '0');
        return ans;
    }
    else{
        insertBeg(&ans, '1'); //if l1==l2 then ans is 0
        ans->data = sign;
        return ans;
    }
    return NULL;
}

