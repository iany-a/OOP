#include <iostream>
#include <string>
#include <string.h>

//pointers - main use is to refference outside the main function into other functions and/or classes
//dynamic arrays
//functions + passing values to functions
//address of a variable can be retrieved using the "&" symbol
//the pointer variable returns the value whose adress it is pointing to, with the "*" symbol


using namespace std;

void printValue(int value) {
	int temp;
}

void interchange(int a, int b) {
	int temp = a;
	a = b;
	b = temp;
}

void interchange2(int* pa, int* pb) {
	int temp = *pa;
	*pa = *pb;
	*pb = temp;
}

void interchange3(int& a, int& b) { //most elegant solution, which we will use
	int temp = a;
	a = b;
	b = temp;
}

int main() {

	//pointer definition
	int variable = 10;
	int noStudents = 1000;

	//int* pointer = nullptr; //pointers only store addresses
	int* pointer = (int*)10; //casted the pointer as int value as some sort of admin privilege override
	//pointer = (int*)20; //don't need to define the pointer more than once, we can override the value further. 

	//read what is at address 10 in RAM

	cout << endl << "The number in memory at address 10 is: " << pointer;
	//cout << endl << "The number in memory at address 10 is: " << *pointer; //read access violation error (intended)
	cout << endl << "The number in memory at address 10 is: " << &pointer;
	cout << endl << "The variable is: " << variable;
	cout << endl << "The value at the address with the value equal to the variable value is: " << &variable;


	pointer = &noStudents;
	cout << endl << "No. students: " << noStudents;
	cout << endl << "No. students: " << pointer;
	cout << endl << "No. students: " << *pointer;

	noStudents = 2000;
	*pointer = 3000; //assign a specific value in memory at the pointer address
	cout << endl << "No. students: " << noStudents;


	printValue(variable);

	int value1 = 10;
	int value2 = 20;

	cout << endl << "v1=" << value1 << " v2=" << value2;

	int temp = value1;
	value1 = value2;
	value2 = temp;

	cout << endl << "v1=" << value1 << " v2=" << value2;

	interchange(value1, value2);

	cout << endl << "v1=" << value1 << " v2=" << value2;

	interchange2(&value1, &value2);

	cout << endl << "v1=" << value1 << " v2=" << value2;

	interchange3(value1, value2);

	cout << endl << "v1=" << value1 << " v2=" << value2;

}