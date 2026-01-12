#include <iostream>
#include <string>

using namespace std;

//virtual methods
//frameworks

//Inheritance (is-a)
//Vehicle (parent class) -> Electric: Battery capacity, 
//						 -> Thermal-Combustion: Engine capacity, consumption per km

//has-a is composition, not in this example.


class Vehicle {
	string registrationNumber = "";
	float km = 0;

public:
	virtual void getDescription() {
		cout << endl << "It's a vehicle";
	}

};

class ElectricVehicle: public Vehicle {
	float batteryCapacity = 0;
public:
	//parent class method override = has the same header with the same parameters (if any). 
	//If you modify the parameters list, it's called overloading (just like for operators).
	void getDescription() {
		cout << endl << "It's an electric vehicle";
	}
};

class InternalCombustionVehicle: public Vehicle {
	int engineCapacity = 0;
	float litersPerKm = 0.0f;
public:
	void getDescription() {
		cout << endl << "It's an internal combustion vehicle";
	}
};



int main() {
	Vehicle v;
	v.getDescription();
	ElectricVehicle ev;
	ev.getDescription();
	InternalCombustionVehicle icv;
	icv.getDescription();

	//upcasting
	v = ev;
	//downcasting - does not work
	//ev = v;

	Vehicle vehicles[3]; //static array of objects - this solution will never work.
	vehicles[0] = v;
	vehicles[1] = ev;
	vehicles[2] = icv;
	//this will only copy the parent class attributes and methods in the array objects. Everything else defined in the child classes is lost.

	Vehicle* vehiclesPtr[3]; //array of pointers to objects
	vehiclesPtr[0] = &v; //copy only the address
	vehiclesPtr[1] = &ev; //copy only the address
	vehiclesPtr[2] = &icv; //copy only the address

	//**********in C#, JAVA, PYTHON, all declarations are pointers without the special annotation.

	cout << endl << "_________________________________________________";
	for (int i = 0; i < 3; i++) {
		vehiclesPtr[i]->getDescription();
	}
	


}