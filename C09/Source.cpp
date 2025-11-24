#include <iostream>
#include <string>
#include <string.h>

using namespace std;

class Student {
	int* grades = nullptr;
	int noGrades = 0;
	const string name = "";
	int age = 0;

public:
	
	Student(const Student& student): name(student.name), age(student.age) {
		if (student.grades == nullptr) {
			this->grades = nullptr;
		}
		else {
			this->grades = new int[student.noGrades];
			for (int i = 0; i < student.noGrades; i++) {
				this->grades[i] = student.grades[i];
			}
		}
	}

	Student(string name, int age) : name(name), age(age) {

	}



	~Student() {
		delete[] this->grades;
	}


};




int main() {
	Student john("John", 22);
	Student temp("Temp", 0);
	Student johnClone = john; //copy constructor

	//test the destructor
	//option A
	Student* alice = new Student("Alice", 22);
	delete alice;

	//option B
	{
		Student s("", 0);
	}
	//s.name; this will return an error, showing that the object was deleted on codeblock exit.

	//operator= 
	temp = john;
	//stream operators
	cout << john;
	cin >> john;
	cout << john;

	//math operators
	//+= -= /=
	
	john += 23; //add 23 to age
	john -= 5;

	//+ - / *
	john = john + 8; // add 8 to grades
	john = 9 + john;
	john = john + "Test";

	//++ --
	john++; //increment age (post)
	++john; //pre incrementation

	//logic operators <, >, ==, >=, <=, !
	if (john == alice) {
		cout << endl << "They have the same grades average";
	}
	if (!john) { // return true if at least 1 grade is <5
		cout << endl << "John has at least 1 failed exam.";
	}

	//cast
	float average = (float)john;

	//function operator
	bool isInRange = john(5, 8); //returns true if john average is between 5 and 8

	//index operator []
	int firstGrade = john[0]; //get grade at index 0
	john[0] = 10; //set grade at index 0




}