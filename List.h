/**
 * @file List.h
 * stores List class
 *
 * @author Christopher Nostrand, Patrick Gildea, Brooks Beverstock
 * @date 06 February 2011	(created)
 *		 08 February 2011	(last updated)		Modified by: Christopher Nostrand
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
 *		void list_visit_items(List *l, void (*visitor)(void *v))
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
typedef struct node {
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
 *		int (*compare)(const void *this, const void *other) function pointer to a compare method
 *			for comparing data values
 *		void (*datum_delete)(void *) function pointer to a delete function for deleting nodes or the list
 */
typedef struct {
	Node *head, *tail;
	unsigned length;
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
void list_init(List *l, int(*compare)(const void *this, const void *other),
		void(*datum_delete)(void *datum)) {

	l = (List *) malloc(sizeof(List));
	l->head = l->tail = NULL;
	l->length = 0;
	l->compare = compare;
	l->datum_delete = datum_delete;
}

//Part 3: Patrick
/**
 * @method list_visit_items
 * method_description
 *
 * @param args	command line parameters
 * @pre  description
 * @post description
 */
void list_visit_items(List *l, void(*visitor)(void *v)) {

}

//Part 4: Patrick
/**
 * @method list_insert_tail
 * method_description
 *
 * @param args	command line parameters
 * @pre  description
 * @post description
 */
void list_insert_tail(List *l, void *v) {
	// initialize variables
	Node new, *probe;
	new.datum = v;

	if (l != NULL) {
		// insert new
		if (l->length == 0) // first item in the list

		{
			l->head = l->tail = &new;
			new.prev = new.next = NULL;
		} else // length > 1; 3 cases
		{
			// locate position to insert
			for (probe = l->head; probe != NULL; probe = probe->next)
				if (l->compare(new.datum, probe->datum) <= 0)
					break;
			// determine case
			if (probe == l->head) // case 1: new belongs before first Node
			{
				new.prev = NULL;
				new.next = probe;
				probe->prev = l->head = &new;
			} else if (probe == NULL) // case 2: ran off list
			{
				new.prev = l->tail;
				new.next = NULL;
				l->tail->next = l->tail = &new;
			} else // case 3: somewhere in the middle of the list
			{
				new.prev = probe->prev;
				new.next = probe;
				probe->prev->next = probe->prev = &new;
			}
		}
		l->length++; // increase size
	}
}

//Part 5: Chris
/**
 * @method list_insert_sorted
 * inserts data into the list in sorted (ascending) order
 *
 * @param l		list
 * 		  v		datum to be stored
 * @pre  list points to a initialized list and v point to a vaild datum
 * @post v is inserted into l
 */
void list_insert_sorted(List *l, void *v) {
	// initialize variables
	Node new, *probe;
	new.datum = v;

	// insert new
	if (l->length == 0) // first item in the list
	{
		l->head = l->tail = &new;
		new.prev = new.next = NULL;
	} else // length > 1; 3 cases
	{
		// locate position to insert
		for (probe = l->head; probe != NULL; probe = probe->next)
			if (l->compare(new.datum, probe->datum) <= 0)
				break;
		// determine case
		if (probe == l->head) // case 1: new belongs before first Node
		{
			new.prev = NULL;
			new.next = probe;
			probe->prev = l->head = &new;
		} else if (probe == NULL) // case 2: ran off list
		{
			new.prev = l->tail;
			new.next = NULL;
			l->tail->next = l->tail = &new;
		} else // case 3: somewhere in the middle of the list
		{
			new.prev = probe->prev;
			new.next = probe;
			probe->prev->next = probe->prev = &new;
		}
	}
	l->length++; // increase size

}

//Part 6: Brooks
/**
 * @method list_remove_head
 * method_description
 *
 * @param args	command line parameters
 * @pre  description
 * @post description
 */
void list_remove_head(List *list) {

}

#endif /* LIST_H_ */
