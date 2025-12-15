#include <iostream>
#include <string>

using namespace std;

//relationship between classes:
//1. has-a = Composition
//2. is-a = Inheritance or Extension

class PersonalInformation {
	string address;
	string country;
	int postalCode;
	string phone;
};

class Group {
	int number;
	//many students
	//has-a (1:M)

	//Student students[100]; //static approach
	Student* students = nullptr; //dynamic array of objects
	int noStudents = 0;

};


class Student {
	string name;
	int age;
	
	//has-a relationship (1:1)
	PersonalInformation personalInformation; //define a class inside a class


	
public:

};

int main() {

}