#include <iostream>
#include <string.h>
#include <string>

using namespace std;

class Student{
private:
	int id = 0;
	string* name = nullptr;
	const int nameMaxLimit = 100;
	const int nameMinLimit = 3;
public:
	Student(int id_, string* name_) {
		if (id_ >= 0) this->id = id_;
		else cout << endl<< "Error: Invalid ID: Needs to be a real positive number.";
		if (name_->length() >= nameMinLimit && name_->length() <= nameMaxLimit) {
			setName(name_);
		}
		else cout <<endl << "Error: Name length needs to be between 3 and 100 characters.";

	}

	void setName(string* name_) {
		this->name = name_;
	}

	string* getName() {
		return this->name;
	}

	void setID(int id_) {
		this->id = id_;
	}

	int getId() {
		return this->id;
	}

	~Student() {
		delete this->name;
	}

	Student(int id_, string* name) {

	}

};


int main() {
	Student studentA(2, new string("Michael"));
	cout << endl<< "ID of student A is " << studentA.getId();
	cout << endl<< "Name of student A is " << *studentA.getName();
	Student studentB(-2, new string("AA"));



}