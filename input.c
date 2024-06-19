#include"input.h"
int getSizeOfList(char *str){ // char pointer //string //sequence of characters in memory
    int size = 0;
    while(str[size] != '\0')
        size++;

    return size;
}
int getNoOfLists(char *str){ //counts the number of operands
    char *p = str;
    int count = 0;
    int isNumberFlag = false;
    while(*p != '\0'){
        if(isdigit(*p))
            isNumberFlag = true;
        else{
            if(*p == '+' || *p == '-' || *p == '*' || *p == '/' || *p == '%' || *p == '(' || *p == ')' || *p == '^' || *p == '>' || *p == '<'){
                count++;
            }
            else{
                printf("Incorrect Syntax!");
                exit(0);
            }
        }
        p++;
    }
    if(isNumberFlag == true)
        count++;
    return count;
}

int getNoOfOperators(char *input){ //counts the number of operators
    int count = 0;
    char *p = input;

    while(*p != '\0'){
        if(*p  == '+' || *p == '-' || *p == '*' || *p == '/' || *p == '%' || *p == '(' || *p == ')' || *p == '^' || *p == '>' || *p == '<'){
            count++;
        }
        p++;
    }
return count;
}

void InputProcess(){
    char input[100];
    while (true){
        printf("$ ");
        int i = 0;
        char c;
        do{
            scanf("%c", &c);
            if(c == '\n')
                input[i++] = '\0'; //if newline then end of string
            else if(c == ' '){
                //do nothing
            }
            else{
                input[i++] = c;
            }
        }while(c != '\n');
        
        int noOfLists = getNoOfLists(input);
        int noOfOperators = getNoOfOperators(input);
        if(noOfLists <= noOfOperators){
            printf("Invalid Syntax!");
            exit(0);
        }

        list l[noOfLists]; //make an array of lists
        list operators[noOfOperators]; //make an array of operators
        int j = 0;

        char *p = input;
        int operandIndex = 0;
        int operatorIndex = 0;

        
        //insertion begins here-----------
        Infix infix;
        initInfix(&infix, noOfLists + noOfOperators);

        while(*p != '\0'){
            while(*p == ' ')
                p++;

            if(isdigit(*p)){
                initList(&l[operandIndex]);
                while(isdigit(*p)){
                    char c = *p;
                    insertBeg(&l[operandIndex], c);
                    p++;
                }
                createInfix(&infix, l[operandIndex]);
                operandIndex++;
            }
            else{
                initList(&operators[operatorIndex]);
                char c = *p;
                insertBeg(&operators[operatorIndex], c);
                p++;
                createInfix(&infix, operators[operatorIndex]);
                operatorIndex++;
            }
        }
        Postfix postfixExp;
        initPostFix(&postfixExp, noOfLists+noOfOperators);
        postfixExp = createPostfix(infix);
        //displayPostfix(postfixExp);
        printf("\n");
        displayNumbers(evaluatePostfix(postfixExp));
        printf("\n");
    }
}
