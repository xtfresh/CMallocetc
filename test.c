#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/* Here we are going to write some functions to support a linked list that stores Students (first name, last name)  */
/* Here is the data the user in this case us will be storing into our linked list */
/* YOU ARE REQUIRED TO COMPLETE THIS PART */
typedef struct Student
{
	const char* first_name;
	const char* last_name;
} Student;

/* Example functions given to you. Understand why these are written this way As you will be writing your own functions for part 2*/
Student* create_student(const char* first_name, const char* last_name)
{
	Student* s = malloc(sizeof(Student));
	s->first_name = first_name;
	s->last_name = last_name;
	return s;
}

void print_student(void* data)
{
	printf("%s %s\n", ((Student*)data)->first_name, ((Student*)data)->last_name);
}

void free_student(void* data)
{
	// free structure.
	free(data);
}

int pred_func(const void* data){
	if( strcmp( ((Student*)data)->first_name,"David") == 0)
		return 0;
	return 1;
}


/* This main function does a little testing
   Like all good CS Majors you are required to test
   your code here. There is no substitute for testing
   and you should be sure to test for all edge cases
   e.g., calling remove_front on an empty list.
*/
int main(void) 
{
	/* Now to make use of all of this stuff */
	list* llist = create_list();
	
/* 
  	
  	printf("TEST CASE 1\nAn Empty list should print nothing here:\n");
  	traverse(llist, print_student);
	printf("\n");

	
 	
 	push_front(llist, create_student("Nick", "Emmel"));
 	printf("TEST CASE 2\nA List with one student should print that student:\n");
 	traverse(llist, print_student);
 	printf("\n");
 	
 	
 	
 	remove_front(llist, free_student);
 	printf("TEST CASE 3\nAnother Empty list should print nothing here:\n");
 	traverse(llist, print_student);
 	printf("\n");

 	
 	push_front(llist, create_student("Scott", "Emmel"));
 	push_front(llist, create_student("David", "Johnson"));
 	printf("TEST CASE 4\nA List with two students should print those two students:\n");
 	traverse(llist, print_student);
 	printf("\n"); 	

  	
  	empty_list(llist, free_student);
 	printf("TEST CASE 5\nAfter freeing all nodes the list should be empty:\n");
 	traverse(llist, print_student);	
	printf("\n");
 	
 	
  	printf("TEST CASE 6\nAn Empty list should print nothing here:\n");
  	traverse(llist, print_student);
	printf("\n");

	
 
 	push_back(llist, create_student("Nick", "Emmel"));
 	printf("TEST CASE 7\nA List with one student should print that student:\n");
 	traverse(llist, print_student);
 	printf("\n");
 	
 	

 	remove_front(llist, free_student);
 	printf("TEST CASE 8\nAnother Empty list should print nothing here:\n");
 	traverse(llist, print_student);
 	printf("\n");
 	if(is_empty(llist)){
 		printf("EMPTY LIST!\n");
 	}	

	
 	
 	push_back(llist, create_student("Scott", "Emmel"));
 	push_back(llist, create_student("David", "Johnson"));
 	printf("TEST CASE 9\nA List with two students should print those two students:\n");
 	traverse(llist, print_student);
 	printf("\n"); 	

  	
  	empty_list(llist, free_student);
 	printf("TEST CASE 10\nAfter freeing all nodes the list should be empty:\n");
 	traverse(llist, print_student);	
	printf("\n");
	

  	printf("TEST CASE 11\nAn Empty list should print nothing here:\n");
  	traverse(llist, print_student);
	printf("\n");

	
 	
 	push_back(llist, create_student("Nick", "Emmel"));
 	printf("TEST CASE 12\nA List with one student should print that student:\n");
 	traverse(llist, print_student);
 	printf("\n");
 	
 	
 	
 	remove_back(llist, free_student);
 	printf("TEST CASE 13\nAnother Empty list should print nothing here:\n");
 	traverse(llist, print_student);
 	printf("\n");

 	
 	push_back(llist, create_student("Scott", "Emmel"));
 	push_back(llist, create_student("David", "Johnson"));
 	printf("TEST CASE 14\nA List with two students should print those two students:\n");
 	traverse(llist, print_student);
 	printf("\n"); 	

  
  	empty_list(llist, free_student);
 	printf("TEST CASE 15\nAfter freeing all nodes the list should be empty:\n");
 	traverse(llist, print_student);	
	printf("\n");
	
	
	remove_back(llist, free_student);
 	printf("TEST CASE 16\nAnother Empty list should print nothing here:\n");
 	traverse(llist, print_student);
 	printf("\n");
*/ 	
 	/* Lets add two elements and then print */
 	push_back(llist, create_student("Scott", "Emmel"));
 	push_back(llist, create_student("David", "Johnson"));
 	push_front(llist, create_student("Tom", "Johnson"));
 	printf("TEST CASE 17\nA List with 3 students should print those two students:\n");
 	traverse(llist, print_student);
 	
 	printf("\n"); 
 	
 	
 	remove_if(llist, pred_func, free_student);
 	printf("TEST CASE 18\nremove if name is David:\n");
 	traverse(llist, print_student);
 	printf("\n"); 
 	
 	remove_if(llist, pred_func, free_student);
 	printf("TEST CASE 18\nremove if name is Tom:\n"); //have to update pred_func for this to Tom
 	traverse(llist, print_student);
 	printf("\n"); 
 	
 	empty_list(llist, free_student);
 	
 	
 	
 	
	
 	/* Testing over clean up*/
 	
 	free(llist);
 	
  	return 0;
}
