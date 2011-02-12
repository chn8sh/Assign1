/**
 * @file List.h
 * reads in a file and performs actions based on user input
 *
 * @author Christopher Nostrand, Patrick Gildea, Brooks Beverstock
 * @date 06 February 2011	(created)
 *		 11 February 2011	(last updated)		Modified by: Christopher Nostrand
 */
#include "List.h"

// prototypes
// --File I/O
int getLine(FILE *fp, char *line, char c);
// --options
void echo(FILE *fp);
void list_insert_line(FILE *fp, List *l, void(*list_insert)(List *l, void *v));
void delete_list(List *l);
// --function pointers
int compareTo(const void *this, const void *other);
void delete(void *v);
void print(void *v);

/**
 * @method main
 * takes two arguments from the command line--a file name and a string.  Opening the file, it performs one of four options
 * given by the 2nd argument
 * - "echo"			displays the contents of the file without white-spaces, one word per line
 * - "sort"			inserts input into a list in sorted order and displays its contents
 * - "tail"			inserts input into back of a list and displays the contents
 * - "tail-remove"	inserts input into a list and continuously removes the first 3 items from the list until empty
 * Error checking is provided
 *
 * @param argc	number of arguments (first argument is name of executable)
 * 		  argv	pointer to arguments (command line parameters)
 * @pre  description
 * @post description
 * @return exit status '0' (normal exit)
 */
int main(int argc, char **argv)
{
	// initialize variables
	// TODO rewrite error messages to standerd error
	char *options[] = {"echo", "sort", "tail", "tail-remove"};
	List list;
	list_init(&list, compareTo, delete); // TODO provide delete function

	// checks for correct # of arguments
	if(argc != 3)
	{
		fprintf(stderr, "Invalid number of arguments: %d\n", argc-1);
		exit(1);
	}

	// open file: 1st argument
	FILE *fp = fopen(argv[1], "r");
	if(ferror(fp))
	{
		fprintf(stderr, "Cannot open file: %s\n", argv[1]);
		exit(1);
	}

	// determine operation: 2nd argument
	if( strcmp(argv[2], options[0]) == 0 ) { // argv[2] == "echo"
		echo(fp);
	} else if( strcmp(argv[2], options[1]) == 0 ) { // argv[2] == "sort"
		list_insert_line(fp, &list, list_insert_sorted);
		list_visit_items(&list, print);
	} else if( strcmp(argv[2], options[2]) == 0 ) { // argv[2] == "tail"
		list_insert_line(fp, &list, list_insert_tail);
		list_visit_items(&list, print);
	}
	else if( strcmp(argv[2], options[3]) == 0 ) { // argv[2] == "tail-remove"
		list_insert_line(fp, &list, list_insert_tail);
		delete_list(&list);
	}
	else { // 2nd argument is invalid
		fprintf(stderr, "Invalid input argument: %s\n", argv[2]);
		exit(1);
	}

	fclose(fp);
	return 0;
}

// --File I/O functions

/**
 * @method main
 * method_description
 *
 * @param args	command line parameters
 * @pre  description
 * @post description
 * @return description
 */
int getLine(FILE *fp, char *line, char c)
{
	int length = 0;
	while(c != '\n') {
		line[length++] = c;
		c = fgetc(fp);
	}
	line[length++] = c;
	line[length] = '\0';
	return length;
}

// option functions

/** TODO update header
 * @method echo
 * reads all characters from a string (ignoring white-spaces) and prints each word on a separate line
 *
 * @param line	pointer to a string
 * @pre  line points to a valid string in memory
 * @post the contents of the string is displayed
 */
void echo(FILE *fp)
{
	char str[256];
	int check = fscanf(fp, "%s", str);
	while(check != EOF)
	{
		printf("%s\n", str);
		check = fscanf(fp, "%s", str);
	}
}

/**  TODO update header
 * @method main
 * method_description
 *
 * @param args	command line parameters
 * @pre  description
 * @post description
 * @return description
 */
void list_insert_line(FILE *fp, List *l,
					  void(*list_insert)(List *l, void *v))
{
	char line[1000], c = fgetc(fp);
	int length = 0;
	while(c != EOF)
	{
		length = getLine(fp, line, c); // retrieve line
		//printf("%d %s", length, line);

		if(length > 1) // skip empty lines
		{
			char *datum = malloc(length);
			memcpy(datum, line, length);
			//printf("%d %s", length, datum);
			list_insert(l, datum);
		}
		length = 0;
		c = fgetc(fp);
	}
}


/**  TODO update header
 * @method main
 * method_description
 *
 * @param args	command line parameters
 * @pre  description
 * @post description
 * @return description
 */
void delete_list(List *l)
{
	int done = 0;
	int x;
	do {
		for(x = 0; x < 3; x++) {
			if(l->length == 0) {
				done = 1;
				break;
			} else {
				list_remove_head(l);
			}
		}
		list_visit_items(l, print);
		printf("-------------------------\n");
	} while(!done);
	list_visit_items(l, print);
}

// function pointers

/**
 * @method compareTo
 * compare method for list that compares two strings and returns the result
 *
 * @param this	current string
 * 		  other	string in comparison against
 * @pre  this and other point to a valid string in memory
 * @post strings are compared
 * @return an int: [-1] - this < other; [0] - this = other; [1] - this > other
 */
int compareTo(const void *this, const void *other)
{
	const char *str1 = this, *str2 = other;
	return strcmp(str1, str2);
}

/**
 * @method main
 * method_description
 *
 * @param args	command line parameters
 * @pre  description
 * @post description
 * @return description
 */
void delete(void *v)
{
	char *str = v;
	free(str);
}

/**
 * @method print
 * prints the value to standard out
 *
 * @param v		pointer to a string
 * @pre  v is a valid pointer to a string in memory
 * @post a string is displayed
 */
void print(void *v)
{
	char *str = v;
	printf("%s", str);
}




// method header
/**
 * @method main
 * method_description
 *
 * @param args	command line parameters
 * @pre  description
 * @post description
 * @return description
 */

