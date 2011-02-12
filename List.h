/**
 * @file List.h
 * stores List class
 *
 * @author Christopher Nostrand, Patrick Gildea, Brooks Beverstock
 * @date 06 February 2011	(created)
 *		 11 February 2011	(last updated)		Modified by: Christopher Nostrand
 */
#ifndef LIST_H_
#define LIST_H_
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


/**
 * @class List
 * This C style class (a struct) implements a two doubly-linked list with nodes to hold data
 *
 *		void list_init(List *l, int (*compare)(const void *this, const void *other),
 *			void (*datum_delete)(void *datum)) constructor
 *		void list_visit_items(List *l, void (*visitor)(void *v)) constructor
 *		void list_insert_tail(List *l, void *v)
 *		void list_insert_sorted(List *l, void *v)
 *		void list_remove_head(List *list)
 */

// structs

/**
 * @struct Node
 * holds a datum in the linked list
 *
 *		struct node *prev - pointer to previous node in the list
 *		struct node *next - pointer to next node in the list
 *		void *datum		  - pointer to value in the Node (can be anything)
 */
typedef struct node
{
	struct node *prev, *next;
	void *datum;
} Node;

/**
 * @struct List
 * definition of the doubly-linked list
 *
 *		Node *head		- pointer to the front of the list
 *		Node *tail		- pointer to the back of the list
 *		unsigned lenght	- size of the list
 *		int *compare	- function pointer to a compare method for comparing data values
 *		void *datum_delete - function pointer to a delete function for deleting nodes or the list
 */
typedef struct
{
	Node *head, *tail;
	unsigned int length;
	int (*compare)(const void *this, const void *other);
	void (*datum_delete)(void *);
} List;

// List methods

/**
 * @method list_init
 * constructor
 *
 * @param l				pointer to list
 * 		  compare		function pointer to comparison function
 * 		  datum_delete	function pointer to Node deletion function
 * @pre  each pointer belongs to a valid place in memory
 * @post data fields are initialized
 */
void list_init(List *l,
			   int (*compare)(const void *this, const void *other),
			   void (*datum_delete)(void *datum))
{
	l->head = l->tail = NULL;
	l->length = 0;
	l->compare = compare;
	l->datum_delete = datum_delete;
}

/**
 * @method list_visit_items
 * This method calls a function each item in list
 *
 * @param l		list
 *		  v		datum to be stored
 * @pre list points to a initialized list and v point to a vaild datum
 * @post operation completed
 */
void list_visit_items(List *l, void(*visitor)(void *v))
{
	//variable to hold the current node
	Node* current = l->head;

	//iterate through the list until the last item in the list
	//is reached which has a NULL tail pointer
	while(current != NULL)
	{
		//print the datum as a string
		//printf("%s",current->datum);

		//calls on the function in v
		visitor(current->datum);

		//move to the next node
		current = current->next;
	}
}

/**
 * @method list_insert_tail
 * Inserts an element into the list (at the beginning) and prints the contents of the list.
 *
 * @param l The list
 * @param v datum to be stored
 * @pre list points to a initialized list and v point to a valid datum
 * @post v is inserted into l
 */
void list_insert_tail(List *l, void *v)
{
	// variable to hold the tail node
	Node *newNode = malloc( sizeof(Node) ); // create the new node

	// check to make sure that memory is free, if not send error msg to std output
	if(newNode == NULL) { // print error message on the std output line
		fprintf(stderr, "There is no more memory - cannot insert a new node");
		exit(1);
	}

	newNode->datum = v; // initialize the datum

	if(l->length == 0) // first item in the list
	{
		l->head = l->tail = newNode;
		newNode->prev = newNode->next = NULL;
	}
	else
	{
		newNode->next = NULL; // set the next pointer for the new node to NULL
		newNode->prev = l->tail; // set the prev pointer for the new node to the old tail node
		l->tail->next = newNode; //set the tail node to the new node
		l->tail = newNode;
	}
	l->length++;
}

/**
 * @method list_insert_sorted
 * inserts data into the list in sorted (ascending) order
 *
 * @param l		list
 * 		  v		datum to be stored
 * @pre  list points to a initialized list and v point to a vaild datum
 * @post v is inserted into l
 */
void list_insert_sorted(List *l, void *v)
{
	// initialize variables
	Node *new = malloc( sizeof(Node) ), *probe;
	if(new == NULL) {
		fprintf(stderr, "There is no more memory - cannot insert a new node");
		exit(1);
	}
	new->datum = v;

	// insert new
	if(l->length == 0) // first item in the list
	{
		l->head = l->tail = new;
		new->prev = new->next = NULL;
	}
	else // length > 1; 3 cases
	{
		// locate position to insert
		for(probe = l->head; probe != NULL; probe = probe->next)
			if( l->compare(new->datum, probe->datum) <= 0 )
				break;

		// determine case
		if(probe == l->head) // case 1: new belongs before first Node
		{
			new->prev = NULL;
			new->next = probe;
			probe->prev = l->head = new;
		}
		else if(probe == NULL) // case 2: ran off list
		{
			new->prev = l->tail;
			new->next = NULL;
			l->tail->next = l->tail = new;
		}
		else // case 3: somewhere in the middle of the list
		{
			new->prev = probe->prev;
			new->next = probe;
			probe->prev->next = probe->prev = new;
		}
	}
	l->length++; // increase size
}

/**
 * @method list_remove_head
 * removes a Node and its data from the front of the list
 *
 * @param list	pointer to a list
 * @pre  list must point to a valid List in memory
 * @post first Node in the list is deleted
 */
void list_remove_head(List *list)
{
	Node *temp = list->head;
	list->head = list->head->next;
	list->datum_delete(temp->datum);
	temp->prev = temp->next = NULL;
	free(temp);
}

#endif /* LIST_H_ */
