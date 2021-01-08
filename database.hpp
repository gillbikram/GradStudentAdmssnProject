#ifndef DATABASE_H
#define DATABASE_H

using namespace std; //use namespace std
#include <string>    //you will have to use string in C++
#include <vector>
#include "student.hpp"

class Node//node class for the linked list
{
public:
    //node for international and domestic objects
    Node(DomesticStudent stu);
    Node(InternationalStudent stu);
    //checks international or domestic student, returns char = i or d
    char intOrDom();
    DomesticStudent ds;
    InternationalStudent is;
    Node *next = NULL;
};

class StudentDatabase
{
public:
    //constructor to initializing a new international student with the given info
    StudentDatabase();
    ~StudentDatabase(); 
    StudentDatabase(StudentDatabase& sd);
    StudentDatabase& operator=(StudentDatabase& sd);
    //general sorting
    void sort();
    //adds student to end of linked list
    void append(DomesticStudent s);
    void append(InternationalStudent s);
    //mergeSort for linked list
    void general_isMergeSort();
    void general_isMergeSort(Node **hRef);
    Node *isSorter(Node *a, Node *b);
    //for domestic students
    void general_dsMergeSort();
    void general_dsMergeSort(Node **hRef);
    Node *dsSorter(Node *a, Node *b);
    //merge function, no print function is for the analysis
    void merge();
    void mergeNoPrint();

    void general_mMergeSort();
    void general_mMergeSort(Node **hRef);
    Node *mSorter(Node *a, Node *b);
    //split the list when doing merge sort
    void mergeSplit(Node *source, Node **fr, Node **br);
    //sort by first name only
    void sortFirstName();
    //sort by last name only
    void sortLastName();
    //sort by CGPA only
    void sortCGPA();
    //sort by research score only
    void sortResearch();
    //print function
    void print();
    void printVector();
    //search functions, linear search
    void searchByCGPA(float CGPA);
    void searchNoPrint(float CGPA);
    void searchByResearch(int research);
    void searchByID(int ID);
    //virtual function as required
    virtual void searchByCGPAandResearch(float CPGA, int research);
    //search functions cont
    void searchByLastName(string name);
    void searchByFristName(string name);
    bool searchByLastFristName(string fristName, string lastName);
    //get the student by certain parameters
    Node* getByFirstLastName(string firstName, string lastName);
    Node* getBeforeByFirstLastName(string firstName, string lastName);
    Node* getByAppNum(int appNum);
    Node* getByResearch(int research);
    Node* getByCGPA(float CGPA);
    //delete functions
    void deleteStudent(string firstName, string lastName);
    //delete head and tail
    void deleteHeadTail();
    //delete function for big o analysis
    void deleteStudentNoPrint(string firstName, string lastName);
    //filtering system, special feature
    void filteringInternational(float CGPA, int research, int TOEFL);
    void filteringDomestic(float CPGA, int research, string province);
    //insert a new student
    void addStudent();
    //insert function time analysis
    void addDomesticStudentTest(string firstName, string lastName, float CGPA, int research, string province);
    int latestAppNum();

    //node initializing
    Node *isHead = NULL;
    Node *isTail = NULL;

    Node *dsHead = NULL;
    Node *dsTail = NULL;

    Node *mHead = NULL;
    Node *mTail = NULL;

    ////ERROR CHECKING////
    void findMissingFields();
    void checkProvinces();
    void checkCountries();
    bool provinceCheck(string province);
    bool stringCheck(string input);

private:
    void concatenate(Node *a, Node *b);
    bool merged = false;
};

#endif