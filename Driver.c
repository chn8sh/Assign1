/**
 * @file List.h
 * reads in a file and performs actions based on user input
 *
 * @author Christopher Nostrand, Patrick Gildea, Brooks Beverstock
 * @date 06 February 2011	(created)
 *		 08 February 2011	(last updated)		Modified by: Christopher Nostrand
 */
#include "List.h"
//#include <string.h>

// prototypes
int compareTo(const void *this, const void *other);
void echo(FILE *fp);
void sort(FILE *fp, List *l);

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
	List *list = NULL;
	list_init(list, compareTo, NULL); // TODO provide delete function

	// checks for correct # of arguments
	if(argc != 3)
	{
		printf("Invalid number of arguments: %d\n", argc-1);
		exit(0);
	}

	// open file: 1st argument
	FILE *fp = fopen(argv[1], "r");
	if(ferror(fp))
	{
		printf("Cannot open file: %s \n", argv[1]);
		exit(0);
	}

	// determine operation: 2nd argument
	if( strcmp(argv[2], options[0]) == 0 ) // argv[2] == "echo"
		echo(fp);
	else if( strcmp(argv[2], options[1]) == 0 ) // argv[2] == "sort"
		sort(fp, list);
	else if( strcmp(argv[2], options[2]) == 0 ) // argv[2] == "tail"
		printf("does something\n"); // call function to print words
	else if( strcmp(argv[2], options[3]) == 0 ) // argv[2] == "tail-remove"
		printf("does something\n"); // do something
	else // 2nd argument is invalid
	{
		printf("Invalid input argument: %s \n", argv[2]);
		exit(0);
	}

	fclose(fp);
	return 0;
}

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
 * @method echo
 * reads all characters from a file (ignoring white-spaces) and prints each word on a separate line
 *
 * @param fp	pointer to position in the specified file
 * @pre  fp points to a valid file in memory
 * @post the contents of the file is displayed
 */
void echo(FILE *fp)
{
	char str[256];
	int check;
	check = fscanf(fp, "%s", str);
	while(check != EOF)
	{
		printf("%s \n", str);
		check = fscanf(fp, "%s", str);
	}
}

void sort(FILE *fp, List *l)
{
	char str[256];
	int check;
	check = fscanf(fp, "%s", str);
	while(check != EOF)
	{
		list_insert_sorted(l, str);
		check = fscanf(fp, "%s", str);
	}
}

void tail(FILE *fp, List *l)
{
	char str[256];
	int check;
	check = fscanf(fp, "%s", str);
	while(check != EOF)
	{
		list_insert_tail(l, str);// TDDO l is still NULL :(
		check = fscanf(fp, "%s", str);
	}
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

