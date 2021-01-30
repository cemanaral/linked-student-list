/*
Cem Anaral 150119761
Purpose of this program is to leverage a student management system 
by using a custom made linked list data structure.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_LEN 30 // maximum length of name and surname


struct student {
	char name[MAX_LEN];
	char surname[MAX_LEN];
	long int ID;
	struct student *name_next; 
	struct student *surname_next; 
	struct student *ID_next;
};

struct student *name_head = NULL;
struct student *surname_head = NULL;
struct student *ID_head = NULL;

// function prototypes (only if needed)
void ID_insert(struct student *std);
void surname_insert(struct student *std);
void name_insert(struct student *std);
void insertNode(struct student *std);
////////////////////////////////

void print_student(struct student *std, int count) {
	// Prints values of a student struct
	printf("\t%d. %s %s\t%d\n", count, std->name, std->surname, std->ID);
}

void read_file(char *input) {
	/*
		Reads provided input file
	*/
	FILE *fp;
	char name[MAX_LEN], surname[MAX_LEN];
	long int ID;
	
	fp = fopen(input, "r");

	while ( fscanf(fp, "%s %s\t%d", name, surname, &ID) != EOF ) {
		// allocating memory and inserting data
		struct student *std = malloc(sizeof(struct student));
		if (std == NULL) {
			puts("Memory allocation failed!");
			exit(-1);
		}
		strcpy(std->name, name);
		strcpy(std->surname, surname);
		std->ID = ID;
		
		std->ID_next = NULL;
		std->name_next = NULL;
		std->surname_next = NULL;
		
		insertNode(std);
	}	
	fclose(fp);
}

void print_ID_head(void) {
	struct student *current;
	current = ID_head->ID_next;
	int count = 1;
	puts("The list in ID sorted order:");
	while (current->ID_next != NULL) {
		print_student(current, count++);
		current = current->ID_next;
	}
	print_student(current, count);
}

void print_name_head(void) {
	struct student *current;
	current = name_head->name_next;
	int count = 1;
	puts("The list in name-alphabetical order:");
	while (current->name_next != NULL) {
		print_student(current, count++);
		current = current->name_next;
	}
	print_student(current, count);
}

void print_surname_head(void) {
	struct student *current;
	current = surname_head->surname_next;
	int count = 1;
	puts("The list in surname-alphabetical order:");
	while (current->surname_next != NULL) {
		print_student(current, count++);
		current = current->surname_next;
	}
	print_student(current, count);
}

void ID_insert(struct student *std) {
	struct student *previousPtr = NULL;
	struct student *currentPtr = ID_head->ID_next;
	
	// loop to find the correct location in the list
	while (currentPtr != NULL && std->ID > currentPtr->ID) {
		previousPtr = currentPtr;
		currentPtr = currentPtr->ID_next;
	}
	
	// insert new node at the beginning
	if (previousPtr == NULL) {
		std->ID_next = ID_head->ID_next;
		ID_head->ID_next = std;
	}
	else { // insert new node between previousPtr and currentPtr
		previousPtr->ID_next = std;
		std->ID_next = currentPtr;
	}
}

void name_insert(struct student *std) {
	struct student *previousPtr = NULL;
	struct student *currentPtr = name_head->name_next;
	
	// loop to find the correct location in the list  strcmp(std->name, currentPtr->name);
	while (currentPtr != NULL && strcmp(std->name, currentPtr->name)>0) {  // Strcmp is to compare two strings
		previousPtr = currentPtr;
		currentPtr = currentPtr->name_next;
	}
	
	// insert new node at the beginning
	if (previousPtr == NULL) {
		std->name_next = name_head->name_next;
		name_head->name_next = std;
	}
	else {
		previousPtr->name_next = std;
		std->name_next = currentPtr;
	}
	
	
}

void surname_insert(struct student *std) {
	struct student *previousPtr = NULL;
	struct student *currentPtr = surname_head->surname_next;
	
	// loop to find the correct location in the list
	while (currentPtr != NULL && strcmp(std->surname, currentPtr->surname)>0) { // strcmp to compare alphabetically
		previousPtr = currentPtr;
		currentPtr = currentPtr->surname_next;
	}
	
	// insert new node at the beginning
	if (previousPtr == NULL) {
		std->surname_next = surname_head->surname_next;
		surname_head->surname_next = std;
	}
	else {
		previousPtr->surname_next = std;
		std->surname_next = currentPtr;
	}
	
}

void printList(void) {
	print_name_head();
	print_surname_head();
	print_ID_head();
}

void insertNode(struct student *std) {
	name_insert(std);
	surname_insert(std);
	ID_insert(std);
}

void print_instructions(void) {
	  puts("Enter your choice:\n"
      "   1 to insert a student into the list.\n"
      "   2 to delete a student from the list.\n"
      "   3 to print the students in the list.\n"
	  "   4 to print the students to an output file.\n"
	  "   5 to end.");
}

void write_out(char *filename){
	// writes student list to provided filename
	
	FILE *f = fopen(filename, "w");
	
	// Writing names
	struct student *std;
	std = name_head->name_next;
	int count = 1;
	fputs("The list in name-alphabetical order:\n", f);
	while (std->name_next != NULL) {
		fprintf(f, "\t%d. %s %s\t%d\n", count++, std->name, std->surname, std->ID);
		std = std->name_next;
	}
	fprintf(f, "\t%d. %s %s\t%d\n", count++, std->name, std->surname, std->ID);
	////////
	
	// Writing surnames
	std = surname_head->surname_next;
	count = 1;
	fputs("The list in surname-alphabetical order:\n", f);
	while (std->surname_next != NULL) {
		fprintf(f, "\t%d. %s %s\t%d\n", count++, std->name, std->surname, std->ID);
		std = std->surname_next;
	}
	fprintf(f, "\t%d. %s %s\t%d\n", count++, std->name, std->surname, std->ID);
	////////////////
	
	// Writing ID
	std = ID_head->ID_next;
	count = 1;
	fputs("The list in ID sorted order:\n", f);
	while (std->ID_next != NULL) {
		fprintf(f, "\t%d. %s %s\t%d\n", count++, std->name, std->surname, std->ID);
		std = std->ID_next;
	}
	fprintf(f, "\t%d. %s %s\t%d\n", count++, std->name, std->surname, std->ID);
	
	fclose(f);
	printf("Output is printed to the file %s\n", filename);
}

struct student* get_std(long int ID) {
	// finds student struct by ID and returns it.

	if (ID == ID_head->ID_next->ID) { // if it is first
		return ID_head->ID_next;
	}
	else {
		struct student *currentPtr = ID_head->ID_next->ID_next;
		
		while (currentPtr != NULL && currentPtr->ID != ID) {
			currentPtr = currentPtr->ID_next;
		}
		return currentPtr;
	}
}

void deleteNode(long int ID) {
	/*
	Deletes student from ID
	*/
	struct student* std = get_std(ID); // finds related memory location of student
	if (std == NULL) {		// If ID is invalid
		puts("Student could not be found!");
		return;
	}
	
	// disconnecting name_head
	if (name_head->name_next == std) {	// if it is the first item
		name_head->name_next = std->name_next;
	}
	else {
		struct student* previousPtr = name_head->name_next;
		while (previousPtr->name_next != std)  // looping to find previousPtr
			previousPtr = previousPtr->name_next;
		previousPtr->name_next = (previousPtr->name_next)->name_next;
	}
	////////////////////////

	// disconnecting surname_head
	if (surname_head->surname_next == std) {  // if it is the first one
		surname_head->surname_next = std->surname_next;
	}
	else {
		struct student *previousPtr = surname_head->surname_next;
		while (previousPtr->surname_next != std)
			previousPtr = previousPtr->surname_next;
		previousPtr->surname_next = (previousPtr->surname_next)->surname_next;
	}
	////////////////////////
	
	// disconnecting ID_head
	if (ID_head->ID_next == std) {
		ID_head->ID_next = std->ID_next;
	}
	else {
		struct student *previousPtr = ID_head->ID_next;
		while (previousPtr->ID_next != std)
			previousPtr = previousPtr->ID_next;
		previousPtr->ID_next = (previousPtr->ID_next)->ID_next;
	}
	///////////////////////
	
	// printing student info
	printf("The student \"%s %s\t%d\" is deleted from the list!\n", std->name, std->surname, std->ID);
	
	// finally, freeing memory
	free(std);
}

int main(int argc, char *argv[]) {
	// Please note that there is *not* 3 separate linked lists, I'm having a problem with double pointers that is why I initialized it like this
	// What I mean above is that there exists only 1 memory location for each student, but 3 head pointers in struct student type exists.
	ID_head = malloc(sizeof(struct student));
	ID_head->ID_next = NULL;
	
	name_head = malloc(sizeof(struct student));
	name_head->name_next = NULL;
	
	surname_head = malloc(sizeof(struct student));
	surname_head->surname_next = NULL;
	////////////////////////////////////////////////////7
	
	read_file(argv[1]);

	printList();
	print_instructions();	
	printf("%s", "? ");
	unsigned int choice; // user's choice
	scanf("%u", &choice);
	
	// loop until user types 5
	while (choice != 5) {
		
		// to prevent label errors
			// for case 1
			char name[MAX_LEN];
			char surname[MAX_LEN];
			long int ID; //also for case 2
			// for case 4
			char filename[MAX_LEN];
		//////////////////////////
		switch(choice) {
			case 1:	// insert student
				puts("Enter a student name, suname, and ID:");
				scanf("%s %s %d", name, surname, &ID);
				struct student *std = malloc(sizeof(struct student));
				strcpy(std->name, name);
				strcpy(std->surname, surname);
				std->ID = ID;
				
				std->name_next = NULL;
				std->surname_next = NULL;
				std->ID_next = NULL;
				insertNode(std);
				break;
			case 2:	// delete student by ID
				puts("Enter a student ID:");
				scanf("%d", &ID);
				deleteNode(ID);
				break;
			case 3:	// print student list
				printList();
				break;
			case 4: // write output to a txt file
				puts("Enter a file name:");
				scanf("%s", filename);
				write_out(filename);
				break;
			default:
				puts("Invalid choice.");
				break;
		}
		print_instructions();
		printf("%s", "? ");
		scanf("%u", &choice);
	}
	return 0;
}
