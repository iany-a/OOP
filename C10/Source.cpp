#include <iostream> //console
#include <string>
#include <string.h>
#include <fstream> //files

using namespace std;

//managing files
//text files
//binary files
//reading from console

class Student {
	char* name = nullptr;
	int age = 0;
	int* grades = nullptr;
	int noGrades = 0;

public:
	Student(const char* name, int age, int* grades, int noGrades): age(age) {
		this->name = new char[strlen(name) + 1];
		strcpy_s(this->name, strlen(name) + 1, name);
		this->grades = new int[noGrades];
		for (int i = 0; i < noGrades; i++) {
			this->grades[i] = grades[i];
		}
		this->noGrades = noGrades;
	}

	//TODO: copy constructor, operator=, and destructor


	~Student(){
		delete[] this->name;
		delete[] this->grades;
	}

	//alternative to overloading<<

	void writeToTextFile(ofstream& file) {
		if (this->name != nullptr) {
			file << "Name: " << this->name << endl;
		}
		file << "Age: " << this->age;
		if (this->grades != nullptr) {
			file << "Grades: ";
			for (int i = 0; i < this->noGrades; i++) {
				file << "" << this->grades[i];
			}
			file << endl;
		}
	}

	//write the student info into a binary file

	void writeToBinary(ofstream& file) {
		//Don't write addresses in binary files
		//file.write((char*)this, sizeof(Student)); 	//wrong approach
		//write age as value
		file.write((char*)&this->age, sizeof(int));
		//write name + ending \0 as value
		//write the size of the name for input reading (the opposite)
		int nameSize = strlen(this->name) + 1; //+1 is optional in both these lines
		file.write((char*)&nameSize, sizeof(int));
		file.write(this->name, sizeof(char) * strlen(this->name) +1);
		//write grades
		//start with their number
		file.write((char*)&this->noGrades, sizeof(int));
		for (int i = 0; i < this->noGrades; i++) {
			file.write((char*)&this->grades[i], sizeof(int));
		}
		

	
	}

	void readFromBinary(ifstream& file) {
		file.read((char*)this->age, sizeof(int));
		delete[] this->name;
		this->name = new char[nameSize];
		file.read(this->name, nameSize);

		delete[] this->grades;
		file.read((char*)&this->noGrades, sizeof(int));
		this->grades = new int[this->noGrades];
		for (int i = 0; i < this->noGrades; i++) {
			file.read((char*)&this->grades[i], sizeof(int));
		}

	}

	void print() {
		cout << endl << "Name: " << this->name;
		cout << endl << "Age: " << this->age;
		if (this->noGrades > 0) {
			cout << endl << "Grades: ";
			for (int i = 0; i < this->noGrades; i++) {
				cout << this->grades[i] << ", ";
			}
		}
	}



	friend void operator>>(ifstream& file, Student& stud);
	friend void operator<<(ofstream& file, Student& stud);
};

void operator<<(ofstream& file, Student& stud) {
	if (stud.name != nullptr) {
		file << "Name: " << stud.name<<endl;
	}
	file << "Age: " << stud.age;
	if (stud.grades != nullptr) {
		file << "Grades: ";
		for (int i = 0; i < stud.noGrades; i++) {
			file << "" << stud.grades[i];
		}
		file << endl;
	}
}

void operator>>(ifstream& file, Student& stud) {
	char buffer[1000];
	file >> buffer;

	delete[] stud.name;
	stud.name = new char[strlen(buffer) + 1];
	strcpy_s(stud.name, strlen(buffer) + 1, buffer);

	int age;
	file >> age;
	stud.age = age;

	//alternative
	//file >> s.age;

	int noGrades;
	file >> noGrades;

	delete[] stud.grades;
	stud.grades = new int[noGrades];
	stud.noGrades = noGrades;

	for (int i = 0; i < noGrades; i++) {
		file >> stud.grades[i];
	}

	

}




int main() {
	//binary files
	ofstream dataFile("backup.bin", ios::binary | ios::ate); //don't mix with ||

	int grades[3] = { 10, 10, 9 };
	Student john("John", 22, grades, 3);

	int vb = 23;
	//Don't use << for binary files, this is only used for strings.
	//dataFile << vb;

	//2 parameters
	// -first is the pointer to the data to be written, which is cased as a char pointer;
	// -second is the size
	//.write((char*)&vb, sizeof(int));

	john.writeToBinary(dataFile);
	dataFile.close();
	
	Student temp("", 0, grades, 3);
	ifstream inputData("backup.bin", ios::binary);
	temp.readFromBinary(inputData);
	inputData.close();
	temp.print();





	








	


	////reading from console
	//int vb;
	//string text;
	//string text2;
	//string text3;

	//int grades[3] = { 10, 10, 9 };
	//Student john("John", 22, grades, 3);


	//cout << endl << "Give me a number: ";
	//cin >> vb; //values: 23sdf, fjsfj
	//cout << endl<< "Value is: "<<vb; //returns 23, 0 (crash on 2nd)
	
	//strings
	//bug: cin >> will read a buffer. if we use spaces it will assign only the first string until the first space, assigning other strings after space to the next cin
	//this is caused by " " logic: it is read as a string terminator
	//cout << endl << "Input text: ";
	//cin >> text; //values: hello, two words
	//cout << endl << "Text: "<<text; //returns: hello, two
	//cout << endl << "2nd Input text: "; //skipped
	//cin >> text2; //value auto input: two
	//cout << endl << "2nd Text: " << text2; //returns: two

	//read with spaces
	//char buffer[1000];
	//cout << endl << "Input text: ";
	//cin.getline(buffer, 999);
	////cout << endl << "Text: " << buffer;
	//text = string(buffer); //convert char array into a string object
	//cout << endl << "Text: " << text;
	
	//text files
	//they share the same "bug" as cin
	//in C you were using the file structure FILE* pf
	//C++: 3 new libraries: fstream
	//fstream file; //generic class for reading and writing to files
	////recommendation to not use ofstream instead
	//ofstream fileForWriting; //class for opening files in write mode
	//ifstream fileForReading; //class for opening files in read mode

	////create report to store students data
	////by default all files are considered text
	//ofstream report("students.txt", ios::ate); //source, bitmasks(rights) - this opens a file in truncate mode for writing
	////if the file does not exist, it will create it
	////if the file exist and you open it in truncate mode, it will be deleted and recreated
	////if the file exist and you open it in append mode, it will add to the existing file
	//if (report.is_open()) {
	//	//write into the text file
	//	report << "\t\t Students Data Report" << endl;
	//	report << "\t Current date: Nov 27, 2025" << endl;

	//	//report << john;
	//	john.writeToTextFile(report);
	//}
	//else {
	//	cout << endl << "****ERROR: File not created.****";
	//}

	////important: don't forget to close the file when you are done
	//report.close();

	////read from text files
	////some issues
	////create the text file in standard format that is easy to read
	////other formats: csv, JSON, XML, 
	////SIMPLE FORMAT
	////1.each line has a single value
	////2.before multiple lines that store multiple values (array) put a line with their number
	//ifstream inputFile("backup.txt"); //no ios:: for reading txt file
	//if (inputFile.is_open()) {
	//	//use the file pattern
	//	string name;
	//	char buffer[100];
	//	//inputFile >> name; //stop on space
	//	inputFile.getline(buffer, 99);
	//	cout << endl << "Name from file: " << buffer;
	//	int age;
	//	inputFile >> age;
	//	cout << endl << "Age from file: " << age;
	//	int noGrades;
	//	inputFile >> noGrades;
	//	cout << endl << "No of grades from file: " << noGrades;
	//	for (int i = 0; i < noGrades; i++) {
	//		int grade;
	//		inputFile >> grade;
	//		cout << endl << "Grade from file: " << grade;
	//	}
	//}
	//else {
	//	cout << endl << "****ERROR: File not created.****";
	//}

	//
	//ifstream backup("backup.txt");
	//if (backup.is_open()) {
	//	backup >> john;
	//}
	//backup.close();


	//ofstream report2("john.txt");
	//report2 << john;
	//report2.close();

	////binary files
	////343455465 - as text 9 bytes
	////			- as binary 4 bytes
	//ofstream binaryFile("students.bin", ios::binary | ios::ate);
	//if (binaryFile.is_open()) {
	//	//write into binary files
	//	//NEVER use << - that's only used in strings
	//	//binaryFile << vb;
	//	//little endian starts with least important bits
	//	//binaryFile.write((char*)&vb, sizeof(int)); 
	//}
	//binaryFile.close();



}