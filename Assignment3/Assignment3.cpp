#pragma once
#include <iostream>
#include <cstring>
#include <numeric>
#include <string.h>
#include <string>

using namespace std;

class Book {
private:
    char* title = nullptr;            // Dynamic array
    int* copiesPerLibrary = nullptr;  // Dynamic array
    int numLibraries = 0;

public:
    // Default constructor
    Book() {}

    // Parameterized constructor
    Book(const char* t, int libraries, const int* copies) {
        setTitle(t);
        setCopiesPerLibrary(libraries, copies);
    }

    // Destructor
    ~Book() {
        delete[] this->title;
        delete[] this->copiesPerLibrary;
    }

    // Copy constructor
    Book(const Book& other) {
        this->title = new char[strlen(other.title) +1];
        strcpy_s(this->title, strlen(other.title) + 1, other.title);
        this->copiesPerLibrary = new int[other.numLibraries];
        for ( int i = 0; i< other.numLibraries; ++i){
            this->copiesPerLibrary[i] = other.copiesPerLibrary[i];
        }
        this->numLibraries = other.numLibraries;
    }
        
    // Getters
    const char* getTitle() const {
        char* copyTitle = new char[strlen(this->title) + 1];
        strcpy_s(copyTitle, strlen(this->title) + 1, this->title);
        return copyTitle;
    }
    int getNumLibraries() const {
        return this->numLibraries;
    }
    int* getCopiesPerLibrary() const {
        int* dummyCopiesArray = new int[this->numLibraries];
        for (int i = 0; i < this->numLibraries; ++i) {
            dummyCopiesArray[i] = this->copiesPerLibrary[i];
        }
        return dummyCopiesArray;
    }

    // Setters
    void setTitle(const char* t) {
        if (t == nullptr) throw "Invalid source title.";
        delete[] this->title;
        this->title = new char[strlen(t) + 1];
        strcpy_s(this->title, strlen(t) + 1, t);
    }

    void setCopiesPerLibrary(int libraries, const int* copies) {
        if (copies == nullptr) throw "Invalid array source!";
        delete[] this->copiesPerLibrary;
        this->copiesPerLibrary = new int[libraries];
        for (int i = 0; i < libraries; i++) {
            this->copiesPerLibrary[i] = copies[i];
        }
        this->numLibraries = libraries;
    }

    // A method to calculate the total number of copies across all libraries
    int getTotalCopies() const {
        int totalCopiesSum = 0;
        for (int i = 0; i < this->numLibraries; i++) {
            totalCopiesSum += this->copiesPerLibrary[i];
        }
        return totalCopiesSum;
    }

    // A method to check if a library, with a given index, has at least a given number of copies
    bool hasAtLeastCopies(int libraryIndex, int threshold) const {
        if (libraryIndex > this->numLibraries-1) throw "Invalid library index!";
        if (this->copiesPerLibrary[libraryIndex] >= threshold) {
            cout << "Library " << libraryIndex << " has " << threshold << " or more copies available.";
            return true;
        }
        cout << "Library "<< libraryIndex <<" has less than " << threshold << " copies available.";
        return false;
       
    }

    // Add a new value to copiesPerLibrary
    void addCopies(int newCopies) {

        int* upsizedArray = new int[this->numLibraries + 1];
        for (int i = 0; i < this->numLibraries; ++i) {
            upsizedArray[i] = this->copiesPerLibrary[i];
        }
        upsizedArray[numLibraries] = newCopies;
        delete[] this->copiesPerLibrary;
        this->copiesPerLibrary = upsizedArray;
        this->numLibraries++;
    }

    // Remove a value from copiesPerLibrary at a given index
    void removeCopiesAtIndex(int index) {
        if (index > this->numLibraries-1) throw "Invalid index.";
        int* shrinkedArray = new int[this->numLibraries - 1];
        for (int i = 0; i < index; i++) {
            shrinkedArray[i] = this->copiesPerLibrary[i];
        }
        for (int i = index; i < numLibraries-1; i++) {
            shrinkedArray[i] = this->copiesPerLibrary[i + 1];
        }
        delete[] this->copiesPerLibrary;
        this->copiesPerLibrary = shrinkedArray;
        this->numLibraries--;
    }

    void display() {
        cout << "________________________" << endl;
        cout << "Title: " << this->title << endl;
        cout << "Number of copies in each library: " << endl;
        for (int i = 0; i < this->numLibraries; i++) {
            cout << this->copiesPerLibrary[i] << " copies available in library " << i << endl;
        }
        cout << "Total number of copies available: " << this->getTotalCopies() << endl;
    }
};

int main() {

    int copiesPerLibraryTest[] = { 5, 6, 7, 8, 20 };
    int libraries = (sizeof(copiesPerLibraryTest) / sizeof(copiesPerLibraryTest[0]));
    cout << libraries << " "<<sizeof(copiesPerLibraryTest);
    Book a("test", libraries, copiesPerLibraryTest);
    a.display();
    int dummyArray[3] = { 3,9,1 };
    int dummyNoLibraries = 3;
    Book b("test2", dummyNoLibraries, dummyArray);
    b.display();
    b.hasAtLeastCopies(2, 2);

    Book c(a);
    a.display();
    c.display();
    c.addCopies(6);
    c.display();
    c.removeCopiesAtIndex(5);
    c.display();
}