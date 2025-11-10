#include <iostream>
#include <string>
#include <string.h>

using namespace std;

//dangling pointer - pointer pointing to an address that was deleted - this will crash


class StringUtils { //ALL FUNCTIONS ARE DECLARED INSIDE CLASSES IN OOP. NO GLOBAL FUNCTIONS.
	//define method for deep copy
public:
	static char* createDeepCopy(const char* value) {
		if (value == nullptr) {
			return nullptr;
		}
		char* copy = new char[strlen(value) + 1];
		strcpy_s(copy, strlen(value) + 1, value);
		return copy;
	}
};


class Course {
	char* name = nullptr;
	unsigned int noStudents = 0;
	bool isOnline = false;
	static int NO_ONLINE_COURSES;

public:

	//default constructor
	Course() {
		this->isOnline = false;
	}

	Course(const char* name, int noStudents, bool isOnline) {
		this->name = StringUtils::createDeepCopy(name);
		this->setNoStudents(noStudents);
		this->isOnline = isOnline;
		if (this->isOnline) {
			Course::NO_ONLINE_COURSES++; //increment the online courses count each time you create an object with the field
		}
	}



	const static int MAX_NO_STUDENTS; //always constant if static

	void setNoStudents(int value) {
		if (value > MAX_NO_STUDENTS) {
			throw "Too many students.";
		}
		this->noStudents = value;
	}

	unsigned int getNoStudents(){ //() receives this for free
		return this->noStudents;
	}

	static int getNoOnlineCourses() { //static method in a class: that's an action for the course story
		//not an action for a particular course. e.g. take exams, take notes, etc. (from a student pov)
		//for static functions you need a class
		//this->noStudents = 100; //error: "this" pointers do not work inside static functions
		//whatever happens in this function is returned as it is, without objects creation.
		return Course::NO_ONLINE_COURSES;
	}

	void setName(const char* value) {
		//StringUtils su;
		//this->name = su.createDeepCopy(value); //need an object to call the function inside the other class
		this->name = StringUtils::createDeepCopy(value); //this is the right way, by adding "static" in the function inside the other class
		
	}

	bool checkIsOnline() {
		return this->isOnline;
	}

	//void setIsOnline(bool isOnline) {} //bad, ChatGPT type coding, don't use
	void moveItOnline() { //correct version, changes a course type to be online.
	/*	if (this->isOnline = false) {
			this->isOnline = true;
			Course::NO_ONLINE_COURSES++;
		}*/

		if (!this->isOnline) {
			Course::NO_ONLINE_COURSES++;
		}
		this->isOnline = true;
	}

	void moveItInClass() {
		this->isOnline = false;
		Course::NO_ONLINE_COURSES--;
	}

	~Course() {
		delete[] this->name;
		if (this->isOnline)
			Course::NO_ONLINE_COURSES--;
	}

	void print() {
		cout << endl << "COurse name :" << this->name;
		cout << endl << "Course students: " << this->noStudents;
	}


	//copy constructor
	Course(const Course& c) { //by reference, as by value will create an infinite loop
		//c is the source
		//c.noStudents = this->noStudents; // incorrect
		this->noStudents = c.noStudents;
		this->name = StringUtils::createDeepCopy(c.name);
		this->isOnline = c.isOnline;
		if (this->isOnline) NO_ONLINE_COURSES++;

	}


};

const int Course::MAX_NO_STUDENTS = 1000;
int Course::NO_ONLINE_COURSES = 0;

void doSomething(Course& c) { //Course* or Course& does not trigger the copy constructor
	
}

Course doSomethingElse() { //everytime we have functiosn that receive or return an object by value, the copy constructor is called
	Course c;
	return c;
}



int main() {
	Course c;
	int noStudents = 10000;
	//Course::MAX_NO_STUDENTS = 100000; //OVERRIDE STATIC FIELD = no bueno
	if(noStudents <Course::MAX_NO_STUDENTS) c.setNoStudents(10000);
	cout << endl << c.getNoStudents();

	Course oop;
	Course atp;

	
	//cout << endl << "No online courses: " << Course::NO_ONLINE_COURSES; //innaccessible
	cout << endl << "No online courses: " << Course::getNoOnlineCourses();
	//cout << endl << "No online courses: " << Course::getNoOnlineCourses();
	
	atp.moveItOnline();
	atp.moveItOnline();
	atp.moveItOnline();
	cout << endl << "No online courses: " << Course::getNoOnlineCourses();

	Course oop2("OOP", 150, false);
	oop2.print();

	//Course newOop = oop2; //copy constructor - shallow copy, crashes the program since the 
	//address copied is already deleted when the destructor is called for the 2nd object created
	// allso called a dangling pointer
	//newOop.print();

	doSomething(oop2);


}