#include <stdio.h>
#include <stdlib.h>

typedef enum {
    false, true
} bool;


typedef struct _listnode
{
    int vertex;
	struct _listnode *next;
} ListNode;
typedef ListNode StackNode;

typedef struct _graph{
    int V;
    int E;
    ListNode **list;
} Graph;

typedef ListNode QueueNode;

typedef struct _queue{
   int size;
   QueueNode *head;
   QueueNode *tail;
} Queue;

typedef struct _stack
{
	int size;
	StackNode *head;
} Stack;

void insertAdjVertex(ListNode** AdjList,int vertex);
void removeAdjVertex(ListNode** AdjList,int vertex);
int matching(Graph g);
bool bfs(Graph g, int source, int sink, int parent[]);

void enqueue(Queue *qPtr, int item);
int dequeue(Queue *qPtr);
int getFront(Queue q);
int isEmptyQueue(Queue q);
void removeAllItemsFromQueue(Queue *qPtr);
void printQ(QueueNode *cur);
//////STACK///////////////////////////////////////////
void push(Stack *sPtr, int vertex);
int pop(Stack *sPtr);
int peek(Stack s);
int isEmptyStack(Stack s);
void removeAllItemsFromStack(Stack *sPtr);
//////////////////////////////////

int main()
{
    int Prj, Std, Mtr; //Project, Student and Mentor;
    int maxMatch;
    scanf("%d %d %d", &Std, &Prj, &Mtr);

    int np,nm; //number of projects and number of mentors
    int proj, ment;

    //build graph
	Graph g;
    //Write your code
    g.E = 0;
    g.V = 2*Std+Prj+Mtr+2;

    g.list = (ListNode **) malloc(g.V*sizeof(ListNode *));
    for(int i=0;i<g.V;i++)
        g.list[i] = NULL;
    for (int j=1; j <= Prj; j++) {
        insertAdjVertex(&(g.list[0]), j);
        g.E++;
    }
    for (int k=1; k<=Std; k++) {
        scanf("%d %d",&np,&nm);
        for (int l=0; l<np; l++) {
            scanf("%d", &proj);
            insertAdjVertex(&(g.list[proj]), Prj+k);
            g.E++;
        }
        insertAdjVertex(&(g.list[Prj+k]), Prj+Std+k);
        g.E++;
        for (int m=0; m<nm; m++) {
            scanf("%d", &ment);
            insertAdjVertex(&(g.list[Prj+Std+k]), Prj+2*Std+ment);
            g.E++;
        }
        scanf("%*c");
    }
    for (int n=1; n<=Mtr; n++) {
        insertAdjVertex(&(g.list[2*Std+Prj+n]), g.V-1);
        g.E++;
    }
    //apply Ford Fulkerson algorithm
    // use DFS or BFS to find a path
	maxMatch = matching(g);
    printf("%d\n", maxMatch);
    return 0;
}

int matching(Graph g)
{
    //Write your code
    int u,v;
    int maxflow = 0;
    int parent[g.V];

    while (bfs(g, 1, g.V, parent)) {
        for (v = g.V-1; v != 0; v = parent[v]) {
            u = parent[v];
            removeAdjVertex(&(g.list[u]), v);
            insertAdjVertex(&(g.list[v]), u);
        }
        // Add path flow to overall flow
        maxflow++;
    }
    return maxflow;
}

// DFS algo
bool bfs(Graph g, int source, int sink, int parent[]) {
    ListNode *temp;
    bool visited[g.V];
    int u,v;
    Queue q;
    q.size = 0;
    q.head = NULL;
    q.tail = NULL;

    for (int i = 0; i<g.V; i++)
        visited[i] = false;
    visited[source-1] = true;
    enqueue(&q, source-1);
    parent[source-1] = -1;

    while (!isEmptyQueue(q)) {
        u = getFront(q);
        dequeue(&q);

        temp = g.list[u];
        while (temp != NULL) {
            v = temp->vertex;
            if (visited[v] == false) {
                if (v == sink-1) {
                    parent[v] = u;
                    return true;
                }
                enqueue(&q, v);
                parent[v] = u;
                visited[v] = true;
            }
            temp = temp->next;
        }
    }
    return false;
}

void removeAdjVertex(ListNode** AdjList,int vertex)
{
    ListNode *temp, *preTemp;
    if(*AdjList != NULL)
    {
        if((*AdjList)->vertex ==vertex){//first node
            temp = *AdjList;
            *AdjList = (*AdjList)->next;
            free(temp);
            return;
        }
        preTemp = *AdjList;
        temp = (*AdjList)->next;
        while(temp!=NULL && temp->vertex != vertex)
        {
            preTemp= temp;
            temp = temp->next;
        }
        preTemp->next = temp->next;
        free(temp);
    }

}
void insertAdjVertex(ListNode** AdjList,int vertex)
{
    ListNode *temp;
    if(*AdjList==NULL)
    {
        *AdjList = (ListNode *)malloc(sizeof(ListNode));
        (*AdjList)->vertex = vertex;
        (*AdjList)->next = NULL;
    }
    else{
        temp = (ListNode *)malloc(sizeof(ListNode));
        temp->vertex = vertex;
        temp->next = *AdjList;
        *AdjList = temp;
    }
}
void enqueue(Queue *qPtr, int vertex) {
    QueueNode *newNode;
    newNode = malloc(sizeof(QueueNode));
    if(newNode==NULL) exit(0);

    newNode->vertex = vertex;
    newNode->next = NULL;

    if(isEmptyQueue(*qPtr))
        qPtr->head=newNode;
    else
        qPtr->tail->next = newNode;

    qPtr->tail = newNode;
    qPtr->size++;
}

int dequeue(Queue *qPtr) {
    if(qPtr==NULL || qPtr->head==NULL){ //Queue is empty or NULL pointer
        return 0;
    }
    else{
       QueueNode *temp = qPtr->head;
       qPtr->head = qPtr->head->next;
       if(qPtr->head == NULL) //Queue is emptied
           qPtr->tail = NULL;

       free(temp);
       qPtr->size--;
       return 1;
    }
}

int getFront(Queue q){
    return q.head->vertex;
}

int isEmptyQueue(Queue q) {
    if(q.size==0) return 1;
    else return 0;
}

void removeAllItemsFromQueue(Queue *qPtr)
{
	while(dequeue(qPtr));
}

void printQ(QueueNode *cur){
    if(cur==NULL) printf("Empty");

    while (cur != NULL){
        printf("%d ", cur->vertex);
        cur = cur->next;
    }
    printf("\n");
}

void push(Stack *sPtr, int vertex)
{
	StackNode *newNode;
    newNode= malloc(sizeof(StackNode));
    newNode->vertex = vertex;
    newNode->next = sPtr->head;
    sPtr->head = newNode;
    sPtr->size++;
}

int pop(Stack *sPtr)
{
    if(sPtr==NULL || sPtr->head==NULL){
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

int isEmptyStack(Stack s)
{
     if(s.size==0) return 1;
     else return 0;
}

int peek(Stack s){
    return s.head->vertex;
}

void removeAllItemsFromStack(Stack *sPtr)
{
	while(pop(sPtr));
}
