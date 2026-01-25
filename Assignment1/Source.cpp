#include <iostream>
#include <string.h>
#include <string>

//Almasanu Iany-Ionut An III Suplimentar CSIE-IE Engleza 25 Oct 2025
//Read requirements from the pdf document
//Implement and test required methods

using namespace std;

struct Book {
	char title[100];
	char author[100];
	int year;
	int pages;
};

void initializeBook(Book* b, const char* title, const char* author, int year, int pages)
{
	strcpy_s(b->title, strlen(title) + 1, title);
	strcpy_s(b->author, strlen(author) + 1, author);
	b->year = year;
	b->pages = pages;

	/*cout << "Initializing fields" << endl;
	cout << "Book init title: " << b->title << endl;
	cout << "Book init author: " << b->author << endl;
	cout << "Book init year: " << b->year << endl;
	cout << "Book init pages: " << b->pages << endl;*/


}

//bonus
//rewrite initializeBook with references
void initializeBookWithReference(Book& b, const char* title, const char* author, int year, int pages)
{
	strcpy_s(b.title, strlen(title)+1, title);
	strcpy_s(b.author, strlen(author)+1, author);
	b.year = year;
	b.pages = pages;

	/*cout << "Initializing fields" << endl;
	cout << "Book init title: " << b.title << endl;
	cout << "Book init author: " << b.author << endl;
	cout << "Book init year: " << b.year << endl;
	cout << "Book init pages: " << b.pages << endl;*/

}

void displayBooks(const Book books[], int size) {
	for (int i = 0; i < size; i++) {
		cout << "_____________Book_" << i + 1 << "_details_____________" << endl;
		cout << "Book "<<i+1<<" title: " << books[i].title << endl;
		cout << "Book " << i + 1 << " author: " << books[i].author << endl;
		cout << "Book " << i + 1 << " year: " << books[i].year << endl;
		cout << "Book " << i + 1 << " pages: " << books[i].pages << endl;
		cout << "________________________________________" << endl;
	}
}

Book* addBook(Book* books, int& size, const Book& newBook) {
	Book* booksLarger = new Book[size+1];
	for (int i = 0; i < size; i++) {
		strcpy_s(booksLarger[i].title, books[i].title);
		strcpy_s(booksLarger[i].author, books[i].author);
		booksLarger[i].year = books[i].year;
		booksLarger[i].pages = books[i].pages;

	}
	strcpy_s(booksLarger[size].title, newBook.title);
	strcpy_s(booksLarger[size].author, newBook.author);
	booksLarger[size].year = newBook.year;
	booksLarger[size].pages = newBook.pages;
	if (size > 5) { //THIS IS IMPORTANT: we start the function calling a static array
		//once this function adds a book, the data is stored in a dynamic array in main, hence we need to
		//make sure to delete heap memory only after the first run of the function (any new calls to this function
		//will pass a pointer to a new dynamic array, the if statement is making sure that the delete only triggers
		//after the first call).
		delete[] books;
		books = nullptr;
	}
	size++; //the function uses the refference of the size from main (&size), meaning that we can modify its value inside this function
	return booksLarger;
}

//The assignment mentions to return the address of the found book.
//This will stop at the first book found. I have tried to create a new array that gets populatd with all matches found, but this
//defeats the purpose of the asignment, as this will not be able to return 1 single book address if we have multiple matches.
Book* searchByTitle(Book* books, int size, const char* title) {
	for (int i = 0; i < size; i++) {
		cout << endl << books[i].title;
		if (strcmp(books[i].title, title) == 0) {
			cout << endl << "Book " << i + 1 << " found with matching title: " << title << endl;
			return &books[i]; //will return only the first match, excluding anything else from the array
		}
	}
	cout << endl << "No matching title book found." << endl; //these get triggered only if the previous return in the if statement doesn't fire
	return nullptr;
	
}

void cleanup(Book*& books) {
	delete[] books;
	books = nullptr;
}

void sortByYear(Book* books, int size) {
	for (int i = 0; i < size; i++) {
		for (int j = 0; j < size-1; j++) {
			if (books[j].year > books[j + 1].year) {
				Book* tempPointerLowerValueGreaterIndex = nullptr; //temp pointer for storing address of lower value but greater index
				Book* tempPointerGreaterValueLowerIndex = nullptr; //temp pointer for storing address of higher value but lower index
				tempPointerGreaterValueLowerIndex = &books[j]; //assignment of address of lower index, greater value
				tempPointerLowerValueGreaterIndex = &books[j + 1]; //assignment of address of greater index, lower value
				Book temporaryObject; //we need this temporary object, otherwise addresses will get overwritten and 
				//we lose the address of one element in the array
				temporaryObject = *tempPointerGreaterValueLowerIndex; //all 3 lines are swapping addresses
				*tempPointerGreaterValueLowerIndex = *tempPointerLowerValueGreaterIndex;
				*tempPointerLowerValueGreaterIndex = temporaryObject;
			}//i thought we will need to add these into a new array, but swapping addresses works directly with the book array
			//which was passed into this function by its pointer.
		}
	}
	cout << endl << "Lists of books Sorted Alphabetically.";
}


int main() {
	Book noReferenceBook;
	Book referenceBook;
	initializeBook(&noReferenceBook, "", "", 0, 0);
	initializeBookWithReference(referenceBook, "", "", 0, 0);

	Book staticBooks[5] = {};
	int size = sizeof(staticBooks)/sizeof(staticBooks[0]);

	char tempTitle[100] = "";
	char tempAuthor[100] = "";
	int tempYear = 0;
	int tempPages = 0;
	

	for (int i = 0; i < size; i++) {
		cout << endl << "Input book " << i+1 << " details below: ";
		cout << endl << "Book title: ";
		cin >> tempTitle;
		cout << "Author: ";
		cin >> tempAuthor;
		cout << "Year of publication: ";
		cin >> tempYear;
		cout << "Number of pages: ";
		cin >> tempPages;
		initializeBook(&staticBooks[i], tempTitle, tempAuthor, tempYear, tempPages);
	}

	displayBooks(staticBooks, size);

	Book newBook;
	initializeBook(&newBook, "Book 6", "Author 6", 1945, 230);
	Book* dynamicBooks = addBook(staticBooks, size, newBook); //i am starting with the static populated book array
	displayBooks(dynamicBooks, size);
	Book anotherNewBook;
	initializeBook(&anotherNewBook, "Redemption", "James B. Clark", 2003, 193);
	dynamicBooks = addBook(dynamicBooks, size, anotherNewBook); //from here on, we stop using the static array
	displayBooks(dynamicBooks, size);
	searchByTitle(dynamicBooks, size, "Redemption");
	
	sortByYear(dynamicBooks, size);
	displayBooks(dynamicBooks, size);


	cleanup(dynamicBooks); //cleaning up the memory in heap before exiting the program
	return 0;
}