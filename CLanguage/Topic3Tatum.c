/*
 ============================================================================
 Name        :
 Author      : Lindy Tatum
 Version     : 1.0
 Copyright   : Your copyright notice
 Description : This program will manage the records for students of Regis University
 	 	 	   by creating new records and displaying the list of the current records
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define NAME_SIZE 50
#define GRADE 6
#define MAJOR 20

// new_Record Creates a new student record
 typedef struct newRecord {

//Variables with size
 char student_name[NAME_SIZE];
 int idNum;
 char average_Grade[GRADE];
 char major [MAJOR];

//Points to next node in list
 struct newRecord* next;

 } newRecord_Student;

 // Declares Function
 void newStudent (newRecord_Student**);
 void displayRecords(newRecord_Student*);

 int main(void) {

	 //Declares pointer and initializes it
	 newRecord_Student* top = NULL;

	 //User input
	 int answer;



	do {
		printf("Welcome to RU Record Management System\n");
		printf("Press\n");
		printf(" 1 to create a new Student Record\n");
		printf(" 2 to view all records\n");
		printf(" 3 to Exit\n");

		printf(" Enter your Choice\n ");
		scanf("%d", &answer);

		//Flushes memory
		fflush (stdin);

		switch (answer){
		case 1:
			newStudent(&top);
			break;
		case 2:
			displayRecords(top);
			break;
		case 3:
			printf("Exit\n");
			break;
		default:
			printf("Invalid, try again\n");
			break;
		}

	}while (answer != 3);

	//Pointer declaration
	newRecord_Student* temp;

	//Loop that contains the pointer of the top node to be the next node
	while(top != NULL){
		temp = top;
		top = top->next;

		//Free memory for current node
		free(temp);
	}
	return 0;

 }

/* Inputs new record and saves in system */
void newStudent (newRecord_Student** top){

	// Initialize/ declares Top list pointer and allocates memory
	newRecord_Student *createRecord = (newRecord_Student*)malloc(sizeof(newRecord_Student));

	bool recordEmpty = false;

	if (createRecord == NULL){
		printf("Error\n");
		recordEmpty = true;
	}

		printf ("\nEnter Name: ");
		scanf ("%s",createRecord->student_name );
		fflush (stdin);

		printf ("Enter Id number: ");
		scanf ("%d",&createRecord->idNum);
		fflush (stdin);

		//Checks for duplicate
		newRecord_Student* temp = *top;
		bool duplicate = false;

		while (temp != NULL){
			if (temp->idNum == createRecord->idNum){
				printf("Error:  ID already exists\n");
				duplicate = true;
			}
			temp = temp ->next;
		}
	if (!duplicate){
		printf ("Enter average grade of Student: ");
		scanf ("%s",createRecord->average_Grade );
		fflush (stdin);
		printf ("Enter major of Student: ");
		scanf ("%s",createRecord->major);
		fflush (stdin);

	//Add to link list
	createRecord->next = *top;
	*top = createRecord;

}else{
	free(createRecord);
}
}

/* displayRecords displays all records*/
void displayRecords(newRecord_Student* top){
	newRecord_Student* current = top;

	while(current != NULL){
		printf ("Name: %s; Id: %d; Major: %s; Average Grade: %s\n",
		current->student_name , current->idNum, current->average_Grade, current->major);
		current = current-> next;
}
}

