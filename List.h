/**
 * @file List.h
 * stores List class
 *
 * @author Christopher Nostrand
 * @date 06 February 2011	(created)
 *		 06 February 2011	(last updated)		Modified by: Christopher Nostrand
 *		 08 February 2011	(last updated)		Modified by: Patrick Gildea
 */
#ifndef LIST_H_
#define LIST_H_

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
	l->head = l->tail = '\0'; // NULL value
	l->length = 0;
	l->compare = compare;
	l->datum_delete = datum_delete;
}

//Part 3: Patrick
/**
 * @method list_visit_items
 * This method prints each item in the linked list
 *
 * @param l		list
 * @param v    	datum to be stored
 * @pre  list points to a initialized list and v point to a vaild datum
 * @post v is inserted into l
 */
//takes a pointer to a function, visitor, and calls it on each member of l in order from
	//l->head to l->tail. You will need to use this to print your list.

void list_visit_items(List *l, void(*visitor)(void *v)) {
	//variable to hold the current node
	struct Node* current = l->head;

	//iterate through the list until the last item in the list
	//is reached which has a NULL tail pointer
	while(current != NULL){
		//print the datum as a string
		//printf("%s",current->datum);

		//calls on the function in v
		visitor(current->datum);

		//move to the next node
		current = current->next;
	}
}

//Part 4: Patrick
/**
 * @method list_insert_tail
 * Inserts an element into the list (at the beginning) and prints the contents of the list.
 *
 * @param l		The list
 * @param v		datum to be stored
 * @pre  list points to a initialized list and v point to a valid datum
 * @post v is inserted into l
 */
//to insert the input, line by line, when the second parameter is �tail�, and print the
	//contents of the list, one member per line before exiting

void list_insert_tail(List *l, void *v) {

	//variable to hold the tail node
	struct node* TheHead = l->tail;

	struct node* newNode;		//Create the new node

	//Check to make sure that memory is free, if not send error msg to std output
	if(newNode= malloc(sizeof(struct node)) != NULL){  // allocate memory
		newNode->datum = *v;		//initialize the datum
		newNode->next = NULL;		//set the next pointer for the new node to NULL
		newNode->prev = TheHead;	//set the prev pointer for the new node to the old tail node

		l->tail = newNode;			//set the tail node to the new node
	}
	else{
		//print error message on the std output line
		fprintf(stderr,"There is no more memory - cannot insert a new node");
		exit(1);
	}






/*	This is the code to add to the top (head) of the list

	//variable to hold the head node
	struct node* head = l->head;
	struct node* newNode;	//the new node
	newNode= malloc(sizeof(struct node)); // allocate memory
	newNode->datum = *v;	//initialize the datum
	newNode->next = head; 	// link next
	head = newNode; 		// link head
	// now head points to the list
*/

}

//Part 5: Chris
/**
 * @method list_insert_sorted
 * method_description
 *
 * @param args	command line parameters
 * @pre  description
 * @post description
 */
void list_insert_sorted(List *l, void *v) {
	// initialize variables
		Node new, *probe;

		new->datum = v;

		// insert new
		if (l->length == 0) // first item in the list
		{
			l->head = l->tail = new;
			new->prev = new->next = '\0';
		}

		else // length > 1; 3 cases
		{
			// locate position to insert
			for (probe = l->head; probe != '\0'; probe = probe->next)
				if (l->compare(new->datum, probe->datum) <= 0)
					break;
			// determine case
			if (probe == l->head) // case 1: new belongs before first Node
			{
				new->prev = '\0';
				new->next = probe;
				probe->prev = l->head = new;
			}

			else if (probe == '\0') // case 2: ran off list
			{
				new->prev = l->tail;
				new->next = '\0';
				l->tail->next = l->tail = new;
			}
			else // case 3: somewhere in the middle of the list
			{
				new->prev = probe->prev;
				new->next = probe;
				probe->prev->next = probe->prev = new;
			}
		}
		length++; // increase size
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
