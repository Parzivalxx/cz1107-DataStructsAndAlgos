#include <stdio.h>
#include <stdlib.h>

#define SIZE 80 //The limit of expression length

typedef struct _stackNode{
    char item;
    struct _stackNode *next;
}StackNode;

typedef struct _stack{
   int size;
   StackNode *head;
}Stack;

void push(Stack *sPtr, char item);
int pop(Stack *sPtr);
char peek(Stack s);
int isEmptyStack(Stack s);

void in2Pre(char*, char*);
int precedence(char c);

int main()
{
    char infix[SIZE];
    char prefix[SIZE];

    printf("Enter an infix expression:\n");
    gets(infix);

    in2Pre(infix,prefix);
    printf("The prefix expression is \n");
    printf("%s\n",prefix);

    return 0;
}

void in2Pre(char* infix, char* prefix)
{
    // Write your code here
    Stack s;
    s.size = 0;
    s.head = NULL;
    int i = 0;
    int j = 0;
    int count = 0;
    char c;
    char revInfix[SIZE];
    char revPrefix[SIZE];

    // revinfix -> add to revprefix -> reverse revprefix -> prefix

    while (infix[count] != '\0')
        count++;
    for (int k = 0; k<count; k++)
        revInfix[k] = infix[count-1-k];
    revInfix[count] = '\0';

    while (revInfix[i] != '\0') {
        c = revInfix[i++];
        if (c=='+'||c=='-'||c=='*'||c=='/') {
            while ((isEmptyStack(s)==0) && (peek(s)!=')') && (precedence(peek(s))>precedence(c))) {
                revPrefix[j++] = peek(s);
                pop(&s);
            }
            push(&s, c);
        }
        else if (c==')')
            push(&s, c);
        else if (c=='(') {
            while (peek(s) != ')') {
                    revPrefix[j++] = peek(s);
                    pop(&s);
            }
            pop(&s);
        }
        else
            revPrefix[j++] = c;
    }

    while (isEmptyStack(s)==0) {
        revPrefix[j++] = peek(s);
        pop(&s);
    }
    revPrefix[j] = '\0';

    count = 0;
    while (revPrefix[count] != '\0')
        count++;

    for (int l = 0; l<count; l++)
        prefix[l] = revPrefix[count-1-l];
    prefix[count] = '\0';

    return;
}

int precedence(char c) {
    if (c=='*'||c=='/')
        return 1;
    return 0;
}

void push(Stack *sPtr, char item){
    StackNode *newNode;
    newNode = malloc(sizeof(StackNode));
    newNode->item = item;
    newNode->next = sPtr->head;
    sPtr->head = newNode;
    sPtr->size++;
}

int pop(Stack *sPtr){
    if(sPtr == NULL || sPtr->head == NULL){
        return 0;
    }
    else{
       StackNode *temp = sPtr->head;
       sPtr->head = sPtr->head->next;
       free(temp);
       sPtr->size--;
       return 1;
    }
}

char peek(Stack s){
    return s.head->item;
}

int isEmptyStack(Stack s){
     if(s.size == 0) return 1;
     else return 0;
}
