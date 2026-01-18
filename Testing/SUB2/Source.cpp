#include <iostream>
#include <string>

using namespace std;

enum class ExchangeType{
	NYSE,
	NASDAW,
	TSE
};



class StockBroker {
	string name = "";
	int noShares = 0;
	bool* areProfitable = nullptr;
	static int BREAKING_POINT_VALUE;
	ExchangeType type = ExchangeType::NYSE;
public:

	StockBroker(string name, int noShares, bool* areProfitable, ExchangeType type) {
		this->name = name;
		setAreProfitable(areProfitable, noShares);
		this->type = type;
	}
	
	
	void setAreProfitable(bool* areProfitable, int noShares) {
		if (areProfitable == nullptr || noShares < 1) throw "Invalid arguments.";
		delete[] this->areProfitable;
		this->areProfitable = new bool[noShares];
		float sum = 0;
		for (int i = 0; i < noShares; i++) {
			sum+= areProfitable[i]; 
		}
		float checkShare = (sum / noShares) * 100;
		cout <<endl<< checkShare;
		if (checkShare < BREAKING_POINT_VALUE) throw "Shares not profitable.";

		for (int i = 0; i < noShares; i++) {
			this->areProfitable[i] = areProfitable[i];
		}
		this->noShares = noShares;
		
	}

	void setName(string name) {
		this->name = name;
	}

	StockBroker(const StockBroker& source) {
		this->name = source.name;
		setAreProfitable(source.areProfitable, source.noShares);
		this->type = source.type;
	}

	void display() {
		cout << endl << "Object details:";
		cout << endl << "Object name: " << this->name;
		cout << endl << "Object shares: " << this->areProfitable[0];
		for (int i = 1; i < this->noShares; i++) cout << ", " << this->areProfitable[i];
		cout << endl << "Object type: ";
		switch (this->type) {
		case ExchangeType::NYSE: cout << "NYSE";
			break;
		case ExchangeType::NASDAW: cout << "NASDAW";
			break;
		case ExchangeType::TSE: cout << "TSE";
			break;
		default: cout << "UNSPECIFIED";
		}
	}


	~StockBroker() {
		cout << endl << "Destructor called for object " << this->name;
		delete[] this->areProfitable;
		
	}

	bool operator>(int value) {
		int sum = 0;
		for (int i = 0; i < this->noShares; i++) {
			if (this->areProfitable[i] == 1) sum++;
		}
		if (sum > value) return true;
		return false;
	}

	StockBroker operator+(bool share) {
		if (share != 1 && share != 0) throw "Invalid input.";
		StockBroker newObj = *this;
		float sum = 0.0f;
		for (int i = 0; i < this->noShares; i++) {
		   if (this->areProfitable[i] == 1) sum++;
		}
		if (share) sum += share;
		float checkShare = (sum / (this->noShares + 1)) * 100;
		cout << endl << checkShare;
		if (checkShare < BREAKING_POINT_VALUE) {
			cout <<endl<< "Case unhappy";
			bool* dummy = new bool[this->noShares + 1];
			for (int i = 0; i < this->noShares; i++) {
				dummy[i] = this->areProfitable[i];
			}
			dummy[this->noShares] = share;
			newObj.setAreProfitable(dummy, this->noShares + 1);
		}
		else {
			cout <<endl<< "Case happy";
			bool* dummy = new bool[(this->noShares + 1)*2];
			for (int i = 0; i < this->noShares; i++) {
				dummy[i] = this->areProfitable[i];
			}
			dummy[this->noShares] = share;
			for (int i = noShares+1; i < (this->noShares+1)*2; i++) {
				dummy[i] = this->areProfitable[i-noShares-1];
			}
			dummy[(this->noShares + 1) * 2-1] = share;


			newObj.setAreProfitable(dummy, (noShares + 1) * 2);
		}
		return newObj;
	}

};

int StockBroker::BREAKING_POINT_VALUE = 65;


int main() {
	bool shares[6] = { 1, 1, 0, 1, 1, 0};


	StockBroker a("Test A", 6, shares, ExchangeType::NASDAW);

	a.display();

	StockBroker b(a);
	b.setName("Test B");
	b.display();
//	b->~StockBroker();

	StockBroker* c = new StockBroker("Test C", 6, shares, ExchangeType::TSE);
	delete c;
	c = nullptr;
	cout << endl;
	if (a > 4) cout << "Yes";
	else cout << "No";


	StockBroker d = a + 1;
	d.setName("Test D");
	d.display();

}