#include <iostream>
#include <string>

using namespace std;

//inheritance
//build framework for classes
//upcasting
//downcasting
//virtual functions
//overriding + overloading = polimorphism


class Student {
private: 
	string name = "";
protected: //same as private, however it's seen as public for classes that inherit their data
	int age = 0;
	string faculty;
	string bachePr;
public:
	string getName() {
		return this->name;
	}

	Student(string name, int age) {
		this->name = name;
		this->age = age;
	}

	Student() {

	}

	virtual void getBasicInfo() {
		cout << endl << "It is a student.";
	}

};

//inherits or extends
class MasterStudent : public Student { //public inheritance keeps the variables privacy setting as it was in the origin class
	string masterProgram = "";
	string masterFaculty = "";
	//private fields from origin class will always remain private (you will need getters or any other public method to get the data from it)
	//workaround: protected
public:
	void display() {
		cout << endl << "Name: " << this->getName();
		cout << endl << "Age: " << this->age;
		cout << endl << "Faculty: " << this->faculty;
		cout << endl << "Bachelor: " << this->bachePr;
		cout << endl << "Master: " << this->masterProgram;
		cout << endl << "Master faculty: " << this->masterFaculty;

	}

	MasterStudent(): Student("John", 0) {

	}

	MasterStudent(string name, int age, string masterProgram): Student(name, age) {
		this->masterProgram = masterProgram;
	}

	//overriding the method from parent class
	void getBasicInfo() {
		cout << endl << "It is a master student.";
	}
};

class PhdStudent : public MasterStudent {
	string phdProgram = "";
public:
	//override
	void getBasicInfo() {
		cout << endl << "It is a Phd student.";
	}
};

class ErasmusStudent : public Student {
	string country = "";
};


int main() {
	Student john("john", 23);
	
	MasterStudent alice("Alice", 24, "whatever");
	//cout << endl << "Alice name: " << alice.getName();
	alice.display();

	//how do we handle all types of students?
	//Student students[10];
	//MasterStudent masterStudents[10];
	//PhdStudent phdStudents[10];
	//ErasmusStudent erasmusStudents[10];
	//this is too time consuming and prone to errors

	//elegant solution: 1 single array for all types of students

	john.getBasicInfo();
	PhdStudent bob;
	Student student;
	student = alice; //up-casting
	alice.getBasicInfo();

	student = bob; //up-casting
	bob.getBasicInfo();

	//Student students[3];
	//students[0] = john;
	//students[1] = alice;
	//students[2] = bob;

	Student* studentsPointers[3];
	studentsPointers[0] = &john;
	studentsPointers[1] = &alice; //upcasting at pointer level
	studentsPointers[2] = &bob;
	
	PhdStudent* pPhd = (PhdStudent*)studentsPointers[2]; //downcasting at pointers level works!

	//down-casting (!) - works only if you know what you are doing, it's dangerous. requires manual casting of objects
	//PhdStudent kevin = (PhdStudent)students[2];

	//cout << endl << "_______________________";
	//for (int i = 0; i < 3; i++) {
	//	students[i].getBasicInfo();
	//}
	cout << endl << "_______________________";
	for (int i = 0; i < 3; i++) {
		studentsPointers[i]->getBasicInfo(); //without using "virtual" in the parent class method, it is called early binding
		//with virtual method definition in main class, it is called late-binding
		//the virtual keyword will generate an array of pointers to functions
		//studentsPointers[i] -> vfptr[i];
	}


}