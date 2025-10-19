#include <iostream>
#include <string.h>
#include <string>

using namespace std;

//simple app to manage students grades

void printStringsArrays(string* values, int noElements);
void printIntegersArray(int* values, int noElements);
void initNumbersArray(int* values, int noElements, int defaultValue);
int* createAndInitAnIntegersArray(int noElements, int defaultValue);



int main() {
	//data
	char faculty[100] = "CSIE";
	strcpy_s(faculty, "ASE - CSIE");
	cout << endl << "Faculty " << faculty;

	int noStudents = 0;
	int* grades = nullptr; //pointer; always initialized with nullptr

	
	//char** names; //C style
	
	string* names = nullptr; //CPP style
	cout << endl << "No. of students: ";
	cin >> noStudents;

	//allocate
	names = new string[noStudents];
	grades = new int[noStudents];
	//init the grades array
	initNumbersArray(grades, noStudents, 5);


	names[0] = "John";
	grades[0] = 9;


	printStringsArrays(names, noStudents);
	printIntegersArray(grades, noStudents);

	int staticGrades[100];
	initNumbersArray(staticGrades, noStudents, 5);
	staticGrades[0] = 9;
	printIntegersArray(staticGrades, noStudents);

	//test create and init
	int* newValues = createAndInitAnIntegersArray(noStudents, 0);


	//professor tried to make the break the program as the create and initialize function is not supposed to work
	//but override values on sequential steps done before it runs
	/*initNumbersArray(staticGrades, noStudents, 5);
	initNumbersArray(staticGrades, noStudents, 5);
	initNumbersArray(staticGrades, noStudents, 5);
	initNumbersArray(staticGrades, noStudents, 5);

	printStringsArrays(names, noStudents);
	printIntegersArray(grades, noStudents); printStringsArrays(names, noStudents);
	printIntegersArray(grades, noStudents); printStringsArrays(names, noStudents);
	printIntegersArray(grades, noStudents); printStringsArrays(names, noStudents);
	printIntegersArray(grades, noStudents); printStringsArrays(names, noStudents);
	printIntegersArray(grades, noStudents); printStringsArrays(names, noStudents);
	printIntegersArray(grades, noStudents);*/




	printIntegersArray(newValues, noStudents);
}


void printStringsArrays(string* values, int noElements) { //parameter has the same type as the variable that invokes this function
	cout << endl << "The values are: ";
	for (int i = 0; i < noElements; i++) {
		cout << " " << values[i];
	}
}

void printIntegersArray(int* values, int noElements) {
	cout << endl << "Numerical values: ";
	for (int i = 0; i < noElements; i++) {
		cout << " " << values[i];
	}
}

void initNumbersArray(int* values, int noElements, int defaultValue) {
	for (int i = 0; i < noElements; i++) {
		values[i] = defaultValue;
	}
}

int* createAndInitAnIntegersArray(int noElements, int defaultValue) {
	int newArray[1000];
	for (int i = 0; i < noElements; i++) {
		newArray[i] = defaultValue;
	}
	return newArray;
}