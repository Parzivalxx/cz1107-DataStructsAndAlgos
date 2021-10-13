#include <stdio.h>
#include <stdlib.h>

#define SIZE 80 //The limit of expression length

typedef struct _stackNode{
    double item;
    struct _stackNode *next;
}StackNode;

typedef struct _stack{
   int size;
   StackNode *head;
}Stack;

void push(Stack *sPtr, double item);
int pop(Stack *sPtr);
double peek(Stack s);
int isEmptyStack(Stack s);

double exePostfix(char*);

int main()
{
    char postfix[SIZE];

    printf("Enter a postfix expression:\n");
    gets(postfix);

    printf("The answer is %.2lf.\n",exePostfix(postfix));

    return 0;
}


double exePostfix(char* postfix)
{
    // Write your code here
    Stack s;
    s.size = 0;
    s.head = NULL;
    int i = 0;
    double op1, op2;
    double result;
    char c;

    // for evaluate prefix, go from back to front, so need to get count of string first
    // int i = 0;
    // while (prefix[i] != '\0')
    //      i++;
    // for (int j=i-1; j>=0; j--) {
    //      c = prefix[j];
    //      continue with algorithm...
    // }

    while (postfix[i] != '\0') {
        c = postfix[i++];
        if (c=='+'||c=='-'||c=='*'||c=='/') {
            op1 = peek(s);
            pop(&s);
            op2 = peek(s);
            pop(&s);
            if (c=='+')
                push(&s, op2+op1);
            else if (c=='-')
                push(&s, op2-op1);
            else if (c=='*')
                push(&s, op2*op1);
            else if (c=='/')
                push(&s, op2/op1);
        }
        else
            push(&s, (c-'0'));
    }
    result = peek(s);
    pop(&s);
    return result;
}

void push(Stack *sPtr, double item){
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

double peek(Stack s){
    return s.head->item;
}

int isEmptyStack(Stack s){
     if(s.size == 0) return 1;
     else return 0;
}
