#include <iostream>
#include <string>
#include <string.h>
#include <iomanip>

using namespace std;

class TestChar {
	char* name = nullptr;
	static int BUFFER_MAX_SIZE;
public:

	void setName(char* name) {
		if (!name || name[0] == '\0') {
			delete[] this->name;
			this->name = nullptr;
			return;
		}
		delete[] this->name;
		this->name = new char[strlen(name) + 1];
		strcpy_s(this->name, strlen(name) + 1, name);
	}

	char* getName() {
		char* dummy = new char[strlen(this->name) + 1];
		strcpy_s(dummy, strlen(this->name) + 1, this->name);
		return dummy;
	}

	TestChar() {

	}

	TestChar(char* name) {
		setName(name);
	}

	~TestChar() {
		delete[] this->name;
	}
	
	friend istream& operator>>(istream& is, TestChar& c);
};

//istream& operator>>(istream& is, TestChar& c) {
//	cout << endl << "Enter name: ";
//	char buffer[100];
//	is.getline(buffer, 99);
//	c.setName(buffer);
//	cout << "Name entered: " << (c.name? c.name : "N/A");
//	return is;
//}

istream& operator>>(istream& is, TestChar& c) {
	
	char* buffer = new char[TestChar::BUFFER_MAX_SIZE+1];
	cout << endl << "Enter name (MAX "<<TestChar::BUFFER_MAX_SIZE<< " CHAR): ";
	is >> setw(TestChar::BUFFER_MAX_SIZE + 1);
	is.getline(buffer, TestChar::BUFFER_MAX_SIZE +1);
	c.setName(buffer);
	cout << "Name entered: " << (c.name ? c.name : "N/A");
	return is;
}

int TestChar::BUFFER_MAX_SIZE = 10;

int main() {
	TestChar a;
	cin >> a;
	cout<<endl<<a.getName();

}