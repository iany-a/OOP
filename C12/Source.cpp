//NOTE: THIS CODE DOES NOT WORK, NEED TO UPDATE IT

#include <iostream>
#include <string>

using namespace std;

//relationship between classes:
//1. has-a = Composition
//2. is-a = Inheritance or Extension

//IMPORTANT: put the classes in order if you nest them
//each class is responsible for its own attributes
//default constructors in any linked classes are a big NO

class PersonalInformation {
public:
	string address;
	string country;
	int postalCode;
	string phone;

	PersonalInformation(string address, string country): address(address), country(country) { 
		//has-a now will break in main due to no default constructor

	}
};




class Student {
public:
	string name;
	const int id = 0;

	//has-a relationship (1:1)
	PersonalInformation personalInformation; //define a class inside a class
	Student(): id(id), personalInformation("Piata Romana", "Romania") {
		this->name = "John";
		//this->personalInformation = PersonalInformation("Piata Romana", "Romania"); //this is trying to use the = operator, to change 
		//other existing data, but in this case there is no existing data as no default constructor exists for PersonalInformation class
	}

	Student(int id, string name, string address, string country): id(id), personalInformation(address, country) {
		//we need to use the initialization list for calling the constructor of the sub-class, this is treated as a constant value
	}

};

//is-A relation
class BachelorStudent : public Student { //x : y => x inherits everything from y, here you specify access type: private, public, protected
	//if we don't mention the access type, it will make everything private. if we mark it public, it will keep everything as it was stated
	float bachelorExamAverage = 0.0f;
public:
	BachelorStudent() : Student(1, "Bob", "Bucharest", "RO") {

	}


};

class Group {
public:
	int number;
	//many students
	//has-a (1:M)

	//Student students[100]; //static approach
	Student** students = nullptr; //dynamic array of addresses of objects
	int noStudents = 0;

	Group() {

	}

	void initStudents(Student* students, int noStudents) {
		delete[] this->students;
		this->students = new Student*[noStudents]; //create a dynamic array of POINTERS not objects
		for (int i = 0; i < noStudents; i++) {
			this->students[i] = &students[i]; //get the address of each object with &
		}
		this->noStudents = noStudents;
	}
	void addStudent(int idStudent) {
		Student* newStudent = new Student(idStudent);
		Student** newStudents = new Student * [this->noStudents + 1];
		for (int i = 0; i < this->noStudents; i++) {
			newStudents[i] = this->students[i];
		}
		newStudents[this->noStudents] = newStudent;
		delete[] this->students;
		this->students = newStudents;
		this->noStudents += 1;
	}


};

int main() {
	//Student student;
	Student alice(1, "Alice", "Bucharest", "Romania");
	//student.personalInformation.country = "Romania";
	Group g1070;
	//the country of the 2nd student
	//g1070.students[1].personalInformation.country = "Romania";
	g1070.students[1]->personalInformation.country = "Romania";

	BachelorStudent stud;
	stud.name = "John";
	stud.personalInformation.country = "Romania";

}