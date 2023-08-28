
#include <iostream>       
#include <conio.h>        
#include <stdio.h>        
#include <fstream>        
#include <stdlib.h>       
#include <string>         


using namespace std;      

class student
{
private:
    
    string name, index_no, registration_no, course, address, email_id;
    long long int contact_no;

public:
    
    void menu();
    void insert();
    void display();
    void modify();
    void search();
    void deleted();
};


void student::menu()
{
menustart:
    int choice;
    char x;
    system("cls");  

   
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

    
    cout << "\t\t\t------------------------------------" << endl;
    cout << "\t\t\t    Choose Options:[1/2/3/4/5/6] :  " << endl;
    cout << "\t\t\t------------------------------------" << endl;
    cout << "\t\t\t    Enter Your Choice: ";
    cin >> choice;

    switch (choice)
    {
    case 1:
        do
        {
            insert();  
            cout << "\n\n\t\t\t Add Another Student Record (Y, N) : ";
            cin >> x;
        } while (x == 'y' || x == 'Y');
        break;
    case 2:
        display();  
        break;
    case 3:
        modify();   
        break;
    case 4:
        search();   
        break;
    case 5:
        deleted();  
        break;
    case 6:
        cout << "\n\t\t\t Program Is Exit";
        exit(0);    
    default:
        cout << "\n\n\t\t\t Invalid Choice... Please Try Again...";
    }
    _getch();  
    goto menustart;  
}


void student::insert()
{
    system("cls");  

    fstream file;  

   
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
    cout << "\t\t\tEnter Email Id: ";
    cin >> email_id;
    cout << "\t\t\tEnter Contact No : ";
    cin >> contact_no;
    cout << "\t\t\tEnter Address: ";
    cin >> address;

    
    file.open("studentRecord.txt", ios::app | ios::out);
    file << " " << name << " " << index_no  << " " << registration_no << " " << course << " " << email_id << " " << contact_no << " " << address << "\n";
    file.close();  
}


void student::display()
{
    system("cls");  

    fstream file;  
    int total = 1;  

    
    cout << "\t\t\t------------------------------------"  << endl;
    cout << "\t\t\t| STUDENT MANAGEMENT SYSTEM BY 4840 |" << endl;
    cout << "\t\t\t|       Student Record Table        |" << endl;
    cout << "\t\t\t------------------------------------"  << endl;
    
    
    file.open("studentRecord.txt", ios::in);
    if (!file)  
    {
        cout << "\n\t\t\tNo Data is Present... ";
        file.close();
    }
    else
    {
        
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

            
            file >> name >> index_no >> registration_no >> course >> email_id >> contact_no >> address;
        }

        if (total == 1)  
        {
            cout << "\n\t\t\tNo Data is Present..." << endl;
        }
    }

    file.close();  
}


void student::modify()
{
    system("cls");  

    fstream file, file1;  

    string indexno;  
    int found = 0;  

    
    cout << "\t\t\t------------------------------------"  << endl;
    cout << "\t\t\t| STUDENT MANAGEMENT SYSTEM BY 4840 |" << endl;
    cout << "\t\t\t|       Student Modify Details      |" << endl;
    cout << "\t\t\t------------------------------------"  << endl;


    
    file.open("studentRecord.txt", ios::in);
    if (!file)  
    {
        cout << "\n\t\t\tNo Data is Present..";
        file.close();
    }
    else
    {
        
        cout << "\nEnter Index No. of Student which you want to Modify: ";
        cin >> indexno;

        
        file1.open("record.txt", ios::app | ios::out);

        
        file >> name >> index_no >> registration_no >> course >> email_id >> contact_no >> address;
        while (!file.eof())
        {
            if (indexno != index_no)
            {
                
                file1 << " " << name << " " << index_no << " " << registration_no << " " << course << " " << email_id << " " << contact_no << " " << address << "\n";
            }
            else
            {
                
                cout << "\n\t\t\tEnter Name: ";
                cin >> name;
                cout << "\t\t\tEnter Index No.: ";
                cin >> index_no;
                cout << "\t\t\tEnter Registration No. : ";
                cin >> registration_no;
                cout << "\t\t\tEnter Course: ";
                cin >> course;
                cout << "\t\t\tEnter Email Id: ";
                cin >> email_id;           
                cout << "\t\t\tEnter Contact No: ";
                cin >> contact_no;
                cout << "\t\t\tEnter Address: ";
                cin >> address;

                
                file1 << " " << name << " " << index_no << " " << registration_no << " " << course << " " << email_id << " " << contact_no << " " << address << "\n";
                found++;
            }

            
            file >> name >> index_no >> registration_no >> course >> email_id >> contact_no >> address;
        }

        if (found == 0)  
        {
            cout << "\n\n\t\t\t Student Index No. Not Found....";
        }

        file1.close();  
        file.close();   

    
        remove("studentRecord.txt");
        rename("record.txt", "studentRecord.txt");
    }
}


void student::search()
{
    system("cls");  

    fstream file;  

    int found = 0;  

    
    cout << "\t\t\t------------------------------------"  << endl;
    cout << "\t\t\t| STUDENT MANAGEMENT SYSTEM BY 4840 |" << endl;
    cout << "\t\t\t|       Student Search Table        |" << endl;
    cout << "\t\t\t------------------------------------"  << endl;

    
    file.open("studentRecord.txt", ios::in);
    if (!file)  
    {
        cout << "\n\t\t\tNo Data is Present... " << endl;
    }
    else
    {
        string indexno;  

        
        cout << "\nEnter index No. of Student which you want to search: ";
        cin >> indexno;

        
        file >> name >> index_no >> registration_no >> course >> email_id >> contact_no >> address;
        while (!file.eof())
        {
            if (indexno == index_no)
            {
                
                cout << "\n\n\t\t\tName: " << name << "\n";
                cout << "\t\t\tIndex No.: " << index_no << "\n";
                cout << "\t\t\tReg. No.: " << registration_no << "\n";
                cout << "\t\t\tCourse: " << course << "\n";
                cout << "\t\t\tEmail Id: " << email_id << "\n";
                cout << "\t\t\tContact No.: " << contact_no << "\n";
                cout << "\t\t\tAddress: " << address << "\n";
                found++;
            }

            
            file >> name >> index_no >> registration_no >> course >> email_id >> contact_no >> address;
        }

        if (found == 0)  
        {
            cout << "\n\t\t\t Student index No. Not Found....";
        }

        file.close();  
    }
}


void student::deleted()
{
    system("cls");  

    fstream file, file1;  

    int found = 0;  
    string index;    

    

    cout << "\t\t\t------------------------------------"  << endl;
    cout << "\t\t\t| STUDENT MANAGEMENT SYSTEM BY 4840 |" << endl;
    cout << "\t\t\t|      Delete Student Details       |" << endl;
    cout << "\t\t\t------------------------------------"  << endl;

    
    file.open("studentRecord.txt", ios::in);
    if (!file)  
    {
        cout << "\n\t\t\tNo Data is Present..";
        file.close();
    }
    else
    {
        
        cout << "\nEnter Index No. of Student which you want Delete Data: ";
        cin >> index;

        
        file1.open("record.txt", ios::app | ios::out);

        
        file >> name >> index_no >> registration_no >> course >> email_id >> contact_no >> address;
        while (!file.eof())
        {
            if (index != index_no)
            {
                
                file1 << " " << name << " " << index_no << " " << registration_no << " " << course << " " << email_id << " " << contact_no << " " << address << "\n";
            }
            else
            {
                found++;
                cout << "\n\t\t\tSuccessfully Delete Data";
            }

            
            file >> name >> index_no >> registration_no >> course >> email_id >> contact_no >> address;
        }

        if (found == 0)  
        {
            cout << "\n\t\t\t Student index No. Not Found....";
        }

        file1.close();  
        file.close();   

        
        remove("studentRecord.txt");
        rename("record.txt", "studentRecord.txt");
    }
}

int main()
{
    student s; 
    s.menu(); 
    return 0;       
}
