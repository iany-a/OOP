#include <iostream>
#include <string>
#include <string.h>

using namespace std;

//static variables - how to define and use
//static methods

//at test/exam we will use static fields for:
//magic number or do something like hasScolarship
//low probability for ID

//rule of 3
//

class Util {
public:
	static int* copyArray(int* values, int noValues) {
		//TODO - implement deep copy
		return nullptr;
	}

};

class Student {
	const int id;
	int age = 0;
	string name = "";
	bool hasScolarship = false;
	static const int MIN_AGE;
	static const int MAX_AGE;
	static int STUDENTS_WITH_SCOLARSHIP;
	static int ID_COUNTER;
public:

	Student() : id(++ID_COUNTER) {

	}

	Student(string name):id(++ID_COUNTER), name(name){ //const id needs to be declared in the initialization list in constructors

	}


	void setAge(int value) {
		//always validate your inputs
		if (value < 10 || value >100) { //magic numbers
			throw "Invalid value for age";
		}
		else {
			this->age = value;
		}
	}

	bool checkScolarship() {
		return this->hasScolarship;
	}

	void gainScolarship() {
		if (!this->hasScolarship) {
			this->hasScolarship = true;
			Student::STUDENTS_WITH_SCOLARSHIP++;
		}
	}

	void loseScolarship() {
		if (this->hasScolarship) {
			this->hasScolarship = false;
			Student::STUDENTS_WITH_SCOLARSHIP--;
		}
	}

	static int getScolarshipCounter() {
		return Student::STUDENTS_WITH_SCOLARSHIP;
	}

	int getID() {
		return this->id;
	}


//Option A - provide a public static method for the static attribute - this will only work if you provide the "static" term to not require an object

	static const int getMinAge() {
		return Student::MIN_AGE;
	}

//Option B - make the static variable a constant, but public, so in that way it is accessible in main with Student::MIN_AGE instead of using the getter

//
//	int getMaxAge() {
//		return Student::MAX_AGE;
//	}
	//post version
	Student operator++(int) {
		Student result = *this; //first assign the initial value
		this->age += 1; //increment it
		return result; //return the initial value, not the incremented one
	}

	//pre version
	Student operator++() {
		this->age += 1; //increment the value
		return *this; //return the incremented value
	}

};

int const Student::MIN_AGE = 10;
int const Student::MAX_AGE = 100;
int Student::STUDENTS_WITH_SCOLARSHIP = 0; //used for the counter at object creation / deletion
int Student::ID_COUNTER = 0;





int main() {
	Student s1;
	Student s2;

	//cout << endl << Student::getMinAge();
	//Question: how many students have scolarship?
	//inneficient way to check
	//int counter = 0; 
	//if (s1.checkScolarship()) counter++;

	s1.gainScolarship();
	s1.gainScolarship();

	cout << "Scolarship counter: " << Student::getScolarshipCounter();

	cout << endl << "S1 ID: " << s1.getID();
	cout << endl << "S2 ID: " << s2.getID();



}