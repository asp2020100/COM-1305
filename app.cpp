/*  
Student Management System With File Handing In C++
R.M.Y.P.Rathnayake 
ASP/19/20/100
4840
COM1305 - Mini Project
2023/08/25
*/

// Include necessary libraries for the program
#include <iostream>       // Provides input-output stream functionality
#include <conio.h>        // Provides console input/output functions (non-standard)
#include <stdio.h>        // Provides standard input/output functions
#include <fstream>        // Provides file stream functionality
#include <stdlib.h>       // Includes functions for various operations
#include <cstdlib>        // Includes standard C library functions
#include <string>         // Provides string manipulation functions and classes



using namespace std;      // Use the "std" namespace throughout the program

class student
{
private:
    // Private member variables to store student information
    string name, index_no, registration_no, course, address, email_id;
    long long int contact_no;

public:
    // Public member function declarations
    void menu();
    void insert();
    void display();
    void modify();
    void search();
    void deleted();
};

// Project Menu function definition
void student::menu()
{
menustart:
    int choice;
    char x;
    system("cls");  // Clear the console screen

    // Display the menu header
    cout << "\t\t\t------------------------------------" << endl;
    cout << "\t\t\t| STUDENT MANAGEMENT SYSTEM BY 4840 |" << endl;
    cout << "\t\t\t------------------------------------" << endl;
    cout << "\t\t\t 1. Enter New Record" << endl;
    cout << "\t\t\t 2. Display Record" << endl;
    cout << "\t\t\t 3. Modify Record" << endl;
    cout << "\t\t\t 4. Search Record" << endl;
    cout << "\t\t\t 5. Delete Record" << endl;
    cout << "\t\t\t 6. Exit\n"
         << endl;

    // Display options and prompt for user choice
    cout << "\t\t\t------------------------------------" << endl;
    cout << "\t\t\t    Choose Options:[1/2/3/4/5/6] :  " << endl;
    cout << "\t\t\t------------------------------------" << endl;
    cout << " Enter Your Choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        do
        {
            insert();  // Call the insert function to add a new student record
            cout << "\n\n\t\t\t Add Another Student Record (Y, N) : ";
            cin >> x;
        } while (x == 'y' || x == 'Y');
        break;
    case 2:
        display();  // Call the display function to show student records
        break;
    case 3:
        modify();   // Call the modify function to edit a student record
        break;
    case 4:
        search();   // Call the search function to find a student record
        break;
    case 5:
        deleted();  // Call the deleted function to remove a student record
        break;
    case 6:
        cout << "\n\t\t\t Program Is Exit";
        exit(0);    // Exit the program
    default:
        cout << "\n\n\t\t\t Invalid Choice... Please Try Again...";
    }
    getch();  // Wait for a key press
    goto menustart;  // Go back to the menu
}

// Function to insert student details
void student::insert()
{
    system("cls");  // Clear the console screen

    fstream file;  // Declare a file stream

    // Prompt and gather student details
    cout << "\t\t\t------------------------------------"  << endl;
    cout << "\t\t\t| STUDENT MANAGEMENT SYSTEM BY 4840 |" << endl;
    cout << "\t\t\t|        Add Student Details        |" << endl;
    cout << "\t\t\t------------------------------------"  << endl;
    cout << "\t\t\tEnter Name: ";
    cin >> name;
    cout << "\t\t\tEnter Index No.: ";
    cin >> index_no;
    cout << "\t\t\tEnter Reg. No.: ";
    cin >> registration_no;
    cout << "\t\t\tEnter Course: ";
    cin >> course;
    cout << "\t\t\tEnter Email Id(name@gmail.com): ";
    cin >> email_id;
    cout << "\t\t\tEnter Contact No : ";
    cin >> contact_no;
    cout << "\t\t\tEnter Address: ";
    cin >> address;

    // Open the file in append mode and write the student details
    file.open("studentRecord.txt", ios::app | ios::out);
    file << " " << name << " " << index_no  << " " << registration_no << " " << course << " " << email_id << " " << contact_no << " " << address << "\n";
    file.close();  // Close the file
}

// Function to display student records
void student::display()
{
    system("cls");  // Clear the console screen

    fstream file;  // Declare a file stream
    int total = 1;  // Initialize a counter for student numbering

    // Display the header
    cout << "\t\t\t------------------------------------"  << endl;
    cout << "\t\t\t| STUDENT MANAGEMENT SYSTEM BY 4840 |" << endl;
    cout << "\t\t\t|       Student Record Table        |" << endl;
    cout << "\t\t\t------------------------------------"  << endl;
    
    // Open the file for reading
    file.open("studentRecord.txt", ios::in);
    if (!file)  // If the file cannot be opened
    {
        cout << "\n\t\t\tNo Data is Present... ";
        file.close();
    }
    else
    {
        // Read and display student records
        file >> name >> index_no >> registration_no >> course >> email_id >> contact_no >> address;
        while (!file.eof())
        {
            cout << "\n\n\t\t\tStudent No.: " << total++ << endl;
            cout << "\t\t\tName: " << name << "\n";
            cout << "\t\t\tIndex No.: " << index_no << "\n";
            cout << "\t\t\tReg. No.: " << registration_no << "\n";
            cout << "\t\t\tCourse: " << course << "\n";
            cout << "\t\t\tEmail Id: " << email_id << "\n";
            cout << "\t\t\tContact No.: " << contact_no << "\n";
            cout << "\t\t\tAddress: " << address << "\n";

            // Read the next set of student details
            file >> name >> index_no >> registration_no >> course >> email_id >> contact_no >> address;
        }

        if (total == 1)  // if No records found
        {
            cout << "\n\t\t\tNo Data is Present..." << endl;
        }
    }

    file.close();  // Close the file
}

// Function to modify student details
void student::modify()
{
    system("cls");  // Clear the console screen

    fstream file, file1;  // Declare two file streams for reading and writing

    string indexno;  // Stores the Index number of the student to be modified
    int found = 0;  // Flag to indicate if the student was found for modification

    // Display header
    cout << "\t\t\t------------------------------------"  << endl;
    cout << "\t\t\t| STUDENT MANAGEMENT SYSTEM BY 4840 |" << endl;
    cout << "\t\t\t|       Student Modify Details      |" << endl;
    cout << "\t\t\t------------------------------------"  << endl;


    // Open the original file for reading
    file.open("studentRecord.txt", ios::in);
    if (!file)  // If the file cannot be opened
    {
        cout << "\n\t\t\tNo Data is Present..";
        file.close();
    }
    else
    {
        // Prompt for the Index number to be modified
        cout << "\nEnter Index No. of Student which you want to Modify: ";
        cin >> indexno;

        // Open a temporary file for writing
        file1.open("record.txt", ios::app | ios::out);

        // Read the original file line by line
        file >> name >> index_no >> course >> email_id >> contact_no >> address;
        while (!file.eof())
        {
            if (indexno != index_no)
            {
                // Write unchanged student details to the temporary file
                file1 << " " << name << " " << index_no << " " << course << " " << email_id << " " << contact_no << " " << address << "\n";
            }
            else
            {
                // Prompt and gather modified student details
                cout << "\n\t\t\tEnter Name: ";
                /// getline(cin,name);
                cin >> name;
                cout << "\t\t\tEnter Index No.: ";
                cin >> index_no;
                cout << "\t\t\tEnter Registration No. : ";
                cin >> registration_no;
                cout << "\t\t\tEnter Course: ";
                cin >> course;
                cout << "\t\t\tEnter Email Id(name@gmail.com): ";
                cin >> email_id;           
                cout << "\t\t\tEnter Contact No(9639xxxxxx): ";
                cin >> contact_no;
                cout << "\t\t\tEnter Address: ";
                //  getline(cin,address);
                cin >> address;

                // Write modified student details to the temporary file
                file1 << " " << name << " " << index_no << " " << registration_no << " " << course << " " << email_id << " " << contact_no << " " << address << "\n";
                found++;
            }

            // Read the next set of student details from the original file
            file >> name >> index_no >> registration_no >> course >> email_id >> contact_no >> address;
        }

        if (found == 0)  // If the specified Index number was not found
        {
            cout << "\n\n\t\t\t Student Index No. Not Found....";
        }

        file1.close();  // Close the temporary file
        file.close();   // Close the original file

        // Remove the original file and rename the temporary file
        remove("studentRecord.txt");
        rename("record.txt", "studentRecord.txt");
    }
}

// Function to search for student details
void student::search()
{
    system("cls");  // Clear the console screen

    fstream file;  // Declare a file stream

    int found = 0;  // Flag to indicate if the student was found

    // Display header
    cout << "\t\t\t------------------------------------"  << endl;
    cout << "\t\t\t| STUDENT MANAGEMENT SYSTEM BY 4840 |" << endl;
    cout << "\t\t\t|       Student Search Table        |" << endl;
    cout << "\t\t\t------------------------------------"  << endl;

    // Open the file for reading
    file.open("studentRecord.txt", ios::in);
    if (!file)  // If the file cannot be opened
    {
        cout << "\n\t\t\tNo Data is Present... " << endl;
    }
    else
    {
        string indexno;  // Stores the index number of the student to be searched

        // Prompt for the index number to be searched
        cout << "\nEnter index No. of Student which you want to search: ";
        cin >> indexno;

        // Read the file line by line
        file >> name >> index_no >> registration_no >> course >> email_id >> contact_no >> address;
        while (!file.eof())
        {
            if (indexno == index_no)
            {
                // Display the student details if found
                cout << "\n\n\t\t\tName: " << name << "\n";
                cout << "\t\t\tIndex No.: " << index_no << "\n";
                cout << "\t\t\tReg. No.: " << registration_no << "\n";
                cout << "\t\t\tCourse: " << course << "\n";
                cout << "\t\t\tEmail Id: " << email_id << "\n";
                cout << "\t\t\tContact No.: " << contact_no << "\n";
                cout << "\t\t\tAddress: " << address << "\n";
                found++;
            }

            // Read the next set of student details from the file
            file >> name >> index_no >> course >> email_id >> contact_no >> address;
        }

        if (found == 0)  // If the specified index number was not found
        {
            cout << "\n\t\t\t Student index No. Not Found....";
        }

        file.close();  // Close the file
    }
}

// Function to delete student data
void student::deleted()
{
    system("cls");  // Clear the console screen

    fstream file, file1;  // Declare two file streams for reading and writing

    int found = 0;  // Flag to indicate if the student was found
    string index;    // Stores the index number of the student to be deleted

    // Display header

    cout << "\t\t\t------------------------------------"  << endl;
    cout << "\t\t\t| STUDENT MANAGEMENT SYSTEM BY 4840 |" << endl;
    cout << "\t\t\t|      Delete Student Details       |" << endl;
    cout << "\t\t\t------------------------------------"  << endl;

    // Open the original file for reading
    file.open("studentRecord.txt", ios::in);
    if (!file)  // If the file cannot be opened
    {
        cout << "\n\t\t\tNo Data is Present..";
        file.close();
    }
    else
    {
        // Prompt for the index number to be deleted
        cout << "\nEnter Index No. of Student which you want Delete Data: ";
        cin >> index;

        // Open a temporary file for writing
        file1.open("record.txt", ios::app | ios::out);

        // Read the original file line by line
        file >> name >> index_no >> registration_no >> course >> email_id >> contact_no >> address;
        while (!file.eof())
        {
            if (index != index_no)
            {
                // Write student details to the temporary file if not to be deleted
                file1 << " " << name << " " << index_no << " " << registration_no << " " << course << " " << email_id << " " << contact_no << " " << address << "\n";
            }
            else
            {
                found++;
                cout << "\n\t\t\tSuccessfully Delete Data";
            }

            // Read the next set of student details from the original file
            file >> name >> index_no >> registration_no >> course >> email_id >> contact_no >> address;
        }

        if (found == 0)  // If the specified index number was not found
        {
            cout << "\n\t\t\t Student index No. Not Found....";
        }

        file1.close();  // Close the temporary file
        file.close();   // Close the original file

        // Remove the original file and rename the temporary file
        remove("studentRecord.txt");
        rename("record.txt", "studentRecord.txt");
    }
}

int main()
{
    student project; // Create an object of the 'student' class named 'project'
    project.menu();  // Call the 'menu()' function of the 'project' object
    return 0;        // Return 0 to indicate successful program execution
}
