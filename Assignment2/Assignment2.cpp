#pragma once

#include <iostream>
#include <string>
#include <string.h>

using namespace std;

class Book {
private:
    std::string title = "";
    char author[50];
    int year = 0;
    float* reviews = nullptr;      // Dynamic array for review scores (from 1 to 5; accepts floating point values like 2.3)
    int reviewCount = 0;     // Number of reviews

public:
    // Default constructor
    Book() {
        this->title = "";//init title with ""
        strcpy_s(this->author, "No author");//init author with "No author"
        this->year = 0;//init year with 0
        this->reviews = nullptr;//init reviews with null pointer
        this->reviewCount = 0;//init reviews count with 0
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

    // Getter methods
    std::string getTitle() {
        return this->title;
    }
    char* getAuthor() {
        char* copyPointer = nullptr;
        copyPointer = new char[strlen(this->author) + 1];
		strcpy_s(copyPointer, strlen(this->author)+1, this->author);
        return copyPointer;
    }

    int getYear() {
		return this->year;
    }

    // Deep copy for array
    void setReviews(const float* newReviews, int size) {
        float* copyReviews = new float[size];
        for (int i = 0; i < size; i++) {
            copyReviews[i] = newReviews[i];
        }
        delete[] this->reviews;
        this->reviews = copyReviews;
        this->reviewCount = size;
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

    // Setter methods
    void setTitle(std::string title) {
        if (title.length() < 3 || title.length() > 100) {
            throw "Title length must be between 3 and 100 characters.";
        }
        this->title = title;
    }
    void setAuthor(const char* author) {
        if(strlen(author) < 3 || strlen(author) > 50){
            throw "Author length must be between 3 and 50 characters.";
		}
        strcpy_s(this->author, strlen(author) + 1, author);

    }
    void setYear(int year) {
		if (year / 1 != year) throw "Year must be an integer value.";
        if (year > 2025) throw "Invalid year.";
		this->year = year;
    }

 

    // Add a review to the reviews array
    void addReview(float score) {
        float* tempArray = new float[this->reviewCount + 1]; //5+1=6
        for (int i = 0; i < this->reviewCount; i++) { //i=0,1,2,3,4 (5 values)
            tempArray[i] = this->reviews[i];
        }
        tempArray[reviewCount] = score; //tA[5]
        delete[] reviews;
        this->reviews = tempArray; //append the reviews array to the temporary array address
        this->reviewCount++; //increment review count
    }

    // Display book details
    void display() {
        cout << endl << "______________Printing_book_details_________________";
        cout << endl << "Book title: " << this->getTitle();
        cout << endl << "Book author: " << this->getAuthor();
        cout << endl << "Book year of publication: " << this->getYear();
        cout << endl << "Book reviews: ";
        if (getNoReviews() == 0) cout << "No reviews received.";
        else {
            for (int i = 0; i < getNoReviews(); i++) {
                cout << this->reviews[i] << ", ";
            }
            cout << endl << "Average book review score: " << getAverageReviewsValue();
            cout << endl << "Worst book review score: " << getMinimumReviewValue() << " received " << getMinimumReviewCount() << " times.";
        }
    }

    // Average value of all reviews
    float getAverageReviewsValue() {
        float sum = 0;
        for (int i = 0; i < getNoReviews(); i++) {
            sum += this->reviews[i];
        }
        return sum / getNoReviews();
    }

    // The minium value of all reviews 
    float getMinimumReviewValue() {
        float minValue = 0;
        for (int i = 0; i < getNoReviews(); i++) {
            for (int j=0; j<getNoReviews()-1-i; j++)
                if (this->reviews[j] < this->reviews[j + 1]) minValue = this->reviews[j];
        }
        return minValue;
    }

    // Number of reviews with minium value  
    int getMinimumReviewCount() {
        int counterMin = 0;
        for (int i = 0; i < getNoReviews(); i++) {
            if (this->reviews[i] == getMinimumReviewValue()) counterMin++;
        }
        return counterMin;
    }

    ~Book() {
        delete[] reviews;
    }
};


int main(){
    Book a("test1", "j kenny", 1935);
    a.display();
    const int noReviewsDummy = 5;
    float dummyArray[noReviewsDummy] = { 2.4f, 2.9f, 3.6f, 4.6f, 3.5f};
    
    Book b("test2", "george mann", 2003, dummyArray, noReviewsDummy);
    b.display();
    b.addReview(3.0f);
    b.display();
    b.addReview(2.4f);
    b.display();
}