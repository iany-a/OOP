//classes

#include <iostream>
#include <string>
#include <string.h>

using namespace std;

struct StudentStructure {
	string name="";
	int grade = 0;
	char faculty[1000]="";
};

class StudentClass {
private:
		string name = "";
		char faculty[1000] = "";
		int grade = 0;

public:
		void printStudentObjectInfo() {
			cout << endl << "Name: " << this->name; //CTRL+D to duplicat active line below it
			cout << endl << "Grade: " << this->grade;
			cout << endl << "Faculty: " << this->faculty;
		}

		int getGrade() {
			return this->grade;
		}

		void setGrade(int newGrade) {
			if (newGrade < 0 || newGrade>10) { //ALWAYS validate otherwise 0 points awarded at exam
				throw "Wrong value.";
			}
			else this->grade = newGrade;
		}



	};




//void printStudentInfo(StudentStructure student) {
//	cout << endl << "Name: " << student.name; //CTRL+D to duplicat active line below it
//	cout << endl << "Grade: " << student.grade;
//	cout << endl << "Faculty: " << student.faculty;
//
//}

//void printStudentObjectInfo(StudentClass student) {
//	cout << endl << "Name: " << student.name; //CTRL+D to duplicat active line below it
//	cout << endl << "Grade: " << student.grade;
//	cout << endl << "Faculty: " << student.faculty;
//}

//abstract: the most complex function ever to read and validate the grade
void noOneWillUseIt(StudentStructure& student) {
	//
	//TODO
}



int main() {
	//data stored into variables
	//in STACK you get 0xCC for each byte for unitialized variables
	//in HEAP you get 0xCD for each byte on unitialized variables
	char facultyName[1000]= ""; //always initialize variables post definition
	char* courseName = nullptr;
	int noStudents = 0;

	string* names = nullptr;
	int* grades = nullptr;

	cout << endl << facultyName;

	StudentStructure student; //student now is a structure
	student.name = "John";

	StudentStructure* students = nullptr; //array of students
	//printStudentInfo(student);

	//cout << endl << "Provide student grade: ";
	//cin >> student.grade;
	//printStudentInfo(student);

	StudentClass studentObject;
	/*cout << endl << "Student Obj name" << studentObject.name;
	studentObject.grade = -6;*/

	studentObject.printStudentObjectInfo();
	StudentClass alice;
	StudentClass john;

	alice.printStudentObjectInfo();
	john.printStudentObjectInfo();

	cout << endl << "Alice grade is: " << alice.getGrade();

	//alice.setGrade(-6); //returns error
	alice.setGrade(10);
	alice.printStudentObjectInfo();
}