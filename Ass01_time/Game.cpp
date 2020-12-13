#include <assert.h>

#include "Game.h"


/*
* Get a random nubmer in the given range
min - IN bottom of the range
max - IN top o fthe range
precond - the random number generator has been seeded
postcond - returns the random result
*/
float GetRandRange(float min, float max)
{
	float toOne = (float)(rand() % RAND_MAX) / (float)RAND_MAX;

	return min + max * toOne;
}
//same thing but pass by reference
void GetRandRange(float min, float max, float& result)
{
	float toOne = (float)(rand() % RAND_MAX) / (float)RAND_MAX;

	result = min + max * toOne;
}


void Game::Keyboard(sf::Keyboard::Key code)
{
	if (code == sf::Keyboard::Space)
	{
		//keyboard stuff
		rndOffset = (float)(rand() % 360);
		rndOffset2 = (float)(rand() % 360);
	}
}


void Game::Initialise()
{
	if (texAnaFace.loadFromFile("data/clock_face.png") == false)
		assert(false);
		
	if (texAnaHands.loadFromFile("data/clock_hands.png") == false)
		assert(false);
		
}

void Game::Render(sf::RenderWindow& window)
{
	sf::Vector2f pos{ 600.f,400.f };
	for (int i = 0; i < 20; ++i)
	{
		sf::Vector2f npos;
		float clockAngOff = clockAng + i * 3.141f * 0.1f;
		npos.x = pos.x + sinf(clockAngOff) * 200;
		npos.y = pos.y + cosf(clockAngOff) * 200;
		RenderClockFace(window, npos, baseRotation, 0.25f);
	}
}

void Game::RenderClockFace(sf::RenderWindow& window, sf::Vector2f& pos, float angle, float scale)
{
	sf::Sprite spr(texAnaFace);
	spr.setOrigin(sf::Vector2f{ 256,256 });
	spr.setPosition(pos);
	spr.setScale(scale, scale);
	window.draw(spr);

	spr.setTexture(texAnaHands, true);
	spr.setRotation(angle);
	sf::IntRect rect{ 92,0,60,512 };
	sf::Vector2f ori{ 30,457 };
	spr.setOrigin(ori);
	spr.setPosition(pos);
	spr.setTextureRect(rect);
	spr.setScale(scale * 0.5f, scale * 0.5f);
	window.draw(spr);
}

void Game::Update(float dT)
{
	const float ROT_SPEED = 25;
	baseRotation += dT * ROT_SPEED;
	const float scale = 0.5f;
	clockAng += dT * 0.5f;
}


//------Time Class------

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
int Time::getHours() const { 								//return a data member value, hrs_
	return hrs_;
}
int Time::getMinutes() const {								//return a data member value, mins_
	return mins_;
}
int Time::getSeconds() const {								//return a data member value, secs_
	return secs_;
}
void Time::setTime(int h, int m, int s) {					//set the time
	hrs_ = h;
	mins_ = m;
	secs_ = s;
}
void Time::readInTime() {  									//read in time form user
	cout << "Enter the hours: ";
	cin >> hrs_;
	cout << "Enter the minutes: ";
	cin >> mins_;
	cout << "Enter the seconds: ";
	cin >> secs_;
}
void Time::displayTime() const {							//display time (00:00:00)
	const char prev(cout.fill('0')); 						//save previous fill and set it to new value
	cout << setw(2) << hrs_ << ":"
		<< setw(2) << mins_ << ":"
		<< setw(2) << secs_;
	cout.fill(prev); 										//reset previous fill
}

//private support functions_______________________________________________
long long Time::toSeconds() const {							//return time in seconds
	return (hrs_ * 3600) + (mins_ * 60) + secs_;
}

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
	Time aTime(t.tm_hour, t.tm_min, t.tm_sec);				//line5
	cout << "\nAt the end of getCut=rrentTime...";
	return(aTime);											//line6
}