#include <stdio.h>
#include <stdlib.h>

#define SIZE 80 //The size of the array

enum ExpType {OPT,OPERAND};

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

typedef struct _listnode
{
    int  item;
    enum ExpType type;
	struct _listnode *next;
} ListNode;

typedef struct _linkedlist{
   int size;
   ListNode *head;
} LinkedList;

void insertNode(LinkedList *llPtr, int item,enum ExpType type);
int deleteNode(LinkedList *llPtr);
void removeAllNodes(LinkedList *llPtr);
int isEmptyLinkedList (LinkedList ll);


void in2PreLL(char* infix, LinkedList *inExpLL);
int precedence(char);
char reversestr(char *string);

void printExpLL(LinkedList inExpLL);

int main()
{
    char infix[SIZE];

    printf("Enter an infix expression:\n");
    gets(infix);

    LinkedList inExpLL;
    inExpLL.head = NULL;
    inExpLL.size = 0;

    in2PreLL(infix, &inExpLL);

    printExpLL(inExpLL);

    removeAllNodes(&inExpLL);
    return 0;
}

void in2PreLL(char* infix, LinkedList *inExpLL)
{
    //Write your code here
    Stack s;
    s.head = NULL;
    s.size = 0;
    char st[20];
    char st2[20];
    int stridx = 0;
    st[0] = '\0';
    st2[0] = '\0';

    char revInfix[SIZE];
    int i=0;
    int j;
    char c;
    int count =0;
    int count2 = 0;

    //reverse the string
    while(infix[count]!='\0')
        count++;
    for(i=count-1;i>=0;i--)
        revInfix[count-1-i] = infix[i];
    revInfix[count]='\0';

    i=0;
    while(i<SIZE && revInfix[i]!='\0')
    {
        c = revInfix[i++];
        switch(c)
        {
            case '*': //operators
            case '/':
            case '+':
            case '-':
                if (st[0] != '\0') {
                    //reverse the string
                    while(st[count2]!='\0')
                        count2++;
                    for(j=count2-1;j>=0;j--)
                        st2[count2-1-j] = st[j];
                    st2[count2]='\0';
                    insertNode(inExpLL, atoi(st2), OPERAND);
                    st2[0] = '\0';
                    st[0] = '\0';
                    stridx = 0;
                    count2 = 0;
                }
                while(isEmptyStack(s)==0 && peek(s) != ')' && precedence(peek(s)) > precedence(c) ) //note the precedence comparison
                {
                    insertNode(inExpLL, (int)(peek(s)), OPT);
                    pop(&s);
                }
                push(&s,c);
                break;
            case ')':
                if (st[0] != '\0') {
                    //reverse the string
                    while(st[count2]!='\0')
                        count2++;
                    for(j=count2-1;j>=0;j--)
                        st2[count2-1-j] = st[j];
                    st2[count2]='\0';
                    insertNode(inExpLL, atoi(st2), OPERAND);
                    st2[0] = '\0';
                    st[0] = '\0';
                    stridx = 0;
                    count2 = 0;
                }
                push(&s,c);
                break;
            case '(':
                if (st[0] != '\0') {
                    //reverse the string
                    while(st[count2]!='\0')
                        count2++;
                    for(j=count2-1;j>=0;j--)
                        st2[count2-1-j] = st[j];
                    st2[count2]='\0';
                    insertNode(inExpLL, atoi(st2), OPERAND);
                    st2[0] = '\0';
                    st[0] = '\0';
                    stridx = 0;
                    count2 = 0;
                }
                while(isEmptyStack(s)==0)
                {
                    if(peek(s)!=')')
                    {
                        insertNode(inExpLL, (int)(peek(s)), OPT);
                        pop(&s);
                    }
                    else
                    {
                        pop(&s);
                        break;
                    }
                };
                break;
            default: //operand
                st[stridx++] = c;
                st[stridx] = '\0';
        }
    }

    if (st[0] != '\0') {
        //reverse the string
        while(st[count2]!='\0')
            count2++;
        for(j=count2-1;j>=0;j--)
            st2[count2-1-j] = st[j];
        st2[count2]='\0';
        insertNode(inExpLL, atoi(st2), OPERAND);
    }

    while(isEmptyStack(s)==0)
    {
        insertNode(inExpLL, (int)(peek(s)), OPT);
        pop(&s);
    };
}

int precedence(char op)
{
    if(op == '*' || op == '/')
        return 1;
    else return 0;
}

void printExpLL(LinkedList inExpLL)
{
    ListNode* temp = NULL;
    temp = inExpLL.head;
    while(temp!= NULL){
        if(temp->type == OPERAND)
            printf(" %d ",temp->item);
        else
            printf(" %c ",(char)(temp->item));
        temp = temp->next;
    }
    printf("\n");
}

void insertNode(LinkedList *LLPtr, int item, enum ExpType type) {
    ListNode *newNode;
    newNode = malloc(sizeof(ListNode));
    if(newNode==NULL) exit(0);

    newNode->item = item;
    newNode->type = type;
    newNode->next = LLPtr->head;
    LLPtr->head=newNode;
    LLPtr->size++;
}

int deleteNode(LinkedList *LLPtr) {
    if(LLPtr==NULL || LLPtr->size==0){
        return 0;
    }
    else{
       ListNode *temp = LLPtr->head;
       LLPtr->head = LLPtr->head->next;

       free(temp);
       LLPtr->size--;
       return 1;
    }
}

int isEmptyLinkedList (LinkedList ll) {
    if(ll.size==0) return 1;
    else return 0;
}

void removeAllNodes(LinkedList *LLPtr)
{
	while(deleteNode(LLPtr));
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
