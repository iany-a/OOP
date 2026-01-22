#include <iostream>
#include <string>

using namespace std;

enum class PlatformType {
	UNIVERSITY,
	MOOC,
	CORPORATE
};


class OnlineCoursePlatform {
	const string platformWebUrl = "";
	int noCourses = 0;
	string* courseTitles = nullptr;
	static int MAX_COURSES;
	PlatformType type = PlatformType::UNIVERSITY;
public:

	void setCourses(string* courseTitles, int noCourses) {
		if (courseTitles == nullptr || noCourses < 1 || noCourses > MAX_COURSES) throw "Invalid arguments.";
		delete[] this->courseTitles;
		this->courseTitles = new string[noCourses];
		for (int i = 0; i < noCourses; i++) {
			if (courseTitles[i] == "") throw "Invalid input.";
			this->courseTitles[i] = courseTitles[i];
		}
		this->noCourses = noCourses;
	}

	OnlineCoursePlatform(const string platformWebUrl, int noCourses, string* courseTitles, PlatformType type): platformWebUrl(platformWebUrl){
		setCourses(courseTitles, noCourses);
		this->type = type;
	}



	void display() {
		cout << endl << "Printing object details: ";
		cout << endl << this->platformWebUrl;
		cout << endl << "Number of courses: " << this->noCourses;
		if (this->noCourses > 0) {
			cout << endl << "Course Titles: " << this->courseTitles[0];
			for (int i = 1; i < this->noCourses; i++) cout << ", " << this->courseTitles[i];
		}
		cout << endl << "Course type: ";
		switch (this->type) {
		case PlatformType::UNIVERSITY: cout << "University";
			break;
		case PlatformType::CORPORATE: cout << "Corporate";
			break;
		case PlatformType::MOOC: cout << "MOOC";
			break;
		default: cout << endl << "Undefined";
		}
	}

	~OnlineCoursePlatform() {
		cout << endl << "Destructor called for: " << this->platformWebUrl;
		delete[] this->courseTitles;
	}

	bool operator!() {
		if (this->noCourses == 0 || (this->type == PlatformType::UNIVERSITY && this->noCourses < 5)) return true;
		return false;
	}

	OnlineCoursePlatform(const OnlineCoursePlatform& source) : platformWebUrl(source.platformWebUrl) {
		cout << endl << "Copy constructor called!";
		this->noCourses = source.noCourses;
		this->type = source.type;
		if (source.noCourses == 0) this->courseTitles = nullptr;
		else {
			this->courseTitles = new string[source.noCourses];
			for (int i = 0; i < source.noCourses; i++) {
				this->courseTitles[i] = source.courseTitles[i];
			}
		}
	}

	OnlineCoursePlatform operator-(int value) {
		if (value > this->noCourses || value < 0) throw "Invalid arguments.";
		OnlineCoursePlatform newObj = *this;
		if (value == 0) return newObj;
		delete[] newObj.courseTitles;

		newObj.courseTitles = new string[this->noCourses - value];
		for (int i = 0; i < this->noCourses - value; i++) {
			newObj.courseTitles[i] = this->courseTitles[i];
		}
		newObj.noCourses = this->noCourses - value;
		return newObj;
	}


};

int OnlineCoursePlatform::MAX_COURSES = 100;


int main() {
	string courses[3] = { "OOP", "JAVA", "Micro" };
	int size = sizeof(courses) / sizeof(courses[0]);
	OnlineCoursePlatform a("https://google.com/a", size, courses, PlatformType::UNIVERSITY);
	a.display();
	string  courses2[3] = { "BPC", "BTI", "Algebra" };
	a.setCourses(courses2, 3);
	a.display();

	OnlineCoursePlatform* b = new OnlineCoursePlatform("https://google.com/b", size, courses, PlatformType::UNIVERSITY);
	b->display();
	delete b;
	b = nullptr;

	OnlineCoursePlatform c = a;
	c.display();
	string courses3[5] = { "DSAD", "Econometrics", "PSI", "Android", "WebTech" };
	c.setCourses(courses3, 5);
	cout << endl;
	if (!c) cout << "Inactive.";
	else cout << "Active.";

	OnlineCoursePlatform d = a - 3;
	d.display();
	a.display();

}