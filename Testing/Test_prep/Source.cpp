#include <iostream>
#include <string>
#include <string.h>

using namespace std;

enum class Genre {
	Pop,
	Rock,
	Jazz,
	Classical,
	Electronic
};


class MusicAlbum {
	string title = "";
	string artist = "";
	float price = 0.0f;
	int noSongs = 0;
	string* songs = nullptr;
	Genre genre = Genre::Electronic;
public:

	void setSongs(string* songs, int noSongs) {
		if (songs == nullptr || noSongs < 1) throw "Invalid input.";
		delete[] this->songs;
		this->songs = new string[noSongs];
		for (int i = 0; i < noSongs; i++) {
			this->songs[i] = songs[i];
		}
		this->noSongs = noSongs;
	}
	
	
	string* getSongs() {
		string* dummy = new string[this->noSongs];
		for (int i = 0; i < this->noSongs; i++) {
			dummy[i] = this->songs[i];
		}
		return dummy;
	}



};


int main() {

}
