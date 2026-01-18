#include <iostream>
#include <string>

using namespace std;

//sub1

struct Date {
	int day = 0;
	int hour = 0;
	int minute = 0;
} myDate;

class Weather {
private:
	Date date = { 0, 0, 0 };
	float* temp = nullptr;
	int noRecordings = 0;
	string desc = "";
public:

	Weather(Date date, float* temp, int noRecordings, string desc) {
		this->date.day = date.day;
		this->date.hour = date.hour;
		this->date.minute = date.minute;
		setTemp(temp, noRecordings);
		this->desc = desc;
	}



	void setTemp(float* temp, int noRecordings) {
		if (temp == nullptr || noRecordings < 1) throw "Invalid arguments.";
		delete[] this->temp;
		this->temp = new float[noRecordings];
		for (int i = 0; i < noRecordings; i++) {
			this->temp[i] = temp[i];
		}
		this->noRecordings = noRecordings;
	}

	float* getTemp() {
		float* dummy = new float[this->noRecordings];
		for (int i = 0; i < this->noRecordings; i++) {
			dummy[i] = this->temp[i];
		}
		return dummy;
	}

	string getDate() {
		string date = "";
		string dstr = to_string(this->date.day);
		string hstr = to_string(this->date.hour);
		string mstr = to_string(this->date.minute);
		date = dstr + " " + hstr + " " + mstr;
		return date;
	}

	Weather(const Weather& source) {
		cout << endl << "Copy constructor has been called.";
		if (this == &source) {
			cout << endl << "Objects are equal. Aborting copy constructor.";
			return;
		}

		this->date = source.date;
		delete[] this->temp;
		this->temp = new float[source.noRecordings];
		for (int i = 0; i < source.noRecordings; i++) {
			this->temp[i] = source.temp[i];
		}
		this->noRecordings = source.noRecordings;
		this->desc = source.desc;
	}

	Weather() {
		delete[] this->temp;
	}

	Weather operator++(int) {
		//if (this->date.hour == 31) throw "can't modify date past las day of month.";

		if (this->date.hour == 23) {
			this->date.hour = 0;
			if (this->date.day != 31) this->date.day++;
			else throw "Invalid arguments";
		}
		else this->date.hour++;
		return *this;
	}

	Weather& operator+=(float value) {
		float* dummy = new float[this->noRecordings + 1];
		for (int i = 0; i < noRecordings; i++) {
			dummy[i] = this->temp[i];
		}
		dummy[noRecordings] = value;
		delete[] this->temp;
		this->temp = dummy;
		this->noRecordings++;
		return *this;
	}

	void display() {
		cout << endl << "Temperatures array: ";
		for (int i = 0; i < this->noRecordings; i++) {
			cout << endl << this->temp[i];
		}

	}

	void functionOne(Weather a) {
		cout << endl << a.desc;
	}

};

class Region {
protected:
	string name = "";
	Weather weather; //class has a weather object
public:
	virtual void getInfo() {
		cout << endl << "This is region " << this->name;
	}

	Region(string name, const Weather& weather) :name(name), weather(weather) {
	}
};

class Subregion : public Region {
	string sbName = "";
public:
	void getInfo() {
		cout << endl << "This is sub-region " << this->sbName << " included in region " << this->name;
	}
	Subregion(string sbName, string name, const Weather& weather) :sbName(sbName), Region(name, weather){
	}
};





int main() {
	float temps[3] = { 20.0, 24.0, 18.0 };
	float noTemps = sizeof(temps) / (sizeof(temps[0]));
	//cout << noTemps;
	Date dateDayHourMinutes = { 23, 23, 0 };
	Weather a(dateDayHourMinutes, temps, noTemps, "Test A");
	Weather b(a);
	cout << endl << a.getDate();
	a++;
	cout << endl << a.getDate();
	a += 21;
	a.display();
	a += 21;
	a.display();

	a.functionOne(a);

	Region regN("NORTH", a);
	Subregion sbreg("N1", "NORTH", a);

	Region regS("South", b);

	Region** regions = new Region*[3];
	regions[0] = &regN;
	regions[1] = &sbreg;
	regions[2] = &regS;

	for (int i = 0; i < 3; i++) {
		regions[i]->getInfo();
	}



}
