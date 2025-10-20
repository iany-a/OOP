#include <string>
#include <string.h>
#include <iostream>

using namespace std;

void printMessage(string msg) {
	cout << endl << "Message: " << msg;
}

void printMessage(char* msg) {
	cout << endl << "Message: "<< msg;
}

//change course name

//option A
char* readCourseName() {
	//do not use static arrays as returns. these are on the function stack which vanishes once function ends
	char buffer[10000];
	
	//char* newName = new char[strlen(courseName)]

	cout << endl << "Please provide the course name: ";
	cin >> buffer; //this will overwrite the values on the buffer, and the strlen of it will only count the populated indexes

	char* response = new char[strlen(buffer) + 1];
	strcpy_s(response, strlen(buffer) + 1, buffer);
	return response;
}

//option B
void readCourseName(char* courseName, int maxSize) { //need to add maxSize to avoi too long gibberish
	char buffer[10000];
	cout << endl << "Please provide the course name: ";
	cin >> buffer;
	if (strlen(buffer) + 1 > maxSize) {
		cout << endl << "New value is too long. Please use Max" << maxSize - 1;
		return;
	}

	strcpy_s(courseName, maxSize, buffer);
}

string* readStudentNames(int* noStudents) {
	cout << endl << "No of students: ";
	cin >> *noStudents;
	string* names = new string[*noStudents];
	for (int i = 0; i < *noStudents; i++) {
		cout << endl << "Student name: ";
		cin >> names[i];
	}
	return names;
}