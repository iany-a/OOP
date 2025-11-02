#pragma once

#include <iostream>
#include <string>
#include <string.h>

using namespace std;

class Book {
private:
    std::string title;
    char author[50];
    int year;
    float* reviews;      // Dynamic array for review scores (from 1 to 5; accepts floating point values like 2.3)
    int reviewCount;     // Number of reviews

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

    }

    // Getter methods
    std::string getTitle() {
        return this->title;
    }
    char* getAuthor() {
        char* copyPointer = nullptr;
        copyPointer = new char[strlen(this->author) + 1];
		strcpy_s(copyPointer, strlen(this->author), this->author);
		return copyPointer;
    }

    int getYear() {
		int copyYear = this->year;
        return copyYear;
    }

    // Returns a copy of the reviews array
    float* getReviews() {
        return nullptr;
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

    // Deep copy for array
    void setReviews(const float* newReviews, int size) {
        // Implement deep copy of `newReviews` into `reviews`

    }

    // Add a review to the reviews array
    void addReview(float score) {

    }

    // Display book details
    void display() {
        
    }

    // Average value of all reviews
    float getAverageReviewsValue() {
        return 0;
    }

    // The minium value of all reviews 
    float getMinimumReviewValue() {
        return 0;
    }

    // Number of reviews with minium value
    int getMinimumReviewCount() {
        return 0;
    }
};


int main(){
    Book a("test", "j kenny", 1935);

}