/*
******   Made by AMIT KUMAR YADAV  ******

Name      - Amit Kumar Yadav
Email     - amitkryadav7777@gmail.com
Github    - https://github.com/amitkryadav7777
LinkedIn  - https://linkedin.com/in/amitkryadav7777
Twitter/X - https://twitter.com/amitkryadav7777
Instagram - https://instagram.com/amitkryadav7777
Date      - 21 September 2024
*/

#include <iostream>
#include <conio.h>
#include <fstream>
#include <istream>
#include <sstream>
#include <ctime>
#include <time.h>
#include <string>
#include <vector>
#include <thread>
#include <graphics.h>
using namespace std;

string category; // This global varialbe identify admin and normal user
int invalid = 0;
int enroll = 1;
void title() // This will show the title on the top
{
    cout << "\t\t-----------------------------------------------\n";
    cout << "\t\t\t:: Library Management System ::" << endl;
    cout << "\t\t-----------------------------------------------\n\n";
    return;
}
// This fun() will called after successful login...
void home();
// To add new student...
void addStudent();
// To withdraw the amount in the account...
void addBook();
// Login for admin...
void adminLogin();
// Login for user...
void userLogin();

void addStudent() // To add new student
{
    system("cls");
    title();
    string name, mobile, email, address;
    fstream fout;

    // opens existing csv files or creates new files to store student's data
    fout.open("students.csv", ios::out | ios::app);

    // out.open("issuedBooks.csv", ios::out | ios::app);
    cout << "\t\tAdding new student -- \n";
    cout << "\t\tStudent Name  : "; // Now taking input of student's details
    cin.ignore();
    getline(cin, name);
    cout << "\t\tMobile        : ";
    cin >> mobile;
    cout << "\t\tEmail         : ";
    cin >> email;
    cout << "\t\tAddress       : ";
    cin.ignore();
    getline(cin, address);

    fstream file;
    // opening students.csv file to store the detail.
    file.open("students.csv", ios::out | ios::app | ios::in);
    while (file.eof() == 0)
    {
        char delimiter = ',';
        std::string line;
        std::string item;
        std::vector<std::string> row;
        while (std::getline(file, line))
        {
            row.clear();
            std::stringstream string_stream(line);
            while (std::getline(string_stream, item, delimiter))
            {
                row.push_back(item);
            }
            enroll = stoi(row[0]) + 1;
        }
    }

    // Inserting the data into students.csv file
    fout << enroll << ","
         << name << ","
         << mobile << ","
         << email << ","
         << address
         << "\n";

    cout << "\t\tStudent successfully added." << endl;
    cout << "\n\t\tEnrollment Number is : " << enroll << endl;
    fout.close();
    file.close();
    delay(1000);
    home();
    return;
}

void updateStudent()    // This function is use to update the student's data
{
    system("cls");
    title();
    cout << "\n\t\tEnter student's Enrollment ID : ";
    string eID;
    cin >> eID;

    bool isPresent = false;
    fstream file;
    // opening an existing csv file to fetch student's details.
    file.open("students.csv", ios::out | ios::app | ios::in);
    while (file.eof() == 0)
    {
        char delimiter = ',';
        std::string line;
        std::string item;
        std::vector<std::string> row;
        while (std::getline(file, line))
        {
            row.clear();
            std::stringstream string_stream(line);
            while (std::getline(string_stream, item, delimiter))
            {
                row.push_back(item);
            }
            if (row[0] == eID) // Matching data of entered enrollment no
            {
                cout << "\n\t\tStudet Details -\n"  //Printing data
                     << "\n\t\tEnrollment ID  : " << row[0] << "\n"
                     << "\n\t\t1. Name        : " << row[1]
                     << "\n\t\t2. Mobile      : " << row[2]
                     << "\n\t\t3. Email       : " << row[3]
                     << "\n\t\t4. Address     : " << row[4] << endl;
            }
        }
    }
    file.close();

    fstream fout;
    // opens an existing csv file to fetch and store account holders' data.
    fout.open("students.csv", ios::in | ios::out);
    if (fout.fail())
    {
        cout << "\n\t\tError opening the file" << endl;
        delay(1000);
        home();
        return;
    }
    bool done = false;  // to check that updation is complete or not, it wuill store the status
    vector<string> lines;
    string line;
    char delimiter = ',';
    std::string item;
    std::vector<std::string> row;
    while (std::getline(fout, line))
    {
        row.clear();
        std::stringstream string_stream(line);
        while (std::getline(string_stream, item, delimiter))
        {
            row.push_back(item);
        }
        if (row[0] == eID) // Checking accNum and taking new data to update..
        {
            isPresent = true;
            cout << "\n\t\tChoose a option to update : ";
            int option;
            cin >> option;
            line = "";
            string newData;
            switch (option)
            {
            case 1:
                cout << "\n\t\tEnter New Name : ";
                cin.ignore();
                getline(cin, newData);
                row[1] = newData;
                break;
            case 2:
                cout << "\n\t\tEnter New Mobile : ";
                cin >> newData;
                row[2] = newData;
                break;
            case 3:
                cout << "\n\t\tEnter New Email : ";
                cin >> newData;
                row[3] = newData;
                break;
            case 4:
                cout << "\n\t\tEnter New Address : ";
                cin.ignore();
                getline(cin, newData);
                row[4] = newData;
                break;
            default:
                done = false;
                cout << "\n\t\tInvalid option";
                break;
            }
            for (int i = 0; i < row.size(); i++)
            {
                line.append(row[i]);
                if (i != row.size() - 1)
                {
                    line.push_back(',');
                }
            }
            lines.push_back(line);
        }
        else
        {
            lines.push_back(line);
        }
    }
    fout.close();
    fstream fin;
    fin.open("students.csv", ios::out); // Now inserting student's new data in the database
    for (string l : lines)
    {
        fin << l << "\n";
    }
    fin.close();
    if (!isPresent)
    {
        cout << "\n\t\tEnrollment ID doesn't exist!";
    }
    if (done)
    {
        cout << "\n\t\tAccount successfully updated!";
    }
    delay(1000);
    home();
    return;
}

void studentList()  // This function is to show the list of the all students'
{
    system("cls");
    title();

    cout << "\n\t\tEnroll ID\tName\tMobile\t\tEmail\t\t\tAddress\n\n";

    fstream file;
    // opening students.csv file to fetch the detail of all the student.
    file.open("students.csv", ios::out | ios::app | ios::in);
    while (file.eof() == 0)
    {
        char delimiter = ',';
        std::string line;
        std::string item;
        std::vector<std::string> row;
        while (std::getline(file, line))
        {
            row.clear();
            std::stringstream string_stream(line);
            while (std::getline(string_stream, item, delimiter))
            {
                row.push_back(item);
            }
            cout << "\t\t" << row[0] << "\t\t"  // Printing data of the students'
                 << row[1] << "\t"
                 << row[2] << "\t"
                 << row[3] << " \t"
                 << row[4] << "\n";
        }
    }
    file.close();
    cout << "\n\t\tEnter any number to exit... ";
    string inp;
    cin >> inp;
    home();
    return;
}

void addBook()  // To add new book
{
    system("cls");
    title();
    string isbn, name, author, publications, quantity;
    fstream fout;
    fstream fin;

    // opens existing csv files or creates new files to store book details'.
    fout.open("books.csv", ios::out | ios::app);
    fin.open("books.csv", ios::in);

    cout << "\t\tAdding new book -- \n"; // Now taking input of book's details
    cout << "\t\tISBN Number       : ";
    cin >> isbn;
    cout << "\t\tBook Name         : ";
    cin.ignore();
    getline(cin, name);

    cout << "\t\tAuthor            : ";
    cin >> author;
    cout << "\t\tPublications      : ";
    cin.ignore();
    getline(cin, publications);

    cout << "\t\tQuantity         : ";
    cin >> quantity;

    fstream file;
    // opening books.csv file to store book detail.
    file.open("books.csv", ios::out | ios::app | ios::in);
    while (file.eof() == 0)
    {
        char delimiter = ',';
        std::string line;
        std::string item;
        std::vector<std::string> row;
        while (std::getline(file, line))
        {
            row.clear();
            std::stringstream string_stream(line);
            while (std::getline(string_stream, item, delimiter))
            {
                row.push_back(item);
            }
            if (isbn == row[0]) // Checking that book is already exists or not.
            {
                cout << "\n\t\tThis book already exists.\n";
                return;
            }
        }
    }

    // Inserting the book's into books.csv file
    fout << isbn << ","
         << name << ","
         << author << ","
         << publications << ","
         << quantity
         << "\n";

    cout << "\t\tBook successfully added." << endl;
    fout.close();
    file.close();
    fin.close();
    delay(1000);
    home();
    return;
}

void updateBook()   // To update book's detail
{
    system("cls");
    title();
    cout << "\n\t\tEnter book's ISBN ID : ";
    string isbnID;
    cin >> isbnID;

    bool isPresent = false;
    fstream file;
    // opening an existing csv file to fetch book's details.
    file.open("books.csv", ios::out | ios::app | ios::in);
    while (file.eof() == 0)
    {
        char delimiter = ',';
        std::string line;
        std::string item;
        std::vector<std::string> row;
        while (std::getline(file, line))
        {
            row.clear();
            std::stringstream string_stream(line);
            while (std::getline(string_stream, item, delimiter))
            {
                row.push_back(item);
            }
            if (row[0] == isbnID) // Now printing data of book
            {
                cout << "\n\t\tBooks Details -\n"
                     << "\n\t\tISBN ID         : " << row[0] << "\n"
                     << "\n\t\t1. Name         : " << row[1]
                     << "\n\t\t2. Author       : " << row[2]
                     << "\n\t\t3. Publications : " << row[3]
                     << "\n\t\t4. Quantity     : " << row[4] << endl;
            }
        }
    }
    file.close();

    fstream fout;
    // opens an existing csv file to fetch and store books' data.
    fout.open("books.csv", ios::in | ios::out);
    if (fout.fail())
    {
        cout << "\n\t\tError opening the file" << endl;
        delay(1000);
        home();
        return;
    }
    bool done = false;
    vector<string> lines;
    string line;
    char delimiter = ',';
    std::string item;
    std::vector<std::string> row;
    while (std::getline(fout, line))
    {
        row.clear();
        std::stringstream string_stream(line);
        while (std::getline(string_stream, item, delimiter))
        {
            row.push_back(item);
        }
        if (row[0] == isbnID) // Checking book's ISBN to fetch the data
        {
            isPresent = true;
            cout << "\n\t\tChoose a option to update : ";
            int option;
            cin >> option;
            line = "";
            string newData;
            switch (option)
            {
            case 1:
                cout << "\n\t\tEnter New Name : ";
                cin.ignore();
                getline(cin, newData);
                row[1] = newData;
                break;
            case 2:
                cout << "\n\t\tEnter New Author : ";
                cin.ignore();
                getline(cin, newData);
                row[2] = newData;
                break;
            case 3:
                cout << "\n\t\tEnter New Publications : ";
                cin.ignore();
                getline(cin, newData);
                row[3] = newData;
                break;
            case 4:
                cout << "\n\t\tEnter New Quantity : ";
                cin >> newData;
                row[4] = newData;
                break;
            default:
                done = false;
                cout << "\n\t\tInvalid option";
                break;
            }
            for (int i = 0; i < row.size(); i++)
            {
                line.append(row[i]);
                if (i != row.size() - 1)
                {
                    line.push_back(',');
                }
            }
            lines.push_back(line);
        }
        else
        {
            lines.push_back(line);
        }
    }
    fout.close();
    fstream fin;
    fin.open("books.csv", ios::out);
    for (string l : lines)
    {
        fin << l << "\n";
    }
    fin.close();
    if (!isPresent)
    {
        cout << "\n\t\tWrong ISBN ID!";
    }
    if (done)
    {
        cout << "\n\t\tBook successfully updated!";
    }
    delay(1000);
    home();
    return;
}

void bookList() // To show the list of the book
{
    system("cls");
    title();

    cout << "\n\t\tISBN No\tName\tAuthor\t\tPublications\t\tQuantity\n\n";

    fstream file;
    // opening books.csv file to show all the book
    file.open("books.csv", ios::out | ios::app | ios::in);
    while (file.eof() == 0)
    {
        char delimiter = ',';
        std::string line;
        std::string item;
        std::vector<std::string> row;
        while (std::getline(file, line))
        {
            row.clear();
            std::stringstream string_stream(line);
            while (std::getline(string_stream, item, delimiter))
            {
                row.push_back(item);
            }
            cout << "\t\t" << row[0] << "\t"    // Printing the data
                 << row[1] << "\t"
                 << row[2] << "\t\t"
                 << row[3] << "\t\t"
                 << row[4] << "\n";
        }
    }
    file.close();

    cout << "\n\t\tEnter any number to exit... ";
    string inp;
    cin >> inp;
    home();
    return;
}

void issueBook()    // To issue a new book
{
    system("cls");
    title();

    string eID;
    cout << "\n\t\tEnter Student's Enrollment No : ";
    cin >> eID;
    string isbnID;
    cout << "\n\t\tEnter Book's ISBN No          : ";
    cin >> isbnID;

    string bookName, name, issueDate, returnDate, fine;

    fstream file;
    // Opening students.csv file to check students exists or not in the library record
    file.open("students.csv", ios::in);

    while (file.eof() == 0)
    {
        bool present = false;
        char delimiter = ',';
        std::string line;
        std::string item;
        std::vector<std::string> row;
        while (std::getline(file, line))
        {
            row.clear();
            std::stringstream string_stream(line);
            while (std::getline(string_stream, item, delimiter))
            {
                row.push_back(item);
            }
            if (eID == row[0])
            {
                present = true;
                name = row[1];
            }
        }
        if (!present)
        {
            cout << "\n\t\tStudent doesn't exist.";
            delay(1000);
            home();
            return;
        }
    }
    file.close();

    fstream fin;
    // Now opening books.csv file to check book exist or not
    fin.open("books.csv", ios::in);

    while (fin.eof() == 0)
    {
        bool present = false;
        char delimiter = ',';
        std::string line;
        std::string item;
        std::vector<std::string> row;
        while (std::getline(fin, line))
        {
            row.clear();
            std::stringstream string_stream(line);
            while (std::getline(string_stream, item, delimiter))
            {
                row.push_back(item);
            }
            if (isbnID == row[0])
            {
                present = true;
                bookName = row[1];
            }
        }
        if (!present)
        {
            cout << "\n\t\tBook doesn't exist.";
            delay(1000);
            home();
            return;
        }
    }
    fin.close();

    fstream fout;
    // Now opening issuedBooks.csv file to store the issued details
    fout.open("issuedBooks.csv", ios::out | ios::app);

    time_t t;
    struct tm *tm;
    char Date[30];
    std::time(&t);
    tm = localtime(&t);
    strftime(Date, sizeof Date, "%x", tm);
    bool isPresent = false;
    issueDate = Date;
    returnDate = "0";
    fine = "0";

    fstream fUpdate;
    // Opening books.csv file to update the quantity of the book
    fUpdate.open("books.csv", ios::in);

    vector<string> lines1;
    string line1;
    char delimiter1 = ',';
    std::string item1;
    std::vector<std::string> row1;

    while (std::getline(fUpdate, line1))
    {
        row1.clear();
        std::stringstream string_stream(line1);
        while (std::getline(string_stream, item1, delimiter1))
        {
            row1.push_back(item1);
        }
        if (row1[0] == isbnID)  // Fetching book quantity
        {
            int quant = stoi(row1[4]) - 1;
            if (quant < 0)
            {
                isPresent = false;
            }
            else
            {
                isPresent = true;
                row1[4] = to_string(quant);
                line1 = "";
                for (int i = 0; i < row1.size(); i++)
                {
                    line1.append(row1[i]);
                    if (i != row1.size() - 1)
                    {
                        line1.push_back(',');
                    }
                }
            }
        }
        lines1.push_back(line1);
    }
    fUpdate.close();
    fstream fDone;
    fDone.open("books.csv", ios::out | ios::in);
    for (string l1 : lines1)
    {
        fDone << l1 << "\n";
    }
    fDone.close();

    fout << isbnID << ","   // Now storing data
         << bookName << ","
         << eID << ","
         << name << ","
         << issueDate << ","
         << returnDate << ","
         << fine << "\n";
    fout.close();
    if (isPresent){
        cout << "\n\t\tBook issued succesfully."
             << "\n\n\t\tPlease retur the book within 15 days otherwise"
             << "\n\t\tafter 15 days, fine of Rs 1 per day will be levied";
        cout << "\n\n\t\tEnter any number to exit... ";
        string exit;
        cin >> exit;
    }
    else
        cout << "\n\t\tBook is unavailable";
    delay(1000);
    home();
    return;
}

void updateFine() // To update fine it will run, when we run the application
{
    system("cls");
    title();
    fstream fout;
    fstream flogin;
    // opening issuedBooks.csv to update the fine according to the real time
    fout.open("issuedBooks.csv", ios::in | ios::out);

    if (fout.fail() || flogin.fail())
    {
        cout << "\n\t\tError opening the file" << endl;
        delay(1000);
        home();
        return;
    }

    vector<string> lines;
    string line;
    char delimiter = ',';
    std::string item;
    std::vector<std::string> row;
    string prev, curr;
    long diff;
    while (std::getline(fout, line))
    {
        row.clear();
        std::stringstream string_stream(line);

        while (std::getline(string_stream, item, delimiter))
        {
            row.push_back(item);
        }

        line = "";
        prev = row[4];
        time_t t;
        struct tm *tm;
        char Date[30];
        std::time(&t);
        tm = localtime(&t);
        strftime(Date, sizeof Date, "%d-%m-%Y", tm);
        curr = Date;


        // Finding difference between dates to update the fine
        stringstream ss(curr + "-" + prev);
        int year, month, day;
        char hyphen;

        // Parse the first date into seconds
        ss >> day >> hyphen >> month >> hyphen >> year;

        struct tm starttm = {0, 0, 0, day,
                             month - 1, year - 1900};
        time_t start = mktime(&starttm);

        // Parse the second date into seconds
        ss >> hyphen >> day >> hyphen >> month >> hyphen >> year;
        struct tm endtm = {0, 0, 0, day,
                           month - 1, year - 1900};
        time_t end = mktime(&endtm);
        diff = abs(end - start) / 86400;

        if (diff > 15 && row[5] == "0")
        {
            row[6] = to_string(diff - 15);
        }

        for (int i = 0; i < row.size(); i++)
        {
            line.append(row[i]);
            if (i != row.size() - 1)
            {
                line.push_back(',');
            }
        }

        lines.push_back(line);
    }
    fout.close();

    fstream fin;
    fin.open("issuedBooks.csv", ios::out);
    for (string l : lines) 
    {
        fin << l << "\n";
    }
    fin.close();
    return;
}

void issuedBookToStudent()  // To check issued book to a student according studen's enrollment no
{
    system("cls");
    title();

    cout << "\n\t\tEnter student's enrollment number to see issued book : ";
    string eID;
    cin >> eID;

    cout << "\n\t\tISBN No\tBook Name\tStd ID\tName\tIssued Date\tReturned Date\tFine\n\n";

    bool isPresent = false;
    fstream file;
    // opening issuedBooks.csv file to fetch the data
    file.open("issuedBooks.csv", ios::out | ios::app | ios::in);
    while (file.eof() == 0)
    {
        char delimiter = ',';
        std::string line;
        std::string item;
        std::vector<std::string> row;
        while (std::getline(file, line))
        {
            row.clear();
            std::stringstream string_stream(line);
            while (std::getline(string_stream, item, delimiter))
            {
                row.push_back(item);
            }
            if (row[2] == eID)
            {
                isPresent = true;
                cout << "\t\t" << row[0] << "\t" // Now printing the fetched data of the student
                     << row[1] << "\t\t"
                     << row[2] << "\t"
                     << row[3] << "\t"
                     << row[4] << "\t"
                     << row[5] << "\t"
                     << row[6] << "\n";
            }
        }
    }
    file.close();
    if (!isPresent)
    {
        cout << "\n\t\tEnrollment Number doesn't exist...  ";
    }
    cout << "\n\n\t\tEnter any number to exit... ";
    string inp;
    cin >> inp;
    home();
    return;
}

void issueBookList()    // To see list of the issued book
{
    system("cls");
    title();

    cout << "\n\t\tISBN No\tBook Name\tStd ID\tName\tIssued Date\tReturned Date\tFine\n\n";

    fstream file;
    // opening issuedBooks.csv file to fetch the all data of the isssued books
    file.open("issuedBooks.csv", ios::out | ios::app | ios::in);
    while (file.eof() == 0)
    {
        char delimiter = ',';
        std::string line;
        std::string item;
        std::vector<std::string> row;
        while (std::getline(file, line))
        {
            row.clear();
            std::stringstream string_stream(line);
            while (std::getline(string_stream, item, delimiter))
            {
                row.push_back(item);
            }
            cout << "\t\t" << row[0] << "\t"    // Printing the all data
                 << row[1] << "\t\t"
                 << row[2] << "\t"
                 << row[3] << "\t"
                 << row[4] << "\t"
                 << row[5] << "\t"
                 << row[6] << "\n";
        }
    }
    file.close();

    cout << "\n\t\tEnter any number to exit... ";
    string inp;
    cin >> inp;
    home();
    return;
}

void returnBook()   // To return a book
{
    system("cls");
    title();

    string eID;
    cout << "\n\t\tEnter Student's Enrollment No : ";
    cin >> eID;
    string isbnID;
    cout << "\n\t\tEnter Book's ISBN No          : ";
    cin >> isbnID;

    fstream fout;
    // opening issuedBooks.csv file to fetch account holders' details and to delete it.
    fout.open("issuedBooks.csv", ios::in | ios::out);

    if (fout.fail())
    {
        cout << "\n\t\tError opening the file" << endl;
        delay(1000);
        home();
        return;
    }

    string returnDate;
    time_t t;
    struct tm *tm;
    char Date[30];
    std::time(&t);
    tm = localtime(&t);
    strftime(Date, sizeof Date, "%x", tm);

    returnDate = Date;
    bool isPresent = false;
    vector<string> lines;
    string line;
    char delimiter = ',';
    std::string item;
    std::vector<std::string> row;

    while (std::getline(fout, line))
    {
        row.clear();
        std::stringstream string_stream(line);

        while (std::getline(string_stream, item, delimiter))
        {
            row.push_back(item);
        }

        if ((row[0] == isbnID) && (row[2] == eID))
        {
            isPresent = true;
            row[5] = returnDate;
            line = "";
            for (int i = 0; i < row.size(); i++)
            {
                line.append(row[i]);
                if (i != row.size() - 1)
                {
                    line.push_back(',');
                }
            }

            cout << "\n\t\tTotal fine is : " << row[6] << endl;

            fstream fUpdate;
            fUpdate.open("books.csv", ios::out | ios::in);
            if (fUpdate.fail())
            {
                cout << "\n\t\tError opening the file" << endl;
                delay(1000);
                home();
                return;
            }
            vector<string> lines1;
            string line1;
            char delimiter1 = ',';
            std::string item1;
            std::vector<std::string> row1;
     
            while (std::getline(fUpdate, line1))
            {
                row1.clear();
                std::stringstream string_stream(line1);
                while (std::getline(string_stream, item1, delimiter1))
                {
                    row1.push_back(item1);
                }
                if (row1[0] == isbnID)
                {
                    int quant = stoi(row1[4]) + 1;
                    row1[4] = to_string(quant);
                    line1 = "";
                    for (int i = 0; i < row1.size(); i++)
                    {
                        line1.append(row1[i]);
                        if (i != row1.size() - 1)
                        {
                            line1.push_back(',');
                        }
                    }
                }
                lines1.push_back(line1);
            }
            fUpdate.close();
            fstream fDone;
            fDone.open("books.csv", ios::out | ios::in);
            for (string l1 : lines1)
            {
                fDone << l1 << "\n";
            }
            fDone.close();
        }
        lines.push_back(line);
    }
    fout.close();

    fstream fin;
    fin.open("issuedBooks.csv", ios::out);
    for (string l : lines)
    {
        fin << l << "\n";
    }
    fin.close();
    if (isPresent)
    {
        cout << "\n\t\tBook returned.";
    }
    else
    {
        cout << "\n\t\tInvalid Details";
    }
    delay(1000);
    home();
    return;
}

void home() // This will be executed after login
{
    int option = 0;
    system("cls");
    title();

    cout << "\t\t1. Add New Student\n";
    cout << "\t\t2. Update Student Details\n";
    cout << "\t\t3. Students List\n";
    cout << "\t\t4. Add New Book\n";
    cout << "\t\t5. Update Book Details\n";
    cout << "\t\t6. Books List\n";
    cout << "\t\t7. Issue Book\n";
    cout << "\t\t8. Return Book\n";
    cout << "\t\t9. Issued Books to a student\n";
    cout << "\t\t10. See Issued Book List\n";
    cout << "\t\t11. Logout & Exit\n";
    cout << "\n\t\tEnter your choice : ";
    cin >> option;
    string optionData;
    switch (option)
    {
    case 1:
        addStudent();
        break;
    case 2:
        updateStudent();
        break;
    case 3:
        studentList();
        break;
    case 4:
        addBook();
        break;
    case 5:
        updateBook();
        break;
    case 6:
        bookList();
        break;
    case 7:
        issueBook();
        break;
    case 8:
        returnBook();
        break;
    case 9:
        issuedBookToStudent();
        break;
    case 10:
        issueBookList();
        break;
    case 11:
        cout << "\n\t\tThank You...";
        return;
    }
}

int main()
{
    system("cls");
    title();
    // This is login credentials you can change it according you
    string username1 = "admin";
    string password1 = "1234";

    string username2 = "";
    string password2 = "0";
    int session = 0;

    updateFine();

    while(!session){
        system("cls");
        title();
        cout << "\n\t\tEnter Username : " ;
        cin >> username2;
        cout << "\n\t\tEnter Password : " ;
        cin >> password2;

        if(username1 == username2 && password1 == password2){// Checking login credentials
            session = 1;
            break;
        }
        cout << "\n\t\tInvalid Credentials." ;
        delay(1000);
    }
    home(); // Calling home() which is important

    return 0;
}