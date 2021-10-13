#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define SIZE 200 //The number digit limitation

typedef struct _btnode{
	int item;
	struct _btnode *left;
	struct _btnode *right;
} BTNode;   // You should not change the definition of BTNode

typedef struct _node{
     BTNode* item;
     struct _node *next;
}StackNode;

typedef struct _stack{
   int size;
   StackNode *head;
}Stack;

void deleteTree(BTNode **root);

void createExpTree(BTNode** root,char* prefix);
void printTree(BTNode *node);
void printTreePostfix(BTNode *node);
double computeTree(BTNode *node);

void push(Stack *sPtr,  BTNode* item);
int pop(Stack *sPtr);
BTNode *peek(Stack s);
int isEmptyStack(Stack s);

int main()
{
    char prefix[SIZE];
    BTNode* root=NULL;

    printf("Enter an prefix expression:\n");
    gets(prefix);

    createExpTree(&root, prefix);

    printf("The Infix Expression:\n");
    printTree(root);
    printf("\n");
    printf("The Postfix (Reverse Polish) Expression:\n");
    printTreePostfix(root);
    printf("\n");
    printf("Answer ");
    printf("%.2f\n", computeTree(root));
    deleteTree(&root);
    return 0;
}

void createExpTree(BTNode** root,char* prefix)
{
    //Write your code here
    Stack s;
    s.head = NULL;
    s.size = 0;
    char st[10];
    st[0] = '\0';
    int num = 0;
    BTNode *cur;
    BTNode *temp;
    for (int i = 0; prefix[i] != '\0'; i++) {
        if (prefix[i]==' ' || prefix[i]=='(' || prefix[i]==')')
            continue;
        if (prefix[i]=='+'||prefix[i]=='-'||prefix[i]=='*'||prefix[i]=='/'||prefix[i]=='^')
            num = (int)(prefix[i++]) - 999;
        while (isdigit(prefix[i])) {
            st[0] = prefix[i++];
            st[1] = '\0';
            num = num*10 + atoi(st);
            st[0] = '\0';
        }
        while (1) {
            if (*root == NULL) {
                cur = (BTNode*)malloc(sizeof(BTNode));
                cur->item = num;
                cur->left = NULL;
                cur->right = NULL;
                *root = cur;
                temp = *root;
                if (num < 0)
                    push(&s, *root);
                num = 0;
                break;
            }
            else if ((*root)->left == NULL) {
                cur = (BTNode*)malloc(sizeof(BTNode));
                cur->item = num;
                cur->left = NULL;
                cur->right = NULL;
                (*root)->left = cur;
                if (num < 0) {
                    *root = (*root)->left;
                    push(&s, *root);
                }
                num = 0;
                break;
            }
            else if ((*root)->right == NULL) {
                cur = (BTNode*)malloc(sizeof(BTNode));
                cur->item = num;
                cur->left = NULL;
                cur->right = NULL;
                (*root)->right = cur;
                if (num < 0) {
                    *root = (*root)->right;
                    push(&s, *root);
                }
                num = 0;
                break;
            }
            if (!isEmptyStack(s)) {
                *root = peek(s);
                pop(&s);
            }
            //printf("%d", (*root)->item);
        };
        i--;
    }
    *root = temp;
}

void printTree(BTNode *node){
    //Write your code here
    if (node == NULL)
        return;
    else {
        printTree(node->left);
        if (node->item >= 0)
            printf("%d ", node->item);
        else
            printf("%c ", (node->item) + 999);
        printTree(node->right);
    }
    return;
}


void printTreePostfix(BTNode *node){
    //Write your code here
    if (node == NULL)
        return;
    else {
        printTreePostfix(node->left);
        printTreePostfix(node->right);
        if (node->item >= 0)
            printf("%d ", node->item);
        else
            printf("%c ", (node->item) + 999);
    }
    return;
}

double computeTree(BTNode *node){
    //Write your code here
    if (node == NULL)
        return 0;
    if (node->item >= 0)
        return node->item;
    double left = computeTree(node->left);
    double right = computeTree(node->right);
    if ((node->item) + 999 == 43)
        return left + right;
    if ((node->item) + 999 == 45)
        return left - right;
    if ((node->item) + 999 == 42)
        return left * right;
    if ((node->item) + 999 == 47)
        return left / right;
    return pow(left, right);
}

void push(Stack *sPtr, BTNode *item){
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

BTNode *peek(Stack s){
    return s.head->item;
}

int isEmptyStack(Stack s){
     if(s.size == 0) return 1;
     else return 0;
}

void deleteTree(BTNode **root){
    BTNode* temp;
    if(*root !=NULL)
    {
        temp = (*root)->right;
        deleteTree(&((*root)->left));
        free(*root);
        *root = NULL;
        deleteTree(&temp);
    }
}
