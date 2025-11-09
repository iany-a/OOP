#pragma once

#include <iostream>
#include <string>
#include <string.h>

using namespace std;

enum class BookType {
    ROMANCE,
    DRAMA,
    //SCIENCE_FICTION,
    //PHILOSOPHY,
    SCIENCE,
    //ADVENTURE,
    CRIME,
    //SELF_IMPROVEMENT,
    UNDEFINED
};


class Book {
private:
    std::string title = "";
    char author[50];
    int year = 0;
    BookType bookType = BookType::UNDEFINED;
    float* reviews = nullptr;      // Dynamic array for review scores (from 1 to 5; accepts floating point values like 2.3)
    int reviewCount = 0;     // Number of reviews
    static int MIN_VALUE;
    static int MAX_VALUE;
    static int CURRENT_YEAR;

public:
    // Default constructor
    Book() {
        setTitle("");
        setAuthor("");
        setYear(0);
        BookType booktype = BookType::UNDEFINED;
        this->reviews = nullptr;
        this->reviewCount = 0;
    }

    // Parameterized constructor
    // Init Book attributes with received values. 
    // Init reviews and reviewCount with null pointer and 0
    Book(const std::string& title, const std::string& author, int year) {
        setTitle(title);
        setAuthor(author.c_str());
        setYear(year);
        this->reviews = nullptr;
        this->reviewCount = 0;
    }

    // Parameterized constructor
    // Init Book attributes with received values. 
    Book(const std::string& title, const std::string& author, int year, float* reviews, int reviewCount) {
        setTitle(title);
        setAuthor(author.c_str());
        setYear(year);
        setReviews(reviews, reviewCount);
    }

    // new parameterized constructor which includes the book type
    Book(const std::string& title, const std::string& author, int year, BookType bookType, float* reviews, int reviewCount) {
        setTitle(title);
        setAuthor(author.c_str());
        setYear(year);
        setBookType(bookType);
        setReviews(reviews, reviewCount);
    }

    // Getter methods
    std::string getTitle() {
        return this->title;
    }
    char* getAuthor() {
        char* copyauthor = new char[strlen(this->author) + 1];
        strcpy_s(copyauthor, strlen(this->author) + 1, this->author);
        return copyauthor;
    }

    int getYear() {
        return this->year;
    }

    // Returns a copy of the reviews array
    float* getReviews() {
        float* copyReviews = new float[this->reviewCount];
        for (int i = 0; i < this->reviewCount; i++) {
            copyReviews[i] = this->reviews[i];
        }
        return copyReviews;
    }

    int getNoReviews() {
        return this->reviewCount;
    }

    //enum getter
    BookType getBookType() {
        return this->bookType;
    }

    // Setter methods
    void setTitle(std::string title) {
        if (title.length() < MIN_VALUE || title.length() > MAX_VALUE)
            throw "Title name number of characters is not between 3 and 50";
        this->title = title;
    }
    void setAuthor(const char* author) {
        if (strlen(author) < MIN_VALUE || strlen(author) > MAX_VALUE)
            throw "Author name number of characters is not between 3 and 50";
        for (int i = 0; i < strlen(author); i++) {
            this->author[i] = author[i];
        }
    }
    void setYear(int year) {
        if (year<0 || year > CURRENT_YEAR)
            throw "Invalid year: must be a positive value between 0 and current year";
        this->year = year;
    }

    // Deep copy for array
    void setReviews(const float* newReviews, int size) {
        // Implement deep copy of `newReviews` into `reviews`
        if (size <= 0 || newReviews == nullptr) throw "Invalid array size";
        delete[] this->reviews; //each time this function is called, we allocate new memory. to combat memory leaks,
        //delete the old array in memory before allocating new memory.
        this->reviews = new float[size];
        for (int i = 0; i < size; i++) {
            this->reviews[i] = newReviews[i];
        }
        this->reviewCount = size;
    }

    //enum setter
    void setBookType(BookType booktype) {
        this->bookType = booktype;
    }

    // Add a review to the reviews array
    void addReview(float score) {
        float* updatedReviewsArray = new float[(this->reviewCount)+1]; //5+1 elements max size
        for (int i = 0; i <this->reviewCount; i++) { //0-4 = 5 elements
            updatedReviewsArray[i] = this->reviews[i]; //0-4 = 5 elements filled
        }
        updatedReviewsArray[reviewCount] = score; //a[5] = 6th element
        delete[] this->reviews; //prevent memory leaks as stated in the previous setter
        this->reviews = updatedReviewsArray;
        this->reviewCount++;
    }

    // Display book details
    void display() {
        cout<<endl<< "______________Book <" << this->title << "> details___________";
        cout << endl <<"Title: " << this->title;
        cout << endl <<"Author: " << this->author;
        cout << endl <<"Year of publication: " << this->year;
        cout << endl << "Genre: ";
        switch (this->bookType) {
            case BookType::ROMANCE:
                cout << "Romance";
                break;
            case BookType::SCIENCE:
                cout << "SCIENCE";
                break;
            case BookType::CRIME:
                cout << "CRIME";
            case BookType::DRAMA:
                cout << "DRAMA";
                break;
            case BookType::UNDEFINED:
                cout << "UNDEFINED";
                break;
            default:
                cout << "UNDEFINED";
        }
        if (this->reviewCount > 0) {
            cout << endl << this->reviewCount;
            cout << endl;
            for (int i = 0; i < this->reviewCount; i++) {
                cout << this->reviews[i] << ", ";
            }
            cout << endl << "Average review count: " << this->getAverageReviewsValue();
            cout << endl << "Minimum review score received: " << this->getMinimumReviewValue();
            cout << endl << "Minimum review score counter: " << this->getMinimumReviewCount();
        }
    }

    // Average value of all reviews
    float getAverageReviewsValue() {
        float sum = 0;
        for (int i = 0; i < this->reviewCount; i++) {
            sum += this->reviews[i];
        }
        return sum / reviewCount;
    }

    // The minium value of all reviews 
    float getMinimumReviewValue() {
        float minVal = reviews[0];
        for (int i = 1; i < this->reviewCount; i++) {
            if (reviews[i] < minVal)
                minVal = reviews[i];
        }
        
        return minVal;
    }

    // Number of reviews with minium value
    int getMinimumReviewCount() {
        int minValCounter = 0;
        for(int i=0;i<this->reviewCount;i++){
            if (reviews[i] == this->getMinimumReviewValue()) {
                minValCounter++;
            }
        }
        return minValCounter;
    }

    ~Book() {
        delete[] this->reviews;
    }
};

int Book::MIN_VALUE = 3;
int Book::MAX_VALUE = 50;
int Book::CURRENT_YEAR = 2025;

int main(){
    float testingFloatArray[] = { 4.2f, 3.4f, 5.0f, 1.6f, 4.1f };
    int testingReviewsCount = sizeof(testingFloatArray)/sizeof(testingFloatArray[0]);
    Book a("Victory", "Iann Alemme", 2024, testingFloatArray, testingReviewsCount);
    a.display();
    a.addReview(2.5f);
    a.setBookType(BookType::SCIENCE);
    a.display();
    Book b("Master", "Iann Alemme", 2025, BookType::SCIENCE, testingFloatArray, testingReviewsCount);
    b.display();
}