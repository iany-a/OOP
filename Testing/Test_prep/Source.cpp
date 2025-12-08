#include <iostream>
#include <string>
#include <string.h>

using namespace std;


enum class Genre {
	Pop = 0,
	Rock = 1,
	Jazz = 2,
	Classical = 3,
	Electronic = 4
};



class MusicAlbum {
	string title = "";
	string artist = "";
	float price = 0.0f;
	int noSongs = 0;
	string* songs = nullptr;
	Genre genre = Genre::Electronic;
	static const int MIN_CHAR;
	static const int MAX_CHAR;
public:

	MusicAlbum() {

	}

	MusicAlbum(string title, float price) {
		setTitle(title);
		setPrice(price);
	}

	MusicAlbum(string title, string artist, float price, int noSongs, string* songs, Genre genre) {
		setTitle(title);
		this->artist = artist;
		if (genre == Genre::Electronic || genre == Genre::Pop) this->price = price * 65 / 100;
		else setPrice(price);
		setSongs(songs, noSongs);
		this->genre = genre;
	}

	void setTitle(string title) {
		if (title == "") throw "Invalid input.";
		this->title = title;
	}

	void setPrice(float price) {
		if (price < 1) throw "Invalid input.";
		this->price = price;
	}


	void setSongs(string* songs, int noSongs) {
		if (songs == nullptr || noSongs < 1) throw "Invalid input.";
		delete[] this->songs;
		this->songs = new string[noSongs];
		for (int i = 0; i < noSongs; i++) {
			if (songs[i].length() < MIN_CHAR || songs[i].length() > MAX_CHAR) throw "Invalid input.";
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

	

	void display() {
		cout << endl << "__________________";
		cout << endl << "Title: " << this->title;
		cout << endl << "Artist: " << this->artist;
		cout << endl << "Price: " << this->price;
		cout << endl << "No. songs: " << this->noSongs;
		if (this->noSongs > 0) {
			cout << endl << "Songs: "<<this->songs[0];
			for (int i = 1; i < this->noSongs; i++) {
				cout << ", " << this->songs[i];
			}
		}
		cout << endl << "Genre: ";
		switch (this->genre) {
		case Genre::Classical:
			cout << "Classical";
			break;
		case Genre::Electronic:
			cout << "Electronic";
			break;
		case Genre::Jazz:
			cout << "Jazz";
			break;
		case Genre::Pop:
			cout << "Pop";
			break;
		case Genre::Rock:
			cout << "Rock";
			break;
		default: cout << "Undefined";
		}
	}

	//destructor
	~MusicAlbum() {
		delete[] this->songs;
	}

	//copy constructor
	MusicAlbum(const MusicAlbum& b) {
		this->artist = b.artist;
		this->title = b.title;
		this->genre = b.genre;
		this->noSongs = b.noSongs;
		this->songs = new string[this->noSongs];
		for (int i = 0; i < this->noSongs; i++) {
			this->songs[i] = b.songs[i];
		}
		this->price = b.price;
	}

	bool isValuable() {
		if (this->noSongs >= 8 || (this->price / this->noSongs) < 10 || this->genre != Genre::Classical) return true;
		return false;
	}

		//Overload operator== to compare two albums for equality based on criteria you choose.
	bool operator==(MusicAlbum& m) {
		if (this->title == m.title && this->artist == m.artist && this->noSongs == m.noSongs) {
			int matchSong = 0;
			for (int i = 0; i < this->noSongs; i++) {
				if (this->songs[i] == m.songs[i]) matchSong++;
			}
			if (matchSong == this->noSongs) return true;
		}
		return false;
	}

		//Overload operator!= as the logical opposite of operator==.
	bool operator!=(MusicAlbum& m) {
		if (this->title == m.title && this->artist == m.artist && this->noSongs == m.noSongs) {
			int matchSong = 0;
			for (int i = 0; i < this->noSongs; i++) {
				if (this->songs[i] == m.songs[i]) matchSong++;
			}
			if (matchSong == this->noSongs) return false;
		}
		return true;
	}

		//Overload operator< to define an ordering between albums(e.g., by price or title).


		//Overload relational operators <= , >, >= by reusing your other comparison logic.


	//Overload the assignment operator operator= ensuring a proper deep copy of the dynamic array.
	MusicAlbum operator=(MusicAlbum& m) {
		this->artist = m.artist;
		this->title = m.title;
		this->genre = m.genre;
		this->noSongs = m.noSongs;
		delete[] this->songs;
		this->songs = new string[this->noSongs];
		for (int i = 0; i < this->noSongs; i++) {
			this->songs[i] = m.songs[i];
		}
		this->price = m.price;

		return *this;
	}

	//operator++ pre
	MusicAlbum& operator++() {
		this->price +=0.5f; //directly increment price
		return *this; //return altered object
	}

	//operator++ post
	MusicAlbum operator++(int) {
		MusicAlbum result = *this; //copy initial object state
		this->price +=0.5f; //increment original object
		return result; //return the initial object state
	}


	//Overload operator[] to access a song by its index, with bounds checking.
	string operator[](int index) {
		if (index <0 || index> this->noSongs-1) throw "Invalid input.";
		return this->songs[index];
	}

	//overload cast operator
	explicit operator float(){
		return this->price;
	}

	explicit operator string() {
		return this->songs[0];
	}


		//Overload operator+ to combine two albums into a new one(you decide how they merge).
	MusicAlbum operator+(MusicAlbum& m) {
		MusicAlbum newAlbum;
		int mergedSpace = this->noSongs + m.noSongs;
		newAlbum.noSongs = mergedSpace;
		delete[] newAlbum.songs;
		newAlbum.songs = new string[newAlbum.noSongs];
		for (int i = 0; i < this->noSongs; i++) {
			newAlbum.songs[i] = this->songs[i];
		}
		for (int i = this->noSongs; i < newAlbum.noSongs; i++) {
			newAlbum.songs[i] = m.songs[i-this->noSongs];
		}
		
		return newAlbum;
	}

		//Overload operator+= to append another album’s songs to the current one.


	


		//Overload unary operator! to return a condition about the album(invalid, empty, or another rule you define).
	bool operator!() {
		if (this->noSongs < 5) return true;
		return false;
	}

	friend ostream& operator<<(ostream& os, MusicAlbum& m);
	friend istream& operator>>(istream& is, MusicAlbum& m);
};

const int MusicAlbum::MIN_CHAR = 3;
const int MusicAlbum::MAX_CHAR = 40;

//Overload stream operators << and >> to output and input album data in a readable format.
ostream& operator<<(ostream& os, MusicAlbum& m) {
	os << endl << "__________________";
	os << endl << "Title: " << m.title;
	os << endl << "Artist: " << m.artist;
	os << endl << "Price: " << m.price;
	os << endl << "No. songs: " << m.noSongs;
	if (m.noSongs > 0) {
		os << endl << "Songs: " << m.songs[0];
		for (int i = 1; i < m.noSongs; i++) {
			os << ", " << m.songs[i];
		}
	}
	os << endl << "Genre: ";
	switch (m.genre) {
	case Genre::Classical:
		os << "Classical";
		break;
	case Genre::Electronic:
		os << "Electronic";
		break;
	case Genre::Jazz:
		os << "Jazz";
		break;
	case Genre::Pop:
		os << "Pop";
		break;
	case Genre::Rock:
		os << "Rock";
		break;
	default: os << "Undefined";
	}
	return os;
}



istream& operator>>(istream& is, MusicAlbum& m) {
	cout << endl << "__________________";
	cout << endl << "Title: ";
	getline(is >> ws, m.title);
	cout << endl << "Artist: ";
	getline(is >> ws, m.artist);
	cout << endl << "Price: ";
	is >> m.price;
	cout << endl << "No. songs: ";
	is >> m.noSongs;
	m.songs = new string[m.noSongs];
	if (m.noSongs > 0) {
		for (int i = 0; i < m.noSongs; i++) {
			cout<<endl << "Song " << i + 1 << " name: ";
			getline(is >> ws, m.songs[i]);
		}
	}
	int temp = 0;
	cout << endl << "Genre: ";
	cout << endl << "(0 - Pop, 1 - Rock, 2 - Jazz, 3 - Classical, 4 - Electronic) ";
	is >> temp;
	switch (temp) {
		case 0: m.genre = Genre::Pop; break;
		case 1: m.genre = Genre::Rock; break;
		case 2: m.genre = Genre::Jazz; break;
		case 3: m.genre = Genre::Classical; break;
		case 4: m.genre = Genre::Electronic; break;
		default: m.genre = Genre::Pop;
	}
	return is;
}



int main() {
	MusicAlbum a("What?", 34.5f);
	a.display();
	string songsArray[] = { "Song 1", "Song 2", "Song 3" };
	MusicAlbum b("Testing this", "Maydup Naem", 50.0f, 3, songsArray, Genre::Pop);
	b.display();

	if (b.isValuable()) cout <<endl<< "Album is valuable.";
	else cout <<endl<< "Album is not valuable.";

	MusicAlbum c(b);
	c.display();
	string songsArray2[] = { "Song 1", "Song 2", "Song 4" };
	c.setSongs(songsArray2, 3);
	c.display();
	if (c == b) cout << endl << "They match.";
	else cout << endl << "No match.";
	if (c != b) cout << endl << "No match.";
	else cout << endl << "They match";

	cout << c;

	//MusicAlbum d;
	//cin >> d;
	//cout << d;
	cout <<endl<< c[2];

	MusicAlbum e;
	e = c;
	cout << endl << float(e);
	++e;
	cout << endl << float(e);
	e++;
	cout << endl << float(e);
	if (!b) cout << endl << "Album has less than 5 songs.";
	else cout << endl << "Album has more than 5 songs.";
	cout << endl << string(b);

	cout << e;
	cout << b;
	MusicAlbum f = e + b;
	cout << f;
}
