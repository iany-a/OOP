#include <iostream>
#include <string> // for c++ string data type
#include <string.h> // for char* data type

//enum - enumeration defined for the entire program.
// think of custom bool, with as many options as possible 
//needs to be defined OUTSIDE the class
enum StudentType {
	BACHELOR = 10, MASTER, PHD //DEFAULT VALUES: 0, 1, ..., can be overwritten manually, and each member following the first member will have n+1 value
};

int main() {

	//data types
	char aSingleChar; //!!! NAMING CONVENTION - Camelcase, descriptive - german style
	//CTRL+SPACE intellisense
	aSingleChar = 'a'; 
	//aSingleChar = "a"; // (const char[2]) = this is an array (string) of chars, not what we need here
	
	std::cout << std::endl << "A single char: " << aSingleChar;
	
	aSingleChar = 64; // this will assign the ASCII code reference, not an actual int value.

	std::cout << std::endl << "A single char: " << aSingleChar;

	int noStudents = 10; //signed int, 1st bit will be used for the sign
	unsigned int noClasses = 23; //only positive values, and we use all the bits for storing the value
	float average = 9.8;
	double passingRate = 73.2226;
	bool isValidated = true; // NAMING CONVENTION: start with "is" or "has for readability
	bool hasScholarship = false;

	StudentType studentType = StudentType::MASTER;
	studentType = StudentType::BACHELOR;

	std::cout << std::endl << "The student type is: " << studentType; //ALWAYS prints the numerical value. For the associated values we need a function

	//arrays
	//static
	float grades[100]; //hard-coded value, not feasible
	grades[0] = 9;
	//grades[100] = 10; - last index is 99 not 100
	grades[99] = 10;

	//dynamic
	float* multipleGrades; // undecided number of grades
	//memory allocation
	//set a value for the lenght of the array
	unsigned int noGrades;
	std::cout << std::endl << "Input the no. of grades: ";
	std::cin >> noGrades;
	//define the dynamic array
	multipleGrades = new float[noGrades]; 
	
	//init array values
	for (int i = 0; i < noGrades; i++) {
		multipleGrades[i] = 0;
	}

	multipleGrades[0] = 10;
	
	//char arrays
		//static
	char facultyName[100];
	//facultyName[0] = 'C'; - bad joke

	//facultyName = "CSIE"; - CAN NOT INITIALIZE IN THIS WAY

	strcpy_s(facultyName, "CSIE");


		//dynamic
	char* universityName;

	//allocate memory
	universityName = new char[strlen("ASE")+1];
	strcpy_s(universityName, strlen("ASE")+1, "ASE");



	
	



	return 0;
}