////////////////////////////////////////////////////////////


//#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>

////////////////////////////////////////////////////////////

typedef struct _listnode{
	int item;
	struct _listnode *next;
} ListNode;


void main()
{
	ListNode *head, *p, *temp;
	int n;


	head=NULL;
	p=NULL;		// pointing to the last node in the list
	printf("Enter a list of numbers, terminated by the value -1:\n");

	/////////////////////////////////////////////////////////////////

	//Question 2
    //Write your program code here

    scanf("%d", &n);
    while (n != -1) {
        if (head == NULL) {
            head = malloc(sizeof(ListNode));
            temp = head;
        }
        else {
            temp -> next = malloc(sizeof(ListNode));
            temp = temp -> next;
        };
        temp -> item = n;
        scanf("%d", &n);
    };
    temp -> next = NULL;
    p = head;
    printf("Current list: ");
    while (p != NULL) {
        printf("%d ", p -> item);
        p = p -> next;
    };
   //////////////////////////////////////////////////////////////////
}
