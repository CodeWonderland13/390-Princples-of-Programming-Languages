//============================================================================
// Name        : Topic4Tatum.cpp
// Author      : Lindy Tatum
// Version     : Version 1.0
// Copyright   : Your copyright notice
// Description : Program that keeps creates, displays and keeps record
//               of new student and new student
//============================================================================

#include <iostream>
#include <string>
using namespace std;


class Person {

	private:
		string name;
		int id;

	public:
		//Constructor
		Person(string name, int id) : name(name), id(id){}

		 int getID() const{return id;}
		 string getName() const {return name;}

		 //Virtual Deconstructor 
		 virtual void printAbout() const = 0;
		 virtual ~Person() {}

};
//Node structure for linked list
struct Node {
	Node* prev;
	Node* next;
    Person* person;

//Contructor
Node(Person* person): person(person), next(nullptr),prev(nullptr){}

};

class Student : public Person{
	private:
		string average_Grade;
		string major;

	public:
		Student(string name, int id, string grade, string major)
		: Person(name, id), average_Grade(grade), major(major){}

		void printAbout() const override {
			cout << "Name: " << getName() << "; Id: " << getID()
			<< "; Major: " << major << " ; Average Grade: "
			<< average_Grade << endl;
		}
};

class Teacher : public Person{
		private:
			string title;
			string department;

		public:
			Teacher(string name, int id, string title, string department)
			: Person(name, id), title (title), department(department){}

			void printAbout() const override {
				cout << "Name: " << getName() << "; Id: " << getID()
				 << "Title: " << title<< "; Department: "
				 << department << endl;
			}
};


/* Inputs new record and saves in system */
void newStudent (Node** top){

	string name, grade, major;
	int id;

	cout <<("\nEnter Name: ");
	cin.ignore();
	getline(cin, name);

	cout << ("Enter Id number: ");
	cin >> id;
	cin.ignore();

	//Checks for duplicate
	Node* temp = *top;

	while (temp != nullptr){
		if (temp->person->getID() == id){
			cout <<("Error:  ID already exists\n");
			return;
			}
			temp = temp ->next;
		}

	cout <<("Enter average grade of Student: ");
	getline (cin, grade );

	cout << ("Enter major of Student: ");
	getline (cin, major );


	//Add to link list
	tudent* newStudent = new Student(name, id, grade, major);

	Node* newNode = new Node(newStudent);
	newNode->next = *top;

	if (*top!= nullptr){
		(*top)->prev = newNode;

}
	*top = newNode;
}

/* Inputs new record and saves in system */
void newTeacher(Node** top){

	string name, title, department;
	int id;
	int titleTeacher;

	cout <<("\nEnter Name: ");
	cin.ignore();
	getline(cin, name);

	cout << ("Enter Id number: ");
	cin >> id;
	cin.ignore();


	//Checks for duplicate
	Node* temp = *top;

	while (temp != nullptr){
		if (temp-> person-> getID() == id){
				cout <<("Error:  ID already exists\n");
				return;
			}
			temp = temp ->next;
		}

	cout <<("Enter title of Teacher: 1 if lecturer ; 2 if assistant professor ; 3 if associate professor");
	cin >> titleTeacher;


	cin.ignore();
	switch (titleTeacher){
		case 1:
			title = "lecturer";
			break;
		case 2:
			title = "assistant professor";
			break;
		case 3:
			title = "associate professor";
			break;
		default:
			cout <<("Invalid, try again\n");
			return;
				}

	cout << ("Enter teacher department: ");
	getline (cin, department );


	//Add to link list
	Teacher* newTeacher = new Teacher(name, id, title, department);

	Node* newNode = new Node(newTeacher);
	newNode->next = *top;

	if (*top!= nullptr){
		(*top)->prev = newNode;

}
	*top = newNode;
}

/* displayRecords displays all records*/
void displayRecords(Node* top){
	Node* current = top;

	while(current != nullptr){

		current-> person-> printAbout();

		current = current-> next;
}
}
int main() {


	//Declares pointer and initializes it
	    	 Node* top = nullptr;

	 //User input
	 int answer;

	do {
		cout << "Welcome to RU Record Management System\n";
		cout <<("Press\n");
		cout <<(" 1 to create a new Student Record\n");
		cout <<(" 2 to create a new teacher record\n");
		cout <<(" 3 to view all records\n");
		cout <<(" 4 to Exit\n");

		cout <<(" Enter your Choice\n ");
		cin >> (answer);



		switch (answer){
		case 1:
			newStudent(&top);
			break;
		case 2:
			newTeacher(&top);
			break;
		case 3:
			displayRecords(top);
			break;
		case 4:
			cout <<"Exit\n";
				break;
		default:
			cout <<"Invalid, try again\n";
			break;
		}

	}while (answer != 4);

	//Pointer declaration
	Node* temp;

	//Loop that contains the pointer of the top node to be the next node
	while(top != nullptr){
		temp = top;
		top = top->next;

		//Free memory for current node
		delete temp-> person;;
		delete temp;
	}
	return 0;

 }

