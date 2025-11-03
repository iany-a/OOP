#include <iostream>
#include <string>
#include <string.h>

using namespace std;

enum class UniversityType {
	STATE,
	PRIVATE,
	FOREIGN
};


class University {
	UniversityType type = UniversityType::STATE;
	string* faculties = nullptr; //DEFINE A SINGLE SETTER FOR FACULTIES AND NOFACULTIES 
	int noFaculties = 0; //NO SOLO SETTER FOR THIS!!! NOFACULTIES NEEDS TO CHANGE TOGETHER WITH THE FACULTIES ARRAY 
	int noStudents = 0;
	string name = "";

public:
	void setFaculties(string* values, int noValues) {
		//DEEP COPY
		this->faculties = new string[noValues];
		for (int i = 0; i < noValues; i++) {
			this->faculties[i] = values[i];
		}
		this->noFaculties = noValues;
	}

	void setName(string name) {
		this->name = name;
	}

	string getName() {
		return this->name;
	}

	string* getFaculties() {
		string* copyFaculties = new string[this->noFaculties];
		for (int i = 0; i < noFaculties; i++) {
			copyFaculties[i] = this->faculties[i];
		}
		return copyFaculties;
	}

	void displayUniversityDetails() {
		cout << endl << "University name: " << this->name;
		cout << endl << "No students: " << this->noStudents;
		switch (this->type) {
		case UniversityType::STATE:
			cout << endl << "Type: " << "State universtity";
			break;
		case UniversityType::PRIVATE:
			cout << endl << "Type: " << "Private universtity";
			break;
		case UniversityType::FOREIGN:
			cout << endl << "Type: " << "Foreign universtity";
			break;
		default:
			cout << endl << "Type not covered";
		}

		cout << endl << "Faculties: ";
		if (this->faculties == nullptr) {
			cout << "None";
		}
		else for (int i=0; i < this->noFaculties; i++) {
			cout << " " << this->faculties[i];
		}
	}

};

int main() {

	University university;
	university.displayUniversityDetails();

	//static arrays created for testing purposes
	string faculties[3] = { "CSIE", "MK", "MAN" };
	int values[3] = { 10,20,30 };
	//char name[] = "CSIE";
	//char* newName = new char[5] {"CSIE"};

	university.setFaculties(faculties, 3);
	university.displayUniversityDetails();




}