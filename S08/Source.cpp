#include <iostream>
#include <string>
#include <string.h>

using namespace std;

//static variables vs magic numbers
//constant static variables
//static methods
//constant attributes
//memory leaks
//destructor
//copy constructor

class StringUtils {
public:
	static string* copyStringArray(string* values, int noValues) { //static method = does not require an object to be created
		string* copy = new string[noValues];
		for (int i = 0; i < noValues; i++) {
			copy[i] = values[i];
		}
		return copy;
	}

};


class VideoGame {
	string* hallOfFame = nullptr;
	int noPlayers = 0;
	const string name = ""; //for constant, to not forget about it, put no default value
	float price = 0;
	static float TOTAL_VALUE; //sum of all video games prices

public:

	//for arrays, always set the values array and size in the same setter, but implement two individual getters
	void setHallOfFame(string* values, int noValues) {
		//avoid memoryleak
		//every time we change the address of the object, make sure to delete previous pointer memory
		if (this->hallOfFame != nullptr) delete[] this->hallOfFame;

		this->hallOfFame = StringUtils::copyStringArray(values, noValues);
		this->noPlayers = noValues;
	}

	string* getHallOfFame() {
		return StringUtils::copyStringArray(this->hallOfFame, this->noPlayers); //this is awesome
	}

	int getNoPlayers() {
		return this->noPlayers;
	}

	void print() {
		cout << endl << "Video game: " << this->name;
		cout << endl << "Hall of fame: ";
		for (int i = 0; i < this->noPlayers; i++) {
			cout << ", " << this->hallOfFame[i];
		}
	}


	VideoGame():name("") { //default constructor with initialized const value

	}

	~VideoGame() {
		delete[] this->hallOfFame;
	}

	//copy constructor
	VideoGame(const VideoGame& game): name(game.name) {
		this->price = game.price;
		this->hallOfFame = StringUtils::copyStringArray(game.hallOfFame, game.noPlayers);
		this->noPlayers = game.noPlayers;
		//this->name = game.name; does not work for constant values, use the name(game.name) outside the parameter list to define it
	}

};

float VideoGame::TOTAL_VALUE = 0;


int main() {
	VideoGame wow;
	wow.print();

	string topPlayers[3] = {"John", "Alice", "Bob"};
	wow.setHallOfFame(topPlayers, 3);
	wow.print();

	VideoGame starcraft;
	starcraft.setHallOfFame(topPlayers, 3);
	starcraft.print();

}