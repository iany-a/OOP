#include <iostream>
#include <fstream>
#include <string>
using namespace std;
//
//class A {
//public:
//    A() {
//        cout << endl << "default constructor";
//    }
//    A(const A&) {
//        cout << endl << "c constructor";
//    }
//    ~A() {
//        cout << endl << "deconstructor";
//    }
//};
//
//int main() {
//    A a;
//    A* p = new A(a);
//    {
//        A b = *p;
//        A c(b);
//    }
//    delete p;
//    return 0;
//}

//class A {
//public:
//    A() { cout << endl << "default constructor"; }
//    A(const A&) { cout << endl << "c constructor"; }
//    ~A() { cout << endl << "deconstructor"; }
//};
//
//A f(A x) {
//    A y = x;
//    return y;
//}
//
//int main() {
//    A a;
//    A b = f(a);
//    return 0;
//}

//class A {
//public:
//    A() { cout << "C "; }
//    A(const A&) { cout << "CC "; }
//    ~A() { cout << "D "; }
//};
//
//int main() {
//    A a;
//    A b = a;
//    
//    float* grades = new float[9999];
//    cout << endl << sizeof(grades) << endl;
//    return 0;
//}

class A {
	char* name;
public:
	A(const char* n) {
		name = new char[strlen(n) + 1];
		strcpy_s(this->name, strlen(n) + 1, n);
	}
	void setName(const char* n) {
		name = new char[strlen(n) + 1];
		strcpy_s(this->name, strlen(n) + 1, n);
	}
	~A() { delete[] name; }
};

int main() {

}