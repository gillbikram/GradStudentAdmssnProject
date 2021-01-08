//header file student.hpp to declare your classes
#ifndef STUDENT_H
#define STUDENT_H

using namespace std; //use namespace std
#include <string>    //you will have to use string in C++
#include <vector>

//Parent class
class Student
{
public:
    //consructor
    Student(); 
    //constructor to initializing a new student with the given info
    
    //get functions
    string getLastName();
    //Precondition:the respective child class object must be instantiated
    //Postcondition:returns the last name of the student
    string getFirstName();
    //Precondition:the respective child class object must be instantiated
    //Postcondition:returns the first name of the student
    float getCGPA();
    //Precondition:the respective child class object must be instantiated
    //Postcondition:returns the CGPA name of the student
    int getResearchPt();
    //Precondition:the respective child class object must be instantiated
    //Postcondition:returns the Research score of the student
    int getAppNum();
    //Precondition:the respective child class object must be instantiated
    //Postcondition:returns the application id of the student
    bool isEmpty();
    //Precondition:the respective child class object must be instantiated
    //Postcondition:returns true if the student information is missing
    
    //set functions
    void setLastName(string i);
    //Precondition:the input is a string object.
    //Postcondition:assigns the last name to the respective child classs object.
    void setFirstName(string i);
    //Precondition:the input is a string object.
    //Postcondition:assigns the first name to the respective child classs object.
    void setCGPA(float i);
    //Precondition:the input must be a non negative number.
    //Postcondition:assigns the CGPA to the respective child classs object.
    void setResearchPt(int i);
    //Precondition:the input must be a non negative number.
    //Postcondition:assigns the research score to the respective child classs object.
    void setAppNum(int i);
    //Precondition:the input must be a non negative number.
    //Postcondition:assigns the appliction id to the respective child classs object.

    //compare friend functions for CGPA, research score, last name and first name
    //Both international student class and domestic student class can use these
    friend int compareCGPA(Student student1, Student student2);
    //Precondition:Both students must me assigned and must be non-empty.
    //Postcondition:returns the compared result about Cgpa between the students.  
    friend int compareResearch(Student student1, Student student2);
    //Precondition:Both students must me assigned and must be non-empty.
    //Postcondition:returns the compared result about research score between the students.  
    friend int compareLastName(Student student1, Student student2);
    //Precondition:Both students must me assigned and must be non-empty.
    //Postcondition:returns the compared result about last name between the students.  
    friend int compareFirstName(Student student1, Student student2);
    //Precondition:Both students must me assigned and must be non-empty.
    //Postcondition:returns the compared result about first name between the students.  
    friend int isEqualCGPA(Student student1, float CPGA);
    //Precondition:Student must be assigned and must be non-empty.
    //Postcondition:returns 1 if the input cgpa is of the student.  
    friend int isEqualresearch(Student student1, int research);
    //Precondition:Student must be assigned and must be non-empty.
    //Postcondition:returns 1 if the input research score is of the student.
    friend bool isEqualID(Student student1, int ID);
    //Precondition:Student must be assigned and must be non-empty.
    //Postcondition:returns true if the input application id is of the student.
    friend bool isEqualLastName(Student student1, string name);
    //Precondition:Student must be assigned and must be non-empty.
    //Postcondition:returns true if the input last name is of the student.
    friend bool isEqualFirstName(Student student1, string name);
    //Precondition:Student must be assigned and must be non-empty.
    //Postcondition:returns true if the input first name is of the student.


private:
    bool empty = true;
    string firstName;
    string lastName;
    float CGPA;
    int researchScore;
    int appNum; //application number
};
//sub calss inheriting from the student class
class DomesticStudent : public Student
{
public:
    //constructor
    DomesticStudent();
    //constructor to initializing a new domestic student with the given info
    
    //get province function
    string getProvince();
    //Precondition:student object must be instantiated
    //Postcondition:returns the province that the student belongs to.
    
    //set province function
    void setProvince(string i);
    //Precondition:the input is a string object
    //Postcondition:assigns the input province to the student object. 
    
    //compare province function
    friend int compareProvince(DomesticStudent student1, DomesticStudent student2);
    //Precondition:Both students must me assigned and must be non-empty.
    //Postcondition:returns the compared result of province of both the students.
    friend bool isequalProvince(DomesticStudent student1, string province);
    //Precondition:Student must be assigned and must be non-empty.
    //Postcondition:return true if the student is of the input province.
private:
    string province;
    bool legitForScholarships;
    friend std::ostream &operator<<(std::ostream &os, DomesticStudent &ds);
};

class ToeflScore
{
public:
    //constructor
    ToeflScore();
    //constructor to initializing a new Toefl with the given info
    
    //get functions
    int getReadingPt();
    //Precondition:International student object must be instantiated
    //Postcondition:return the toefl reading score of the student.
    int getListeningPt();
    //Precondition:International student object must be instantiated
    //Postcondition:return the toefl listening score of the student.
    int getSpeakingPt();
    //Precondition:International student object must be instantiated
    //Postcondition:return the toefl speaking score of the student.
    int getWritingPt();
    //Precondition:International student object must be instantiated
    //Postcondition:return the toefl writing score of the student.
    
    //set functions
    void setReadingPt(int i);
    //Precondition:the input must be a non negative number.
    //Postcondition:assigns the toefl reading score of the student.
    void setListeningPt(int i);
    //Precondition:the input must be a non negative number.
    //Postcondition:assigns the toefl listening score of the student.
    void setSpeakingPt(int i);
    //Precondition:the input must be a non negative number.
    //Postcondition:assigns the toefl speaking score of the student.
    void setWritingPt(int i);
    //Precondition:the input must be a non negative number.
    //Postcondition:assigns the toefl writing score of the student.
    void setSum();
    //Precondition:the student object must be instantiated.
    //Postcondition:assign the total score to the repective student.
    void setSum(int i);
    //Precondition:the input must be a non negative number.
    //Postcondition:assigns the totalscore independently to the student override sumTotal()
    
    //sum up the total
    int sumTotal();
    //Precondition:the student object must be instantiated with all the individual scores.
    //Postcondition:returns the total score of the student.

private:
    int reading, listening, speaking, writing;
    int sum;
    int totalScore = reading + listening + speaking + writing;
};

class InternationalStudent : public Student
{
public:
    //constructor to initializing a new international student with the given info
    InternationalStudent();
    
    //get functions
    string getCountry();
    //Precondition:student object must be instantiated
    //Postcondition:returns the country that the student belongs to.
    
    //set functions
    void setCountry(string i);
    //Precondition:the input is a string object
    //Postcondition:assigns the input country to the student object.
    void setToefl(int reading, int listening, int speaking, int writing);
    //Precondition:all the four input are non negative number and must be assigned.
    //Postcondition:assigns the individual scores to the student object.
    void setToefl(int sum);
    //Precondition:the input is the total score and must be a non negative number
    //Postcondition:assigns the total score to the student object.
    
    //type functions
    ToeflScore getToefl();
    //Precondition:the student must be assigned the total score.
    //Postcondition:return the Toefl total score of the student.
    ToeflScore *getToeflRef();
    //Precondition:the Toeflscore object must be instantiated.
    //Postcondition:returns the Toeflscore object.
    
    //compare function to compare country
    friend int compareCountry(InternationalStudent student1, InternationalStudent student2);
    //Precondition:Both students must me assigned and must be non-empty.
    //Postcondition:returns the compared result of countries of both the students.
    
    //friend bool function to determine if the TOEFL score set is qualified for the standards
    friend bool qualified(InternationalStudent student);
    //Precondition:student must be assigned and must be non-empty.
    //Postcondition:return true if the student Toefl scores meet the requirements.
    friend int isEqualTOEFL(InternationalStudent student, int total);
    //Precondition:student must me assigned and must be non-empty.
    //Postcondition:returns 1 if the input Toefl score is equal to that of student.
    
    //<<operator overload
    friend std::ostream &operator<<(std::ostream &os, InternationalStudent &is);
    //Precondition:International student object must be instantiated
    //Postcondition:Outputs the member variables of the international student.

private:
    string country;
    ToeflScore toeflScore;
};


#endif
