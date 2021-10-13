//////////////////////////////////////////////////////////////////////////////////

/* CE1107/CZ1107 Data Structures
Assignment 1 - Linked List Questions
Purpose: Implementing the required functions for Question 4 */

//////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////////////////

typedef struct _listnode{
	int item;
	struct _listnode *next;
} ListNode;			// You should not change the definition of ListNode

typedef struct _linkedlist{
	int size;
	ListNode *head;
} LinkedList;			// You should not change the definition of LinkedList


///////////////////////// function prototypes ////////////////////////////////////

// This is for question 4. You should not change the prototype of this function
void frontBackSplitLinkedList(LinkedList* ll, LinkedList *resultFrontList, LinkedList *resultBackList);

// You may use the following functions or you may write your own
void printList(LinkedList *ll);
void removeAllItems(LinkedList *l);
ListNode * findNode(LinkedList *ll, int index);
int insertNode(LinkedList *ll, int index, int value);
int removeNode(LinkedList *ll, int index);


///////////////////////////// main() /////////////////////////////////////////////

int main()
{
	int c, i;
	LinkedList ll_a, ll_b, resultList;

	//Initialize the linked lists as empty linked lists
	ll_a.head = NULL;
	ll_b.head = NULL;
	resultList.head = NULL;
	ll_a.size = 0;
	ll_b.size = 0;
	resultList.size = 0;

	printf("1: Insert an integer to linked list 1:\n");
	printf("2: Insert an integer to linked list 2:\n");
	printf("3: Print the resulting linked lists after joining:\n");
	printf("0: Quit:\n");
	printf("Please input your choice(1/2/3/0): ");
	scanf("%d", &c);

	while (c != 0)
	{
		switch (c)
		{
		case 1:
			printf("Input an integer that you want to add to linked list 1: ");
			scanf("%d", &i);
			insertNode(&ll_a, ll_a.size, i);
			printf("The resulting linked list 1 is: ");
			printList(&ll_a);
			break;
        case 2:
			printf("Input an integer that you want to add to linked list 2: ");
			scanf("%d", &i);
			insertNode(&ll_b, ll_b.size, i);
			printf("The resulting linked list 2 is: ");
			printList(&ll_b);
			break;
		case 3:
			printf("The resulting linked lists after joining the given linked lists are:\n");
			join(&ll_a, &ll_b, &resultList); // You need to code this function
			printf("The resulting linked list 1 is: ");
			printList(&ll_a);
			printf("The resulting linked list 2 is: ");
			printList(&ll_b);
			printf("Resultant list: ");
			printList(&resultList);
			printf("\n");
			removeAllItems(&ll_a);
			removeAllItems(&ll_b);
			removeAllItems(&resultList);
			break;
		case 0:
			removeAllItems(&ll_a);
			removeAllItems(&ll_b);
			removeAllItems(&resultList);
			break;
		default:
			printf("Choice unknown;\n");
			break;
		}

		printf("\nPlease input your choice(1/2/3/0): ");
		scanf("%d", &c);
	}

	return 0;
}

//////////////////////////////////////////////////////////////////////////////////

void join(LinkedList *ll_a, LinkedList *ll_b, LinkedList *resultList)
{
	/* add your code here */
	ListNode *cur1 = ll_a->head;
	ListNode *cur2 = ll_b->head;
	int tmp1, tmp2, i = 1, j = 1, removed1 = 0, removed2 = 0;

	if (cur1 == NULL || cur2 == NULL)
        return;
    tmp1 = cur1->item;
    tmp2 = cur2->item;
    cur1 = cur1->next;
    cur2 = cur2->next;
    while (cur1 != NULL) {
        if (cur1->item == tmp1) {
            cur1 = cur1->next;
            removeNode(ll_a, i-removed1);
            removed1++;
        }
        else {
            tmp1 = cur1->item;
            cur1 = cur1->next;
        }
        i++;
    };
    while (cur2 != NULL) {
        if (cur2->item == tmp2) {
            cur2 = cur2->next;
            removeNode(ll_b, j-removed2);
            removed2++;
        }
        else {
            tmp2 = cur2->item;
            cur2 = cur2->next;
        }
        j++;
    };
    cur1 = ll_a->head;
    cur2 = ll_b->head;
    while (cur1 != NULL) {
        while (cur2 != NULL) {
            if (cur1->item == cur2->item) {
                insertNode(resultList, resultList->size, cur1->item);
                break;
            }
            cur2 = cur2->next;
        };
        cur2 = ll_b->head;
        cur1 = cur1->next;
    };
    return;
}

//////////////////////////////////////////////////////////////////////////////////

void printList(LinkedList *ll)
{
	ListNode *cur;
	if (ll == NULL)
		return;
	cur = ll->head;
	if (cur == NULL)
		printf("Empty");
	while (cur != NULL)
	{
		printf("%d ", cur->item);
		cur = cur->next;
	}
	printf("\n");
}

void removeAllItems(LinkedList *ll)
{
	ListNode *cur = ll->head;
	ListNode *tmp;

	while (cur != NULL){
		tmp = cur->next;
		free(cur);
		cur = tmp;
	}
	ll->head = NULL;
	ll->size = 0;
}

ListNode * findNode(LinkedList *ll, int index)
{
	ListNode *temp;

	if (ll == NULL || index < 0 || index >= ll->size)
		return NULL;

	temp = ll->head;

	if (temp == NULL || index < 0)
		return NULL;

	while (index > 0){
		temp = temp->next;
		if (temp == NULL)
			return NULL;
		index--;
	}

	return temp;
}

int insertNode(LinkedList *ll, int index, int value)
{
	ListNode *pre, *cur;

	if (ll == NULL || index < 0 || index > ll->size)
		return -1;

	// If empty list or inserting first node, need to update head pointer
	if (ll->head == NULL || index == 0){
		cur = ll->head;
		ll->head = malloc(sizeof(ListNode));
		ll->head->item = value;
		ll->head->next = cur;
		ll->size++;
		return 0;
	}


	// Find the nodes before and at the target position
	// Create a new node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){
		cur = pre->next;
		pre->next = malloc(sizeof(ListNode));
		pre->next->item = value;
		pre->next->next = cur;
		ll->size++;
		return 0;
	}

	return -1;
}

int removeNode(LinkedList *ll, int index)
{
	ListNode *pre, *cur;

	// Highest index we can remove is size-1
	if (ll == NULL || index < 0 || index >= ll->size)
		return -1;

	// If removing first node, need to update head pointer
	if (index == 0){
		cur = ll->head->next;
		free(ll->head);
		ll->head = cur;
		ll->size--;

		return 0;
	}

	// Find the nodes before and after the target position
	// Free the target node and reconnect the links
	if ((pre = findNode(ll, index - 1)) != NULL){

		if (pre->next == NULL)
			return -1;

		cur = pre->next;
		pre->next = cur->next;
		free(cur);
		ll->size--;
		return 0;
	}

	return -1;
}
