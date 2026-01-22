#pragma once
#include <iostream>
#include <string>
#include <stdexcept>

using namespace std;

class Book {
private:
    const int id = 0;
    std::string title = "";
    std::string* authors = nullptr;
    int authorCount = 0;
    int pages = 0;
    //i've added this static field manually, not sure if it's correct
    static int ID_COUNTER;

	// Method to be used to copy authors from one array to another
    void copyAuthors(const std::string* src, int count) {
        if (src == nullptr || count < 0) throw "Invalid input data.";
        delete[] this->authors;
        string* copyArray = new string[count];
        for (int i = 0; i < count; i++) {
            copyArray[i] = src[i]; //i don't understand why this warning keeps showing, it has enough memory to store the array
        }
        this->authors = copyArray;
        this->authorCount = count;
    }

 
public:
    // Default Constructor
	// Inits the title to "Unknown", authors to nullptr, authorCount to 0, pages to 0 and id to 0
    Book(): id(0){
        this->title = "Unknown";
        this->authors = nullptr;
        this->authorCount = 0;
        this->pages = 0;
    }

    // Parameterized Constructor
	// Don't do shallow copy of authors
    Book(int id, const std::string& title, const std::string* authors, int authorCount, int pages): id(++ID_COUNTER){
        setTitle(title);
        copyAuthors(authors, authorCount);
        setPages(pages);
    }

    //remade the constructor without the ID parameter
    Book(const std::string& title, const std::string* authors, int authorCount, int pages) : id(++ID_COUNTER) {
        setTitle(title);
        copyAuthors(authors, authorCount);
        setPages(pages);
    }

    //setters
    void setTitle(string title) {
        if (title == "") throw "Invalid input.";
        this->title = title;
    }


    void setPages(int pages) {
        if (pages <= 0) throw "Invalid input.";
        this->pages = pages;
    }

    // Copy Constructor
    Book(const Book& other): id(++ID_COUNTER) {
        this->title = other.title;
        copyAuthors(other.authors, other.authorCount);
        this->pages = other.pages;
    }

    // Destructor
    ~Book() {
        delete[] this->authors;
        --ID_COUNTER;
    }

    // Assignment Operator
	Book& operator=(const Book& other) {
        delete[] this->authors;
        this->title = other.title;
        copyAuthors(other.authors, other.authorCount);
        this->pages = other.pages;
		return *this;
    }

    int getPages() const {
        return this->pages;
    }

    int getID() {
        return this->id;
    }

    // Check if a name is an author of the book
    bool isAuthor(const std::string& name) const {
        for (int i = 0; i < this->authorCount; i++) {
            if (this->authors[i] == name) return true;
        }
        return false;
    }

    // Returns the position of an author in the list, or -1 if not found
    int getAuthorPosition(const std::string& name) const {
        for (int i = 0; i < this->authorCount; i++) {
            if (this->authors[i] == name) return i;
        }
        return -1;
    }

    // Display details at the console
    void display() {
        cout << endl << "_________________________________________";
        cout << endl << "Book " << this->title << " details: ";
        cout << endl << "ID: " << this->id;
        cout << endl << "Title: " << this->title;
        cout << endl << "Author(s): ";
        for (int i = 0; i < this->authorCount; i++) {
            cout << authors[i] << ", ";
        }
        cout << endl << "Number of author(s): " << this-> authorCount;
        cout << endl << "Number of pages: " << this->pages;
    }

    //overload operator+
    Book operator+(int pages) {
        Book result = *this; //book 5
        //ID_COUNTER--; //return to ID previous version to avoid unnecessary IDs being generated - in destructor
        result.pages += pages;
        return result;
    }

    //overload operator+=
    Book& operator+=(int extraPages) {
        this->pages += extraPages;
        return *this;
    }

  
    //overload operator==
    bool operator==(const Book& other) {
        if (this->title == other.title && this->authorCount == other.authorCount && this->pages == other.pages) {
            for (int i = 0; i < this->authorCount; i++) {
                if (this->authors[i] == other.authors[i]) return true;
            }
        }
        return false;
    }

    //overloat operator>
    bool operator>(const Book& other) {
        if (this->pages == other.pages) return false;
        if (this->pages > other.pages) return true;
        return false;
    }

    //overload operator!
    bool operator!() {
        if (this->authors == nullptr) return true;
        return false;
    }

    //overload operator++
    Book& operator++() {
        this->pages += 1;
        return *this;
    }

    Book operator--(int) {
        Book result = *this;
        this->pages -=1;
        return result;
    }

    string operator[](int index) {
        if (index<0 || index>this->authorCount - 1) throw "Invalid input.";
        return this->authors[index];
    }

    int operator()() {
        return this->pages;
    }

    string operator()(int index) {
        if (index<0 || index>this->authorCount - 1) throw "Invalid input.";
        return this->authors[index];
    }

    explicit operator string() {
        return this->title;
    }
    explicit operator int() {
        return this->authorCount;
    }
 
    friend Book operator+(int pages, Book book);
    friend ostream& operator<<(ostream& os, const Book& book);
    friend istream& operator>>(istream& is, Book& book);
};

int Book::ID_COUNTER = 0;

Book operator+(int pages, Book book) {
    Book result = book;
    //--Book::ID_COUNTER; //same logic as previously stated - in destructor
    result.pages += pages;
    return result;
}

ostream& operator<<(ostream& os, const Book& book) {
    os << endl << "ID: " << book.id;
    os<<endl<< "Title: " << book.title;
    os << endl << "Authors: ";
    for (int i = 0; i < book.authorCount; i++) {
        os << book.authors[i] << ", ";
    }
    os << endl << "Number of authors: " << book.authorCount;
    os << endl << "Number of pages: " << book.pages;
    return os;
}

istream& operator>>(istream& is, Book& book) {
    cout<<endl<< "Enter title: ";
    getline(is >>ws, book.title);
    cout << endl << "Enter number of authors: ";
    is >> book.authorCount;
    delete[] book.authors;
    book.authors = new string[book.authorCount];
    for (int i = 0; i < book.authorCount; i++) {
        cout << "Enter author " << i + 1 << ": ";
        getline(is>>ws, book.authors[i]);
    }
    cout<<endl<< "Enter number of pages: ";
    is >> book.pages;
    return is;

}

int main() {
    Book a; //id 0 from default constructor
    a.display();
    string authors[] = { "James Cameron", "Veni Abened" };
    string authors1[] = { "Daniel Manchester", "Reinier Zonneveld", "Oliver Huntemann"};
    Book b0("Book 0", authors, 2, 250); // id 1
    b0.display();
    cout << endl << "Is Veni Abened one of the authors?";
    if (b0.isAuthor("Veni Abened")) {
        cout << endl << "Yes, on position " << b0.getAuthorPosition("Veni Abened");
    }
    else cout << endl << "No.";

    Book b1("Book 1", authors1, 3, 220); //id 2
    b1.display();

    a = b1; //id remains 0
    a.display();

    Book b2 = b1 + 50;  // Add pages //id 3
    //b1.display();
    b2.display();

    Book b3 = 100 + b1; // Add pages with int on the left //id 4
    b3.display();

    b1 += 20;           // Increase pages //id 2
    b1.display();

    cout<<endl << "Are b1 and b2 equal? " << (b1 == b2 ? "Yes" : "No") << "\n";
    cout << "Is b1 greater than b2? " << (b1 > b2 ? "Yes" : "No") << "\n";
    cout << "Has no authors? " << (!b1 ? "Yes" : "No") << "\n";
 
    ++b1;               // Increment pages
    b1.display();

    b1--;               // Decrement pages
    b1.display();

    cout <<endl<< "First author: " << b1[0] << "\n";
    
    //Function operator to Return the number of pages
    cout << "Pages: " << b1() << std::endl;
    //Function operator to Return an author's name based on a given index
    cout << "First author: " << b1(0) << std::endl;
    cout << "Title as string: " << string(b1) << "\n";
    //string title = (string)b1;   //cast to string
    //cout << "Title: " << title << std::endl;
    cout << b1;

    //Input a new book
    //Book b4;
    //cin >> b4;
    //cout <<endl<< "You entered:\n" << b4;

    int testInt = int(a);
    cout << endl << testInt;

}


