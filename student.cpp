#include "student.hpp"
#include <iostream>
#include <string.h>
#include <vector>
#include <math.h>
#include <limits>
#include <typeinfo>
#include <iomanip>
#include <exception>
using namespace std;
////////////STUDENT CLASS//////////////

Student::Student()
{ //student initialization
}

string Student::getLastName()
{ //returns last name
	return lastName;
}

string Student::getFirstName()
{ //returns first name
	return firstName;
}

float Student::getCGPA()
{ //returns CGPA
	return CGPA;
}

int Student::getResearchPt()
{ //returns research score
	return researchScore;
}

int Student::getAppNum()
{ //returns application number
	return appNum;
}

bool Student::isEmpty() {
	return empty;
}

void Student::setLastName(string i)
{ //sets last name
	lastName = i;
	empty = false;
}

void Student::setFirstName(string i)
{ //sets first name
	firstName = i;
	empty = false;
}

void Student::setCGPA(float i)
{ //sets and rounds CGPA to 1 decimal place
	i = round(i * 10) / 10;
	CGPA = i;
	empty = false;
}

void Student::setResearchPt(int i)
{ //sets research score
	researchScore = i;
	empty = false;
}

void Student::setAppNum(int i)
{ //sets application number
	appNum = i;
	empty = false;
}

int compareCGPA(Student student1, Student student2)
{ //compares CGPA returns -1 if student1 > student2 and 1 if < and 0 if ==
	if (student1.getCGPA() > student2.getCGPA())
	{
		return -1;
	}
	else if (student1.getCGPA() < student2.getCGPA())
	{
		return 1;
	}
	else if (student1.getCGPA() == student2.getCGPA())
	{
		return 0;
	}
	return 1;
}

int compareResearch(Student student1, Student student2)
{ //compares research score, same algo as above
	if (student1.getResearchPt() > student2.getResearchPt())
	{
		return -1;
	}
	else if (student1.getResearchPt() < student2.getResearchPt())
	{
		return 1;
	}
	else if (student1.getResearchPt() == student2.getResearchPt())
	{
		return 0;
	}
	return 1;
}

int compareFirstName(Student student1, Student student2)
{ //compares student1 to student2 first name, returns 1 if s1 > s2, -1 if s1 < s2 and 0 if ==
	string s1 = student1.getFirstName();
	string s2 = student2.getFirstName();
	int sSize;

	if (s1.size() <= s2.size())
	{
		sSize = s1.size();
	}
	else
	{
		sSize = s2.size();
	}

	for (int i = 0; i < sSize; i++)
	{
		s1[i] = tolower(s1[i]);
		s2[i] = tolower(s2[i]);
		if (s1[i] > s2[i])
		{
			return 1;
		}
		else if (s1[i] < s2[i])
		{
			return -1;
		}
		else
		{
			continue;
		}
	}
	return 0;
}

int compareLastName(Student student1, Student student2)
{ //compares student1 to student2, same algo as compareFirstName
	string s1 = student1.getLastName();
	string s2 = student2.getLastName();
	int sSize;

	if (s1.size() <= s2.size())
	{
		sSize = s1.size();
	}
	else
	{
		sSize = s2.size();
	}

	for (int i = 0; i < sSize; i++)
	{
		s1[i] = tolower(s1[i]);
		s2[i] = tolower(s2[i]);
		if (s1[i] > s2[i])
		{
			return 1;
		}
		else if (s1[i] < s2[i])
		{
			return -1;
		}
		else
		{
			continue;
		}
	}
	return 0;
}

int isEqualCGPA(Student student1, float CPGA)
{
	double studentCPGA = student1.getCGPA();
	if (studentCPGA == CPGA)
	{
		return 1;
	}
	else if (studentCPGA > CPGA)
	return 2;

	else{
		return 0;
	}
}

int isEqualresearch(Student student1, int research)
{
	int studentResearch = student1.getResearchPt();
	if (studentResearch == research)
	{
		return 1;
	}
	else if (studentResearch > research)
	return 2;
	
	else{
		return 0;
	}
}

bool isEqualID(Student student1, int ID)
{
	int studentID = student1.getAppNum();
	if (studentID == ID)
	{
		return true;
	}
	return false;
}

bool isEqualLastName(Student student1, string name)
{
	string lastName = student1.getLastName();
	int sSize;
	if (lastName.size() <= name.size())
	{
		sSize = lastName.size();
	}
	else
	{
		sSize = name.size();
	}
	//converting everthing to lower case
	for (int i = 0; i < sSize; i++)
	{
		lastName[i] = tolower(lastName[i]);
		name[i] = tolower(name[i]);
	}
	//then compare
	if (lastName == name)
	{
		return true;
	}
	return false;
}

bool isEqualFirstName(Student student1, string name)
{
	string fristName = student1.getFirstName();
	int sSize;
	if (fristName.size() <= name.size())
	{
		sSize = fristName.size();
	}
	else
	{
		sSize = name.size();
	}
	//converting everthing to lower case
	for (int i = 0; i < sSize; i++)
	{
		fristName[i] = tolower(fristName[i]);
		name[i] = tolower(name[i]);
	}
	//then compare
	if (fristName == name)
	{
		return true;
	}
	return false;
}

///////////DOMESTIC CLASS////////////

DomesticStudent::DomesticStudent()
{ //constructor
}

string DomesticStudent::getProvince()
{ //returns province
	return province;
}

void DomesticStudent::setProvince(string i)
{ //sets province
	province = i;
}

int compareProvince(DomesticStudent student1, DomesticStudent student2)
{ //compares student1 to student2 province, returns 1 if student1 > student2, -1 if <, and 0 if ==
	string province1 = student1.province;
	string province2 = student2.province;

	for (int i = 0; i < province1.size(); i++)
	{
		if (province1[i] >= 'a' && province1[i] <= 'z')
		{
			province1[i] -= ('a' - 'A');
		}
	}
	for (int i = 0; i < province2.size(); i++)
	{
		if (province2[i] >= 'a' && province2[i] <= 'z')
		{
			province2[i] -= ('a' - 'A');
		}
	}
	return province1.compare(province2);
}

bool isequalProvince(DomesticStudent student1, string province){
	string province1 = student1.province;

	for (int i = 0; i < province1.size(); i++)
	{
		if (province1[i] >= 'a' && province1[i] <= 'z')
		{
			province1[i] -= ('a' - 'A');
		}
	}
	for (int i = 0; i < province.size(); i++)
	{
		if (province[i] >= 'a' && province[i] <= 'z')
		{
			province[i] -= ('a' - 'A');
		}
	}
	if (province1 == province){
		return true;
	}
	if (province == "NA"){
		return true;
	}
	return false;
}

ostream &operator<<(ostream &os, DomesticStudent &ds)
{ //prints out object info
	cout << "\n"
		 << ds.getFirstName() << "\n"
		 << ds.getLastName() << "\n"
		 << ds.getResearchPt() << "\n"
		 << ds.getAppNum() << "\n"
		 << ds.getProvince();
}

/////////INTERNATIONAL CLASS/////////

InternationalStudent::InternationalStudent()
{ //constructor
}

string InternationalStudent::getCountry()
{ //returns country
	return country;
}

void InternationalStudent::setCountry(string i)
{ //return country
	country = i;
}

ToeflScore InternationalStudent::getToefl()
{ //return ToeflScore object
	return toeflScore;
}

ToeflScore *InternationalStudent::getToeflRef()
{ //return ToeflScore object
	return &toeflScore;
}

void InternationalStudent::setToefl(int reading, int listening, int speaking, int writing)
{ //sets all variabls of toefl
	//use this one to load the inputs
	toeflScore.setReadingPt(reading);
	toeflScore.setListeningPt(listening);
	toeflScore.setSpeakingPt(speaking);
	toeflScore.setWritingPt(writing);
}

void InternationalStudent::setToefl(int sum)
{ //sets sum of toefl
	toeflScore.setSum(sum);
}

int compareCountry(InternationalStudent student1, InternationalStudent student2)
{ //compares country of student1 and student2, returns 1 if val of student1 is greater, 0 if equal, and -1 if lesser
	string country1 = student1.getCountry();
	string country2 = student2.getCountry();

	for (int i = 0; i < country1.size(); i++)
	{
		if (country1[i] >= 'a' && country1[i] <= 'z')
		{
			country1[i] -= ('a' - 'A');
		}
	}
	for (int i = 0; i < country2.size(); i++)
	{
		if (country2[i] >= 'a' && country2[i] <= 'z')
		{
			country2[i] -= ('a' - 'A');
		}
	}
	return country1.compare(country2);
}

bool qualified(InternationalStudent student)
{ //evaluates qualification of object
	int reading = student.getToefl().getReadingPt();
	int listening = student.getToefl().getListeningPt();
	int speaking = student.getToefl().getSpeakingPt();
	int writing = student.getToefl().getWritingPt();
	int sum = writing + speaking + listening + reading;
	if (reading < 20 || listening < 20 || speaking < 20 || writing < 20 || sum < 93)
	{
		return false;
	}
	return true;
}

int isEqualTOEFL(InternationalStudent student, int total){
	int reading = student.getToefl().getReadingPt();
	int listening = student.getToefl().getListeningPt();
	int speaking = student.getToefl().getSpeakingPt();
	int writing = student.getToefl().getWritingPt();
	int sum = writing + speaking + listening + reading;
	if (sum == total){
		return 1;
	}
	else if(sum > total)
	{
		return 2;
	}
	return 0;
}

ostream &operator<<(ostream &os, InternationalStudent &is)
{ //outputs InternationalStudent object  member variables
	cout << "\n"
		 << is.getFirstName() << "\n"
		 << is.getLastName() << "\n"
		 << is.getResearchPt() << "\n"
		 << is.getAppNum() << "\n"
		 << is.getCountry() << "\nReading: " << is.getToefl().getReadingPt()
		 << "\nListening: " << is.getToefl().getListeningPt() << "\nSpeaking: " << is.getToefl().getSpeakingPt()
		 << "\nWriting: " << is.getToefl().getWritingPt() << "\nToefl Sum: " << is.getToefl().sumTotal();
}

///////////TOEFL SCORE///////////

ToeflScore::ToeflScore()
{ //constructor
}

int ToeflScore::getReadingPt()
{ //returns reading member variable
	return reading;
}

int ToeflScore::getListeningPt()
{ //returns listening member variable
	return listening;
}

int ToeflScore::getSpeakingPt()
{ //returns speaking member variable
	return speaking;
}

int ToeflScore::getWritingPt()
{ //returns writing member variable
	return writing;
}

void ToeflScore::setReadingPt(int i)
{ //sets reading member variable
	reading = i;
	setSum();
}

void ToeflScore::setListeningPt(int i)
{ //sets listening member vairable
	listening = i;
	setSum();
}

void ToeflScore::setSpeakingPt(int i)
{ //sets speaking member variable
	speaking = i;
	setSum();
}

void ToeflScore::setWritingPt(int i)
{ //sets writing member variable
	writing = i;
	setSum();
}

void ToeflScore::setSum() 
{
	sum = totalScore;
}

void ToeflScore::setSum(int i)
{ //independently sets sum member variable, used to override value of sumTotal()
	sum = i;
}

int ToeflScore::sumTotal()
{ //sets sum from member variables
	sum = reading + listening + speaking + writing;
	return sum;
}

