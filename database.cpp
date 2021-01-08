#include "student.hpp"
#include "database.hpp"
#include <iostream>
#include <string.h>
#include <vector>
#include <math.h>
#include <limits>
#include <typeinfo>
#include <iomanip>
#include <exception>
using namespace std;

///////////Database Operations//////////

//Constructor
StudentDatabase::StudentDatabase()
{ 

}

//Deletes all dynamically allocated nodes
StudentDatabase::~StudentDatabase() 
{
	Node *temp;
	if (!merged) 
	{
		while (dsHead != NULL)
		{
			temp = dsHead->next; 
			delete dsHead; 
			dsHead = temp; 
		}
		dsHead = NULL;
		dsTail = NULL;
		while (isHead != NULL) 
		{
			temp = isHead->next; 
			delete isHead;
			isHead = temp; 
		}
		isHead = NULL;
		isTail = NULL;
	}
	else 
	{
		while(mHead != NULL)
		{
			temp = mHead->next; 
			delete mHead; 
			mHead = temp; 
		}
		mHead = NULL; 
		mTail = NULL; 
	}
}

//Exact copy and assignment overloads using memcpy
StudentDatabase::StudentDatabase(StudentDatabase& sd)
{
	memcpy(this, &sd, sizeof(StudentDatabase));
}

StudentDatabase& StudentDatabase::operator=(StudentDatabase& sd)
{
	if (this == &sd) return *this;
	memcpy(this, &sd, sizeof(StudentDatabase)); 
	return *this;
}

//Uses merged member variable to decide which lists to print
void StudentDatabase::print()
{ 

	int counter = 0;

	Node *cursor;
	if (merged)
	{
		if (mHead == NULL) return;
		general_mMergeSort();
		cursor = mHead;

		cout << setw(15) << "Type"
			 << " | " << setw(15) << "First Name"
			 << " | " << setw(15) << "Last Name"
			 << " | " << setw(15) << "Research Score"
			 << " | " << setw(15) << "CGPA"
			 << " | " << setw(15) << "Country/Prov"
			 << " | " << setw(15) << "Toefl"
			 << endl;

		while (cursor != NULL)
		{
			if (cursor->ds.isEmpty())
			{
				if (qualified(cursor->is) == true)
				{
					cout << setw(15) << "International"
						 << " | " << setw(15) << cursor->is.getFirstName()
						 << " | " << setw(15) << cursor->is.getLastName()
						 << " | " << setw(15) << cursor->is.getResearchPt()
						 << " | " << setw(15) << cursor->is.getCGPA()
						 << " | " << setw(15) << cursor->is.getCountry()
						 << " | " << setw(15) << cursor->is.getToefl().sumTotal()
						 << " | "
						 << endl;
					counter++;
				}
			}
			if (cursor->is.isEmpty())
			{
				cout << setw(15) << "Domestic"
					 << " | " << setw(15) << cursor->ds.getFirstName()
					 << " | " << setw(15) << cursor->ds.getLastName()
					 << " | " << setw(15) << cursor->ds.getResearchPt()
					 << " | " << setw(15) << cursor->ds.getCGPA()
					 << " | " << setw(15) << cursor->ds.getProvince()
					 << " | " << setw(18)
					 << " | "
					 << endl;
				counter++;
			}
			cursor = cursor->next;
		}
		cout << endl
			 << "Rows printed: " << counter << endl;
		return;
	}
	int flag;

	while (1)
	{
		cout << "Press 1: print international. Press 2: print domestic\nInput: ";
		while (!(cin >> flag))
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Input must be numeric. Try again please: \n";
		}
		if (flag == 1 || flag == 2)
		{
			break;
		}
		else
		{
			cout << "Enter a proper option number please!" << endl;
		}
	}
	if (flag == 1)
	{
		cout << setw(15) << "Type"
			 << " | " << setw(15) << "First Name"
			 << " | " << setw(15) << "Last Name"
			 << " | " << setw(15) << "Research Score"
			 << " | " << setw(15) << "CGPA"
			 << " | " << setw(15) << "Country/Prov"
			 << " | " << setw(10) << "Tfl Read."
			 << " | " << setw(10) << "Tfl List."
			 << " | " << setw(10) << "Tfl Speak."
			 << " | " << setw(10) << "Tfl Writ."
			 << " | " << setw(10) << "Tfl Total"
			 << endl;
		if (isHead == NULL) return;
		general_isMergeSort();
		cursor = isHead;
		while (cursor != NULL)
		{
			if (qualified(cursor->is) == true)
			{

				cout << setw(15) << "International"
					 << " | " << setw(15) << cursor->is.getFirstName()
					 << " | " << setw(15) << cursor->is.getLastName()
					 << " | " << setw(15) << cursor->is.getResearchPt()
					 << " | " << setw(15) << cursor->is.getCGPA()
					 << " | " << setw(15) << cursor->is.getCountry()
					 << " | " << setw(10) << cursor->is.getToefl().getReadingPt()
					 << " | " << setw(10) << cursor->is.getToefl().getListeningPt()
					 << " | " << setw(10) << cursor->is.getToefl().getSpeakingPt()
					 << " | " << setw(10) << cursor->is.getToefl().getWritingPt()
					 << " | " << setw(15) << cursor->is.getToefl().sumTotal()
					 << " | "
					 << endl;
				counter++;
			}
			cursor = cursor->next;
		}
	}
	else
	{
		cout << setw(15) << "Type"
			 << " | " << setw(15) << "First Name"
			 << " | " << setw(15) << "Last Name"
			 << " | " << setw(15) << "Research Score"
			 << " | " << setw(15) << "CGPA"
			 << " | " << setw(15) << "Country/Prov"
			 << endl;
		if (dsHead == NULL) return;
		general_dsMergeSort();
		cursor = dsHead;
		while (cursor != NULL)
		{

			cout << setw(15) << "Domestic"
				 << " | " << setw(15) << cursor->ds.getFirstName()
				 << " | " << setw(15) << cursor->ds.getLastName()
				 << " | " << setw(15) << cursor->ds.getResearchPt()
				 << " | " << setw(15) << cursor->ds.getCGPA()
				 << " | " << setw(15) << cursor->ds.getProvince()
				 << endl;
			counter++;

			cursor = cursor->next;
		}
	}
	cout << endl
		 << "Rows printed: " << counter << endl;
}

//Two seperate appends overloaded for domestic or international 
void StudentDatabase::append(DomesticStudent s)
{
	if (!merged)
 	{
 		if (dsHead == NULL)
 		{
 			try
 			{
 			dsHead = new Node(s);
 			}catch(bad_alloc exp) {
 			cout<<"Bad allocation "<<exp.what()<<endl;
 			}
 			dsHead->next = NULL;
 			dsTail = dsHead;
 		}
 		else
 		{
 			try
 			{
 			dsTail->next = new Node(s);
 			}catch(bad_alloc exp) {
 			cout<<"Bad allocation "<<exp.what()<<endl;
 			}	
 			dsTail = dsTail->next;
 			dsTail->next = NULL;
 		}
	}
	else
 	{
 		if (mHead == NULL)
 		{
 			try
 			{
 			mHead = new Node(s);
 			}catch(bad_alloc exp) {
 			cout<<"Bad allocation "<<exp.what()<<endl;
 			}
 			mHead->next = NULL;
 			mTail = mHead;
 		}
 		else
 		{
 			try
 			{
 			mTail->next = new Node(s);
 			}catch(bad_alloc exp) {
 			cout<<"Bad allocation "<<exp.what()<<endl;
 			}
 			mTail = mTail->next;
 			mTail->next = NULL;
 		}
	}
}

void StudentDatabase::append(InternationalStudent s)
{
	if (!merged)
 	{
 		if (isHead == NULL)
 		{
 			try
 			{
 			isHead = new Node(s);
 			}catch(bad_alloc exp) {
 			cout<<"Bad allocation "<<exp.what()<<endl;
 			}
 			isHead->next = NULL;
 			isTail = isHead;
 		}
 		else
 		{
 			try
 			{
 			isTail->next = new Node(s);
 			}catch(bad_alloc exp) {
 			cout<<"Bad allocation "<<exp.what()<<endl;
 			}
 			isTail = isTail->next;
 			isTail->next = NULL;
 		}
	}
	else
 	{
 		if (mHead == NULL)
 		{
 			try
 			{
 			mHead = new Node(s);
 			}catch(bad_alloc exp) {
 			cout<<"Bad allocation "<<exp.what()<<endl;
 			}
 			mHead->next = NULL;
 			mTail = mHead;
 		}
 		else
 		{
 			try
 			{
 			mTail->next = new Node(s);
 			}catch(bad_alloc exp) {
 			cout<<"Bad allocation "<<exp.what()<<endl;
 			}
 			mTail = mTail->next;
 			mTail->next = NULL;
 		}
	}
}

//Add student to active list with error correction
void StudentDatabase::addStudent()
{
    //domestic by default
    bool isInternational = false;
    char charTemp;
    bool hasDetailedToefl = false;
    string firstName, lastName, country, province;
    float CGPA;
    int researchScore, tReading, tListening, tSpeaking, tWriting, tTotal;
    while (1)
    {
        cout << "Would you like to input an international or domestic student? Type i or d: ";
        cin >> charTemp;
        if (charTemp == 'i' || charTemp == 'd')
        {
            break;
        }
        else
        {
            cout << "Please enter the correct symbol\n";
        }
    }
    if (charTemp == 'i')
        isInternational = true;

    if (isInternational)
    {
        InternationalStudent s;
        while (1)
        {
            cout << "Do you have detailed TOEFL information? y/n ";
            cin >> charTemp;
            if (charTemp == 'y' || charTemp == 'n')
            {
                break;
            }
            else
            {
                cout << "Please enter the correct symbol\n";
            }
        }
        if (charTemp == 'y')
            hasDetailedToefl = true;
        while (1)
        {
            cout << "First name? :";
            cin >> firstName;
            if (stringCheck(firstName) == 1)
            {
                break;
            }
            else
            {
                cout << "ERROR: Please enter a valid name.\n";
            }
        }
        s.setFirstName(firstName);

        while (1)
        {
            cout << "Last name? :";
            cin >> lastName;
            if (stringCheck(lastName) == 1)
            {
                break;
            }
            else
            {
                cout << "ERROR: Please enter a valid name.\n";
            }
        }
        s.setLastName(lastName);

        while (1)
        {
            cout << "Country? :";
            cin >> country;
            if (stringCheck(country) == 1)
            {
                break;
            }
            else
            {
                cout << "ERROR: Please enter a valid country name.\n";
            }
        }
        s.setCountry(country);

        cout
            << endl
            << "CGPA? ";
        while (!(std::cin >> CGPA) || CGPA > 4.33 || CGPA < 0)
        {
            cin.clear();                                                   //Clear error flags to allow normal input
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //ignore errorneous output still sitting in buffer
            cout << "ERROR: Please enter a CGPA between 0 and 4.33.\n";
        }
        s.setCGPA(CGPA);

        cout
            << endl
            << "Research Score? ";
        while (!(cin >> researchScore) || researchScore < 0 || researchScore > 100)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "ERROR: Please enter a research score between 0 and 100.\nTry again please: \n";
        }
        s.setResearchPt(researchScore);

        if (hasDetailedToefl)
        {
            cout
                << endl
                << "Reading Score? ";
            cin >> tReading;
            s.getToeflRef()->setReadingPt(tReading);
            cout
                << endl
                << "Writing Score? ";
            cin >> tWriting;
            s.getToeflRef()->setWritingPt(tWriting);
            cout
                << endl
                << "Speaking Score? ";
            cin >> tSpeaking;
            s.getToeflRef()->setSpeakingPt(tSpeaking);
            cout
                << endl
                << "Listening Score? ";
            cin >> tListening;
            s.getToeflRef()->setListeningPt(tListening);
            tTotal = tReading + tWriting + tSpeaking + tListening;
        }
        else
        {
            cout
                << endl
                << "Toefl Score? ";
            cin >> tTotal;
            s.getToeflRef()->setSum(tTotal);
        }
        s.setAppNum(latestAppNum());

        append(s); //Decides which list to append to
        if (merged) 
        {
            general_mMergeSort();
        }
        else
        {
            general_isMergeSort();
        }
        cout << "The new international student just inserted into the list:\n";
        cout << firstName << " "
             << lastName << "\n"
             << "From: " << country << "\n"
             << "CGPA: " << CGPA << "\n"
             << "Research score: " << researchScore << "\n"
             << "Total TOEFL score: " << tTotal << "\n"
             << "\n";
    }
    else
    {
        DomesticStudent s;
        while (1)
        {
            cout << "First name? :";
            cin >> firstName;
            if (stringCheck(firstName) == 1)
            {
                break;
            }
            else
            {
                cout << "ERROR: Please enter a valid name.\n";
            }
        }
        s.setFirstName(firstName);

        while (1)
        {
            cout << "Last name? :";
            cin >> lastName;
            if (stringCheck(lastName) == 1)
            {
                break;
            }
            else
            {
                cout << "ERROR: Please enter a valid name.\n";
            }
        }
        s.setLastName(lastName);

        cout
            << endl
            << "CGPA? ";
        while (!(std::cin >> CGPA) || CGPA > 4.33 || CGPA < 0)
        {
            cin.clear();                                                   //Clear error flags to allow normal input
            cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //ignore errorneous output still sitting in buffer
            cout << "ERROR: Please enter a CGPA between 0 and 4.33.\n";
        }
        s.setCGPA(CGPA);

        cout
            << endl
            << "Research Score? ";
        while (!(cin >> researchScore) || researchScore < 0 || researchScore > 100)
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "ERROR: Please enter a research score between 0 and 100.\nTry again please: \n";
        }
        s.setResearchPt(researchScore);

        while (1)
        {
            cout
                << endl
                << "Province? ";
            cin >> province;
            if (provinceCheck(province) == 1)
            {
                break;
            }
            else
            {
                cout << "ERROR: Please enter a valid province. eg. 'AB' for Alberta.\n";
            }
        }
        s.setProvince(province);
        s.setAppNum(latestAppNum());
        append(s);
        if (merged)
        {
            general_mMergeSort();
        }
        else
        {
            general_dsMergeSort();
        }
        cout << "The new domestic student just inserted into the list:\n";
        cout << firstName << " "
             << lastName << "\n"
             << "From: " << province << "\n"
             << "CGPA: " << CGPA << "\n"
             << "Research score: " << researchScore << "\n"
             << "\n";
    }
}


//Goes through every case to delete node from active list
void StudentDatabase::deleteStudent(string firstName, string lastName)
{
	Node *node;
	Node *before;
	Node *after;

	node = getByFirstLastName(firstName, lastName);

    if (node == NULL) 
    {
        cout << endl << "Node not found" << endl;
    }

	if (!merged) //If the lists have not yet been merged
	{
		if (node == isHead) //If the node ends up being the international student head
		{
			isHead = isHead->next;
			delete node;
			cout
				<< endl
				<< "Node deleted"
				<< endl;
			return;
		}

		if (node == isTail) //If the node ends up being the internation student tail
		{
			
			before = getBeforeByFirstLastName(firstName, lastName);
			isTail = before;
			isTail->next = NULL;
			delete node;
			cout
				<< endl
				<< "Node deleted"
				<< endl;
			return;
		}

		if (node == dsHead)
		{
			dsHead = dsHead->next;
			delete node;
			cout
				<< endl
				<< "Node deleted"
				<< endl;
			return;
		}

		if (node == dsTail)
		{
			before = getBeforeByFirstLastName(firstName, lastName);
			dsTail = before;
			delete node;
			cout
				<< endl
				<< "Node deleted"
				<< endl;
			return;
		}

		before = getBeforeByFirstLastName(firstName, lastName);
		if (node != NULL)
		{
			after = node->next;
			delete node;
			before->next = after;
			cout
				<< endl
				<< "Node deleted"
				<< endl;
			return;
		}
	}
	else
	{
		if (node == mHead)
		{
			mHead = mHead->next;
			delete node;
			cout
				<< endl
				<< "Node deleted"
				<< endl;
			return;
		}

		if (node == mTail)
		{
			before = getBeforeByFirstLastName(firstName, lastName);
			mTail = before;
			delete node;
			cout
				<< endl
				<< "Node deleted"
				<< endl;
			return;
		}

		before = getBeforeByFirstLastName(firstName, lastName);
		if (node != NULL)
		{
			after = node->next;
			delete node;
			before->next = after;
			cout
				<< endl
				<< "Node deleted"
				<< endl;
			return;
		}
	}

	cout
		<< endl
		<< "Delete node failed"
		<< endl;
}

//Deletes both head and tail, two cases: if the list has even or odd number of nodes
void StudentDatabase::deleteHeadTail()
{
	Node *temp;
	Node *cursor;
	if (merged)
	{
		if (mHead != NULL && mTail != NULL)
		{
			if (mHead->next == mTail)
			{
				mHead == NULL;
				mTail == NULL;
				return;
			}
			if (mHead == mTail)
			{
				delete mTail;
				mHead = NULL;
				mTail = NULL;
				return;
			}
			cursor = mHead;
			while (cursor->next != mTail)
			{
				cursor = cursor->next;
			}
			delete mTail;
			mTail = cursor;
			mTail->next = NULL;
			temp = mHead;
			mHead = mHead->next;
			delete temp;
		}
	}
	else
	{
		if (isHead != NULL && isTail != NULL)
		{

			if (isHead->next == isTail)
			{
				isTail = NULL;
				isHead = NULL;
				return;
			}
			if (isHead == isTail)
			{
				delete isTail;
				isHead = NULL;
				isTail = NULL;
				return;
			}
			cursor = isHead;
			while (cursor->next != isTail)
			{
				cursor = cursor->next;
			}
			delete isTail;
			isTail = cursor;
			isTail->next = NULL;
			temp = isHead;
			isHead = isHead->next;
			delete temp;
		}
		if (dsHead != NULL && dsTail != NULL)
		{
			if (dsHead->next == dsTail)
			{
				dsHead == NULL;
				dsTail == NULL;
				return;
			}
			if (dsHead == dsTail)
			{
				delete dsTail;
				dsHead = NULL;
				dsTail = NULL;
				return;
			}
			cursor = dsHead;
			while (cursor->next != dsTail)
			{
				cursor = cursor->next;
			}
			delete dsTail;
			dsTail = cursor;
			dsTail->next = NULL;
			temp = dsHead;
			dsHead = dsHead->next;
			delete temp;
		}
	}
}

//A delete student but without printing for repeated deletes and testing
void StudentDatabase::deleteStudentNoPrint(string firstName, string lastName)
{
	Node *node;
	Node *before;
	Node *after;
	node = getByFirstLastName(firstName, lastName);
	if (!merged)
	{
		if (node == isHead)
		{
			isHead = isHead->next;
			delete node;
			return;
		}

		if (node == isTail)
		{
			
			before = getBeforeByFirstLastName(firstName, lastName);
			isTail = before;
			isTail->next = NULL;
			delete node;
			return;
		}

		if (node == dsHead)
		{
			dsHead = dsHead->next;
			delete node;
			return;
		}

		if (node == dsTail)
		{
			before = getBeforeByFirstLastName(firstName, lastName);
			dsTail = before;
			delete node;
			return;
		}

		before = getBeforeByFirstLastName(firstName, lastName);
		if (node != NULL)
		{
			after = node->next;
			delete node;
			before->next = after;
			return;
		}
	}
	else
	{
		if (node == mHead)
		{
			mHead = mHead->next;
			delete node;
			return;
		}

		if (node == mTail)
		{
			before = getBeforeByFirstLastName(firstName, lastName);
			mTail = before;
			delete node;
			return;
		}

		before = getBeforeByFirstLastName(firstName, lastName);
		if (node != NULL)
		{
			after = node->next;
			delete node;
			before->next = after;
			return;
		}
	}
}

//Test function
void StudentDatabase::addDomesticStudentTest(string firstName, string lastName, float CGPA, int research, string province){
	DomesticStudent s;
		s.setFirstName(firstName);
		s.setLastName(lastName);
		s.setCGPA(CGPA);
		s.setResearchPt(research);
		s.setProvince(province);
		append(s);
		if (merged) 
		{
			general_mMergeSort(); 
		}
		else
		{
			general_dsMergeSort();
		}
	}

//Merges InternationalStudent and DomesticStudent lists
void StudentDatabase::merge()
{
	if (isHead == NULL || isTail == NULL) 
	{
		cout
		<< endl
		<< "InternationStudent list empty, cannot merge"
		<< endl;
		return;
	} 

	if (dsHead == NULL || dsTail == NULL) 
	{
		cout
		<< endl
		<< "DomesticStudent list empty, cannot merge"
		<< endl;
		return;
	} 

	if(merged == true)
	{
		cout 
		<< endl 
		<< "Notice: the lists have already been merged, no action taken" 
		<< endl
		<< endl; 
		return;
	}

	dsTail->next = isHead;
	mHead = dsHead;
	mTail = isTail;
	merged = true;
}

//Merges wihtout printing
void StudentDatabase::mergeNoPrint()
{
	if (isHead == NULL || isTail == NULL || dsHead == NULL || dsTail == NULL) return; 

	if(merged == true)
	{
		return;
	}
	dsTail->next = isHead;
	mHead = dsHead;
	mTail = isTail;
	merged = true;
}

////////////////////////////////////////////////////////////
/////////////////////////MERGESORT//////////////////////////
////////////////////////////////////////////////////////////

///////////////////////INTERNATIONAL////////////////////////

//mergeSort for InternationalStudent, requires 4 functions in total
void StudentDatabase::general_isMergeSort()
{
	if (merged)
	{
		cout
		<< endl
		<< "As list has been merged, running general_mMergesort() instead"
		<< endl; 
		general_mMergeSort();
		return; 
	}
	Node *a;
	Node *b;
	if (isHead == NULL || isHead->next == NULL)
	{
		return;
	}

	mergeSplit(isHead, &a, &b);

	general_isMergeSort(&a);
	general_isMergeSort(&b);

	isHead = isSorter(a, b);

	while (isTail->next != NULL)
		isTail = isTail->next;

}

void StudentDatabase::general_isMergeSort(Node **hRef)
{
	Node *head = *hRef;
	Node *a;
	Node *b;
	if (head == NULL || head->next == NULL)
	{
		return;
	}

	mergeSplit(head, &a, &b);

	general_isMergeSort(&a);
	general_isMergeSort(&b);

	*hRef = isSorter(a, b);

}

Node *StudentDatabase::isSorter(Node *a, Node *b)
{
	Node *res = NULL;

	if (a == NULL)
		return b;
	if (b == NULL)
		return a;

	if (compareResearch(a->is, b->is) == true)
	{
		res = b;
		res->next = isSorter(a, b->next);
	}
	else if (a->is.getResearchPt() == b->is.getResearchPt())
	{
		if (a->is.getCGPA() > b->is.getCGPA())
		{
			res = a;
			res->next = isSorter(a->next, b);
		}
		else if (a->is.getCGPA() == b->is.getCGPA())
		{
			if (compareCountry(a->is, b->is) == true)
			{
				res = a;
				res->next = isSorter(a->next, b);
			}
			else
			{
				res = b;
				res->next = isSorter(a, b->next);
			}
		}
		else
		{
			res = b;
			res->next = isSorter(a, b->next);
		}
	}
	else
	{
		res = a;
		res->next = isSorter(a->next, b);
	}

	return res;
}

void StudentDatabase::mergeSplit(Node *source, Node **fr, Node **br)
{
	Node *f;
	Node *s;
	s = source;
	f = source->next;

	while (f != NULL)
	{
		f = f->next;
		if (f != NULL)
		{
			s = s->next;
			f = f->next;
		}
	}

	*fr = source;
	*br = s->next;
	s->next = NULL;
}

/////////////////////////DOMESTIC///////////////////////////

//mergeSort for DomesticStudent, requires 4 functions in total
void StudentDatabase::general_dsMergeSort()
{

	if (merged)
	{
		cout
		<< endl
		<< "As list has been merged, running general_mMergesort() instead"
		<< endl; 
		general_mMergeSort();
		return; 
	}
	Node *a;
	Node *b;
	if (dsHead == NULL || dsHead->next == NULL)
	{
		return;
	}

	mergeSplit(dsHead, &a, &b);

	general_dsMergeSort(&a);
	general_dsMergeSort(&b);

	dsHead = dsSorter(a, b);

	while (dsTail->next != NULL)
		dsTail = dsTail->next;
}

void StudentDatabase::general_dsMergeSort(Node **hRef)
{
	Node *head = *hRef;
	Node *a;
	Node *b;
	if (head == NULL || head->next == NULL)
	{
		return;
	}

	mergeSplit(head, &a, &b);

	general_dsMergeSort(&a);
	general_dsMergeSort(&b);

	*hRef = dsSorter(a, b);
}

Node *StudentDatabase::dsSorter(Node *a, Node *b)
{
	Node *res = NULL;

	if (a == NULL)
		return b;
	if (b == NULL)
		return a;

	if (compareResearch(a->ds, b->ds) == true)
	{
		res = b;
		res->next = dsSorter(a, b->next);
	}
	else if (a->ds.getResearchPt() == b->ds.getResearchPt())
	{
		if (a->ds.getCGPA() < b->ds.getCGPA())
		{
			res = b;
			res->next = dsSorter(a, b->next);
		}
		else if (a->ds.getCGPA() == b->ds.getCGPA())
		{
			if (compareProvince(a->ds, b->ds) == true)
			{
				res = a;
				res->next = dsSorter(a->next, b);
			}
			else
			{
				res = b;
				res->next = dsSorter(a, b->next);
			}
		}
		else
		{
			res = a;
			res->next = dsSorter(a->next, b);
		}
	}
	else
	{
		res = a;
		res->next = dsSorter(a->next, b);
	}

	return res;
}

/////////////////////////MERGED///////////////////////////

//mergeSort for merged, requires 4 functions in total
void StudentDatabase::general_mMergeSort()
{
	Node *a;
	Node *b;

	if (merged != true)
	{
		cout << "Please merge lists first before attempting to sort merged list" << endl;
		return;
	}

	if (mHead == NULL || mHead->next == NULL)
	{
		return;
	}

	mergeSplit(mHead, &a, &b);

	general_mMergeSort(&a);
	general_mMergeSort(&b);

	mHead = mSorter(a, b);

	while (mTail->next != NULL)
		mTail = mTail->next;

}

void StudentDatabase::general_mMergeSort(Node **hRef)
{
	Node *head = *hRef;
	Node *a;
	Node *b;
	if (head == NULL || head->next == NULL)
	{
		return;
	}

	mergeSplit(head, &a, &b);

	general_mMergeSort(&a);
	general_mMergeSort(&b);

	*hRef = mSorter(a, b);
}

Node *StudentDatabase::mSorter(Node *a, Node *b)
{
	Node *res = NULL;
	Student *a_sel;
	Student *b_sel;

	if (a == NULL)
		return b;
	if (b == NULL)
		return a;

	if (a->is.isEmpty())
	{
		a_sel = &a->ds;
	}
	else if (a->ds.isEmpty())
	{
		a_sel = &a->is;
	}

	if (b->is.isEmpty())
	{
		b_sel = &b->ds;
	}
	else if (b->ds.isEmpty())
	{
		b_sel = &b->is;
	}

	if (compareResearch(*a_sel, *b_sel) == true)
	{
		res = b;
		res->next = mSorter(a, b->next);
	}
	else if ((*a_sel).getResearchPt() == (*b_sel).getResearchPt())
	{
		if ((*a_sel).getCGPA() > (*b_sel).getCGPA())
		{
			res = a;
			res->next = mSorter(a->next, b);
		}
		else if ((*a_sel).getCGPA() == (*b_sel).getCGPA())
		{
			if (a->is.isEmpty())
			{
				res = a;
				res->next = mSorter(a->next, b);
			}
			else if (a->ds.isEmpty())
			{
				res = b;
				res->next = mSorter(a, b->next);
			}
		}
		else
		{
			res = b;
			res->next = mSorter(a, b->next);
		}
	}
	else
	{
		res = a;
		res->next = mSorter(a->next, b);
	}

	return res;
}

////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////

Node::Node(DomesticStudent stu)
{
	ds = stu;
}

Node::Node(InternationalStudent stu)
{
	is = stu;
}

////////////////////linear search////////////////////////////
void StudentDatabase::searchByCGPA(float CGPA)
{
	Node *cursor;
	int isFlag = 0;
	int dsFlag = 0;
	cursor = isHead;
	while (cursor != NULL)
	{
		if (isEqualCGPA(cursor->is, CGPA) == 1)
		{
			cout << "------------------------\n";
			cout << "International student"
				 << ": " << cursor->is.getFirstName() << " "
				 << cursor->is.getLastName() << "\n"
				 << "From: " << cursor->is.getCountry() << "\n"
				 << "CGPA: " << cursor->is.getCGPA() << "\n"
				 << "Research score: " << cursor->is.getResearchPt() << "\n"
				 << "TOEFL reading score: " << cursor->is.getToefl().getReadingPt() << "\n"
				 << "TOEFL listening score: " << cursor->is.getToefl().getListeningPt() << "\n"
				 << "TOEFL speaking score: " << cursor->is.getToefl().getSpeakingPt() << "\n"
				 << "TOEFL writing score: " << cursor->is.getToefl().getWritingPt() << "\n"
				 << "Total TOEFL score: " << cursor->is.getToefl().sumTotal() << "\n"
				 << "\n";
				 isFlag++;
		}
		cursor = cursor->next;
	}
	if(isFlag == 0){
		cout << "No international student meet the requirement!\n";
	}
	cursor = dsHead;
	while (cursor != NULL)
	{
		if (isEqualCGPA(cursor->ds, CGPA) == 1)
		{
			cout << "------------------------\n";
			cout << "Domestic student"
				 << ": " << cursor->ds.getFirstName() << " "
				 << cursor->ds.getLastName() << "\n"
				 << "From: " << cursor->ds.getProvince() << "\n"
				 << "CGPA: " << cursor->ds.getCGPA() << "\n"
				 << "Research score: " << cursor->ds.getResearchPt() << "\n"
				 << "\n";
				dsFlag++;
		}
		cursor = cursor->next;
	}
	if(dsFlag == 0){
		cout << "No domestic student meet the requirement!\n";
	}
}

void StudentDatabase::searchNoPrint(float CGPA)
{
	Node *cursor;
	cursor = isHead;
	int flag[300];
	while (cursor != NULL)
	{
		if (isEqualCGPA(cursor->is, CGPA) == 1)
		{
			string firstName = cursor->is.getFirstName();
			string lastName = cursor->is.getLastName();
			string country = cursor->is.getCountry();
			float CGPA = cursor->is.getCGPA();
			int research = cursor->is.getResearchPt();
			int reading = cursor->is.getToefl().getReadingPt();
			int listining = cursor->is.getToefl().getListeningPt();
			int speaking = cursor->is.getToefl().getSpeakingPt();
			int writing = cursor->is.getToefl().getWritingPt();
			int total = cursor->is.getToefl().sumTotal();
		}
		cursor = cursor->next;
	}
	cursor = dsHead;
	while (cursor != NULL)
	{
		if (isEqualCGPA(cursor->ds, CGPA) == 1)
		{
			string firstName = cursor->ds.getFirstName();
			string lastName = cursor->ds.getLastName();
			string province = cursor->ds.getProvince();
			float CGPA = cursor->ds.getCGPA();
			int research =  cursor->ds.getResearchPt();
		}
		cursor = cursor->next;
	}
}


void StudentDatabase::searchByResearch(int research)
{
	Node *cursor;
	cursor = isHead;
	int isFlag = 0;
	int dsFlag = 0;
	while (cursor != NULL)
	{
		if (isEqualresearch(cursor->is, research) == 1)
		{
			cout << "------------------------\n";
			cout << "International student"
				 << ": " << cursor->is.getFirstName() << " "
				 << cursor->is.getLastName() << "\n"
				 << "From: " << cursor->is.getCountry() << "\n"
				 << "CGPA: " << cursor->is.getCGPA() << "\n"
				 << "Research score: " << cursor->is.getResearchPt() << "\n"
				 << "TOEFL reading score: " << cursor->is.getToefl().getReadingPt() << "\n"
				 << "TOEFL listening score: " << cursor->is.getToefl().getListeningPt() << "\n"
				 << "TOEFL speaking score: " << cursor->is.getToefl().getSpeakingPt() << "\n"
				 << "TOEFL writing score: " << cursor->is.getToefl().getWritingPt() << "\n"
				 << "Total TOEFL score: " << cursor->is.getToefl().sumTotal() << "\n"
				 << endl
				 << endl;
			isFlag++;
		}
		cursor = cursor->next;
	}
	if(isFlag == 0){
		cout << "No international student meet the requirement!\n";
	}
	cursor = dsHead;
	while (cursor != NULL)
	{
		if (isEqualresearch(cursor->ds, research) == 1)
		{
			cout << "------------------------\n";
			cout << "Domestic student"
				 << ": " << cursor->ds.getFirstName() << " "
				 << cursor->ds.getLastName() << "\n"
				 << "From: " << cursor->ds.getProvince() << "\n"
				 << "CGPA: " << cursor->ds.getCGPA() << "\n"
				 << "Research score: " << cursor->ds.getResearchPt() << "\n"
				 << endl;
			dsFlag++;

		}
		cursor = cursor->next;
	}
	if(dsFlag == 0){
		cout << "No domestic student meet the requirement!\n";
	}

}

void StudentDatabase::searchByID(int ID)
{
	Node *cursor;
	cursor = isHead;
	int isFlag = 0;
	int dsFlag = 0;

	while (cursor != NULL)
	{
		if (isEqualID(cursor->is, ID) == 1)
		{
			cout << "------------------------\n";
			cout << "International student"
				 << ": " << cursor->is.getFirstName() << " "
				 << cursor->is.getLastName() << "\n"
				 << "From: " << cursor->is.getCountry() << "\n"
				 << "CGPA: " << cursor->is.getCGPA() << "\n"
				 << "Research score: " << cursor->is.getResearchPt() << "\n"
				 << "TOEFL reading score: " << cursor->is.getToefl().getReadingPt() << "\n"
				 << "TOEFL listening score: " << cursor->is.getToefl().getListeningPt() << "\n"
				 << "TOEFL speaking score: " << cursor->is.getToefl().getSpeakingPt() << "\n"
				 << "TOEFL writing score: " << cursor->is.getToefl().getWritingPt() << "\n"
				 << "Total TOEFL score: " << cursor->is.getToefl().sumTotal() << "\n"
				 << endl
				 << endl;
			isFlag++;
		}
		cursor = cursor->next;
	}
	if(isFlag == 0){
		cout << "No international student meet the requirement!\n";
	}
	cursor = dsHead;
	while (cursor != NULL)
	{
		if (isEqualID(cursor->ds, ID) == 1)
		{
			cout << "------------------------\n";
			cout << "Domestic student"
				 << ": " << cursor->ds.getFirstName() << " "
				 << cursor->ds.getLastName() << "\n"
				 << "From: " << cursor->ds.getProvince() << "\n"
				 << "CGPA: " << cursor->ds.getCGPA() << "\n"
				 << "Research score: " << cursor->ds.getResearchPt() << "\n"
				 << endl;
			dsFlag++;

		}
		cursor = cursor->next;
	}
	if(dsFlag == 0){
		cout << "No domestic student meet the requirement!\n";
	}
}

void StudentDatabase::searchByCGPAandResearch(float CGPA, int research){
	Node *cursor;
	cursor = isHead;
	int isFlag = 0;
	int dsFlag = 0;

	while (cursor != NULL)
	{
		if (isEqualCGPA(cursor->is, CGPA) != 0 && isEqualresearch(cursor->is, research) != 0)
		{
			cout << "------------------------\n";
			cout << "International student"
				 << ": " << cursor->is.getFirstName() << " "
				 << cursor->is.getLastName() << "\n"
				 << "From: " << cursor->is.getCountry() << "\n"
				 << "CGPA: " << cursor->is.getCGPA() << "\n"
				 << "Research score: " << cursor->is.getResearchPt() << "\n"
				 << "TOEFL reading score: " << cursor->is.getToefl().getReadingPt() << "\n"
				 << "TOEFL listening score: " << cursor->is.getToefl().getListeningPt() << "\n"
				 << "TOEFL speaking score: " << cursor->is.getToefl().getSpeakingPt() << "\n"
				 << "TOEFL writing score: " << cursor->is.getToefl().getWritingPt() << "\n"
				 << "Total TOEFL score: " << cursor->is.getToefl().sumTotal() << "\n"
				 << endl
				 << endl;
				 isFlag++;
		}
		cursor = cursor->next;
	}
	if(isFlag == 0){
		cout << "No international student meet the requirement!\n";
	}
	cursor = dsHead;
	while (cursor != NULL)
	{
		if (isEqualCGPA(cursor->ds, CGPA) != 0 && isEqualresearch(cursor->ds, research) != 0)
		{
			cout << "------------------------\n";
			cout << "Domestic student"
				 << ": " << cursor->ds.getFirstName() << " "
				 << cursor->ds.getLastName() << "\n"
				 << "From: " << cursor->ds.getProvince() << "\n"
				 << "CGPA: " << cursor->ds.getCGPA() << "\n"
				 << "Research score: " << cursor->ds.getResearchPt() << "\n"
				 << endl;
				dsFlag++;
		}
		cursor = cursor->next;
	}
	if(dsFlag == 0){
		cout << "No domestic student meet the requirement!\n";
	}
}

void StudentDatabase::searchByLastName(string name)
{
	Node *cursor;
	cursor = isHead;
	int isFlag = 0;
	int dsFlag = 0;

	while (cursor != NULL)
	{
		if (isEqualLastName(cursor->is, name) == 1)
		{
			cout << "------------------------\n";
			cout << "International student"
				 << ": " << cursor->is.getFirstName() << " "
				 << cursor->is.getLastName() << "\n"
				 << "From: " << cursor->is.getCountry() << "\n"
				 << "CGPA: " << cursor->is.getCGPA() << "\n"
				 << "Research score: " << cursor->is.getResearchPt() << "\n"
				 << "TOEFL reading score: " << cursor->is.getToefl().getReadingPt() << "\n"
				 << "TOEFL listening score: " << cursor->is.getToefl().getListeningPt() << "\n"
				 << "TOEFL speaking score: " << cursor->is.getToefl().getSpeakingPt() << "\n"
				 << "TOEFL writing score: " << cursor->is.getToefl().getWritingPt() << "\n"
				 << "Total TOEFL score: " << cursor->is.getToefl().sumTotal() << "\n"
				 << endl
				 << endl;
			isFlag++;
		}
		cursor = cursor->next;
	}
	if(isFlag == 0){
		cout << "No international student meet the requirement!\n";
	}
	cursor = dsHead;
	while (cursor != NULL)
	{
		if (isEqualLastName(cursor->ds, name) == 1)
		{
			cout << "------------------------\n";
			cout << "Domestic student"
				 << ": " << cursor->ds.getFirstName() << " "
				 << cursor->ds.getLastName() << "\n"
				 << "From: " << cursor->ds.getProvince() << "\n"
				 << "CGPA: " << cursor->ds.getCGPA() << "\n"
				 << "Research score: " << cursor->ds.getResearchPt() << "\n"
				 << endl;
			dsFlag++;
		}
		cursor = cursor->next;
	}
	if(dsFlag == 0){
		cout << "No domestic student meet the requirement!\n";
	}
}

void StudentDatabase::searchByFristName(string name)
{
	Node *cursor;
	cursor = isHead;
	int isFlag = 0;
	int dsFlag = 0;
	while (cursor != NULL)
	{
		if (isEqualFirstName(cursor->is, name) == 1)
		{
			cout << "------------------------\n";
			cout << "International student"
				 << ": " << cursor->is.getFirstName() << " "
				 << cursor->is.getLastName() << "\n"
				 << "From: " << cursor->is.getCountry() << "\n"
				 << "CGPA: " << cursor->is.getCGPA() << "\n"
				 << "Research score: " << cursor->is.getResearchPt() << "\n"
				 << "TOEFL reading score: " << cursor->is.getToefl().getReadingPt() << "\n"
				 << "TOEFL listening score: " << cursor->is.getToefl().getListeningPt() << "\n"
				 << "TOEFL speaking score: " << cursor->is.getToefl().getSpeakingPt() << "\n"
				 << "TOEFL writing score: " << cursor->is.getToefl().getWritingPt() << "\n"
				 << "Total TOEFL score: " << cursor->is.getToefl().sumTotal() << "\n"
				 << endl
				 << endl;
				isFlag++;

		}
		cursor = cursor->next;
	}
	if(isFlag == 0){
		cout << "No international student meet the requirement!\n";
	}
	cursor = dsHead;
	while (cursor != NULL)
	{
		if (isEqualFirstName(cursor->ds, name) == 1)
		{
			cout << "------------------------\n";
			cout << "Domestic student"
				 << ": " << cursor->ds.getFirstName() << " "
				 << cursor->ds.getLastName() << "\n"
				 << "From: " << cursor->ds.getProvince() << "\n"
				 << "CGPA: " << cursor->ds.getCGPA() << "\n"
				 << "Research score: " << cursor->ds.getResearchPt() << "\n"
				 << endl;
			dsFlag++;
		}
		cursor = cursor->next;
	}
	if(dsFlag == 0){
		cout << "No domestic student meet the requirement!\n";
	}
}

bool StudentDatabase::searchByLastFristName(string fristName, string lastName){
	Node *cursor;
	cursor = isHead;
	int isFlag = 0;
	int dsFlag = 0;
	while (cursor != NULL)
	{
		if (isEqualFirstName(cursor->is, fristName) == 1 && isEqualLastName(cursor->is, lastName) == 1)
		{
			cout << "------------------------\n";
			cout << "International student"
				 << ": " << cursor->is.getFirstName() << " "
				 << cursor->is.getLastName() << "\n"
				 << "From: " << cursor->is.getCountry() << "\n"
				 << "CGPA: " << cursor->is.getCGPA() << "\n"
				 << "Research score: " << cursor->is.getResearchPt() << "\n"
				 << "TOEFL reading score: " << cursor->is.getToefl().getReadingPt() << "\n"
				 << "TOEFL listening score: " << cursor->is.getToefl().getListeningPt() << "\n"
				 << "TOEFL speaking score: " << cursor->is.getToefl().getSpeakingPt() << "\n"
				 << "TOEFL writing score: " << cursor->is.getToefl().getWritingPt() << "\n"
				 << "Total TOEFL score: " << cursor->is.getToefl().sumTotal() << "\n"
				 << "Application ID: " << cursor->is.getAppNum() << "\n"
				 << endl
				 << endl;
				 isFlag++;
				 return true; 
		}
		cursor = cursor->next;
	}
	if(isFlag == 0){
		cout << "No international student meet the requirement!\n";
	}
	cursor = dsHead;
	while (cursor != NULL)
	{
		if (isEqualFirstName(cursor->ds, fristName) == 1 && isEqualLastName(cursor->ds, lastName) == 1)
		{
			cout << "------------------------\n";
			cout << "Domestic student"
				 << ": " << cursor->ds.getFirstName() << " "
				 << cursor->ds.getLastName() << "\n"
				 << "From: " << cursor->ds.getProvince() << "\n"
				 << "CGPA: " << cursor->ds.getCGPA() << "\n"
				 << "Research score: " << cursor->ds.getResearchPt() << "\n"
				 << "Application ID: " << cursor->ds.getAppNum() << "\n"
				 << endl;
				 dsFlag++;
				 return true; 
		}
		cursor = cursor->next;
	}
	if(dsFlag == 0){
		cout << "No domestic student meet the requirement!\n";
	}
}

//All these get function return a Node*, mostly to be evaluated in the test unit
Node *StudentDatabase::getByFirstLastName(string firstName, string lastName)
{
    Node *cursor;
    if (merged)
    {
        cursor = mHead;
        while (cursor != NULL)
        {
            if (cursor->ds.isEmpty())
            {

                if (isEqualFirstName(cursor->is, firstName) == 1 && isEqualLastName(cursor->is, lastName) == 1)
                {
                    return cursor;
                }
                cursor = cursor->next;
            }
            else if (cursor->is.isEmpty())
            {

                if (isEqualFirstName(cursor->ds, firstName) == 1 && isEqualLastName(cursor->ds, lastName) == 1)
                {
                    return cursor;
                }
                cursor = cursor->next;
            }
        }
    }
    else
    {
        cursor = isHead;
        while (cursor != NULL)
        {
            if (isEqualFirstName(cursor->is, firstName) == 1 && isEqualLastName(cursor->is, lastName) == 1)
            {
                return cursor;
            }
            cursor = cursor->next;
        }
        cursor = dsHead;
        while (cursor != NULL)
        {
            if (isEqualFirstName(cursor->ds, firstName) == 1 && isEqualLastName(cursor->ds, lastName) == 1)
            {
                return cursor;
            }
            cursor = cursor->next;
        }
    }
    return NULL;
}

Node *StudentDatabase::getByAppNum(int appNum)
{
	Node *cursor;
	if (merged)
	{
		cursor = mHead;
		if (cursor->ds.isEmpty())
		{
			while (cursor != NULL)
			{
				if (cursor->is.getAppNum() == appNum)
				{
					return cursor;
				}
				cursor = cursor->next;
			}
		}
		else if (cursor->is.isEmpty())
		{
			while (cursor != NULL)
			{
				if (cursor->ds.getAppNum() == appNum)
				{
					return cursor;
				}
				cursor = cursor->next;
			}
		}
	}
	else
	{
		cursor = isHead;
		while (cursor != NULL)
		{
			if (cursor->is.getAppNum() == appNum)
			{
				return cursor;
			}
			cursor = cursor->next;
		}
		cursor = dsHead;
		while (cursor != NULL)
		{
			if (cursor->ds.getAppNum() == appNum)
			{
				return cursor;
			}
			cursor = cursor->next;
		}
	}
}

Node *StudentDatabase::getByCGPA(float CGPA)
{
	Node *cursor;
	if (merged)
	{
		cursor = mHead;
		if (cursor->ds.isEmpty())
		{
			while (cursor != NULL)
			{
				if (cursor->is.getCGPA() == CGPA)
				{
					return cursor;
				}
				cursor = cursor->next;
			}
		}
		else if (cursor->is.isEmpty())
		{
			while (cursor != NULL)
			{
				if (cursor->ds.getCGPA() == CGPA)
				{
					return cursor;
				}
				cursor = cursor->next;
			}
		}
	}
	else
	{
		cursor = isHead;
		while (cursor != NULL)
		{
			if (cursor->is.getCGPA() == CGPA)
			{
				return cursor;
			}
			cursor = cursor->next;
		}
		cursor = dsHead;
		while (cursor != NULL)
		{
			if (cursor->ds.getCGPA() == CGPA)
			{
				return cursor;
			}
			cursor = cursor->next;
		}
	}
}

Node *StudentDatabase::getByResearch(int research)
{
	Node *cursor;
	if (merged)
	{
		cursor = mHead;
		if (cursor->ds.isEmpty())
		{
			while (cursor != NULL)
			{
				if (cursor->is.getResearchPt() == research)
				{
					return cursor;
				}
				cursor = cursor->next;
			}
		}
		else if (cursor->is.isEmpty())
		{
			while (cursor != NULL)
			{
				if (cursor->ds.getResearchPt() == research)
				{
					return cursor;
				}
				cursor = cursor->next;
			}
		}
	}
	else
	{
		cursor = isHead;
		while (cursor != NULL)
		{
			if (cursor->is.getResearchPt() == research)
			{
				return cursor;
			}
			cursor = cursor->next;
		}
		cursor = dsHead;
		while (cursor != NULL)
		{
			if (cursor->ds.getResearchPt() == research)
			{
				return cursor;
			}
			cursor = cursor->next;
		}
	}
}

Node *StudentDatabase::getBeforeByFirstLastName(string firstName, string lastName)
{
    Node *cursor;
    Node *before;
    if (merged)
    {
        cursor = mHead;
        before = cursor;
        while (cursor != NULL)
        {
            if (cursor->ds.isEmpty())
            {
                if (isEqualFirstName(cursor->is, firstName) == 1 && isEqualLastName(cursor->is, lastName) == 1)
                {
                    return before;
                }
                before = cursor;
                cursor = cursor->next;
            }
            else if (cursor->is.isEmpty())
            {

                if (isEqualFirstName(cursor->ds, firstName) == 1 && isEqualLastName(cursor->ds, lastName) == 1)
                {
                    return before;
                }
                before = cursor;
                cursor = cursor->next;
            }
        }
    }
    else
    {
        cursor = isHead;
        before = cursor;
        while (cursor != NULL)
        {
            if (isEqualFirstName(cursor->is, firstName) == 1 && isEqualLastName(cursor->is, lastName) == 1)
            {
                return before;
            }
            before = cursor;
            cursor = cursor->next;
        }
        cursor = dsHead;
        while (cursor != NULL)
        {
            if (isEqualFirstName(cursor->ds, firstName) == 1 && isEqualLastName(cursor->ds, lastName) == 1)
            {
                return before;
            }
            before = cursor;
            cursor = cursor->next;
        }
    }
}

void StudentDatabase::filteringInternational(float CGPA, int research, int TOEFL){
	Node *cursor;
	cursor = isHead;
	int isFlag = 0;
	while (cursor != NULL)
	{
		if (isEqualCGPA(cursor->is, CGPA) != 0 && isEqualresearch(cursor->is, research) != 0 && isEqualTOEFL(cursor->is,TOEFL)!= 0)
		{
			cout << "------------------------\n";
			cout << "International student"
				 << ": " << cursor->is.getFirstName() << " "
				 << cursor->is.getLastName() << "\n"
				 << "From: " << cursor->is.getCountry() << "\n"
				 << "CGPA: " << cursor->is.getCGPA() << "\n"
				 << "Research score: " << cursor->is.getResearchPt() << "\n"
				 << "TOEFL reading score: " << cursor->is.getToefl().getReadingPt() << "\n"
				 << "TOEFL listening score: " << cursor->is.getToefl().getListeningPt() << "\n"
				 << "TOEFL speaking score: " << cursor->is.getToefl().getSpeakingPt() << "\n"
				 << "TOEFL writing score: " << cursor->is.getToefl().getWritingPt() << "\n"
				 << "Total TOEFL score: " << cursor->is.getToefl().sumTotal() << "\n"
				 << endl;
				 isFlag++;

		}
		cursor = cursor->next;
	}
	if(isFlag == 0){
		cout << "No international student meet the requirement!\n";
	}
}
void StudentDatabase::filteringDomestic(float CGPA, int research, string province){
	Node *cursor;
	cursor = dsHead;
	int dsFlag = 0;
	while (cursor != NULL)
	{
		if (isEqualCGPA(cursor->ds, CGPA) != 0 && isEqualresearch(cursor->ds, research) != 0 && isequalProvince(cursor->ds,province) != 0)
		{
			cout << "------------------------\n";
			cout << "Domestic student"
				 << ": " << cursor->ds.getFirstName() << " "
				 << cursor->ds.getLastName() << "\n"
				 << "From: " << cursor->ds.getProvince() << "\n"
				 << "CGPA: " << cursor->ds.getCGPA() << "\n"
				 << "Research score: " << cursor->ds.getResearchPt() << "\n"
				 << endl;
				 dsFlag++;
		}
		cursor = cursor->next;
	}
	if(dsFlag == 0){
		cout << "No domestic student meet the requirement!\n";
	}
}
////////////////////////////////////////////////////////////
//////////////////////ERROR CHECKING////////////////////////
////////////////////////////////////////////////////////////

//Goes through every list item to find empty strings as items of the node
void StudentDatabase::findMissingFields()
{
	Node *cursor = mHead;
	if (merged)
	{
		while (cursor->next != NULL)
		{
			if (cursor->ds.isEmpty())
			{
				if (cursor->is.getFirstName() == "")
				{
					cout << endl
						 << "Error: student ID " << cursor->is.getAppNum()
						 << " is missing a first name" << endl;
				}
				if (cursor->is.getLastName() == "")
				{
					cout << endl
						 << "Error: student ID " << cursor->is.getAppNum()
						 << " is missing a last name" << endl;
				}
				if (cursor->is.getCGPA() == 0)
				{
					cout << endl
						 << "Error: student ID " << cursor->is.getAppNum()
						 << " is missing a CGPA value" << endl;
				}
				if (cursor->is.getResearchPt() == 0)
				{
					cout << endl
						 << "Error: student ID " << cursor->is.getAppNum()
						 << " is missing a research point value" << endl;
				}
				if (cursor->is.getToefl().sumTotal() == 0)
				{
					cout << endl
						 << "Error: student ID " << cursor->is.getAppNum()
						 << " is missing a TOEFL value" << endl;
				}
				if (cursor->is.getCountry() == "")
				{
					cout << endl
						 << "Error: student ID " << cursor->is.getAppNum()
						 << " is missing a country" << endl;
				}
			}
			if (cursor->is.isEmpty())
			{
				if (cursor->ds.getFirstName() == "")
				{
					cout << endl
						 << "Error: student ID " << cursor->ds.getAppNum()
						 << " is missing a first name" << endl;
				}
				if (cursor->ds.getLastName() == "")
				{
					cout << endl
						 << "Error: student ID " << cursor->ds.getAppNum()
						 << " is missing a last name" << endl;
				}
				if (cursor->ds.getCGPA() == 0)
				{
					cout << endl
						 << "Error: student ID " << cursor->ds.getAppNum()
						 << " is missing a CGPA value" << endl;
				}
				if (cursor->ds.getResearchPt() == 0)
				{
					cout << endl
						 << "Error: student ID " << cursor->ds.getAppNum()
						 << " is missing a research point value" << endl;
				}
				if (cursor->ds.getProvince() == "")
				{
					cout << endl
						 << "Error: student ID " << cursor->ds.getAppNum()
						 << " is missing a province" << endl;
				}
			}
			cursor = cursor->next;
		}
	}
	else
	{
		cursor = isHead;
		while (cursor->next != NULL)
		{
			if (cursor->is.getFirstName() == "")
			{
				cout << endl
					 << "Error: student ID " << cursor->is.getAppNum()
					 << " is missing a first name" << endl;
			}
			if (cursor->is.getLastName() == "")
			{
				cout << endl
					 << "Error: student ID " << cursor->is.getAppNum()
					 << " is missing a last name" << endl;
			}
			if (cursor->is.getCGPA() == 0)
			{
				cout << endl
					 << "Error: student ID " << cursor->is.getAppNum()
					 << " is missing a CGPA value" << endl;
			}
			if (cursor->is.getResearchPt() == 0)
			{
				cout << endl
					 << "Error: student ID " << cursor->is.getAppNum()
					 << " is missing a research point value" << endl;
			}
			if (cursor->is.getToefl().sumTotal() == 0)
			{
				cout << endl
					 << "Error: student ID " << cursor->is.getAppNum()
					 << " is missing a TOEFL value" << endl;
			}
			if (cursor->is.getCountry() == "")
			{
				cout << endl
					 << "Error: student ID " << cursor->is.getAppNum()
					 << " is missing a country" << endl;
			}
			cursor = cursor->next;
		}
		cursor = dsHead;
		while (cursor->next != NULL)
		{
			if (cursor->ds.getFirstName() == "")
			{
				cout << endl
					 << "Error: student ID " << cursor->ds.getAppNum()
					 << " is missing a first name" << endl;
			}
			if (cursor->ds.getLastName() == "")
			{
				cout << endl
					 << "Error: student ID " << cursor->ds.getAppNum()
					 << " is missing a last name" << endl;
			}
			if (cursor->ds.getCGPA() == 0)
			{
				cout << endl
					 << "Error: student ID " << cursor->ds.getAppNum()
					 << " is missing a CGPA value" << endl;
			}
			if (cursor->ds.getResearchPt() == 0)
			{
				cout << endl
					 << "Error: student ID " << cursor->ds.getAppNum()
					 << " is missing a research point value" << endl;
			}
			if (cursor->ds.getProvince() == "")
			{
				cout << endl
					 << "Error: student ID " << cursor->ds.getAppNum()
					 << " is missing a province" << endl;
			}
			cursor = cursor->next;
		}
	}
}

//Goes through every node containing a non empty DomesticStudent object and 
//corrects misspelled province strings 
void StudentDatabase::checkProvinces()
{
    vector<string> provinces;
    provinces.push_back("NL");
    provinces.push_back("PE");
    provinces.push_back("NS");
    provinces.push_back("NB");
    provinces.push_back("QC");
    provinces.push_back("ON");
    provinces.push_back("MB");
    provinces.push_back("SK");
    provinces.push_back("AB");
    provinces.push_back("BC");
    provinces.push_back("YT");
    provinces.push_back("NT");
    provinces.push_back("NU");

    string prov;
    bool flag = false;

    if (merged)
    {
        Node *cursor = mHead;

        while (cursor->next != NULL)
        {
            if (cursor->is.isEmpty())
            {
                prov = cursor->ds.getProvince();
                for (int i = 0; i < prov.size(); i++)
                {
                    prov[i] = toupper(prov[i]);
                }
                for (int i = 0; i < provinces.size(); i++)
                {
                    if (provinces[i].compare(prov) == 0)
                    {
                        flag = true;
                    }
                }
                if (flag == false)
                {
                    cout << "Student #: "
                         << cursor->ds.getAppNum()
                         << " has erroneous province data: "
                         << cursor->ds.getProvince()
                         << endl;

                    int flag = 0;

                    switch (prov[0]) //Uses a breakdown of occuring letters to 
                    {                //best correct based off of available data
                    case 'N':
                        cursor->ds.setProvince("NL");
                        break;

                    case 'P':
                        cursor->ds.setProvince("PE");
                        break;

                    case 'Q':
                        cursor->ds.setProvince("QC");
                        break;

                    case 'O':
                        cursor->ds.setProvince("ON");
                        break;

                    case 'M':
                        cursor->ds.setProvince("MB");
                        break;

                    case 'S':
                        cursor->ds.setProvince("SK");
                        break;

                    case 'A':
                        cursor->ds.setProvince("AB");
                        break;

                    case 'B':
                        cursor->ds.setProvince("BC");
                        break;

                    case 'Y':
                        cursor->ds.setProvince("YT");
                        break;

                    default:
                        flag++;
                        break;
                    }

                    switch (prov[1])
                    {
                    case 'L':
                        cursor->ds.setProvince("NL");
                        break;

                    case 'S':
                        cursor->ds.setProvince("NS");
                        break;

                    case 'B':
                        cursor->ds.setProvince("NB");
                        break;

                    case 'T':
                        cursor->ds.setProvince("NT");
                        break;

                    case 'U':
                        cursor->ds.setProvince("NU");
                        break;

                    default:
                        flag++;
                        break;
                    }

                    if (flag == 2)
                    {
                        cout
                            << "Province correction system failed, no province match detected"
                            << endl
                            << endl;
                    }
                    else
                    {
                        cout
                            << "Match found, student #: "
                            << cursor->ds.getAppNum()
                            << " province data corrected to: "
                            << cursor->ds.getProvince()
                            << endl
                            << endl;
                    }
                }
                flag = false;
            }
            cursor = cursor->next;
        }
    }
    else
    {
        Node *cursor = dsHead;
        while (cursor->next != NULL)
        {

            prov = cursor->ds.getProvince();
            for (int i = 0; i < prov.size(); i++)
            {
                prov[i] = toupper(prov[i]);
            }
            for (int i = 0; i < provinces.size(); i++)
            {
                if (provinces[i].compare(prov) == 0)
                {
                    flag = true;
                }
            }
            if (flag == false)
            {
                cout << "Student #: "
                     << cursor->ds.getAppNum()
                     << " has erroneous province data: "
                     << cursor->ds.getProvince()
                     << endl;

                int flag = 0;

                switch (prov[0])
                {
                case 'N':
                    cursor->ds.setProvince("NL");
                    break;

                case 'P':
                    cursor->ds.setProvince("PE");
                    break;

                case 'Q':
                    cursor->ds.setProvince("QC");
                    break;

                case 'O':
                    cursor->ds.setProvince("ON");
                    break;

                case 'M':
                    cursor->ds.setProvince("MB");
                    break;

                case 'S':
                    cursor->ds.setProvince("SK");
                    break;

                case 'A':
                    cursor->ds.setProvince("AB");
                    break;

                case 'B':
                    cursor->ds.setProvince("BC");
                    break;

                case 'Y':
                    cursor->ds.setProvince("YT");
                    break;

                default:
                    flag++;
                    break;
                }

                switch (prov[1])
                {
                case 'L':
                    cursor->ds.setProvince("NL");
                    break;

                case 'S':
                    cursor->ds.setProvince("NS");
                    break;

                case 'B':
                    cursor->ds.setProvince("NB");
                    break;

                case 'T':
                    cursor->ds.setProvince("NT");
                    break;

                case 'U':
                    cursor->ds.setProvince("NU");
                    break;

                default:
                    flag++;
                    break;
                }

                if (flag == 2)
                {
                    cout
                        << "Province correction system failed, no province match detected"
                        << endl
                        << endl;
                }
                else
                {
                    cout
                        << "Match found, student #: "
                        << cursor->ds.getAppNum()
                        << " province data corrected to: "
                        << cursor->ds.getProvince()
                        << endl
                        << endl;
                }
            }
            flag = false;
            cursor = cursor->next;
        }
    }
}

//Checks and corrects for misspelled country strings
void StudentDatabase::checkCountries()
{
	vector<string> countries;
	countries.push_back("china");
	countries.push_back("india");
	countries.push_back("korea");
	countries.push_back("iran");

	Node *cursor;
	string country;
	int counter = 0;
	bool matched = false;
	int chinaCounter,
		indiaCounter,
		koreaCounter,
		iranCounter = 0;
	bool isVowel = false;

	if (merged)
	{
		cursor = mHead;
		while (cursor->next != NULL)
		{
			if (cursor->ds.isEmpty())
			{
				country = cursor->is.getCountry();
				for (int i = 0; i < country.size(); i++)
				{
					country[i] = tolower(country[i]);
				}

				for (int i = 0; i < countries.size(); i++)
				{
					if (countries[i].compare(country) == 0)
					{
						matched = true;
					}
				}

				if (!matched)
				{
					cout
						<< endl
						<< "Student #: "
						<< cursor->is.getAppNum()
						<< " country mismatch detected: "
						<< cursor->is.getCountry()
						<< endl;

					if (country.size() == 5)
					{
						if (country[0] == 'c')
						{
							cursor->is.setCountry("China");
						}
						if (country[0] == 'i')
						{
							cursor->is.setCountry("India");
						}
						if (country[0] == 'k')
						{
							cursor->is.setCountry("Korea");
						}
					}
					else if (country.size() == 4)
					{
						cursor->is.setCountry("Iran");
					}
					cout
						<< "Corrected to: "
						<< cursor->is.getCountry()
						<< endl;
				}
			}
			matched = false; 
			cursor = cursor->next;
		}
	}
	else
	{
		cursor = isHead;
		while (cursor->next != NULL)
		{
			if (cursor->ds.isEmpty())
			{
				country = cursor->is.getCountry();
				for (int i = 0; i < country.size(); i++)
				{
					country[i] = tolower(country[i]);
				}

				for (int i = 0; i < countries.size(); i++)
				{
					if (countries[i].compare(country) == 0)
					{
						matched = true;
					}
				}

				if (!matched)
				{
					cout
						<< endl
						<< "Student #: "
						<< cursor->is.getAppNum()
						<< " country mismatch detected: "
						<< cursor->is.getCountry()
						<< endl;

					if (country.size() == 5)
					{
						if (country[0] == 'c')
						{
							cursor->is.setCountry("China");
						}
						if (country[0] == 'i')
						{
							cursor->is.setCountry("India");
						}
						if (country[0] == 'k')
						{
							cursor->is.setCountry("Korea");
						}
					}
					else if (country.size() == 4)
					{
						cursor->is.setCountry("Iran");
					}
					cout
						<< "Corrected to: "
						<< cursor->is.getCountry()
						<< endl;
				}
			}
			matched = false;
			cursor = cursor->next;
		}

	}
}

//Scans current list and returns the highest current AppNum + 1
int StudentDatabase::latestAppNum()
{
	Node *cursor; 
	int latest = 20200000;

	if (merged)
	{
		cursor = mHead;
		while (cursor != NULL)
		{
			if (cursor->is.isEmpty())
			{
				if (cursor->ds.getAppNum() > latest)
				{
					latest = cursor->ds.getAppNum();
				}
			}
			else if (cursor->ds.isEmpty())
			{
				if (cursor->is.getAppNum() > latest)
				{
					latest = cursor->is.getAppNum();
				}
			}
			cursor = cursor->next;
		}
	}
	else
	{
		cursor = dsHead;
		while (cursor != NULL)
		{
			if (cursor->ds.getAppNum() > latest)
			{
				latest = cursor->ds.getAppNum();
			}
			cursor = cursor->next;
		}

		cursor = isHead;
		while (cursor != NULL)
		{
			if (cursor->is.getAppNum() > latest)
			{
				latest = cursor->is.getAppNum();
			}
			cursor = cursor->next;
		}
	}

	return latest + 1;
}

bool StudentDatabase::provinceCheck(string province){
  for (int i = 0; i < province.size(); i++)
	{
		if (province[i] >= 'a' && province[i] <= 'z')
		{
			province[i] -= ('a' - 'A');
		}
	}
  if (province != "NL" && province != "PE" && province != "NS" && province != "NB" && province != "QC" && province != "ON" && province != "MB" && province != "SK" && province != "AB" && province != "BC" && province != "YT" && province != "NT" && province != "NU" && province != "NA"){
    return false;
    }
    return true;
}

bool StudentDatabase::stringCheck(string input)
{
	for (int i = 0; i < input.size(); i++)
	{
		int uppercaseChar = toupper(input[i]); //Convert character to upper case version of character
		if (uppercaseChar < 'A' || uppercaseChar > 'Z') //If character is not A-Z
		{
			return false;
		}
	}
	return true; //Return true since every character had to be A-Z
}
