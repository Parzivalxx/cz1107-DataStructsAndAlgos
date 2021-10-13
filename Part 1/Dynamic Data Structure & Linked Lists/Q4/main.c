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

    //Q3
    printf("\n");
    printf("Enter value to search for: ");
    scanf("%d", &n);
    int i = 0;
    p = head;
    while (p != NULL) {
        if ((p -> item) == n) {
            printf("Value %d found at index %d", n, i);
            break;
        };
        p = p -> next;
        i += 1;
    };
    if (p == NULL) {
        printf("Value %d not found, -1", n);
    }

    //Q4
//    THIS CODE COULD CRASH PROGRAM
//    ListNode *p = head;
//    while (p!= NULL) {
//        free(p);
//        p=p->next;
//    }

//    CORRECT WAY, INCLUDE TEMP POINTER
    ListNode *temp, *p = head;
    while (p!= NULL) {
        temp = p -> next;
        free(p);
        p = temp;
    };
    p = temp = head = NULL;

   //////////////////////////////////////////////////////////////////
}
