#include <iostream>
#include <string>

using namespace std;

//abstract classes + virtual pure methods
//managing exceptions with try-catch


class Student {
protected:
	string name = "";
public:
	virtual void getInfo() {
		cout << endl << "It's a student.";
	}

	virtual void takeExam() = 0; //virtual pure methods, called abstract methods in JAVA
	//this makes the class an abstract class, but there is no "abstract" keyword in C++
	//an interface in JAVA is a class that only has virtual pure methods
};

class MasterStudent : public Student {
	string bachelorDiploma = "";
	void getInfo() {
		cout << endl << "It's a master student."
			<<endl<<"Graduated: " + this->bachelorDiploma;
	}
	void takeExam() {

	}


};

class PhdStudent : public MasterStudent {
	string masterDiploma = "";
public:
	void getInfo() {
		cout << endl << "It's a PhD student"<<endl
			<<"Graduated: " + this->masterDiploma + " and " + this->masterDiploma;
	}
	//void takeExam() {

	//}

	void setDiploma(string diploma) {
		if (diploma.size() < 3) {
			//throw "Wrong diploma.";
			throw exception("Wrong diploma!");
			//throw new exception("Wrong diploma! but now with pointers.");
		}
		this->masterDiploma = diploma;
	}
};

class ErasmusStudent : public Student {
	string country = "";
	void getInfo() {
		cout << endl << "It's an Erasmus student.";
	}
	void takeExam() {
		cout << endl << "Take an exam.";
	}



};



int main() {
	Student* students[4]; //always use pointers to objects

	//use up-casting
	//students[0] = new Student(); //this will not work anymore. fix is to add an extra class
	//called BachelorStudent, and keep Student class as abstract
	//temp fix:
	students[0] = new ErasmusStudent();
	students[1] = new ErasmusStudent();
	students[2] = new MasterStudent();
	students[3] = new PhdStudent();
	for (int i = 0; i < 4; i++) {
		students[i]->getInfo();
	}

	PhdStudent phd;
	try {
		phd.setDiploma("1");
	}
	catch (exception e) {
		cout << endl << "We have an exception: " + (string)e.what(); //or +(string)e->what() if ptr
		//AND delete e; manually!
	}
	catch (...) {
		cout << endl << "Houston, we have a problem!";
	}
	





}