#include <iostream>
#include <string>
#include <string.h>

using namespace std;

enum class TourT {
	LOCAL = 0,
	COUNTRY = 1,
	WORLD = 2
};

class GameT {
	const string name = "";
	int noPlayers = 0;
	int* scores = nullptr;
	static int MAX_PLAYERS;
	static int MAX_SCORE;
	static int MIN_SCORE;
	TourT type = TourT::LOCAL;
public:

	void setScores(int noPlayers, int* scores) {
		if (noPlayers > MAX_PLAYERS || noPlayers < 0) throw "Invalid arguments.";
		delete[] this->scores;
		this->scores = new int[noPlayers];
		for (int i = 0; i < noPlayers; i++) {
			if (scores[i] <MIN_SCORE || scores[i] > MAX_SCORE) throw "Invalid arguments.";
			this->scores[i] = scores[i];
		}
		this->noPlayers = noPlayers;
	}

	GameT(const string name, int noPlayers, int* scores, TourT type) : name(name) {
		setScores(noPlayers, scores);
		this->type = type;
	}

	GameT(const GameT& source) : name(source.name) {
		this->noPlayers = source.noPlayers;
		this->type = source.type;
		if (this->noPlayers == 0) this->scores = nullptr;
		else {
			this->scores = new int[noPlayers];
			for (int i = 0; i < noPlayers; i++) {
				if (source.scores[i] <MIN_SCORE || source.scores[i] > MAX_SCORE) throw "Invalid arguments.";
				this->scores[i] = source.scores[i];
			}
		}
		cout << endl << "Copy constructor finished executing for object " << this->name;
	}

	GameT() :name(name) {
		this->type = TourT::LOCAL;
		this->noPlayers = 0;
		this->scores = nullptr;
	}

	void display() {
		cout << endl << "_________________________";
		cout << endl << "Printing object details: ";
		cout << endl << "Name: " << this->name;
		cout << endl << "No. players: " << this->noPlayers;
		if (this->noPlayers > 0) {
			cout << endl << "Scores list: ";
			cout << this->scores[0];
			for (int i = 1; i < this->noPlayers; i++) cout << ", " << this->scores[i];
		}
		cout << endl << "Type: ";
		switch(this->type) {
		case TourT::COUNTRY: cout << "Country"; break;
		case TourT::LOCAL: cout << "Local"; break;
		case TourT::WORLD: cout << "World"; break;
		default: cout << "N/A"; break;
		}
	}

	////post
	//GameT operator++(int) {
	//	GameT temp = *this;
	//	for (int i = 0; i < this->noPlayers; i++) {
	//		this->scores[i] += 5;
	//		if (this->scores[i] > 100) this->scores[i] = 100;
	//	}
	//	return temp;
	//}

	//pre
	GameT operator++(){
		for (int i = 0; i < this->noPlayers; i++) {
			this->scores[i] += 5;
			if (this->scores[i] > 100) this->scores[i] = 100;
		}
		return *this;
	}


	GameT operator*=(double factor) {
		if (factor <= 0) throw "Invalid arguments.";
		if (factor > 1.0) {
			for (int i = 0; i < this->noPlayers; i++) {
				this->scores[i] /= factor;
			}
		}
		if (factor <=1.0){
			for (int i = 0; i < this->noPlayers; i++) {
				this->scores[i] *= 1/factor;
				if (this->scores[i] > MAX_SCORE) this->scores[i] = 100;
			}
		}
		
		
		return *this;
	}

	//extra operator to verify if the objects are the same
	bool operator==(const GameT& source) {
		int counter = 0;
		if (this->name == source.name && this->type == source.type){
			for (int i = 0; i < this->noPlayers; i++) {
				if (this->scores[i] == source.scores[i]) counter++;
			}
		}
		if (counter == this->noPlayers) return true;
		return false;
	}

	//extra operator to check what value is at a specific index
	int operator[](int index) {
		if (index > this->noPlayers || this->scores == nullptr) throw "Invalid arguments.";
		return this->scores[index];
	}

	//extras operator to compute average of points from one object
	double operator()() {
		if (noPlayers == 0) return -1;
		double sum = 0;
		for (int i = 0; i < this->noPlayers; i++) sum += this->scores[i];
		return sum / this->noPlayers;
	}

	//extra operator to merge two objects into one
	GameT operator+(const GameT& secObj) {
		GameT finalObj = *this;
		finalObj.noPlayers = this->noPlayers + secObj.noPlayers;
		if (finalObj.noPlayers > MAX_PLAYERS) finalObj.noPlayers = 100;
		delete[] finalObj.scores;
		finalObj.scores = new int[finalObj.noPlayers];
		for (int i = 0; i < this->noPlayers; i++) {
			finalObj.scores[i] = this->scores[i];
		}
		for (int i = 0; i < secObj.noPlayers; i++) {
			finalObj.scores[i+this->noPlayers] = secObj.scores[i];
		}
		return finalObj;
	}

	//extra operator to substract values (obj1 - obj 2), but ignore extra members as the objects can have different lengths

	GameT operator-(const GameT& secObj) {
		GameT finalObj = *this;
		for (int i = 0; i < this->noPlayers; i++) {
			if (this->scores[i] < secObj.scores[i] || i>=secObj.noPlayers) finalObj.scores[i] = 0;
			else finalObj.scores[i] = this->scores[i] - secObj.scores[i];
		}
		return finalObj;
	}

	//extra cast operators
	explicit operator float() {
		return this->scores[0];
	}


	friend ostream& operator<<(ostream& os,const GameT& source);
	friend istream& operator>>(istream& is, GameT& out);
};

ostream& operator<<(ostream& os,const GameT& source) {
	os << endl << "_________________________";
	os << endl << "Printing object details: ";
	os << endl << "Name: " << source.name;
	os << endl << "No. players: " << source.noPlayers;
	if (source.noPlayers > 0) {
		os << endl << "Scores list: ";
		os << source.scores[0];
		for (int i = 1; i < source.noPlayers; i++) cout << ", " << source.scores[i];
	}
	cout << endl << "Type: ";
	switch (source.type) {
	case TourT::COUNTRY: cout << "Country"; break;
	case TourT::LOCAL: cout << "Local"; break;
	case TourT::WORLD: cout << "World"; break;
	default: cout << "N/A"; break;
	}
	return os;

}

istream& operator>>(istream& is, GameT& out) {
	//string tempName;
	//cout << endl<< "Enter object title: ";
	//getline(is>>ws, tempName);
	unsigned int temp = 0;
	cout << endl << "Enter object type (0-LOCAL, 1-COUNTRY, 2-WORLD) : ";
	is >> temp;
	switch (temp) {
	case 0: out.type = TourT::LOCAL; break;
	case 1: out.type = TourT::COUNTRY; break;
	case 2: out.type = TourT::WORLD; break;
	default: out.type = TourT::LOCAL;
	}
	cout << endl << "Enter players count: ";
	is >> out.noPlayers;
	if (out.noPlayers == 0) out.scores = nullptr;
	if (out.noPlayers > 0) {
		out.scores = new int[out.noPlayers];
		for (int i = 0; i < out.noPlayers; i++) {
			cout << endl << "Enter score for player " << i+1<<": ";
			is >> out.scores[i];
		}
	}
	return is;
}


int GameT::MAX_PLAYERS = 100;
int GameT::MAX_SCORE = 100;
int GameT::MIN_SCORE = 0;


int main() {
	const int size = 3;
	int scores[size] = { 50, 40, 60 };
	int scores2[size] = { 60, 70, 80 };
	GameT a("Test A", size, scores, TourT::COUNTRY);
	a.display();
	GameT b(a);
	b.setScores(size, scores2);

	GameT* c = new GameT(b);
	c->display();
	delete c;
	c = nullptr;
	GameT* d = new GameT("Test D", size, scores2, TourT::WORLD);
	d->display();
	delete d;
	d = nullptr;

	GameT pre = ++a;
	pre.display();
	//GameT post = a++;
	//post.display();

	a *= 0.75;
	a.display();

	GameT x(a);
	x.setScores(size, scores);
	x.display();
	if (a == x) cout<<endl<<"Match";
	else cout<<endl<<"No match";

	cout << x << endl;

	//GameT y;
	//cin >> y;
	//cout << y;
	cout << a << endl;
	cout << a[2];

	//GameT z;
	//cout << endl << z();

	//double avg = a();
	//cout << endl << avg;

	//int scores3[4] = { 100, 100, 100, 100 };
	//GameT biggerObject("Test long", 4, scores3, TourT::COUNTRY);

	////(x + a).display();
	////(a - x).display();
	//(a - biggerObject).display();
	//(biggerObject-a).display();

	cout<<endl<< float(a);

}