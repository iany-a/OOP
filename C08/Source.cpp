#include <iostream>
#include <string>
#include <string.h>

using namespace std;

//last week
//copy constructor
//static variables and static const
//static methods

//today
//overloading operators - specific to C++, no other programming language.

class StringUtils {
	//int value;
public:
	static string* copyStringArray(string* values, int noValues) {
		string* copy = new string[noValues];
		for (int i = 0; i < noValues; i++) {
			copy[i] = values[i];
		}
		return copy;
	}
};


class Student {
	string* courses = nullptr;
	int noCourses = 0;
	const string code = ""; //id
	string name;
public:

	void setCourses(string* values, int noValues) {
		delete[] this->courses; //prevent memory leaks
		this->courses = StringUtils::copyStringArray(values, noValues);
		this->noCourses = noValues;
	}

	string* getCourses() {
		return StringUtils::copyStringArray(this->courses, this->noCourses); //deep copy always in getters for pointers!
	}

	int getNoCourses() {
		return this->noCourses;
	}
	
	//destructor
	~Student() {
		delete[] this->courses;
	}

	void display() {
		cout << endl << "____________________________________________";
		cout << endl << "Student name: " << this->name;
		cout << endl << "Courses: ";
		for (int i = 0; i < this->noCourses; i++) {
			cout << this->courses[i] << ", ";
		}
	}

	Student(const Student& stud): code(stud.code) { // initialization list: code=(new object code) takes (stud.code) = source
		this->name = stud.name;
		this->courses = StringUtils::copyStringArray(stud.courses, stud.noCourses);
		this->noCourses = stud.noCourses;
		//this->code = stud.code; - can not copy constant
	}

	Student() {

	}

	Student(string name, string code): code(code), name(name) {
		//this-> name = name; - not used as the name is initialized in the initialization list name(name)
	}

	//Student(string name = "", string code = "", string* courses = nullptr, int no = 0) {
	//	//this should not be used as default constructor matches the default values
	//}

	//Student(string name = "", string code, string* courses, int no) {
	//	same thing as above, this is treated as default constructor
	//}

	//Student(string name, string code, string* courses, int no): code(code), name(name), noCourses(no) {
	//	//we are not allowed to use pointers inside an initialization list, as this will create a shallow copy!
	//	this->courses = StringUtils::copyStringArray(courses, no);
	//}

	//overloading =
	//void operator=(Student s1, Student s2) { // error: too many parameters because a 3rd one is "this"
	void operator=(Student s2) { //only the destination is needed as parameter here, as first one is "this"
		if (this == &s2) { //avoid self copy!
			return;
		}
		this->name = s2.name;
		delete[] this->courses; // this is needed before calling the new array creation in the StringUtils function
		//to avoid creating memory leaks
		this->courses = StringUtils::copyStringArray(s2.courses, s2.noCourses);
		this->noCourses = s2.noCourses;
		//this->code = s2.code; //this will never work
	}
};

class StudentUtil {
public:
	//static void printStudent(Student s) {
	//	//copy constructor is called
	//}

	//static Student createStudent() {
	//	return Student();
	//	//copy constructor is called
	//}

	static void printStudent(Student& s) {
		//copy constructor is not called - see parameter called by reference, not by value
	}

	static Student createStudent() {
		Student temp;
		return temp;
	}


};


int add(int a, int b) {
	return a + b;
}

//OVERLOADING = declare same function name with a different parameter list or type, or function type
int add(int a, int b, int c) {
	return a + b + c;
}

int add(Student s, int grade) {

}


int main() {
	
	string extraCourses[3] = { "AI", "Robotics", "Data Structures" };
	Student a("John", "ASE01");
	a.setCourses(extraCourses, 3);
	a.display();

	//clone object
	Student aClone = a; //without declaring the copy constructor, the program will CRASH
	//due to a dangling pointer: this is attempting a shallow copy of the 
	//address of the previously created object which gets deleted when the destructor runs (hence the crash)
	aClone.display();

	StudentUtil::printStudent(a); //crash without copy constructor

	

	Student temp;
	//temp = temp; //this will fail your the exam :)

	// "=", "+" are functions of the operator class
	temp = a; //operator=(Student a, Student b);
	int vb = 10; //operator=(int a, int b);
	vb = vb + 5; //operator+(int a, int b);



}