////////////////////////////////////////////////////////////////////////
// OOP Tutorial 4: Object Creation using a Time class (version 0: to be modified)
////////////////////////////////////////////////////////////////////////

//--------include libraries
#include <ctime>		//for time
#include <iostream>		//for cin >> and cout <<
#include <sstream>		//for string stream processing
#include <string>		//for string routines
#include <iomanip>		//for setw, setfill
using namespace std;

//--------Time class
class Time {
public:
	Time();			//default constructor
	Time(const Time&);	//copy constructor

	Time(int h, int m, int s);			// bespoke contructor
	Time(long long);					// conversion constructor
	Time(const string& timeAsString);	// conversion constructor

	~Time();			//destructor
	int getHours() const;	//return a data member value, hrs_
	int getMinutes() const;	//return a data member value, mins_
	int getSeconds() const;	//return a data member value, secs_
	void setTime(int, int, int);	//set the time to 3 given values
	void readInTime();	//input time from user
	void displayTime() const;	//display in 00:00:00 digital clock format
private:
	int hrs_, mins_, secs_;
	long long toSeconds() const;	//return the time in seconds
};

//public functions_______________________________________________

//Time::Time() 
//: hrs_(0), mins_(0), secs_(0)
//{
//	cout << "\nCalling Time() default constructor! ";
//}
//Q6
/*
Time::Time() {	//default constructor
	time_t now = time(0);
	struct tm t;
	localtime_s(&t, &now);
	hrs_ = t.tm_hour;
	mins_ = t.tm_min;
	secs_ = t.tm_sec;
	cout << "\nCalling amended Time() default constructor!";
}*/

int getCurrentHours() {
	time_t now = time(0);
	struct tm t;
	localtime_s(&t, &now);
	return t.tm_hour;
}
int getCurrentMinutes() {
	time_t now = time(0);
	struct tm t;
	localtime_s(&t, &now);
	return t.tm_min;
}
int getCurrentSeconds() {
	time_t now = time(0);
	struct tm t;
	localtime_s(&t, &now);
	return t.tm_sec;
}
Time::Time()	//default constructor
	: hrs_(getCurrentHours()),
	mins_(getCurrentMinutes()),
	secs_(getCurrentSeconds())
{}


//using memberwise initialisation
Time::Time(const Time& t) 
: hrs_(t.hrs_), mins_(t.mins_), secs_(t.secs_)
{
	cout << "\n   Calling Time(const Time& t) copy constructor!";
}
//Q1
// Create Time from 3 integers representing its hours, minutes ansd seconds
Time::Time(int h, int m, int s)
	: hrs_(h), mins_(m), secs_(s)
{
	cout << "\nCalling Time(int h, int m, int s) bespoke constructor! ";
}
// Create Time from a long long number of seconds
Time::Time(long long s)
	: hrs_(((s / 60) / 60) % 24),
	mins_((s / 60) % 60),
	secs_(s % 60)
{
	cout << "\nCalling Time(long long) conversion constructor! ";
}
//

Time::~Time() {
	cout << "\n   Calling ~Time() destructor!";
}
int Time::getHours() const { 	//return a data member value, hrs_
	return hrs_;
}
int Time::getMinutes() const {	//return a data member value, mins_
	return mins_;
}
int Time::getSeconds() const {	//return a data member value, secs_
	return secs_;
}
void Time::setTime(int h, int m, int s) {	//set the time
	hrs_ = h;
	mins_ = m;
	secs_ = s;
}
void Time::readInTime() {  	//read in time form user
	cout << "Enter the hours: ";
	cin >> hrs_;
	cout << "Enter the minutes: ";
	cin >> mins_;
	cout << "Enter the seconds: ";
	cin >> secs_;
}
void Time::displayTime() const {	 //display time (00:00:00)
	const char prev(cout.fill ('0')); 	//save previous fill and set it to new value
	cout << setw(2) << hrs_ << ":"
	     << setw(2) << mins_ << ":"
	     << setw(2) << secs_;
	cout.fill(prev); 	//reset previous fill
}

//private support functions_______________________________________________
long long Time::toSeconds() const {	 //return time in seconds
	return (hrs_ * 3600) + (mins_ * 60) + secs_;
}

//--------end of Time class

bool isPM(const Time& t) {
	cout << "\nInside isPM...";
	return (t.getHours() >= 12);
	cout << "\nAt the ened of isPM...";
}

Time getCurrentTime() {
	cout << "\nIside getCurrentTime....";
	time_t now = time(0);
	struct tm t;
	localtime_s(&t, &now);
	Time aTime(t.tm_hour, t.tm_min, t.tm_sec);	//line5
	cout << "\nAt the end of getCut=rrentTime...";
	return(aTime);	//line6
}

//---------------------------------------------------------------------------
int main()
{
	Time time3(1, 1, 1);
	time3.displayTime();
	cout << "\n";
	Time time4(3723);
	time4.displayTime();
	cout << "\n";
	Time time5("04:05:06");
	time5.displayTime();

	{
		Time t1;	//line1
		t1.setTime(6, 7, 8);
		Time t2(t1); 	//line2
		Time t3 = t1; 	//line3
	}

	{
		Time t4(12, 2, 3);
		cout << "\nBefore calling isPM";
		if (isPM(t4)) 	//line4
			cout << "\nt4 is in the afternoon";
		cout << "\nAfter calling isPM";
	}

	{
		Time t1; 	//line7
		cout << "\nBefore calling getCurrentTime";
		t1 = getCurrentTime();	//line8
		cout << "\nAfter calling getCurrentTime";
	}

	{
		cout << "\nBefore calling getCurrentTime";
		Time t5(getCurrentTime());	//line9
		cout << "\nAfter calling getCurrentTime";
	}

	Time t;
	const Time ct;
	/*
	cout << t.hrs_;

	cout << t.toSeconds();
	
	readInTime();
	*
	cout << t.displayTime();
	*/
	//cout << t.getHours;

	//ct.readInTime();

	

	cout << "\n\n__ Time t1\n";
	Time t1;
	t1.displayTime();

	cout << "\n\n__ cout << t1.getHours()\n";
	cout << t1.getHours();

	cout << "\n\n__ t1.displayTime()\n";
	t1.displayTime();

	cout << "\n\n__ t1.setTime(1,2,3)\n";
	t1.setTime(1,2,3);
	t1.displayTime();

	cout << "\n\n__ Time t2(t1)\n";
	Time t2(t1);
	t2.displayTime();

	cout << "\n\n__ t1.readInTime()\n";
	t1.readInTime();
	t1.displayTime();


	cout << endl << endl;
	system("pause");
	return 0;
}
