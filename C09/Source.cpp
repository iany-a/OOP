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

	void operator=(const Student& s){
		if (this == &s) return; //can't copy ther same object
		this->age = s.age;
		this->noGrades = s.noGrades;
		delete[] this->grades;
		if (s.grades == nullptr) {
			this->grades = nullptr;
		}
		else {
			this->grades = new int[s.noGrades];
			for (int i = 0; i < s.noGrades; i++) {
				this->grades[i] = s.grades[i];
			}
		}

	}

	Student operator+(int value) {
		Student copy = *this;

		int* newGrades = new int[this->noGrades + 1];
		for (int i = 0; i < this->noGrades; i++) {
			newGrades[i] = this->grades[i];

		}
		newGrades[this->noGrades] = value;
		copy.noGrades += 1;
		copy.grades = newGrades;
		return copy;
	}

	float getAverage() {
		if (this->grades == nullptr)
			return 0.0f;
		float s = 0;
		for (int i = 0; i < this->noGrades; i++) {
			s += this->grades[i];
		}
		return s / this->noGrades;
	}

	
	bool operator==(Student& s) {
		return this->getAverage() == s.getAverage();
	}

	//cast to float
	explicit operator float() { //explicit = every time this cast operator is used is only  when we write it like (float) in main
		return this->getAverage();
	}

	friend void operator<<(ostream console, Student& s);
};

//all the operators which have a first parameter not an object are defined in global space (not inside the class itself)
Student operator+(int value, Student s) {
	return s + value;
}

void operator<<(ostream console, Student& s) {
	console << endl << "Student name: " << s.name; //use GETTERS vs FRIEND as good practice. use FRIEND at exam.
}




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

	////operator= 
	temp = john;
	////stream operators
	cout << john;
	//cin >> john;
	//cout << john;

	////math operators
	////+= -= /=
	//
	//john += 23; //add 23 to age
	//john -= 5;

	////+ - / *
	//DO NOT CHANGE THE PARAMETERS
	john = john + 8; // add 8 to grades, but DOES NOT CHANGE THE OBJECT
	john = 9 + john;
	//john = john + "Test";

	////++ --
	//john++; //increment age (post)
	//++john; //pre incrementation

	////logic operators <, >, ==, >=, <=, !
	if (john == johnClone) {
		cout << endl << "They have the same grades average";
	}
	//if (!john) { // return true if at least 1 grade is <5
	//	cout << endl << "John has at least 1 failed exam.";
	//}

	////cast
	float average = (float)john;

	////function operator
	//bool isInRange = john(5, 8); //returns true if john average is between 5 and 8

	////index operator []
	//int firstGrade = john[0]; //get grade at index 0
	//john[0] = 10; //set grade at index 0




}