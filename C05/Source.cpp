#include <iostream>
#include <string>
#include <string.h>

using namespace std;

class Assignment {
	//int*
	//string*
	char* requirements = nullptr;
	float points = 0;
	unsigned int noSubmissions = 0;
	string students[100] = {}; //students names that submit the solution

public:

	//special methods in a class
	//constructors
	//destructor
	//copy constructor
	
	//define a constructor with parameters -- DO NOT DO IT FIRST
	Assignment(const char* requirements, float points) {
		this->setPoints(points);
		this->setRequirements(requirements);
	}

	//default constructor which gets removed automatically if we create a constructor with parameters
	/*Assignment() {

	}*/

	float getPoints() {
		return this->points;
	}

	void setPoints(float points) {
		if (points < 0 || points >10) {
			throw "Invalid points";
		}
		this->points = points;
	}

	void setRequirements(const char* requirements) {
		//at least 5 chars
		if (strlen(requirements) < 5) {
			throw "Invalid string.";
		}
		this->requirements = new char[strlen(requirements) + 1];
		strcpy_s(this->requirements, strlen(requirements) + 1, requirements);		
	}

	char* getRequirements() {
		if (this->requirements == nullptr)
			return nullptr;
		char* copy = new char[strlen(this->requirements) + 1];
		strcpy_s(copy, strlen(this->requirements) + 1, this->requirements);

		return copy;
	}

};

int main() {
	//encapsulation
	Assignment assign1("Implement something", 10);

	cout << endl << "points: " << assign1.getPoints();
	assign1.setPoints(10);
	cout << endl << "points: " << assign1.getPoints();

	if (assign1.getRequirements() != nullptr) {
		cout << endl << "Requirements " << assign1.getRequirements();
	}
	else{
		cout << endl << "No requirements.";
	}

	assign1.setRequirements("Implement C++ class");

	if (assign1.getRequirements() != nullptr) {
		cout << endl << "Requirements " << assign1.getRequirements();
	}
	else {
		cout << endl << "No requirements.";
	}

}

//next week destructors / copy constr