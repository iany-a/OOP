#include <iostream>
#include <string>
#include <fstream> //important

using namespace std;

enum EngineType {GASOLINE, 
				DIESEL, 
				ELECTRIC};

class DeliveryVan {
	EngineType type = EngineType::ELECTRIC;
	string* addresses = nullptr;
	int noAddresses = 0;
	string driverName = "";
	float km = 0.0f;
public:
	DeliveryVan() {
		this->driverName = "John Doe";
	}

	DeliveryVan(string driverName, float km, EngineType type, string* addresses, int noAddresses): driverName(driverName), km(km), type(type){
		this->addresses = new string[noAddresses];
		for (int i = 0; i < this->noAddresses; i++) {
			this->addresses[i] = addresses[i];
		}
		this->noAddresses = noAddresses;
	}

	//avoid the default copy constructor for this example

	~DeliveryVan() {
		delete[] this->addresses;
	}
	
	friend void operator<<(ofstream& file, DeliveryVan& van);

	//method for serializing an object into a binary file
	//file.write ( cast to char, get address from this->variable with &, second parameter is sizeof(type of variable)
	void serialize(ofstream& file) {
		//write the van km
		file.write((char*)&this->km, sizeof(float));
		//write the type
		file.write((char*)&this->type, sizeof(EngineType)); //no class:: as you are inside the class already
		//write the driver name
		//write the size of the name - you need this later when reading from file
		int nameSize = this->driverName.size() + 1; //need to add one for the extra \0
		file.write((char*)&nameSize, sizeof(int));
		file.write(this->driverName.c_str(), sizeof(char) * nameSize); //this returns a char*, no need to cast or to reference
		//write the addresses number
		file.write((char*)&this->noAddresses, sizeof(int));
		//write the addresses
		for (int i = 0; i < this->noAddresses; i++) {
			int addressSize = this->addresses[i].size() + 1; //need to add one for the extra \0
			file.write((char*)&addressSize, sizeof(int));
			file.write(this->addresses[i].c_str(), sizeof(char) * addressSize); //this returns a char*, no need to cast or to reference
		}
	}

};

void operator<<(ofstream& file, DeliveryVan& van) {
	file << "Van data: Engine" << van.type << "km" << van.km;
	file << endl << "Driver: " << van.driverName;
	if (van.noAddresses > 0) {
		file << endl << "Addresses: ";
		for (int i = 0; i < van.noAddresses; i++) {
			file << " " << van.addresses[i];
		}
	}
}



int main() {
	string destinations[3] = { "Piata Romana", "Piata Victoriei", "Piata Unirii" };
	DeliveryVan fan1("John", 1300, EngineType::GASOLINE, destinations, 3);

	//text files - PREREQUISITE: INCLUDE FSTREAM LIBRARY!!!
	// ios::bin for binary, no ios specific category for txt files
	// ios::ate is default for truncate
	// ios::app is append, need to be manually input
	ofstream reportFile("Vans.txt", ios::app);
	if (!reportFile.is_open()) { //validation checking if the file is NOT open
		cout << endl << "***********ISSUES with the file***********";
	}
	else {
		reportFile << "\n\t\t Vans List:"; //new line, tab, tab
		reportFile << fan1;
		reportFile.close();

	}

	//binary files
	ofstream backupFile("backup.van", ios::binary | ios::ate);
	if (backupFile.is_open()) {
		fan1.serialize(backupFile);
		backupFile.close();
	}
	else {
		cout << endl << "Backup file corrupted.";
	}

}