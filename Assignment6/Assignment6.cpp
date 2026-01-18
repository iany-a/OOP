#pragma once
// Skeleton implementation for LibraryBooks assignment
#include <iostream>
#include <cstring>
#include <string>

using namespace std;

// Borrower Class
class Borrower {
private:
    char* name = nullptr;
    int borrowerId = 0;

public:
    // Constructor: Initialize borrower with a name and unique ID
    Borrower(const char* name, int id) {
        this->setName(name);
        this->setId(id);
    }

    //setters
    void setName(const char* name) {
        if (name == nullptr) throw "Invalid input.";
        delete[] this->name;
        this->name = new char[strlen(name) + 1];
        strcpy_s(this->name, strlen(name) + 1, name);
    }

    void setId(int id) {
        if (id < 0 || id/1 != id) throw "Invalid / non-numerical input.";
        this->borrowerId = id;
    }


    // Destructor: Free allocated memory for name
    ~Borrower() {
        delete[] this->name;
    }

    // Get the name of the borrower
    const char* getName() {
        char* dummy = new char[strlen(this->name) + 1];
        strcpy_s(dummy, strlen(this->name) + 1, this->name);
        return dummy;
    }

    // Get the unique ID of the borrower
    int getId() {
		return this->borrowerId;
    }

    void displayInfo() {
        cout << endl << "______________________";
        cout << endl << "Borrower name: " << this->name;
        cout << endl << "Borrower id: " << this->borrowerId;
    }


};

// Book Base Class
class Book {
protected:
    char* title = nullptr;
    char* author = nullptr;
    bool isBorrowed = false;
    static const int MAX_LENGTH;
public:
    // Constructor: Initialize book with title and author
	Book(const char* title, const char* author) {
        this->setTitle(title);
        this->setAuthor(author);
    }

    //setters
    void setTitle(const char* title) {
        if (title == nullptr) throw "Invalid input.";
        delete[] this->title;
        this->title = new char[strlen(title) + 1];
        strcpy_s(this->title, strlen(title) + 1, title);
    }

    void setAuthor(const char* author) {
        if (author == nullptr) throw "Invalid input.";
        delete[] this->author;
        this->author = new char[strlen(author) + 1];
        strcpy_s(this->author, strlen(author) + 1, author);
    }

    // Destructor: Free allocated memory for title and author
    virtual ~Book() {
        delete[] this->title;
        delete[] this->author;
    }

    // Get the type of the book (overridden in derived classes)
    virtual const char* getType() {
        const char* type = new char[Book::MAX_LENGTH];
        type = "Book";
        return type;
    }

    // Mark the book as borrowed
    virtual void borrowBook() {
        if (isBorrowed) throw "Book is already borrowed by a different user.";
        this->isBorrowed = true;
    }

    // Mark the book as returned
    void returnBook() {
        if (!isBorrowed) throw "Book is already returned by its borrower.";
        this->isBorrowed = false;
    }

    // Get the title of the book
    const char* getTitle() { 
        char* dummy = new char[strlen(this->title)+1];
        strcpy_s(dummy, strlen(this->title) + 1, this->title);
        return dummy;
    }

    // Get the author of the book
    const char* getAuthor() {
        char* dummy = new char[strlen(this->author) + 1];
        strcpy_s(dummy, strlen(this->author) + 1, this->author);
        return dummy;
    }

    // Check if the book is currently borrowed
    bool getBorrowStatus() {
        return this->isBorrowed;
    }


    //display info
    virtual void displayInfo() {
        cout << endl << "______________________";
        cout << endl << "Book title: " << this->title;
        cout << endl << "Book author: " << this->author;
        cout << endl << "Status: ";
        if (isBorrowed) cout << "Borrowed";
        else cout << "In stock";
    }


};

// TextBook Class
class TextBook : public Book {
private:
    char* subject = nullptr;

public:
    // Constructor: Initialize textbook with title, author, and subject
	// Update the call to the base class constructor and pass values for title and author
    TextBook(const char* title, const char* author, const char* subject): Book(title,author) { 
        this->subject = new char[strlen(subject) + 1];
        strcpy_s(this->subject, strlen(subject) + 1, subject);
    }

    // Destructor: Free allocated memory for subject
    ~TextBook() {
        delete[] this->subject;
    }

    // Get the type of the book (returns "TextBook")
    const char* getType() { 
        const char* type = new char[Book::MAX_LENGTH];
        type = "TextBook";
        return type;
    }

    void displayInfo() {
        cout << endl << "______________________";
        cout << endl << "Book title: " << this->title;
        cout << endl << "Book author: " << this->author;
        cout << endl << "Status: ";
        if (isBorrowed) cout << "Borrowed";
        else cout << "In stock";
        cout << endl << "Subject: " << this->subject;
    }

};

// Novel Class
class Novel : public Book {
private:
    char* genre = nullptr;

public:
    // Constructor: Initialize novel with title, author, and genre
    // Update the call to the base class constructor and pass values for title and author
    Novel(const char* title, const char* author, const char* genre) : Book(title, author) {
        this->genre = new char[strlen(genre) + 1];
        strcpy_s(this->genre, strlen(genre) + 1, genre);
    }

    // Destructor: Free allocated memory for genre
    ~Novel() {
        delete[] this->genre;
    }

    // Get the type of the book (returns "Novel")
    const char* getType() {
        const char* type = new char[Book::MAX_LENGTH];
        type = "Novel";
        return type;
    }

    void displayInfo() {
        cout << endl << "______________________";
        cout << endl << "Book title: " << this->title;
        cout << endl << "Book author: " << this->author;
        cout << endl << "Status: ";
        if (isBorrowed) cout << "Borrowed";
        else cout << "In stock";
        cout << endl << "Genre: " << this->genre;
    }


};

//LibrarySection Class
class LibrarySection {
    char* sectionName = nullptr;
    Book* book = nullptr;
public:
    LibrarySection(const char* sectionName, Book* book) {
        if (book == nullptr) throw "Invalid input.";
        this->setSectionName(sectionName);
        this->book = book;
    }

    //setters
    void setSectionName(const char* sectionName) {
        if (sectionName == nullptr) throw "Invalid input.";
        delete[] this->sectionName;
        this->sectionName = new char[strlen(sectionName) + 1];
        strcpy_s(this->sectionName, strlen(sectionName) + 1, sectionName);
    }

    ~LibrarySection() {
        delete[] this->sectionName;
    }

    void displayInfo() {
        cout << endl << "______________________";
        cout << endl << "Library section: " << this->sectionName;
        cout << endl << "Book associated details:";
        book->displayInfo();
    }

};

// Library Class
class Library {
private:
    Book* books[50] = {};
    int bookCount = 0;

public:
    // Constructor: Initialize library with an empty book collection
    Library() {
        this->bookCount = 0;
        this->books[0] = {};
        cout << endl<<endl << "Empty default library constructor test.";
    }

    // Destructor: Free allocated memory for all books in the collection
    ~Library() {
        //delete[] this->books; //this is a static array
    }

    // Add a book to the library (if space is available)
    void addBook(Book* book) {
        if (this->bookCount==50) throw "No space available to add another book.";
        this->bookCount++;
        this->books[this->bookCount-1] = book;
        cout << endl << "Added 1 new book in the current library.";
    }

	// Search for books by a specific author and return an array of matching books pointers
    Book** searchByAuthor(const char* author, int& count) {
        if (author == nullptr) throw "Invalid input";
        cout << endl << endl;
        for (int i = 0; i < this->bookCount; i++) {
            if (strcmp(this->books[i]->getAuthor(), author) == 0) {
               count++;
               cout << "+1 match, ";
            }
        }
        
        if (count > 0) {
            Book** arrayFixedSize = new Book * [count];
            int counter = 0;
            for (int i = 0; i < this->bookCount; i++) {
                if (strcmp(this->books[i]->getAuthor(), author) == 0) {
                    arrayFixedSize[counter] = this->books[i];
                    counter++;
                }
            }
            return arrayFixedSize;
        }
        else {
            cout << endl << "No matching author found in library.";
            return nullptr;
        }
    }

    // Count the number of borrowed books in the library
	int countBorrowedBooks() {
        int counter = 0;
        for (int i = 0; i < this->bookCount; i++) {
            if (this->books[i]->getBorrowStatus()) counter++;
        }
        return counter;
    }

    void displayBooks() {
        for (int i = 0; i < this->bookCount; i++) books[i]->displayInfo();
    }

    void borrowBook(int index) {
        if (index <0 || index>this->bookCount - 1) throw "Invalid input.";
        this->books[index]->borrowBook();
        cout << endl << "(Verification) Borrowed book at index " << index << ".";
    }

    void returnBook(int index) {
        if (index <0 || index>this->bookCount - 1) throw "Invalid input.";
        this->books[index]->returnBook();
        cout << endl << "(Verification) Returned book at index " << index << ".";
    }

    void searchByTitle(const char* title) {
        if (title == nullptr) throw "Invalid input.";
        int counter = 0;
        for (int i = 0; i < this->bookCount; i++) {
            if (strcmp(this->books[i]->getTitle(), title) == 0) {
                cout <<endl<<endl<< "Matching title book found on index "<<i<<":";
                this->books[i]->displayInfo();
                counter++;
            }
        }
        if (counter == 0) cout << endl << "No matching title book found.";

    }
};

//ReferenceBook class
class ReferenceBook : public Book {
public:
    ReferenceBook(const char* title, const char* author) : Book(title, author) {

    }
    void borrowBook() {
        throw "ERROR: Reference book can not be borrowed.";
    }
    const char* getType() {
        const char* type = new char[Book::MAX_LENGTH];
        type = "ReferenceBook";
        return type;
    }
    ~ReferenceBook() {

    }

};

const int Book::MAX_LENGTH = 20;


int main() {
    //book test
    Book a("Book Title", "Book Author");
    a.displayInfo();
    cout<< endl<< a.getType();
    
    //textbook test
    TextBook b("TextBook Title", "TextBook Author", "Physics");
    b.displayInfo();
    cout << endl << b.getType();

    //novel test
    Novel c("Novel Title", "Novel Author", "Fiction");
    c.displayInfo();
    cout << endl << c.getType();
    Novel d("Novel 2 Title", "John Writer", "Fiction");
    Novel e("Novel 3 Title", "Another Novel Author", "Mistery");
    //additional Textbook
    TextBook f("Textbook 2 Title", "John Writer", "C++ Programming"); //John Writer has a lot of imagination, he writes both textbooks and novels
    
    //borrower test
    Borrower t("John Borrower", 1);
    t.displayInfo();

    //library section test
    LibrarySection x("Shelf A", &a);
    x.displayInfo();
    LibrarySection w("Shelf B", &b);
    w.displayInfo();
    //library test
    Library l;
    l.addBook(&a);
    l.addBook(&b);
    l.addBook(&c);
    l.borrowBook(2);
    l.borrowBook(1);
    l.returnBook(2);
    //l.returnBook(2); //verification of error handling, this is crashing as intended
    cout<<endl<<"No. of borrowed books in library: "<<l.countBorrowedBooks();
    l.addBook(&d);
    l.addBook(&e);
    l.addBook(&f);
    l.displayBooks();

    int count = 0;
    Book** matchArray = l.searchByAuthor("John Writer", count);
    for (int i=0; i<count; i++){
        matchArray[i]->displayInfo();
    }
    delete[] matchArray;
   
    ReferenceBook h("Reference Book", "Reference Book Author");
    h.displayInfo();
    cout<<endl<<h.getType();
    //h.borrowBook(); //verification of error handling, this is crashing as intended

    l.searchByTitle("Novel Title");

}
