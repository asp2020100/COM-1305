/*  
Student Management System With File Handing In C++
R.M.Y.P.Rathnayake 
ASP/19/20/100
4840
COM1305 - Mini Project
2023/08/25
*/

// Include necessary libraries for the program
#include <windows.h>        //Preprocessor to set console properties 
#include <iostream>         //Preprocessor to get standard input/output
#include <conio.h>          //Preprocessor to handle functionalities of the console
#include <string>           //Preprocessor to manage string inputs
#include <fstream>          //Preprocessor for file handling methods
#include <regex>            //Preprocessor to handle regular expressions 
#include <iomanip>          //Preprocessor to manipulate input output


using namespace std;        //using standard formats

//global variables
char un[20], pw[20];
int lgStat = 0;//Variable to Store Login Status
char login[20];//LOGGED USERNAME


void Menu(); // Project Menu function definition


// Validate input 
bool validate(string expressions, char tests[]) {
	regex ry(expressions);
	cmatch result;
	//Compare the variables with regular expressions
	if (regex_match(tests, result, ry)) {
		return true;
	}
	else {
		return false;
	}
}




//Create Stucture student to store data
struct users {
	char username[20], password[20];
};

//Create Stucture student to store data
struct student {
    unsigned int sid, age;           // Student ID and age
    char FName[20], SName[30];       // First name and surname (up to 20 and 30 characters respectively)
    char course[20];                 // Course (up to 20 characters)
    char address[100];               // Address (up to 100 characters)
    char phoneNo[11];                // Phone number (up to 11 characters)


    // Member function to clear the struct's data
    void clear() {
        // Reset the values of the struct's members
        sid = 0;
        age = 0;
        FName[0] = '\0';
        SName[0] = '\0';
        course[0] = '\0';
        address[0] = '\0';
        phoneNo[0] = '\0';
	}
};



student stdobject;//Global Variable  for the program to access student





// Heading Function
void heading() {
	if (lgStat == 2)cout << setw(20) << "\n                       Logged in as " << login;
	cout << setw(20) << "\n-------------------------------------------------------------------";
	cout << setw(20) << "\n                 STUDENT MANAGEMENT SYSTEM BY 4840                 ";
	cout << setw(20) << "\n-------------------------------------------------------------------\n";
}



//  Password Function 
void getPassword(string msg) {
	char ch = '0';

	cout << setw(5) << msg + "Enter Password: ";
	//Convert paswword from text to asterisk
	//Check size of characters increment on loop
	for (int x = 0; x <= sizeof(pw); ++x) { 

		//validate character length
		if (ch != 13 && ch != (int)-52) {
			ch = _getch();
			if (ch == 8) {
				cout << endl;
				if (msg != "Re ") msg = "Re ";
				getPassword(msg);//pass the value to the function
				break;
			}
			if (ch != 13) cout << "*";//display * instead of characters

			pw[x] = ch;

		}
		else if ((int)ch == 13) {

			pw[x - 1] = (int)0;
			pw[x] = (int)-52;
			ch = (int)-52;
		}
		else {
			pw[x] = (int)-52;
		}
	}

}

// login input output Function
void LoginIO(string msg) {
	system("cls");//Clear Console
	heading();// Displays Heading 
	cout << setw(20) << "\n                                 " << msg << " Login                                          ";
	cout << setw(20) <<"\n-------------------------------------------------------------------\n";

	cout << setw(5) << "Enter Username: ";
	cin >> un;

	getPassword("");// Call get password function

}


// login Function
void loginFunc()
{
	lgStat = 0;//login status

	system("cls");//Clear Console

	users object;

	ifstream file;



	while (true) {
		if (lgStat == 0) {
			system("cls");//Clear Console

			heading();// Displays Heading
			LoginIO("");//Call Login input output function

			file.open("users.txt", ios::out);  // Open for writing (text mode)
			while (file.read((char*)&object, sizeof(object))) {

				//Compare characters
				if ((strcmp(un, object.username) == 0 && strcmp(pw, object.password) == 0)) {

					//copy charaters to structure's variables
					strncpy_s(login, object.username, sizeof(object.username));
					lgStat = 2;//logged in
					break;
				}
				else {
					lgStat = 1;//logout
				}
			}
			file.close();
			//login
			if (lgStat == 2) break;
		}
		else if (lgStat == 1) {
			system("cls");//Clear Console
			heading();// Displays Heading
			cout << setw(20) << "\n                                  Login                              ";
			cout << setw(20) << "\n-------------------------------------------------------------------\n";
			cout << setw(20) << "\n Access Denied....... Incorrect Username or Password...................\n";
			cout << setw(20) << "\n Press 'Y' to re try Login or any other key to go to Main Menu: ";

			char ch;
			cin >> ch;

			if (ch == 'y' || ch == 'Y') {
				LoginIO("Re ");//call the login input ouput function

				file.open("users.txt", ios::out);  // Open for writing (text mode)
				while (file.read((char*)&object, sizeof(object))) {
					//Compare characters
					if ((strcmp(un, object.username) == 0 && strcmp(pw, object.password) == 0)) {
						lgStat = 2;
						break;
					}
					else {
						lgStat = 1;
					}
				}
				file.close();
				if (lgStat == 2) break;
			}
			else {
				system("cls");//Clear Console
				Menu();//Call Menu Function

				break;
			}
		}
		else if (lgStat == 2) {
			break;

		}
	}



	if (lgStat == 2) {
		system("cls");//Clear Console
		Menu();//Call Menu Function
	}
}


// Add User function
void adduser()
{
	system("cls");//Clear Console

	heading();// Displays Heading
	cout << setw(20) << "\n                          Add new user                               ";
	cout << setw(20) << "\n-------------------------------------------------------------------\n";
	users object;
	ofstream file;
	file.open("users.txt", ios::app | ios::out);

	while (true) {
		char temp[20];
		cout << left << "Enter username: ";
		cin >> temp;
		if (validate("[\\w]+", temp)) {
			//copy data to object 
			strncpy_s(object.username, temp, sizeof(temp));
			break;
		}
		else {
			cout << left << "\t----------- Invalid value.. Please re-enter\n\n";
		}

	}

	while (true) {
		getPassword("");//call get password method
		//validate password
		if (validate("[\\w]+", pw)) {
			//copy data to object 
			strncpy_s(object.password, pw, sizeof(pw));
			break;
		}
		else {
			cout << left << "\t----------- Invalid value.. Please re enter\n\n";
		}

	}

	file.write((char*)&object, sizeof(object));
	file.close();
	cout << "\nData Sucessfully Saved... press any key to go to Main menu..";
	_getch();
	system("cls");//Clear Console
	Menu();//Call Menu Function

}


// Delete User function
void deleteUser()
{
	char opt = 0;
	users userObject;

	while (true) {
		bool firstTime = false;
		bool result = false;

		while (true) {
			system("cls");//Clear Console

            if (!firstTime) {}
            else {
                cout << left << "\nInvalid option selected ...... Please re select in order to continue .......\n";
            }

            heading();// Displays Heading
            cout << setw(20) << "\n                     Delete Student Details Menu                     ";
            cout << setw(20) << "\n-------------------------------------------------------------------\n";

            cout << left << "1. Delete user\n";
            cout << left << "\n2. Return to Main Menu\n";

            cout << setw(20) << "\n------------------------------------\n";

            cout << setw(20) << "\n *To Continue Please Select an Option : ";
            cin >> opt;

            firstTime = true;
        }

		system("cls");//Clear Console
		heading();// Displays Heading

		if (opt == '1') {
			cout << setw(20) << "\n                          Delete user";
		}
		else if (opt == '2') {
			system("cls");//Clear Console
			Menu();//Call Menu Function
			break;
		}

		cout << setw(20) << "\n-------------------------------------------------------------------\n";

		char searchChars[20];
		cout << setw(20) << "** Delete is case sensitive **\n";

		cout << setw(20) << "\nEnter user name to delete : ";
		cin >> searchChars;


		ifstream file;
		file.open("users.txt", ios::out);  // Open for writing (text mode)

		ofstream filet;
		filet.open("userst.txt", ios::app | ios::out);  // Open for writing (text mode)

		while (file.read((char*)&userObject, sizeof(userObject))) {
			if (strcmp(searchChars, userObject.username) == 0) {

				cout << left << "Username : " << userObject.username << endl;
				cout << setw(20) << "\nRecord will be deleted permanantly...... \n";
				cout << setw(20) << "\nType 'Y' to confirm or any other to cancel: ";
				char ch;
				cin >> ch;//get confirmation
				if (ch == 'y' || ch == 'Y') {
					lgStat = 0;
					result = true;
				}
				else {
					filet.write((char*)&userObject, sizeof(userObject));
				}
			}
			else {
				filet.write((char*)&userObject, sizeof(userObject));
			}
		}

		file.close();
		filet.close();

		remove("users.txt");
		rename("userst.txt", "users.txt");

        if (!result) {
            cout << setw(20) << "\n-------------------No records have being deleted---------------------------\n";

            cout << setw(20) << "\n Press any key to continue.........";
            _getch();
        } else {

            cout << setw(20) << "\nRecord has been deleted";

            cout << setw(20) << "\nPress any key to continue.........";
            _getch();
            system("cls");//Clear Console
            Menu();//Call Menu Function
            break;

        }
    }
}




//Display function
void displayStudent()
{
	if (stdobject.age != NULL) {
		cout << endl;
		cout << setw(20) << "---------------------- Student Details ----------------------\n";
		cout << left << "Student Id  : " << stdobject.sid << endl;
		cout << left << "First Name  : " << stdobject.FName << endl;
		cout << left << "Surname Name: " << stdobject.SName << endl;
		cout << left << "Age         : " << stdobject.age << endl;
		cout << left << "Address     : " << stdobject.address << endl;
		cout << left << "Phone Number: " << stdobject.phoneNo << endl;
		cout << left << "Course      : " << stdobject.course << endl;
		cout << endl;
	}

}



// Student Details function
void stdDetailsToObject(char x) {
	//save student id to object
	if (x == 'a') {
		while (true) {
			char id[10];
			cout << left << "\nEnter Student Id                  : ";
			cin >> id;
			//validation
			if (validate("[\\d]+", id)) {
				int num = 0;
				sscanf_s(id, "%d", &num);
				//copy data to object 
				stdobject.sid = num;
				break;
			}
			else {
				cout << left << "\t----------- Invalid value.. Please re enter\n\n";
			}
		}
	}
	//save student first name to object
	if (x == 'a' || x == '1' || x == '7') {
		while (true) {
			char fntemp[20];
			cout << left << "\nEnter first name of the student   : ";
			cin >> fntemp;
			//validation
			if (validate("[a-zA-Z]+", fntemp)) {
				//copy data to object 
				strncpy_s(stdobject.FName, fntemp, sizeof(fntemp));
				break;
			}
			else {
				cout << left << "\t----------- Invalid value.. Please re enter\n\n";
			}

		}
	}
	//save student last name to object
	if (x == 'a' || x == '2' || x == '7') {
		while (true) {
			char sntemp[30];
			cout << left << "\nEnter surname of the student      : ";
			cin >> sntemp;
			//validation
			if (validate("[a-zA-Z]+", sntemp)) {
				//copy data to object 
				strncpy_s(stdobject.SName, sntemp, sizeof(sntemp));
				break;
			}
			else {
				cout << left << "\t----------- Invalid value.. Please re enter\n\n";
			}

		}
	}
	//save student age to object
	if (x == 'a' || x == '3' || x == '7') {
		while (true) {
			char agetemp[10];
			cout << left << "\nEnter age of the student ( 18-40 ): ";
			cin >> agetemp;
			//validation
			if (validate("[\\d]+", agetemp)) {
				int num = 0;
				sscanf_s(agetemp, "%d", &num);
				//copy data to object 
				if (num >= 18 && num <= 40) {
					stdobject.age = num;
					break;
				}
				else {
					cout << left << "\t----------- Invalid limit.. Please re enter\n\n";
				}
			}
			else {
				cout << left << "\t----------- Invalid value.. Please re enter\n\n";
			}

		}
	}
	//save student address to object
	if (x == 'a' || x == '4' || x == '7') {
		while (true) {
			char adTemp[100];
			cout << left << "\nEnter Addreess                    : ";
			cin.ignore();
			cin.getline(adTemp, 99);
			//validation
			if (validate("[/:a-zA-Z0-9\\s]+", adTemp)) {
				//copy data to object 
				strncpy_s(stdobject.address, adTemp, sizeof(adTemp));
				break;
			}
			else {
				cout << left << "\t----------- Invalid value.. Please re enter\n\n";
			}
		}
	}

	//save student phone number to object
	if (x == 'a' || x == '5' || x == '7') {
		while (true) {

			char phnoTemp[11];
			cout << left << "\nEnter Phone Number                : ";
			cin >> phnoTemp;
			//validation
			if (validate("[\\d]{10}", phnoTemp)) {
				//copy data to object 
				strncpy_s(stdobject.phoneNo, phnoTemp, sizeof(phnoTemp));
				break;
			}
			else {
				cout << left << "\t----------- Invalid value.. Please re enter\n\n";
			}

		}
	}
	//save student course to object
	if (x == 'a' || x == '6' || x == '7') {
		while (true) {
			char crseTemp[20];
			cout << left << "\nEnter course                      : ";
			cin >> crseTemp;
			//validation
			if (validate("[\\w\\s]+", crseTemp)) {
				//copy data to object 
				strncpy_s(stdobject.course, crseTemp, sizeof(crseTemp));
				break;
			}
			else {
				cout << left << "\t----------- Invalid value.. Please re enter\n\n";
			}

		}
	}
}


//Student Registration function

void stdRegistration()
{
	system("cls");//Clear Console

	heading();// Displays Heading
	cout << setw(20) << "\n                          Student Registration                       ";
	cout << setw(20) << "\n-------------------------------------------------------------------\n";
	stdobject.clear();//clear object
	ofstream file;
	file.open("stdDetails.txt", ios::app | ios::out);
	stdDetailsToObject('a');//call student details to object function

	file.write((char*)&stdobject, sizeof(stdobject));

	file.close();
	displayStudent();//call display student function

	cout << "Data Sucessfully Saved... press any key to go to Main Menu..";
	_getch();
	system("cls");//Clear Console

	Menu();//Call Menu Function

}


// Search function
void stdSearch() {
	char opt = 0;

	while (true) {
		bool firstTime = false;
		bool result = false;

		while (true) {
			system("cls");//Clear Console

            if (!firstTime) {}
            else {
                cout << left << "Invalid option selected ...... Please re select in order to continue .......\n";
            }
            heading();// Displays Heading
            cout << setw(20) << "\n                          Student Search Menu                        ";
            cout << setw(20) << "\n-------------------------------------------------------------------\n";
            cout << left << "1. Search Student by ID\n";
            cout << left << "2. Search Student by First Name\n";
            cout << left << "3. Search Student By Course\n";
            cout << left << "4. Return to Main Menu\n";

            cout << setw(20) << "\n------------------------------------\n";

            cout << setw(20) << "\n *To Continue Please Select an Option : ";
            cin >> opt;

            firstTime = true;
            if (opt == '1' || opt == '2' || opt == '3' || opt == '4') break;
        }

		system("cls");//Clear Console
		heading();// Displays Heading
		cout << setw(20) << "\n                          Student Search                             ";
		cout << setw(20) << "\n-------------------------------------------------------------------\n";

		char searchChars[20];
		cout << setw(20) << "** Search is case sensitive **\n";

		if (opt == '1') {
			cout << setw(20) << "\nEnter student ID : ";
		}
		else if (opt == '2') {
			cout << setw(20) << "\nEnter student First Name : ";
		}
		else if (opt == '3') {
			cout << setw(20) << "\nEnter student course : ";
		}
		else if (opt == '4') {
			system("cls");//Clear Console
			Menu();//Call Menu Function
			break;
		}

		cin >> searchChars;
		ifstream file;
		file.open("stdDetails.txt", ios::app | ios::out);

		while (file.read((char*)&stdobject, sizeof(stdobject))) {
			//search using student id
			if (opt == '1') {
				int num = 0;
				sscanf_s(searchChars, "%d", &num);

				if ((num = stdobject.sid)) {

					result = true;
					break;
				}
				else {

				}

			}
			//search using student first name
			else if (opt == '2') {
				if (strcmp(searchChars, stdobject.FName) == 0) {

					result = true;
					break;
				}
				else {

				}
			}
			//search using student course
			else if (opt == '3') {

				if (strcmp(searchChars, stdobject.course) == 0) {

					result = true;
					break;
				}
				else {

				}
			}

		}

		file.close();

        if (!result) {
            cout << setw(20) << "\n-------------------Could not find the Searched record ---------------------------\n";

            cout << setw(20) << "\nPress any key to continue.........";
            _getch();

        } else {
            displayStudent();//call display student function
            cout << setw(20) << "\nPress any key to continue.........";
            _getch();
        }
    }
}


// Update function
void stdUpdate()
{
	char opt = 0;

	while (true) {
		bool firstTime = false;
		bool result = false;

		while (true) {
			system("cls");//Clear Console

			if (firstTime == true) {
				cout << left << "\nInvalid option selected ...... Please re select in order to continue .......\n";
			}

			heading();// Displays Heading
			cout << setw(20) << "\n                 Update Student Details Menu                        ";
			cout << setw(20) << "\n-------------------------------------------------------------------\n";

			cout << left << "1. Update Student First Name\n";
			cout << left << "2. Update Student Surname\n";
			cout << left << "3. Update Student Age\n";
			cout << left << "4. Update Student Addreess\n";
			cout << left << "5. Update Student Phone Number\n";
			cout << left << "6. Update Student course\n";
			cout << left << "7. Update Student All Details\n";
			cout << left << "\n8. Return to Main Menu\n";

			cout << setw(20) << "\n------------------------------------\n";

			cout << setw(20) << "\n *To Continue Please Select an Option : ";
			cin >> opt;

			firstTime = true;
            if (opt == '1' && opt == '2' && opt == '3' && opt == '4' && opt == '5' && opt == '6' && opt == '7' &&
                opt == '8')
                continue;
            break;
        }

		system("cls");//Clear Console
		heading();// Displays Heading

		if (opt == '1') {
			cout << setw(20) << "\n                          Update Student First Name";
		}
		else if (opt == '2') {
			cout << setw(20) << "\n                          Update Student Surname";
		}
		else if (opt == '3') {
			cout << setw(20) << "\n                          Update Student Age";
		}
		else if (opt == '4') {
			cout << setw(20) << "\n                          Update Student Addreess";
		}
		else if (opt == '5') {
			cout << setw(20) << "\n                          Update Student Phone Number";
		}
		else if (opt == '6') {
			cout << setw(20) << "\n                          Update Student course";
		}
		else if (opt == '6') {
			cout << setw(20) << "\n                          Update Student All Details";
		}
		else if (opt == '8') {
			system("cls");//Clear Console
			Menu();//Call Menu Function
			break;
		}

		cout << setw(20) << "\n-------------------------------------------------------------------\n";

		char searchChars[20];
		cout << setw(20) << "** Search is case sensitive **\n";

		cout << setw(20) << "\nEnter student ID to make changes : ";
		cin >> searchChars;

		int num = 0;

		sscanf_s(searchChars, "%d", &num);

		ifstream file;
		file.open("stdDetails.txt", ios::app | ios::out);

		ofstream filet;
		filet.open("stdDetailst.txt", ios::app | ios::out);

		while (file.read((char*)&stdobject, sizeof(stdobject))) {
			if (num == stdobject.sid) {
				result = true;
				stdDetailsToObject(opt);//based on opt pass parameter and change data
				filet.write((char*)&stdobject, sizeof(stdobject));
			}
			else {
				filet.write((char*)&stdobject, sizeof(stdobject));
			}
		}

		file.close();
		filet.close();

		remove("stdDetails.txt");
		rename("stdDetailst.txt", "stdDetails.txt");//copy and paste updated data

		if (result == true) {
			file.open("stdDetails.txt", ios::app | ios::out);

			while (file.read((char*)&stdobject, sizeof(stdobject))) {
				if (num == stdobject.sid) {
					cout << setw(20) << "\nData has been updated in the selected record";
					displayStudent();
					cout << setw(20) << "\nPress any key to continue.........";
					_getch();
				}
			}
			file.close();
		}
		else {
			cout << setw(20) << "\n-------------------Could not find the searched record ---------------------------\n";

			cout << setw(20) << "\nPress any key to continue.........";
			_getch();
		}
	}
}


//  Delete Students function
void stdDelete()
{
	char opt = 0;

	while (true) {
		bool firstTime = false;
		bool result = false;

		while (true) {
			system("cls");//Clear Console

			if (firstTime == true) {
				cout << left << "\nInvalid option selected ...... Please re select in order to continue .......\n";
			}

			heading();// Displays Heading
			cout << setw(20) << "\n                    Delete Student Details Menu                      ";
			cout << setw(20) << "\n-------------------------------------------------------------------\n";

			cout << left << "1. Delete Student Record\n";
			cout << left << "\n2. Return to Main Menu\n";

			cout << setw(20) << "\n------------------------------------\n";

			cout << setw(20) << "\n *To Continue Please Select an Option : ";
			cin >> opt;

			firstTime = true;
            if (opt != '1' || opt != '2') { break; }
		}

		system("cls");//Clear Console
		heading();// Displays Heading

		if (opt == '1') {
			cout << setw(20) << "\n                          Delete student";
		}
		else if (opt == '2') {
			system("cls");//Clear Console
			Menu();//Call Menu Function
			break;
		}

		cout << setw(20) << "\n-------------------------------------------------------------------\n";

		char searchChars[20];
		cout << setw(20) << "** Search is case sensitive **\n";

		cout << setw(20) << "\nEnter student ID to delete : ";
		cin >> searchChars;

		int num = 0;

		sscanf_s(searchChars, "%d", &num);

		ifstream file;
		file.open("stdDetails.txt", ios::in | ios::app | ios::out);

		ofstream filet;
		filet.open("stdDetailst.txt", ios::in | ios::app | ios::out);

		while (file.read((char*)&stdobject, sizeof(stdobject))) {
			if (num == stdobject.sid) {

				cout << setw(20) << "\nRecord will be deleted permanantly...... ";
				displayStudent();
				cout << setw(20) << "\nType 'Y' to confirm or any other to cancel: ";
				char ch;
				cin >> ch;
				//delete confirmation validation
				if (ch == 'y' || ch == 'Y') {

					result = true;
				}
				else {
					filet.write((char*)&stdobject, sizeof(stdobject));
				}
			}
			else {
				filet.write((char*)&stdobject, sizeof(stdobject));
			}
		}

		file.close();
		filet.close();

		remove("stdDetails.txt");
		rename("stdDetailst.txt", "stdDetails.txt");//copy and pasting required data

		if (result == true) {

			cout << setw(20) << "\nRecord has been deleted";

			cout << setw(20) << "\nPress any key to continue.........";
			_getch();

		}
		else {
			cout << setw(20) << "\n-------------------No records has being deleted---------------------------\n";

			cout << setw(20) << "\nPress any key to continue.........";
			_getch();
		}
	}
}





// Help function
void help() {

	system("cls");//Clear Console
	heading();// Displays Heading

	cout << "\n\n";
	cout << left << "-----------------------------------" << endl;
	cout << left << " Help - How to use the Application " << endl;
	cout << left << "-----------------------------------" << "\n\n\n";

	cout << "NOTE - All feilds are mandatory and therefore  cannot be ommited.\n";
	cout << "NOTE - All feilds that requires Text will only recognize Text.\n";
	cout << "NOTE - All feilds that requires Numeric Input will only recognize Numeric Input\n";
	cout << "NOTE - All Inputs are retrived precisely to the written format in the files hence all operations are case sensitive.\n";
	cout << "NOTE - Use standard formats and convention to get the best performance from the application."<<"\n\n";

	cout << left << "-----------------------------------" << endl;
	cout << left << "               Login               " << endl;
	cout << left << "-----------------------------------" << endl;
	cout << "Press 1 in the main menu to login to the system." << endl;
	cout << "Then it will be requesting for the credentials." << endl;
	cout << "And by filling all the details correctly, you can login to the system." << endl;
	cout << "NOTE - You must fill all the required details in order to login to the system." << "\n\n";
	cout << "-----------------------------------------------------------------------------------------\n\n";

	cout << left << "-----------------------------------" << endl;
	cout << left << "           Add new users           " << endl;
	cout << left << "-----------------------------------" << endl;
	cout << "NOTE - To do this you must be logged onto the system." << "\n\n";
	cout << "Press 2 in the main menu to add new user to the system." << endl;
	cout << "And by filling all the details correctly, you can add new user to the system." << "\n\n";
	cout << "NOTE - You must fill all the required details in order to login to the system in the future." << "\n\n";
	cout << "-----------------------------------------------------------------------------------------\n\n";

	cout << left << "-----------------------------------" << endl;
	cout << left << "          Delete Users             " << endl;
	cout << left << "-----------------------------------" << endl;
	cout << "NOTE - To do this you must be logged onto the system." << "\n\n";
	cout << "Press 3 in the main menu to delete user to the system." << endl;
	cout << "And by filling all the details correctly, you can delete user from the system." << "\n\n";
	cout << "NOTE - You must fill all the required details in order to remove the user from the system." << "\n\n";
	cout << "-----------------------------------------------------------------------------------------\n\n";

	cout << left << "-----------------------------------" << endl;
	cout << left << "          Register Student         " << endl;
	cout << left << "-----------------------------------" << endl;
	cout << "NOTE - To do this you must be logged onto the system." << "\n\n";
	cout << "Press 4 in the main menu to add a new student to the system." << endl;
	cout << "Then it will be requesting for the student details." << endl;
	cout << "And by filling all the details correctly, you can add a student to the system." << "\n\n";
	cout << "NOTE - You must fill all the required details in order to add a student to the system." << "\n\n";
	cout << "NOTE - The phone number will only accept 10 characters." << "\n\n";
	cout << "NOTE - The Address will be in the below format " << "\n\n";
	cout << "1600 Amphitheatre Parkway  Mountain View  CA ";
	cout << "-----------------------------------------------------------------------------------------\n\n";


	cout << left << "-----------------------------------" << endl;
	cout << left << "       Search Student Detials      " << endl;
	cout << left << "-----------------------------------" << endl;
	cout << "NOTE - To do this you must be logged onto the system." << "\n\n";
	cout << "Press 5 in the main menu to  Search a student from the system." << endl;
	cout << "You will be routed to sub menu which will provide search options." << "\n\n";
	cout << "In this menu you will be able to search according to a variety of options: " << "\n\n";
	cout << "If you press 1 you will be able to search students by using id."<< "\n\n";
	cout << "If you press 2 you will be able to search students by using their first name." << "\n\n";
	cout << "If you press 3 you will be able to search students by using their course." << "\n\n";
	cout << "If you press 4 you will be re-directed to the main menu." << "\n\n";
	cout << "NOTE - Search is HIGHLY CASE SENSITIVE." << "\n\n";

	cout << left << "-----------------------------------" << endl;
	cout << left << "     Update Student Detials        " << endl;
	cout << left << "-----------------------------------" << endl;
	cout << "NOTE - To do this you must be logged onto the system." << "\n\n";
	cout << "Press 6 in the main menu to  Update a student's details from the system." << endl;
	cout << "You will be routed to sub menu which will provide Update options." << "\n\n";
	cout << "In this menu you will be able to Update according to a variety of options: " << endl;
	cout << "If you press 1 you will be able to Update student's id." << endl;
	cout << "If you press 2 you will be able to Update student's first name." << endl;
	cout << "If you press 3 you will be able to Update student's surname." << endl;
	cout << "If you press 4 you will be able to Update student's age." << endl;
	cout << "If you press 5 you will be able to Update student's address." << endl;
	cout << "If you press 6 you will be able to Update student's course." << endl;
	cout << "If you press 7 you will be able to Update student's all details." << endl;
	cout << "If you press 8 you will be re-directed to the main menu." << endl;
	cout << "NOTE - Update will prompt search using student Id hence input is HIGHLY CASE SENSITIVE." << "\n\n";

	cout << left << "-----------------------------------" << endl;
	cout << left << "     Delete Student Detials        " << endl;
	cout << left << "-----------------------------------" << endl;
	cout << "NOTE - To do this you must be logged onto the system." << "\n\n";
	cout << "Press 6 in the main menu to  Delete student details from the system." << endl;
	cout << "You will be routed to sub menu which will provide delete options." << "\n\n";
	cout << "In this menu you will be able to delete according to a variety of options: " << endl;
	cout << "If you press 1 you will be able to delete student details." << endl;
	cout << "If you press 2 you will be re-directed to the main menu." << endl;
	cout << "NOTE - delete will prompt search using student Id hence input is HIGHLY CASE SENSITIVE." << endl;


	cout << left << "-----------------------------------" << endl;
	cout << left << "                Help               " << endl;
	cout << left << "-----------------------------------" << endl;
	cout << "NOTE - To do this you must be logged onto the system." << endl;
	cout << "Help will give you the basic conventions to be followed when using the system." << endl;

	cout << left << "-----------------------------------" << endl;
	cout << left << "        Other functions            " << endl;
	cout << left << "-----------------------------------" << endl;
	cout << "Press 9 in the main menu to log out from the system." << endl;
	cout << "Press 10 in the main menu to exit from the system." << endl;


	cout << "Press any key to go to Main Menu..";
	_getch();

	system("cls");//Clear Console
	Menu();//Call Menu Function



}


// Menu function
void Menu()
{
	while (true) {
		heading();// Displays Heading
		cout << left << "1. Login\n";
		cout << left << "2. Add new user\n";
		cout << left << "3. Delete user\n";
		cout << left << "4. Register Student\n";
		cout << left << "5. Search Students\n";
		cout << left << "6. Update Student Details\n";
		cout << left << "7. Delete Student Details\n";
		cout << left << "8. Help\n";
		cout << left << "9. Logout\n";
		cout << left << "10.Exit\n";

		cout << setw(20) << "\n------------------------------------\n";
		cout << setw(20) << "\n *To Continue Please Select an Option : ";

		unsigned short int opt;
		cin >> opt;

		if (opt == 1) {
			loginFunc();// call login function
			break;
		}
		else if (opt == 2) {
			if (lgStat == 2) {
				adduser();//call add user function
				break;
			}
			else {
				system("cls");//Clear Console
				cout << left << "\nPlease login before continue .......\n";
			}
		}
		else if (opt == 3) {
			if (lgStat == 2) {
				deleteUser();//call delete user function
				break;
			}
			else {
				system("cls");//Clear Console
				cout << left << "\nPlease login before continue .......\n";
			}
		}
		else if (opt == 4) {
			if (lgStat == 2) {
				stdRegistration();//Call student registration function
				break;
			}
			else {
				system("cls");//Clear Console
				cout << left << "\nPlease login before continue .......\n";
			}
		}
		else if (opt == 5) {
			stdSearch();// call student search function
			break;
		}
		else if (opt == 6) {
			if (lgStat == 2) {
				stdUpdate();//Call student update
				break;
			}
			else {
				system("cls");//Clear Console
				cout << left << "\nPlease login before continue .......\n";
			}
		}
		else if (opt == 7) {
			if (lgStat == 2) {
				stdDelete();//Call delete student function
				break;
			}
			else {
				system("cls");//Clear Console
				cout << left << "\nPlease login before continue .......\n";
			}
		}
		else if (opt==8) {
			if (lgStat == 2) {
				help();//Call help function
				break;
			}
			else {
				system("cls");//Clear Console
				cout << left << "\nPlease login before continue .......\n";
			}
		}
		else if (opt == 9) {
			lgStat = 0;
			system("cls");//Clear Console
		}
		else if (opt == 10) {
			exit(0);//exit application
		}
		else {
			system("cls");//Clear Console
			cout << left << "\nInvalid option selected ...... Please re select in order to continue .......\n";
		}
	}

}



// Main function 
int main() {
	system("mode 650");//Set console size
	SetConsoleTitle(TEXT ("STUDENT MANAGEMENT SYSTEM BY 4840"));// Set console window's title
	system("COLOR F0");//Sets the background & text color
	Menu();//Call Menu Function

	system("pause");//to pause the console window
}
// END.
