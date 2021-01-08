//main.cpp, put your driver code here,
//you can manipulate your class objects here
#include <iostream> //cin and cout
#include <fstream>  //file processing
#include <sstream>  //formatted string processing
#include <cstdlib>  //atof and atoi
#include "student.hpp"
#include "database.hpp"
#include <limits>
#include <cstring>
#include <chrono>
using namespace std;

int main()
{
  StudentDatabase db;
  int applicationStart = 20200000;
  int increment = 0;

  //Read the domestic-stu.txt file and exit if failed
  string line;
  ifstream domesticFile("domestic-stu.txt");
  if (!domesticFile.is_open())
  {
    cout << "Unable to open file domestic-stu.txt" << endl;
    return -1;
  }

  //Read the first line of domestic-stu.txt, which specifies
  //the file format. And then print it out to the screen
  getline(domesticFile, line);
  //cout << "File format: " << line << endl;

  /*Keep reading the rest of the lines in domestic-stu.txt.
   *In the example code here, I will read each data separated
   *by a comma, and then print it out to the screen.
   *In your lab assignment 1, you should use these read data
   *to initialize your DomesticStudent object. Then you can
   *use get and set functions to manipulate your object, and
   *print the object content to the screen
   */
  int stu_count = 1;
  while (getline(domesticFile, line))
  {
    /*process each line, get each field separated by a comma.
     *We use istringstream to handle it.
     *Note in this example code here, we assume the file format
     *is perfect and do NOT handle error cases. We will leave the
     *error and exception handling of file format to Lab Assignment 4
     */
    istringstream ss(line);

    string firstName, lastName, province, s_cgpa, s_researchScore;
    float cgpa;
    int researchScore;

    //get firstName separated by comma
    getline(ss, firstName, ',');

    //get lastName separated by comma
    getline(ss, lastName, ',');

    //get province separated by comma
    getline(ss, province, ',');

    //get cpga separated by comma, and convert string to float
    getline(ss, s_cgpa, ',');
    cgpa = atof(s_cgpa.c_str());

    //get researchScore separated by comma, and convert it to int
    getline(ss, s_researchScore, ',');
    researchScore = atoi(s_researchScore.c_str());

    //print the student info to the screen
    //cout << "Domestic student " << stu_count << " " << firstName << " "
    //     << lastName << " from " << province << " province has cgpa of "
    //     << cgpa << ", and research score of " << researchScore << endl;

    //initialising the domestic-stu.txt file values to the domestic student object
    DomesticStudent ds;
    ds.setFirstName(firstName);
    ds.setLastName(lastName);
    ds.setProvince(province);
    ds.setCGPA(cgpa);
    ds.setResearchPt(researchScore);
    ds.setAppNum(applicationStart + increment);
    increment++;

    //storing the object in the vector template
    db.append(ds);
    stu_count++;
  }

  //close your file
  domesticFile.close();

  //Read the international-stu.txt file and exit if failed
  ifstream internationalFile("international-stu.txt");
  if (!internationalFile.is_open())
  {
    cout << "Unable to open file international-stu.txt" << endl;
    return -1;
  }

  //Read the first line of international-stu.txt, which specifies
  //the file format. And then print it out to the screen
  getline(internationalFile, line);
  //cout << "File format: " << line << endl;

  /*Keep reading the rest of the lines in international-stu.txt.
   *In the example code here, I will read each data separated
   *by a comma, and then print it out to the screen.
   *In your lab assignment 1, you should use these read data
   *to initialize your InternationalStudent object. Then you can
   *use get and set functions to manipulate your object, and
   *print the object content to the screen
   */
  stu_count = 1;
  while (getline(internationalFile, line))
  {
    /*process each line, get each field separated by a comma.
     *We use istringstream to handle it.
     *Note in this example code here, we assume the file format
     *is perfect and do NOT handle error cases. We will leave the
     *error and exception handling of file format to Lab Assignment 4
     */
    istringstream ss(line);

    string firstName, lastName, country, s_cgpa, s_researchScore, s_reading, s_listening, s_speaking, s_writing;
    float cgpa;
    int researchScore;
    int Reading, Listening, Speaking, Writing;

    //get firstName separated by comma
    getline(ss, firstName, ',');

    //get lastName separated by comma
    getline(ss, lastName, ',');

    //get province separated by comma
    getline(ss, country, ',');

    //get cgpa separated by comma, and convert string to float
    getline(ss, s_cgpa, ',');
    cgpa = atof(s_cgpa.c_str());

    //get researchScore separated by comma, and convert it to int
    getline(ss, s_researchScore, ',');
    researchScore = atoi(s_researchScore.c_str());

    //get readingPt separated by comma, and convert it to int
    getline(ss, s_reading, ',');
    Reading = atoi(s_reading.c_str());

    //get listeningPt separated by comma, and convert it to int
    getline(ss, s_listening, ',');
    Listening = atoi(s_listening.c_str());

    //get SpeakingPt separated by comma, and convert it to int
    getline(ss, s_speaking, ',');
    Speaking = atoi(s_speaking.c_str());

    //get WritingPt separated by comma, and convert it to int
    getline(ss, s_writing, ',');
    Writing = atoi(s_writing.c_str());

    //get Total Toeflscore
    int totalScore = Reading + Listening + Speaking + Writing;

    //print the student info to the screen
    //cout << "International student " << stu_count << " " << firstName << " "
    //     << lastName << " from " << country << " has cgpa of " << cgpa
    //     << ", research score of " << researchScore << ", reading score of " << Reading
    //     << ", listening score of " << Listening << ", speaking score of " << Speaking
    //     << ", writing score of " << Writing << ", and total toefl score of " << totalScore << endl;

    //initialising the international -stu.txt file values to the international student object
    InternationalStudent is;

    is.setFirstName(firstName);
    is.setLastName(lastName);
    is.setCountry(country);
    is.setCGPA(cgpa);
    is.setResearchPt(researchScore);
    is.setToefl(Reading, Listening, Speaking, Writing);
    is.setAppNum(applicationStart + increment);
    increment++;

    //storing object in the vector template
    db.append(is);
    stu_count++;
  }

  //close your file
  internationalFile.close();

  /////Menu
  int userOption;
  float searchCGPA, scholoCGPA;
  int searchResearch, scholoResearch;
  int searchID;
  int scholoTOEFL;
  string searchLast;
  string searchFrist;
  string scholoProvince;
  int filterOption;
  int searchOption;
  string firstName, lastName;
  char delStudentFlag = 'y';

  //Unit Test Variables
  int UserOption, SearchOption;
  float Cgpa, Cgpa_threshold;
  int Research_Score, Application_id, ResearchScore_threshold;
  string searchlast, searchfirst;
  string firstname, lastname;
  char answer;
  int testCounter = 0;

  StudentDatabase DB, DB_UT;
  DomesticStudent ds1, ds2, ds3, ds4;
  InternationalStudent is1, is2, is3, is4, is5, is6;
  DomesticStudent dsTemp;
  InternationalStudent isTemp;

  string firstName1 = "Oliver", lastName1 = "Morris", province1 = "NL", s_cgpa1 = "3.90", s_researchScore1 = "74";
  float cgpa1 = atof(s_cgpa1.c_str());
  int researchScore1 = atoi(s_researchScore1.c_str());
  int appid1 = 2020007;
  ds1.setLastName(lastName1);
  ds1.setFirstName(firstName1);
  ds1.setProvince(province1);
  ds1.setCGPA(cgpa1);
  ds1.setResearchPt(researchScore1);
  ds1.setAppNum(appid1);

  string firstName2 = "Marry", lastName2 = "White", province2 = "BC", s_cgpa2 = "4.00", s_researchScore2 = "85";
  float cgpa2 = atof(s_cgpa2.c_str());
  int researchScore2 = atoi(s_researchScore2.c_str());
  int appid2 = 2020000;
  ds2.setLastName(lastName2);
  ds2.setFirstName(firstName2);
  ds2.setProvince(province2);
  ds2.setCGPA(cgpa2);
  ds2.setResearchPt(researchScore2);
  ds2.setAppNum(appid2);

  string firstName3 = "", lastName3 = "", province3 = "", s_cgpa3 = "", s_researchScore3 = "88";
  float cgpa3 = atof(s_cgpa3.c_str());
  int researchScore3 = atoi(s_researchScore3.c_str());
  int appid3 = 2020021;
  ds3.setLastName(lastName3);
  ds3.setFirstName(firstName3);
  ds3.setProvince(province3);
  ds3.setCGPA(cgpa3);
  ds3.setResearchPt(researchScore3);
  ds3.setAppNum(appid3);

  string firstName4 = "Anthony", lastName4 = "Long", province4 = "SK", s_cgpa4 = "3.70", s_researchScore4 = "93";
  float cgpa4 = atof(s_cgpa4.c_str());
  int researchScore4 = atoi(s_researchScore4.c_str());
  int appid4 = 2020040;
  ds4.setLastName(lastName4);
  ds4.setFirstName(firstName4);
  ds4.setProvince(province4);
  ds4.setCGPA(cgpa4);
  ds4.setResearchPt(researchScore4);
  ds4.setAppNum(appid4);

  string firstName5 = "Eungyung", lastName5 = "Ghim", country5 = "Korea", s_cgpa5 = "2.90", s_researchScore5 = "84", s_reading5 = "20", s_listening5 = "20", s_speaking5 = "25", s_writing5 = "25";
  int reading5 = atoi(s_reading5.c_str());
  int listening5 = atoi(s_listening5.c_str());
  int speaking5 = atoi(s_speaking5.c_str());
  int writing5 = atoi(s_writing5.c_str());
  int total5 = reading5 + listening5 + speaking5 + writing5;
  float cgpa5 = atof(s_cgpa5.c_str());
  int researchScore5 = atoi(s_researchScore5.c_str());
  int appid5 = 2020105;
  is1.setLastName(lastName5);
  is1.setFirstName(firstName5);
  is1.setCGPA(cgpa5);
  is1.setResearchPt(researchScore5);
  is1.setToefl(reading5, listening5, speaking5, writing5);
  is1.setAppNum(appid5);

  string firstName6 = "Mingmei", lastName6 = "Wang", country6 = "China", s_cgpa6 = "3.15", s_researchScore6 = "97", s_reading6 = "25", s_listening6 = "25", s_speaking6 = "27", s_writing6 = "24";
  int reading6 = atoi(s_reading6.c_str());
  int listening6 = atoi(s_listening6.c_str());
  int speaking6 = atoi(s_speaking6.c_str());
  int writing6 = atoi(s_writing6.c_str());
  int total6 = reading6 + listening6 + speaking6 + writing6;
  float cgpa6 = atof(s_cgpa6.c_str());
  int researchScore6 = atoi(s_researchScore6.c_str());
  int appid6 = 2020119;
  is2.setLastName(lastName6);
  is2.setFirstName(firstName6);
  is2.setCGPA(cgpa6);
  is2.setResearchPt(researchScore6);
  is2.setToefl(reading6, listening6, speaking6, writing6);
  is2.setAppNum(appid6);

  string firstName7 = "Arman", lastName7 = "Shams", country7 = "Iran", s_cgpa7 = "3.60", s_researchScore7 = "92", s_reading7 = "30", s_listening7 = "30", s_speaking7 = "28", s_writing7 = "29";
  int reading7 = atoi(s_reading7.c_str());
  int listening7 = atoi(s_listening7.c_str());
  int speaking7 = atoi(s_speaking7.c_str());
  int writing7 = atoi(s_writing7.c_str());
  int total7 = reading7 + listening7 + speaking7 + writing7;
  float cgpa7 = atof(s_cgpa7.c_str());
  int researchScore7 = atoi(s_researchScore7.c_str());
  int appid7 = 2020160;
  is3.setLastName(lastName7);
  is3.setFirstName(firstName7);
  is3.setCGPA(cgpa7);
  is3.setResearchPt(researchScore7);
  is3.setToefl(reading7, listening7, speaking7, writing7);
  is3.setAppNum(appid7);

  string firstName8 = "Aditya", lastName8 = "Bhattathiri", country8 = "Idian", s_cgpa8 = "3.85", s_researchScore8 = "79", s_reading8 = "25", s_listening8 = "25", s_speaking8 = "29", s_writing8 = "26";
  int reading8 = atoi(s_reading8.c_str());
  int listening8 = atoi(s_listening8.c_str());
  int speaking8 = atoi(s_speaking8.c_str());
  int writing8 = atoi(s_writing8.c_str());
  int total8 = reading8 + listening8 + speaking8 + writing8;
  float cgpa8 = atof(s_cgpa8.c_str());
  int researchScore8 = atoi(s_researchScore8.c_str());
  int appid8 = 2020173;
  is4.setLastName(lastName8);
  is4.setFirstName(firstName8);
  is4.setCGPA(cgpa8);
  is4.setResearchPt(researchScore8);
  is4.setToefl(reading8, listening8, speaking8, writing8);
  is4.setAppNum(appid8);

  string firstName9 = "Jin", lastName9 = "Zhou", country9 = "China", s_cgpa9 = "3.80", s_researchScore9 = "75", s_reading9 = "28", s_listening9 = "28", s_speaking9 = "30", s_writing9 = "21";
  int reading9 = atoi(s_reading9.c_str());
  int listening9 = atoi(s_listening9.c_str());
  int speaking9 = atoi(s_speaking9.c_str());
  int writing9 = atoi(s_writing9.c_str());
  int total9 = reading9 + listening9 + speaking9 + writing9;
  float cgpa9 = atof(s_cgpa9.c_str());
  int researchScore9 = atoi(s_researchScore9.c_str());
  int appid9 = 2020194;
  is5.setLastName(lastName9);
  is5.setFirstName(firstName9);
  is5.setCGPA(cgpa9);
  is5.setResearchPt(researchScore9);
  is5.setToefl(reading9, listening9, speaking9, writing9);
  is5.setAppNum(appid9);

  string firstName10 = "Doyoon", lastName10 = "Yie", country10 = "Korea", s_cgpa10 = "4.15", s_researchScore10 = "82", s_reading10 = "22", s_listening10 = "22", s_speaking10 = "23", s_writing10 = "28";
  int reading10 = atoi(s_reading10.c_str());
  int listening10 = atoi(s_listening10.c_str());
  int speaking10 = atoi(s_speaking10.c_str());
  int writing10 = atoi(s_writing10.c_str());
  int total10 = reading10 + listening10 + speaking10 + writing10;
  float cgpa10 = atof(s_cgpa10.c_str());
  int researchScore10 = atoi(s_researchScore10.c_str());
  int appid10 = 2020139;
  is6.setLastName(lastName10);
  is6.setFirstName(firstName10);
  is6.setCGPA(cgpa10);
  is6.setResearchPt(researchScore10);
  is6.setToefl(reading10, listening10, speaking10, writing10);
  is6.setAppNum(appid10);

  do
  {
    cout << "----------------------------------------------------------------\n"
         << "| Welcome to the simplified graduate student admission system, |\n"
         << "|             Please select your option below:                 |\n"
         << "| Press '1' to Print                                           |\n"
         << "| Press '2' to enter the Unit Test                             |\n"
         << "| Press '3' to merge                                           |\n"
         << "| Press '4' to enter the search engine                         |\n"
         << "| Press '5' to enter the scholarship filtering system          |\n"
         << "| Press '6' to test the error checking system                  |\n"
         << "| Press '7' to add a new student                               |\n"
         << "| Press '8' to see the big-O time complexity analysis          |\n"
         << "| Press '9' to delete student by first and last name           |\n"
         << "| Press '10' to delete both head and tail                      |\n"
         << "| Press '0' to exit the program                                |\n"
         << "----------------------------------------------------------------\n";
    while (!(cin >> userOption))
    {
      cin.clear();
      cin.ignore(numeric_limits<streamsize>::max(), '\n');
      cout << "Input must be numeric. Try again please: \n";
    }

    switch (userOption)
    {
    case 0:
      break;
      ///////////////////////////////////////////////////////////////////////
    case 1:
      db.print();
      break;
      ///////////////////////////////////////////////////////////////////////
    case 2:

      ///////////////////////UNIT_TEST_SECTION/////////////////////////
      ///////////////////////UNIT_TEST_SECTION/////////////////////////
      ///////////////////////UNIT_TEST_SECTION/////////////////////////
      ///////////////////////UNIT_TEST_SECTION/////////////////////////
      ///////////////////////UNIT_TEST_SECTION/////////////////////////

      do
      {
        cout << "--------------------------------------------------------------------------------------\n"
             << "| Welcome to the unit test section for graduate student admission system,            |\n"
             << "|             Please select your option below:                                       |\n"
             << "| Press '1' to insert students sorted                                                |\n"
             << "| Press '2' to search existing student by Application_id or Cgpa or Research_Score   |\n"
             << "| Press '3' to search existing student by FirstName and LastName                     |\n"
             << "| Press '4' to delete existing student by by FirstName and LastName                  |\n"
             << "| Press '5' to delete both the head node and tail node                               |\n"
             << "| Press '6' to merge                                                                 |\n"
             << "| Press '7' to search existing student by Cgpa_threshold or ResearchScore_threshold  |\n"
             << "| Press '8' to initiate AUTOMATIC TEST UNIT                                          |\n"
             << "| Press '0' to exit the program                                                      |\n"
             << "--------------------------------------------------------------------------------------\n";
        while (!(cin >> userOption))
        {
          cin.clear();
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          cout << "Input must be numeric. Try again please: \n";
        }

        switch (userOption)
        {
        case 0:
          break;
          ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case 1:
          DB.append(ds1);
          DB.append(ds2);
          DB.append(ds3);
          DB.append(ds4);
          DB.append(is1);
          DB.append(is2);
          DB.append(is3);
          DB.append(is4);
          DB.append(is5);
          DB.append(is6);
          DB.print();
          break;
          ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case 2:

          cout << "Welcome! You can search student(s) by Application_id or Cgpa or Research_Score.\n"
               << "Enter '1' to search by CGPA\n"
               << "Enter '2' to search by Research_score\n"
               << "Enter '3' to search by Application_id\n";
          while (!(cin >> searchOption))
          {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Input must be numeric. Try again please: \n";
          }
          switch (searchOption)
          {
          case 1:
            do
            {
              cout << "Please enter the CGPA:";
              cin >> Cgpa;
              DB.searchByCGPA(Cgpa);
              cout << "Do you want to search once more ?"
                   << "(Type y for yes or n for no):";
              cin >> answer;
              cout << endl;
            } while (answer == 'y' || answer == 'Y');
            break;
          ///////////////////////////////////////////////////////////////////
          case 2:
          {
            do
            {
              cout << "Please enter the research score:";
              cin >> Research_Score;
              DB.searchByResearch(Research_Score);
              cout << "Do you want to search once more ?"
                   << "(Type y for yes or n for no):";
              cin >> answer;
              cout << endl;
            } while (answer == 'y' || answer == 'Y');

            break;
          }
          ////////////////////////////////////////////////////////////////////
          case 3:
            do
            {
              cout << "Please enter the application ID:";
              cin >> Application_id;
              DB.searchByID(Application_id);
              cout << "Do you want to search once more ?"
                   << "(Type y for yes or n for no):";
              cin >> answer;
              cout << endl;
            } while (answer == 'y' || answer == 'Y');
            break;
          default:
            cout << "ERROR: Enter a proper option number please!" << endl;
          }
          break;
          ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case 3:
          do
          {
            while (1)
        {
          cout << "Please enter the first name of the student:";
            cin >> searchfirst;
          if (db.stringCheck(searchfirst) == 1)
          {
            break;
          }
          else
          {
            cout << "ERROR: Please enter a valid name.\n";
          }
        }
          while (1)
        {
          cout << "Please enter the last name of the student:";
            cin >> searchlast;
          if (db.stringCheck(searchlast) == 1)
          {
            break;
          }
          else
          {
            cout << "ERROR: Please enter a valid name.\n";
          }
        }
            DB.searchByLastFristName(searchfirst, searchlast);
            cout << "Do you want to search once more ?"
                 << "(Type y for yes or n for no):";
            cin >> answer;
            cout << endl;
          } while (answer == 'y' || answer == 'Y');
          break;
          ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case 4:
          do
          {
            while (1)
        {
          cout << "Please enter the first name of the student:";
            cin >> firstname;
          if (db.stringCheck(firstname) == 1)
          {
            break;
          }
          else
          {
            cout << "ERROR: Please enter a valid name.\n";
          }
        }
          while (1)
        {
          cout << "Please enter the last name of the student:";
            cin >> lastname;
          if (db.stringCheck(lastname) == 1)
          {
            break;
          }
          else
          {
            cout << "ERROR: Please enter a valid name.\n";
          }
        }
            DB.deleteStudent(firstname, lastname);
            DB.print();
            cout << "Do you want to delete once more ?"
                 << "(Type y for yes or n for no):";
            cin >> answer;
            cout << endl;
          } while (answer == 'y' || answer == 'Y');
          break;
        ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case 5:
          DB.deleteHeadTail();
          cout << "Both the head node and tail node has been deleted." << endl;
          DB.print();
          break;
          ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case 6:
          DB.merge();
          cout << "Welcome to the merged list: " << endl;
          DB.print();
          break;
          ///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

        case 7:
          do
          {
            cout << "Please enter the threshold CGPA:";
            cin >> Cgpa_threshold;
            cout << "Please enter the threshold Research Score:";
            cin >> ResearchScore_threshold;
            DB.searchByCGPAandResearch(Cgpa_threshold, ResearchScore_threshold);
            cout << "Would you like to search again?"
                 << "(Type y for yes or n for no):";
            cin >> answer;
            cout << endl;
          } while (answer == 'y' || answer == 'Y');
          break;

        case 8:

          DB_UT.append(ds1);
          DB_UT.append(ds2);
          DB_UT.append(ds3);
          DB_UT.append(ds4);
          DB_UT.append(is1);
          DB_UT.append(is2);
          DB_UT.append(is3);
          DB_UT.append(is4);
          DB_UT.append(is5);
          DB_UT.append(is6);
          
          //DOMESTIC STUDENT

          //edge top
          if (compareFirstName(ds1, DB_UT.getByFirstLastName("Oliver", "Morris")->ds) == 0)
          {
            testCounter++;
          }
          else
          {
            cout << endl << "FAILURE append edge top" << endl; 
          }

          //normal
          if (compareFirstName(ds2, DB_UT.getByFirstLastName("Marry", "White")->ds) == 0)
          {
            testCounter++;
          }
          else
          {
            cout << endl << "FAILURE append standard case" << endl; 
          }

          //edge bottom
          if (compareFirstName(ds4, DB_UT.getByFirstLastName("Anthony", "Long")->ds) == 0)
          {
            testCounter++;
          }
          else
          {
            cout << endl << "FAILURE append edge bottom" << endl; 
          }

          //edge bottom
          if (compareFirstName(ds4, DB_UT.getByFirstLastName("AnThOnY", "lOnG")->ds) == 0)
          {
            testCounter++;
          }
          else
          {
            cout << endl << "FAILURE append edge capitalization" << endl; 
          }

          //edge illegal
          //if (compareFirstName(ds4, DB_UT.getByFirstLastName("AnThOnY", "lOnG")->ds))
          if (NULL == DB_UT.getByFirstLastName("93879823rfhiushFF", "@@3jhoiuhf"))
          {
            testCounter++;
          }
          else
          {
            cout << endl << "FAILURE append edge illegal" << endl; 
          }

          //INTERNATIONAL STUDENT

          //edge top
          if (compareFirstName(is1, DB_UT.getByFirstLastName("Eungyung", "Ghim")->is) == 0)
          {
            testCounter++;
          }
          else
          {
            cout << endl << "FAILURE append edge top" << endl; 
          }

          //normal
          if (compareFirstName(is2, DB_UT.getByFirstLastName("Mingmei", "Wang")->is) == 0)
          {
            testCounter++;
          }
          else
          {
            cout << endl << "FAILURE append standard case" << endl; 
          }

          //edge bottom
          if (compareFirstName(is6, DB_UT.getByFirstLastName("Doyoon", "Yie")->is) == 0)
          {
            testCounter++;
          }
          else
          {
            cout << endl << "FAILURE append edge bottom" << endl; 
          }

          //edge capitalization
          if (compareFirstName(is6, DB_UT.getByFirstLastName("doYOoN", "yIe")->is) == 0)
          {
            testCounter++;
          }
          else
          {
            cout << endl << "FAILURE append edge capitalization" << endl; 
          }

          //edge illegal
          //if (compareFirstName(ds4, DB_UT.getByFirstLastName("AnThOnY", "lOnG")->ds))
          if (NULL == DB_UT.getByFirstLastName("93879823rfhiushFF", "@@3jhoiuhf"))
          {
            testCounter++;
          }
          else
          {
            cout << endl << "FAILURE append edge illegal" << endl; 
          }

          //MERGE LIST

          //edge head
          DB_UT.deleteStudent("Mingmei", "Wang");
          if (NULL == DB_UT.getByFirstLastName("Mingmei", "Wang")) {
            testCounter++;
          }
          else
          {
            cout << endl << "FAILURE delete edge head" << endl;
          }

          //edge tail
          DB_UT.deleteStudent("Jin", "Zhou");
          if (NULL == DB_UT.getByFirstLastName("Jin", "Zhou")) {
            testCounter++;
          }
          else
          {
            cout << endl << "FAILURE delete normal" << endl;
          }

          //edge normal
          DB_UT.deleteStudent("Doyoon", "Yie");
          if (NULL == DB_UT.getByFirstLastName("Doyoon", "Yie")) {
            testCounter++;
          }
          else
          {
            cout << endl << "FAILURE delete normal" << endl;
          }

          DB_UT.append(is2);
          DB_UT.append(is5);
          DB_UT.append(is6);
          
          DB_UT.merge();
      
          //DOMESTIC STUDENT

           

          //edge top
          if (compareFirstName(ds1, DB_UT.getByFirstLastName("Oliver", "Morris")->ds) == 0)
          {
            testCounter++;
          }
          else
          {
            cout << endl << "FAILURE append edge top" << endl; 
          }

          //normal
          if (compareFirstName(ds2, DB_UT.getByFirstLastName("Marry", "White")->ds) == 0)
          {
            testCounter++;
          }
          else
          {
            cout << endl << "FAILURE append standard case" << endl; 
          }

          //edge bottom
          if (compareFirstName(ds4, DB_UT.getByFirstLastName("Anthony", "Long")->ds) == 0)
          {
            testCounter++;
          }
          else
          {
            cout << endl << "FAILURE append edge bottom" << endl; 
          }

          //edge bottom
          if (compareFirstName(ds4, DB_UT.getByFirstLastName("AnThOnY", "lOnG")->ds) == 0)
          {
            testCounter++;
          }
          else
          {
            cout << endl << "FAILURE append edge capitalization" << endl; 
          }

          //edge illegal
          if (NULL == DB_UT.getByFirstLastName("93879823rfhiushFF", "@@3jhoiuhf"))
          {
            testCounter++;
          }
          else
          {
            cout << endl << "FAILURE append edge illegal" << endl; 
          }

          //INTERNATIONAL STUDENT

          //edge top
          if (compareFirstName(is1, DB_UT.getByFirstLastName("Eungyung", "Ghim")->is) == 0)
          {
            testCounter++;
          }
          else
          {
            cout << endl << "FAILURE append edge top" << endl; 
          }

          //normal
          if (compareFirstName(is2, DB_UT.getByFirstLastName("Mingmei", "Wang")->is) == 0)
          {
            testCounter++;
          }
          else
          {
            cout << endl << "FAILURE append standard case" << endl; 
          }

          //edge bottom
          if (compareFirstName(is6, DB_UT.getByFirstLastName("Doyoon", "Yie")->is) == 0)
          {
            testCounter++;
          }
          else
          {
            cout << endl << "FAILURE append edge bottom" << endl; 
          }

          //edge capitalization
          if (compareFirstName(is6, DB_UT.getByFirstLastName("doYOoN", "yIe")->is) == 0)
          {
            testCounter++;
          }
          else
          {
            cout << endl << "FAILURE append edge capitalization" << endl; 
          }

          //edge illegal
          if (NULL == DB_UT.getByFirstLastName("93879823rfhiushFF", "@@3jhoiuhf"))
          {
            testCounter++;
          }
          else
          {
            cout << endl << "FAILURE append edge illegal" << endl; 
          } 

          //DELETE MERGED
          //edge head
          DB_UT.deleteStudent("Mingmei", "Wang");
          if (NULL == DB_UT.getByFirstLastName("Mingmei", "Wang")) {
            testCounter++;
          }
          else
          {
            cout << endl << "FAILURE delete edge head" << endl;
          }

          //edge tail
          DB_UT.deleteStudent("Jin", "Zhou");
          if (NULL == DB_UT.getByFirstLastName("Jin", "Zhou")) {
            testCounter++;
          }
          else
          {
            cout << endl << "FAILURE delete normal" << endl;
          }

          for (int i = 0; i < 100; i++) DB_UT.deleteHeadTail();
          testCounter++; 

          cout << endl << "PASSED " << testCounter << "/26 TESTS" << endl; 

          break;
        default:
          cout << "ERROR: Enter a proper option number please!" << endl;
          break;
        }

        
      } while (userOption != 0);
      ///////////////////////UNIT_TEST_SECTION/////////////////////////
      ///////////////////////UNIT_TEST_SECTION/////////////////////////
      ///////////////////////UNIT_TEST_SECTION/////////////////////////
      ///////////////////////UNIT_TEST_SECTION/////////////////////////
      ///////////////////////UNIT_TEST_SECTION/////////////////////////

      break;
      ///////////////////////////////////////////////////////////////////////
    case 3:
      db.merge();
      break;

      //////////////////////////////////////////////////////////////////////////////////////////////////////////
    case 4:
      cout << "Welcome to the searching engine, you can search student(s) by certain parameters.\n"
           << "Enter '1' to search by CGPA\n"
           << "Enter '2' to search by research score\n"
           << "Enter '3' to search by application ID\n"
           << "Enter '4' to search by last and first name\n";
      while (!(cin >> searchOption))
      {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Input must be numeric. Try again please: \n";
      }
      switch (searchOption)
      {
      case 1:
        cout << "Please enter the CGPA:";
        while (!(std::cin >> searchCGPA) || searchCGPA > 4.33 || searchCGPA < 0)
        {
          cin.clear();                                                   //Clear error flags to allow normal input
          cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //ignore errorneous output still sitting in buffer
          cout << "ERROR: Please enter a CGPA between 0 and 4.33.\n";
        }
        db.searchByCGPA(searchCGPA);
        break;
      ///////////////////////////////////////////////////////////////////
      case 2:
        cout << "Please enter the research score:";
        while (!(cin >> searchResearch) || searchResearch < 0 || searchResearch > 100)
        {
          cin.clear();
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          cout << "ERROR: Please enter a research score between 0 and 100.\nTry again please: \n";
        }
        db.searchByResearch(searchResearch);
        break;
      ////////////////////////////////////////////////////////////////////
      case 3:
        cout << "Please enter the application ID:";
        while (!(cin >> searchID) || searchID < 20200000 || searchID > 20201000)
        {
          cin.clear();
          cin.ignore(numeric_limits<streamsize>::max(), '\n');
          cout << "ERROR: Please enter a application ID between 20200000 and 20201000.\nTry again please: \n";
        }
        db.searchByID(searchID);
        break;
      /////////////////////////////////////////////////////////////////////
      case 4:
        while (1)
        {
          cout << "Please enter the frist name of the student:";
          cin >> searchFrist;
          if (db.stringCheck(searchFrist) == 1)
          {
            break;
          }
          else
          {
            cout << "ERROR: Please enter a valid name.\n";
          }
        }

        while (1)
        {
          cout << "Please enter the last name of the student:";
          cin >> searchLast;
          if (db.stringCheck(searchLast) == 1)
          {
            break;
          }
          else
          {
            cout << "ERROR: Please enter a valid name.\n";
          }
        }
        db.searchByLastFristName(searchFrist, searchLast);
        break;
      default:
        cout << "ERROR: Enter a proper option number please!" << endl;
        break;
      }
      break;
      //////////////////////////////////////////////////////////////////////////////////////////////////////////
    case 5:
      cout << "Welcome to the scholarship filtering system, \n"
           << "here you can enter the requirements for your scholoarship.\n"
           << "Only the students who meet the requirements will get printed.\n"
           << "Enter 1 for domestic scholoarship\n"
           << "Enter 2 for international scholoarship\n";
      while (!(cin >> filterOption))
      {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "Input must be numeric. Try again please: \n";
      }
      ///////////////////////switch in filtering system/////////////////////////
      switch (filterOption)
      {
      case 1:
        cout << "Please enter the required CGPA for your scholoarship:";
        while (!(std::cin >> scholoCGPA) || scholoCGPA > 4.33 || scholoCGPA < 0)
        {
          cin.clear();                                                   //Clear error flags to allow normal input
          cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //ignore errorneous output still sitting in buffer
          cout << "ERROR: Please enter a CGPA between 0 and 4.33.\n";
        }

        cout << "Please enter the required research score for your scholoarship:";
        while (!(std::cin >> scholoResearch) || scholoResearch > 100 || scholoResearch < 0)
        {
          cin.clear();                                                   //Clear error flags to allow normal input
          cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //ignore errorneous output still sitting in buffer
          cout << "ERROR: Please enter a research score between 0 and 100.\n";
        }
        while (1)
        {
          cout << "Please enter the province of your scholoarship (enter 'NA' if it's for all Canadian students):";
          cin >> scholoProvince;
          if (db.provinceCheck(scholoProvince) == 1)
          {
            break;
          }
          else
          {
            cout << "ERROR: Please enter a valid province. eg. 'AB' for Alberta.\n";
          }
        }
        db.filteringDomestic(scholoCGPA, scholoResearch, scholoProvince);
        break;
      /////////////////////////////////////////////////////////////////////
      case 2:
        cout << "Please enter the required CGPA for your scholoarship:";
        while (!(std::cin >> scholoCGPA) || scholoCGPA > 4.33 || scholoCGPA < 0)
        {
          cin.clear();                                                   //Clear error flags to allow normal input
          cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //ignore errorneous output still sitting in buffer
          cout << "ERROR: Please enter a CGPA between 0 and 4.33.\n";
        }

        cout << "Please enter the required research score for your scholoarship:";
        while (!(std::cin >> scholoResearch) || scholoResearch > 100 || scholoResearch < 0)
        {
          cin.clear();                                                   //Clear error flags to allow normal input
          cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //ignore errorneous output still sitting in buffer
          cout << "ERROR: Please enter a research score between 0 and 100.\n";
        }

        cout << "Please enter the required total TOEFL score for your scholoarship:";
        while (!(std::cin >> scholoTOEFL) || scholoTOEFL > 120 || scholoTOEFL < 0)
        {
          cin.clear();                                                   //Clear error flags to allow normal input
          cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); //ignore errorneous output still sitting in buffer
          cout << "ERROR: Please enter a TOEFL score between 0 and 100.\n";
        }

        db.filteringInternational(scholoCGPA, scholoResearch, scholoTOEFL);
        break;

      default:
        cout << "ERROR: Enter a proper option number please!" << endl;
        break;
      }
      ///////////////////////////////switch in filtering system/////////////////////////
      break;
    case 6:
      db.checkProvinces();
      db.checkCountries();
      db.findMissingFields();
      break;
      //////////////////////////////////////////////////////////////////////////////////////
    case 7: //add student
      db.addStudent();
      break;
      /////////////////////////////////////////////////////////////////////////////////////
    case 8: //big ohhhhhh
      //insert, search, deletion, and merge functions
      cout << "Big-O time complexity analysis for functions:\n";
      cout << "Insert function:\n";
      double arr[8][2];
      for (int i = 0; i < 8; i++)
      {
        arr[i][0] = (i + 1) * 5 * (2 * i + 1);
      }
      for (int i = 0; i < 8; i++)
      {
        auto start = chrono::high_resolution_clock::now();
        for (int j = 1; j <= arr[i][0]; j++)
        {
          db.addDomesticStudentTest("someone", "someone", 4.2, 95, "BC");
        }
        auto stop = chrono::high_resolution_clock::now();
        chrono::duration<double> diff = stop - start;
        arr[i][1] = diff.count();
        for (int j = 1; j <= arr[i][0]; j++)
        {
          db.deleteStudentNoPrint("someone", "someone");
        }
        db.deleteStudentNoPrint("someone", "someone");
        cout << arr[i][0] << ", " << arr[i][1] << "\n";
      }
      /////////////////////////////////////////////////////////////////////////////
      double arr1[8][2];
      cout << "Delete function:\n";
      for (int i = 0; i < 8; i++)
      {
        arr1[i][0] = (i + 1) * 5 * (2 * i + 1);
      }
      for (int i = 0; i < 8; i++)
      {
        for (int j = 1; j <= arr1[i][0]; j++)
        {
          db.addDomesticStudentTest("someone", "someone", 4.2, 95, "BC");
        }
        auto start = chrono::high_resolution_clock::now();
        for (int j = 1; j <= arr1[i][0]; j++)
        {
          db.deleteStudentNoPrint("someone", "someone");
        }
        auto stop = chrono::high_resolution_clock::now();
        chrono::duration<double> diff = stop - start;
        arr1[i][1] = diff.count();
        cout << arr1[i][0] << ", " << arr1[i][1] << "\n";
      }
      //////////////////////////////////////////////////////////////////////////////
      double arr2[8][2];
      cout << "Merge function:\n";
      for (int i = 0; i < 8; i++)
      {
        arr2[i][0] = (i + 1) * 5 * (2 * i + 1);
      }
      for (int i = 0; i < 8; i++)
      {
        auto start = chrono::high_resolution_clock::now();
        for (int j = 1; j <= arr2[i][0]; j++)
        {
          db.addDomesticStudentTest("someone", "someone", 4.2, 95, "BC");
          db.mergeNoPrint();
        }
        auto stop = chrono::high_resolution_clock::now();
        chrono::duration<double> diff = stop - start;
        arr2[i][1] = diff.count();
        for (int j = 1; j <= arr2[i][0]; j++)
        {
          db.deleteStudentNoPrint("someone", "someone");
        }
        cout << arr2[i][0] << ", " << arr2[i][1] << "\n";
      }
      ///////////////////////////////////////////////////////////////////////////////
      double arr3[8][2];
      cout << "Search function:\n";
      for (int i = 0; i < 8; i++)
      {
        arr3[i][0] = (i + 1) * 5 * (2 * i + 1);
      }
      for (int i = 0; i < 8; i++)
      {
        db.addDomesticStudentTest("someone", "someone", 4.2, 95, "BC");
        auto start = chrono::high_resolution_clock::now();
        for (int j = 1; j <= arr3[i][0]; j++)
        {
          db.searchNoPrint(4.2);
        }
        auto stop = chrono::high_resolution_clock::now();
        chrono::duration<double> diff = stop - start;
        arr3[i][1] = diff.count();
        db.deleteStudentNoPrint("someone", "someone");
        cout << arr3[i][0] << ", " << arr3[i][1] << "\n";
      }
      break;
      /////////////////////////////////////////////////////////////////////////////////////
    case 9:
      while (delStudentFlag == 'y')
      {
        while (1)
        {
          cout << "Please enter the first name of the student:";
          cin >> firstName;
          if (db.stringCheck(firstName) == 1)
          {
            break;
          }
          else
          {
            cout << "ERROR: Please enter a valid name.\n";
          }
        }

        while (1)
        {
          cout << "Please enter the last name of the student:";
          cin >> lastName;
          if (db.stringCheck(lastName) == 1)
          {
            break;
          }
          else
          {
            cout << "ERROR: Please enter a valid name.\n";
          }
        }

        db.deleteStudent(firstName, lastName);

        while (1)
        {
          cout << "Would you like to delete another student by the same name? y/n ";
          cin >> delStudentFlag;
          if (delStudentFlag == 'y')
          {
            db.deleteStudent(firstName, lastName);
          }
          else if (delStudentFlag == 'n')
          {
            break;
          }
          else
          {
            cout << "ERROR: Please enter a valid name.\n";
          }
        }
      }
      break;
      /////////////////////////////////////////////////////////////////////////////////////
    case 10:
      
      db.deleteHeadTail();

      break;
    default:
      cout << "ERROR: Enter a proper option number please!" << endl;
      break;
    }
  } while (userOption != 0);
  cout << "Thank you for using the system, see you next time!\n";
}
