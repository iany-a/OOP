#include <iostream>
#include <string>
#include <string.h>

//after operators: files, inheritance
//this file is for operators

using namespace std;

class VideoGame {
	char* description = nullptr;
	float price = 0.0f;
	const string name = "";

public:
	VideoGame(string name, float price): name(name), price(price) { //no const needed for non-pointer parameters
		//const only prevents modifying the source value inside the function calling it
	}

	VideoGame(const VideoGame& game) : name(game.name), price(game.price) { //don't add the description param
		if (game.description == nullptr) this->description = nullptr; //validation for nullptr
		else {
			this->description = new char[strlen(game.description) + 1]; //strlen can not read nullptr
			strcpy_s(this->description, strlen(game.description) + 1, game.description);
		}
	}




	~VideoGame() {
		delete[] this->description;
	}

	//overload =
	void operator=(const VideoGame& v2) { //avoid tripping the copy constructor by calling the object by reference
		//validation: test if objects are the same before proceeding
		if (this == &v2) {
			return;
		}
		//in = you can't copy the const attributes
		this->price = v2.price;
		delete[] this->description; //operator= always creates memory leaks for dynamic fields.
		if (v2.description == nullptr) {
			this->description = nullptr;
		}
		else {
			this->description = new char[strlen(v2.description) + 1];
			strcpy_s(this->description, strlen(v2.description) + 1, v2.description);
		}
	}

	//overload << will not work inside the class due to "this" pointer
	/*void operator<<(const VideoGame& game) {

	}*/
	friend void operator<<(ostream& console, const VideoGame& game); //friend is not a good practice code, but it's faster than
	//creating getters
	
};

//overload the operator as global method due to first parameter not being a class object
void operator<<(ostream& console, const VideoGame& game) { //always use address of the bufffer
	console << endl<< "Game name: " << game.name;
	console << endl<< "Game price: " << game.price;
	if (game.description != nullptr) {
		console << endl << "Game description: " << game.description;
	}
}


int main() {
	VideoGame fifa("FIFA 2026", 250);
	VideoGame fifaCopy = fifa; //crashes without copy constructor declaration

	//operators - defined inside the class if the first parameter is a class object. if not, defined globally.
	// = operator
	fifaCopy = fifa; //mandatory

	//stream operators
	cout << fifa; //output operator
	//cin >> fifa; //input operator

	////math operators
	////group 1: 1 parameter
	//fifa++; //post increment, similar with --
	//++fifa; //pre increment, similar with --

	////group 2: 2 parameters +, -, *, / all work in the same way
	//VideoGame newGame = fifa + 23; //take the fifa videogame and add 23 to the price
	//newGame = 10 + fifa;
	//fifa = fifa + "A new game for 2026"; //add a description
	////same for  *=, /=, +=, -=
	//fifa *= 1.5; //multiply the price by 1.5

	////logic operators
	//// !, >, <, ==, >=, <=
	//if (!fifa) { //price not greater than 500
	//	//logic here;
	//	cout << endl << "Price is less than 500";
	//}
	//else cout << endl << "It's an expensive game.";

	//if (fifa == newGame) {
	//	cout << endl << "Same game by name and price.";
	//}
	//else cout << endl << "Different games.";

	////cast operator
	//float price = (float)fifa; //try to convert object to float, and set that value as the price
	//
	////function operator
	//bool priceIsInRange = fifa(100, 500); //return a boolean based on the condition that the price is between 100 and 500

	////index operator - setter and getter behavior
	//char descriptionCharacter = fifa[2]; //gets the 3rd char in the description. object acts like an array, but does not convert
	//fifa[2] = 'X'; //setter behavior




}

