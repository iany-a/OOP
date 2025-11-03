#include <iostream>
#include <string>
using namespace std;

//classes and constructors
//memory-leak
//constants and statics
//destructor
//copy-constructor

enum class StudentType {
	ERASMUS,
	INTERNAL
};

class Student {
	const int id = 0;
	string name = "";
	int* grades = nullptr;
	int noGrades = 0;
	StudentType type = StudentType::INTERNAL;
	bool hasScholarship = false;
public:
	//For constraints (min/max values), we need to setup static fields
	static int MIN_NUMBER_CHARS; //DEFINE THE STATIC FIELD INSIDE THE CLASS, OUTSIDE ANY CLASS FUNCTION
	static int MAX_GRADE;
	static int MIN_GRADE;
	void setName(string name) {
		if (name.size() < Student::MIN_NUMBER_CHARS) throw "Name invalid: should be longer then 5 characters"; //never use magic numbers
		this->name = name;
		
	}

	void addGrade(int value) {
		if (value < Student::MIN_GRADE || value>Student::MAX_GRADE) {
			throw "Invalid grade.";
		}

		//you can't add a new value in the existing array
		//step 1: create an array with size+1
		int* newGrades = new int[this->noGrades + 1];
		//step 2: copy existing values
		for (int i = 0; i < this->noGrades; i++) {
			newGrades[i] = this->grades[i];
		}
		//step 3: add the new value
		newGrades[this->noGrades] = value;
		noGrades++; //increment the noGrades size after adding the new grade
		
		//step 4: delete used heap memory
		delete[] this->grades;
		//step 5: keep the new array
		this->grades = newGrades; //newGrades is just a temporary pointer, it does not need to be deleted as it will be
		//automatically deleted on function exit. The heap memory was already cleared before passing the new address to this->grades.
		//there is nothing else remaining to be cleared from heap memory at this step.


	}

	void print() {
		cout << endl << "Name: " << this->name;
		cout << endl << "Number of grades: " << this->noGrades;
		switch (this->type) {
		case StudentType::INTERNAL:
			cout << endl << "Type: Internal";
			break;
		case StudentType::ERASMUS:
			cout << endl << "Type: Erasmus";
			break;
		default:
			cout << endl << "Type: N/A";
		}
		if (this->hasScholarship) cout << endl << "Has scholarship.";
		else cout << endl << "Does not have scolarship";

		cout << endl << "Grades: ";
		if (this->grades == nullptr) {
			cout << endl << "No grades for this student.";
		}
		else {
			for (int i = 0; i < noGrades; i++) {
				cout << endl << this->grades[i];
			}
		}


	}

	void setGrades(int* values, int noValues) {

		//do you need the previous values in HEAP?
		//NO -> delete them
		delete[] this->grades; //[] is used for array deletion
		this->grades = new int[noValues];
		for (int i = 0; i < noValues; i++) {
			if (values[i]<MIN_GRADE || values[i]>MAX_GRADE) {
				throw "Invalid grade";
			}
			this->grades[i] = values[i];
		}
		this->noGrades = noValues;
	}

	Student(string name, int* grades, int noGrades) {
		this->setName(name); //why do we need "this->" for setters inside constructors?
		this->setGrades(grades, noGrades);
	}

	Student(int id_, string name, int* grades, int noGrades): id(id_) { //constant fields can not have setters and getters, hence
		//the :id(id_) declaration
		this->setName(name); //why do we need "this->" for setters inside constructors?
		this->setGrades(grades, noGrades);
	}
	
	Student(): id(0) {

	}

	/*void cleanAfterMe() { not needed
		delete[] this->grades;
	}*/

	~Student() {
		//clean any space you have in heap
		delete[] this->grades; //this is only automatically called when the objects are destroyed
		//meaning that inside setters we still need to manually delete heap memory when working with pointers and dynamic arrays.
	}


};

int Student::MIN_NUMBER_CHARS = 5; //INITIALIZE THE STATIC FIELD OUTSIDE THE CLASS
int Student::MIN_GRADE = 0;
int Student::MAX_GRADE = 10;

int main() {
	Student student;
	cout << endl << "Min number of chars is " << Student::MIN_NUMBER_CHARS;

	student.addGrade(10);
	student.print();

	Student john;
	int values[4] = { 10, 9, 8, 10 };
	string names[10] = { "John", "Bob", "Alice" };

	john.setGrades(values, 4);
	john.print();

	//for (;;) this is an infinite loop that will eat up all local machine resources due to memory leak
	//	john.setGrades(values, 4);
	//}

	//for (;;) {
	//	Student* pStudent = new Student("Vader", values, 4);
	//	//pStudent->cleanAfterMe(); not needed if we have destructor defined
	//	delete pStudent; //without the destructor, this will still create memory leaks as some grades will remain in memory
	//}





}