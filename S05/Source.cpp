#include <iostream>
#include <string>
#include <string.h>

using namespace std;

const int noActivities = 5;

class Course {
	char* name = nullptr;
	string prof = "";
	float pointsPerActivity[noActivities] = {};
	unsigned int noStudents = 0;

public:

	void setName(const char* name) { //CONST when dealing with pointers otherwise you get errors in main
		//not less than 3 chars
		if (strlen(name) < 3) {
			throw "Invalid course name.";
		}

		this->name = new char[strlen(name) + 1];
		strcpy_s(this->name, strlen(name) + 1, name);
	}

	const char* getName() {
		//NEVER return the pointer
		//return this->name;

		//RETURN a copy
		char* nameCopy = new char[strlen(this->name) + 1];
		strcpy_s(nameCopy, strlen(this->name)+1, this->name);
		return nameCopy;
	}

	void setPointsPerActivity(float pointsPerActivity) {

	}

	float* getPointsPerActivity() {
		//return this->pointsPerActivity; - same problem as before
		float* ppActivityCopy = new float[noActivities];
		for (int i = 0; i < noActivities; i++) {
			ppActivityCopy[i] = this->pointsPerActivity[i];
		}
		return ppActivityCopy;
	}

	void setNoStudents(unsigned int noStudents) {
		if (noStudents > 150) {
			throw "Too many students";
		}
		this->noStudents = noStudents;
	}

	unsigned int getNoStudents() {
		return this->noStudents;
	}


	string getProf() {
		return this->prof; //"this" refers to the object where the class functions are called
	}

	void setProf(string prof) {
		//always validate inside setters
		//2=<length<50
		if (prof.size() < 2 || prof.size()>50) {
			throw "Wrong name";
		}
		this->prof = prof;
	}


};

int main() {
	Course course;
	course.setProf("TestName");
	cout << endl << "Course prof: " << course.getProf();
	course.setNoStudents(100);
	cout << endl << "No students: " << course.getNoStudents();

	//char* newName = new char[4] {"OOP"};

	course.setName("OOP");
	cout << endl << "Course name: " << course.getName();

	//char *courseNamePointer = new 
	//courseNamePointer[0] = 'X';
}