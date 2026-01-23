#include <iostream>
#include <string>

class Book {
private:
    static int nextId;
    int id = 0;
    std::string title = "";
    int* chapterPageCounts = nullptr;
    int chapterCount = 0;

public:
    // Constructors and destructor
    Book();
    Book(const std::string& title, const int* chapterPageCounts, int chapterCount);
    Book(const Book& other);
    ~Book();

    // Getters
    int getId() const;
    std::string getTitle() const;
    int getChapterCount() const;
    int getChapterPages(int index) const;
    int getTotalPages() const;
    double getAverageChapterPages() const;

    // Setters
    void setTitle(const std::string& title);
    void setChapterPageCounts(const int* chapterPageCounts, int chapterCount);

    // Processing methods
    bool hasShortChapter(int maxPages) const;
    int getIndexOfFirstChapterWithPages(int pages) const;

    // Extra processing methods
    bool isLongerThan(const Book& other) const;
    int getNumberOfChaptersWithinInterval(int minPages, int maxPages) const;
    bool canBeReadInDays(int days, int maxPagesPerDay) const;
    void display();

    // Static method
    static int getNumberOfBooksCreated();

private:
    void copyChapters(const int* chapterPageCounts, int chapterCount);
};

// Initialize static member
int Book::nextId = 0;

// ======================
// Method definitions
// ======================

Book::Book() {
    this->title = "Unknown";
    this->chapterPageCounts = nullptr;
    this->chapterCount = 0;
    this->id = this->nextId;
    this->nextId++;
}

Book::Book(const std::string& title, const int* chapterPageCounts, int chapterCount) {
    // TODO: implement parameterized constructor
    setTitle(title);
    setChapterPageCounts(chapterPageCounts, chapterCount);
    this->id = this->nextId;
    this->nextId++;
}

Book::Book(const Book& other) {
    // TODO: implement copy constructor (deep copy)
    this->title = other.title;
    copyChapters(other.chapterPageCounts, other.chapterCount);
    this->id = this->nextId;
    this->nextId++;
}

Book::~Book() {
    delete[] this->chapterPageCounts;
}

int Book::getId() const {
    return this->id;
}

std::string Book::getTitle() const {
    return this->title;
}

int Book::getChapterCount() const {
    return this->chapterCount;
}

int Book::getChapterPages(int index) const {
    if (index > this->chapterCount || index < 0) {
        throw "Invalid chapter index.";
        return -1;
    }
    std::cout << std::endl << "Book " << this->title << " page count at chapter " << index << " is: " << this->chapterPageCounts[index] << ".";
    return this->chapterPageCounts[index];
}

int Book::getTotalPages() const {
    int sum = 0;
    for (int i = 0; i < this->chapterCount; i++) {
        sum += this->chapterPageCounts[i];
    }
    return sum;
}

double Book::getAverageChapterPages() const {
    return this->getTotalPages() / this->chapterCount;
}

void Book::setTitle(const std::string& title) {
    if (title == "") throw "Invalid name";
    this->title = title;
}

void Book::setChapterPageCounts(const int* chapterPageCounts, int chapterCount) {
    if (chapterPageCounts == nullptr) throw "Invalid page counter value.";
    if (chapterCount < 1) throw "Invalid chapter counter value.";
    this->copyChapters(chapterPageCounts, chapterCount);
}

bool Book::hasShortChapter(int maxPages) const {
    // TODO: check if any chapter has pages <= maxPages
    if (maxPages < 1) throw "Invalid page counter value.";
    for (int i = 0; i < this->chapterCount; i++) {
        if (this->chapterPageCounts[i] <= maxPages) {
            std::cout << std::endl << "Book " << this->title << " has at least a chapter with less or equal pages to " << maxPages << ".";
            return true;
        }
    }
    std::cout << std::endl << "Book " << this->title << " chapters have more than " << maxPages << " pages.";
    return false;
}

int Book::getIndexOfFirstChapterWithPages(int pages) const {
    // TODO: find first chapter with exactly 'pages' pages, or -1
    for (int i = 0; i < this->chapterCount; i++) {
        if (this->chapterPageCounts[i] == pages) {
            std::cout << std::endl << "Book " << this->title << " has chapter " << i << " with matching number of " << pages << " pages.";
            return i;
        }
    }
    std::cout << std::endl << "Book " << this->title << " has no chapter with matching number of " << pages << " pages";
    return -1;
}

bool Book::isLongerThan(const Book& other) const {
    // TODO: compare total pages of *this with other
    //std::cout << std::endl << "Total A vs Total B: " << this->getTotalPages() << ", " << other.getTotalPages();
    if (this->getTotalPages() == other.getTotalPages()) {
        std::cout<<std::endl << "Both books have the exat same total number of pages.";
        return false;
    }
    if (this->getTotalPages() > other.getTotalPages()) {
        std::cout << std::endl << "Book " << this->title << " has more pages than book " << other.title << ".";
        return true;
    }
    std::cout << std::endl << "Book " << this->title << " has less pages than book " << other.title << ".";
    return false;
}

int Book::getNumberOfChaptersWithinInterval(int minPages, int maxPages) const {
    // TODO: count chapters with pages in [minPages, maxPages]
    int counter = 0;
    for (int i = 0; i < chapterCount; i++) {
        if (this->chapterPageCounts[i] >= minPages && this->chapterPageCounts[i] <= maxPages) counter++;
    }
    if (counter == 0) std::cout << std::endl << "Book " << this->title <<" has no chapters with pages count between "<< minPages << " and " << maxPages << ".";
    else std::cout<<std::endl<<"Book "<<this->title<<" has "<<counter<<" chapters with pages count between "<<minPages << " and " << maxPages << ".";
    return counter;
}

bool Book::canBeReadInDays(int days, int maxPagesPerDay) const {
    // TODO: check if total pages <= days * maxPagesPerDay
    if (this->getTotalPages() <= days * maxPagesPerDay) {
        std::cout << std::endl << "Book "<<this->title<<" can be read in " << days << " days, at a rate of " << maxPagesPerDay << 
            " maximum pages per day.";
        return true;
    }
    std::cout << std::endl << "Book "<<this->title<<" can not be read in " << days << " days, at a rate of " 
        << maxPagesPerDay << " maximum pages per day.";
    return false;
}

int Book::getNumberOfBooksCreated() {
    // TODO: return number of created books (nextId)
    std::cout << std::endl<<std::endl << "Total number of book objects created so far: " << nextId<<std::endl;
    return nextId;
}

void Book::copyChapters(const int* chapterPageCounts, int chapterCount) {
    delete[] this->chapterPageCounts;
    this->chapterPageCounts = new int[chapterCount];
    for (int i = 0; i < chapterCount; i++) {
        this->chapterPageCounts[i] = chapterPageCounts[i];
    }
    this->chapterCount = chapterCount;
}

void Book::display() {
    std::cout << std::endl << "________________Book " << this->title << " details______________";
    std::cout << std::endl << "Title: " << this->title;
    std::cout << std::endl << "ID: " << this->id;
    std::cout << std::endl << "Chapters: " << this->chapterCount;
    std::cout << std::endl << "Pages per chapter: ";
    for (int i = 0; i < this->chapterCount; i++) {
        std::cout << this->chapterPageCounts[i] << ", ";
    }
    std::cout << std::endl << "Total pages: " << this->getTotalPages();
    std::cout << std::endl << "Average number of pages per chapter: " << this->getAverageChapterPages();

}

int main() {
    int array[] = { 3, 5, 10, 20 };
    int size = sizeof(array) / sizeof array[0];
    int array2[] = { 10, 20, 30, 50 };
    int size2 = sizeof(array2) / sizeof array[0];
    std::cout << std::endl << "Test array size: " << size;

    Book a("Test01", array, size);
    a.display();

    Book b("Test02", array2, size2);
    b.display();
    
    Book c(a);
    c.display();

    c.getChapterPages(2);
    c.hasShortChapter(15);
    c.getIndexOfFirstChapterWithPages(10);
    c.isLongerThan(b);
    c.getNumberOfChaptersWithinInterval(3, 15);
    c.canBeReadInDays(10, 1);

    Book::getNumberOfBooksCreated();
}