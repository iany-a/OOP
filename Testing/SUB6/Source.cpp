#include <iostream>
#include <string>
#include <string.h>

using namespace std;

enum class cType {
	UNIVERSITY,
	CORPORATE,
	WORKSHOP
};


class Conference {
	const string name = "";
	int noSessions = 0;
	string* sessionTitles = nullptr;
	static int MAX_SESSIONS;
	static int MIN_ENUM_POS;
	static int MAX_ENUM_POS;
	cType type = cType::UNIVERSITY;
public:

	Conference(const string name): name(name) {};

	void setSessionTitles(int noSessions, string* sessionTitles) {
		if (noSessions > MAX_SESSIONS || noSessions <0) throw "Invalid arguments.";
		if (noSessions == 0) {
			delete[] this->sessionTitles;
			this->noSessions = 0;
			this->sessionTitles = nullptr;
			return;
		}
		delete[] this->sessionTitles;
		this->sessionTitles = new string[noSessions];
		for (int i = 0; i < noSessions; i++) {
			if (sessionTitles[i] == "") throw "Invalid arguments.";
			this->sessionTitles[i] = sessionTitles[i];
		}
		this->noSessions = noSessions;
	}

	Conference(const string name, int noSessions, string* sessionTitles, cType type) : name(name) {
		this->type = type;
		setSessionTitles(noSessions, sessionTitles);
	}

	Conference(const Conference& source) : name(source.name) {
		if (&source == this) return;
		this->type = source.type;
		if (source.noSessions == 0) {
			this->noSessions = 0;
			this->sessionTitles = nullptr;
		}
		else setSessionTitles(source.noSessions, source.sessionTitles);
	}

	~Conference() {
		cout << endl << "Deconstructor called for: " << this->name;
		delete[] this->sessionTitles;
		//this->sessionTitles = nullptr;
	}

	bool operator==(const Conference& secObj) {
		int counter = 0;
		if (this->noSessions == secObj.noSessions) {
			for (int i = 0; i < this->noSessions; i++) {
				if (this->sessionTitles[i] == secObj.sessionTitles[i]) {
					counter++;
					cout << endl;
					cout << "+1 match found";
				}
			}
			float half = this->noSessions / 2.0f;
			if (counter >= half) return true;
		}
		
		return false;
	}

	Conference operator+=(const string s) {
		Conference modObj(*this);
		if (s == "") throw "Invalid input.";
		for (int i = 0; i < this->noSessions; i++) {
			if (this->sessionTitles[i] == s) {
				cout <<endl<< "Duplicate found. Aborting.";
				return modObj;
			}
		}
		if (this->noSessions == MAX_SESSIONS) throw "Overflow error: Initial string array already at max capacity.";
		delete[] modObj.sessionTitles;
		modObj.sessionTitles = new string[this->noSessions+1];
		for (int i = 0; i < this->noSessions; i++) {
			modObj.sessionTitles[i] = this->sessionTitles[i];
		}
		modObj.sessionTitles[this->noSessions] = s;
		modObj.noSessions = this->noSessions + 1;
		return modObj;
	}

	string operator+(string s){
		if (this->noSessions >= 0) this->sessionTitles[0] += s;
		return this->sessionTitles[0];
	}

	int* countVocals() {
		int* counter = new int[this->noSessions];
		for (int i = 0; i < noSessions; i++) {
			counter[i] = 0;
			int n = this->sessionTitles[i].length() + 1;
			char* dummy = new char[n];
			strcpy_s(dummy, n, this->sessionTitles[i].c_str());
			for (int j = 0; j < strlen(dummy); j++) {
				if (strchr("AEIOUaeiou", dummy[j])) {
					counter[i]++;
				}
			}
			delete[] dummy;
			dummy = nullptr;
		}
		return counter;
	}

	void endsWithVocal() {
		for (int i = 0; i < noSessions; i++) { 
			
			int n = this->sessionTitles[i].length() + 1; 
			char* dummy = new char[n];
			strcpy_s(dummy, n, this->sessionTitles[i].c_str()); 
			if (strchr("AEIOUaeiou", dummy[n-2])) { 
				cout << this->sessionTitles[i] << ", ";
			}
			delete[] dummy;
			dummy = nullptr;
		}
	}

	void endsWithVocalPointer(string*& fixedString, int& fixedSize) {
		string* processedString = new string[this->noSessions];
		fixedSize = 0;
		for (int i = 0; i < noSessions; i++) {
			int n = this->sessionTitles[i].length() + 1;
			char* dummy = new char[n];
			strcpy_s(dummy, n, this->sessionTitles[i].c_str());
			if (strchr("AEIOUaeiou", dummy[n - 2])) {
				processedString[fixedSize] = this->sessionTitles[i];
				fixedSize++;
			}
			delete[] dummy;
			dummy = nullptr;
		}
		fixedString = new string[fixedSize];
		for (int i = 0; i < fixedSize; i++) {
			fixedString[i] = processedString[i];
		}
		
	}

	friend ostream& operator<<(ostream& os, const Conference& c);
	friend istream& operator>>(istream& is, Conference& o);

};

int Conference::MAX_SESSIONS = 100;
int Conference::MIN_ENUM_POS = 0;
int Conference::MAX_ENUM_POS = 2;

istream& operator>>(istream& is, Conference& o) {
	cout << endl << "Enter type (0 - University, 1 - Corporate, 2 - Workshop): ";
	int tempType = 0;
	is >> tempType;
	if (tempType < Conference::MIN_ENUM_POS || tempType > Conference::MAX_ENUM_POS) throw "Invalid input";
	switch (tempType) {
	case 0: o.type = cType::UNIVERSITY; break;
	case 1: o.type = cType::CORPORATE; break;
	case 2: o.type = cType::WORKSHOP; break;
	default: o.type = cType::UNIVERSITY;
	}
	cout << endl << "Enter size of array: ";
	is >> o.noSessions;
	if (o.noSessions < 0) throw "Invalid input.";
	if (o.noSessions == 0) {
		o.sessionTitles = nullptr;
		return is;
	}
	else {
		o.sessionTitles = new string[o.noSessions];
		for (int i = 0; i < o.noSessions; i++) {
			cout << "Enter element " << i + 1 << ": ";
			getline(is >> ws, o.sessionTitles[i]);
		}
	}

	return is;
}

ostream& operator<<(ostream& os, const Conference& c) {
	os << endl << "_____________________";
	os << endl << "Object name: " << c.name;
	os << endl << "Object type: ";
	switch (c.type) {
	case cType::UNIVERSITY: cout << "University"; break;
	case cType::WORKSHOP: cout << "Workshop"; break;
	case cType::CORPORATE: cout << "Corporate"; break;
	default: cout << "Unspecified";
	}
	os << endl << "Number of sessions: " << c.noSessions;
	if (c.noSessions > 0) {
		os << endl << "Sessions: " << c.sessionTitles[0];
		for (int i = 1; i < c.noSessions; i++) os << ", " << c.sessionTitles[i];
	}
	return os;
}


int main() {
	string array[3] = { "AAA", "BBB", "CCC" };
	int size = 3;
	Conference a("Test A", size, array, cType::UNIVERSITY);
	a.setSessionTitles(0, nullptr);
	cout << a;
	a.setSessionTitles(size, array);
	cout << a;

	Conference* b = new Conference("Test B", 0, nullptr, cType::WORKSHOP);
	cout << *b;
	delete b;
	b = nullptr;

	Conference c(a);
	cout << c;
	string array2[3] = { "CCC", "BBB", "AAA" };
	c.setSessionTitles(3, array2);
	if (c == a) cout << endl << "Match";
	else cout << endl << "No match";

	//cout << (a += "DDD");
	//Conference d("Test D");
	//cin >> d;
	//cout << d;
	
	string str = "c";
	a + str;
	cout << a;
	string arrayV[10] = { "ari", "KGL", "OFU", "wir", "EOT", "wor", "WOR", "wpd", "wot", "PSJ" };
	Conference v("Test V", 10, arrayV, cType::UNIVERSITY);
	cout << v << endl;
	for (int i = 0; i < 10; i++) {
		cout << v.countVocals()[i] << ", ";
	}
	cout << endl;
	//v.endsWithVocal();

	string* fixedString = nullptr;
	int arrayFixedSize = 0;
	v.endsWithVocalPointer(fixedString, arrayFixedSize);
	for (int i = 0; i < arrayFixedSize; i++) {
		cout << fixedString[i] << ", ";
	}
	
}


