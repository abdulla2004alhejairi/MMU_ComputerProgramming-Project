#include <iostream>
#include <cstring>   // strcpy compare string
#include <windows.h> // functions in the Windows API
#include <fstream>   // create files, write information to files, and read information from files.
#include <conio.h>   // getch
#include <iomanip>   // setfill, setw
#include <string>
#include <cstdlib>
#include <limits>

using namespace std;

class covid_vaccination
{
protected:
    string name;
    string password;
    string contact;
    string user_name, user_IC;
    string IC;

    // vac center
    string VacCenter = "Vaccine Center";

    // vaccination data
    struct vac_data
    {
        char uIC[13];
        char uname[100];
        char dose;
        char manufacturer[16];
        char udate[11];
    };
    int counter;

public:
    void vac_center();

    void title();
    void retypeOpt(); // retype option

    void menu();

    // admin
    void admin();
    void admin_password();

    // user
    void user();
    void user_password();
    void valid(string str); // check IC exist

    // admin func
    void add_vaccine_stock();
    void display_vaccine_stock();
    void vaccination_record();

    // both func
    void apply_vaccine();
    void view_vaccination();
    void delete_vaccination();
};

void covid_vaccination::vac_center()
{
    fstream file;

    file.open("vac_center.txt", ios::in);
    if (file.fail())
    {
        file.close();
        file.open("vac_center.txt", ios::out | ios::app);
        file << 50000;
    }
    file.close();
}

void covid_vaccination::title()
{
    cout << "\n\t\t          COVID VACCINATION SYSTEM       ";
    cout << "\n\t\t-----------------------------------------";
}

void covid_vaccination::retypeOpt()
{
    cout << "\n\n\t\tPlease select from the options given above.";
    cout << "\n\n\t\tPress Any Key To Continue ";
    getch();
    cin.clear();
    fflush(stdin); // clear cin buffer
    cout.flush();  // clear cout buffer
}

void covid_vaccination::menu()
{
    system("cls"); // clear screen
    int option;
    title();
    // main menu
    cout << "\n\n\t\t   Main Menu  ";
    cout << "\n\n\t\t  1. Admin";
    cout << "\n\t\t  2. User";
    cout << "\n\t\t  3. Exit";
    cout << "\n\n\t\tEnter Option: ";
    cin >> option;
    // call function by chosen num
    switch (option)
    {
    case 1:
        admin();
        break;
    case 2:
        user();
        break;
    case 3:
        system("cls");
        cout << "\n\n\t\t\t COVID VACCINATION SYSTEM";
        Sleep(10);
        exit(0);
    default:
        retypeOpt();
        menu();
    }
}

// admin
void covid_vaccination::admin()
{
    admin_password();
A:
    system("cls");
    int a_option;
    title();
    cout << "\n\n\t\t   Admin Menu  ";
    cout << "\n\n\t\t 1. Add Vaccine Stock";
    cout << "\n\t\t 2. Show Vaccine Stock";
    cout << "\n\t\t 3. Search Vaccination Record";
    cout << "\n\t\t 4. Show All Vaccination Record";
    cout << "\n\t\t 5. Add Vaccination Record";
    cout << "\n\t\t 6. Delete Vaccination Record";
    cout << "\n\t\t 7. Sign Out";
    cout << "\n\n\t\tEnter Option: ";
    cin >> a_option;
    switch (a_option)
    {
    case 1:
        add_vaccine_stock();
        goto A;
        break;
    case 2:
        display_vaccine_stock();
        goto A;
        break;
    case 3:
        view_vaccination();
        goto A;
        break;
    case 4:
        vaccination_record();
        goto A;
        break;
    case 5:
        apply_vaccine();
        goto A;
        break;
    case 6:
        delete_vaccination();
        goto A;
        break;
    case 7:
        menu();
    default:
        retypeOpt();
        goto A;
        break;
    }
}

void covid_vaccination::admin_password()
{
    system("cls");
    char a_name[20];
    char a_password[20];
    title();
    cout << "\n\n\t\t   Sign In Admin  ";
    cout << "\n\n\t\tEnter Your Name: ";
    cin >> a_name;
    cout << "\n\t\tEnter Your Password: ";
    cin >> a_password;
    if ((strcmp(a_name, "admin") == 0) && (strcmp(a_password, "admin") == 0))
    {
        cout << "\n\n\t\tWelcome Admin.\n\n";
        getch();
        system("cls");
    }
    else
    {
        cout << "\n\n\t\tWrong Name Or Password.\n\n";
        getch();
        system("cls");
        menu();
    }
}

// user
void covid_vaccination::user()
{
    user_password();
B:
    system("cls");
    int u_option;
    title();
    cout << "\n\n\t\t   User Menu  ";
    cout << "\n\t\t   Welcome " << user_name;
    cout << "\n\t\t 1. Apply For Vaccine";
    cout << "\n\t\t 2. View Vaccination Record";
    cout << "\n\t\t 3. Delete Vaccination Record";
    cout << "\n\t\t 4. Sign Out";
    cout << "\n\n\t\tEnter Option: ";
    cin >> u_option;
    switch (u_option)
    {
    case 1:
        apply_vaccine();
        goto B;
    case 2:
        view_vaccination();
        goto B;
    case 3:
        delete_vaccination();
        goto B;
    case 4:
        menu();
    default:
        retypeOpt();
        goto B;
    }
}

void covid_vaccination::user_password()
{
    system("cls");
    int u_option;
    string fname, usern, userp;
    ofstream fileo;
    ifstream filei;
    title();
    cout << "\n\n\t\t   User Sub-Menu  ";
    cout << "\n\n\t\t 1. User Registration";
    cout << "\n\t\t 2. Sign In";
    cout << "\n\t\t 3. Change Password";
    cout << "\n\t\t 4. Delete Account";
    cout << "\n\t\t 5. Back";
    cout << "\n\t\tEnter Option: ";
    cin >> u_option;
    if (u_option == 1)
    {
        system("cls");
        title();
        cout << "\n\n\t\t   User Registration  ";
    A:
        cout << "\n\n\t\tEnter IC No.: ";
        cin >> IC;
        if (IC.length() != 12)
        {
            cout << "\n\t\tInvalid IC Number";
            char choice;
            cout << "\n\n\t\tEnter Y To Retype IC No. : ";
            cin >> choice;
            if (choice == 'y' || choice == 'Y')
            {
                goto A;
            }
            else
            {
                cin.clear();
                fflush(stdin); // clear input buffer
                user();
            }
        }
        counter = 0;
        valid(IC);
        if (counter >= 3)
        {
            cout << "\n\n\t\tPress Any Key To Continue ";
            getch();
            user_password();
        }
        cout << "\n\t\tEnter Your Name: ";
        cin.ignore();
        getline(cin, name);
        cout << "\n\t\tEnter Your Contact number: ";
        cin >> contact;
        cout << "\n\t\tEnter Your password: ";
        cin >> password;
        fname = IC + ".txt";
        fileo.open(fname.c_str());
        fileo << name << endl
              << password << endl
              << contact << endl;
        cout << "\n\t\tYou are successfully registered:)";
        cout << "\n\n\t\tPress Any Key To Continue..";
        Sleep(500);
        getch();
        fileo.close();
        user();
    }
    else if (u_option == 2)
    {
        system("cls");
        string u_IC, u_pass;
        title();
        cout << "\n\n\t\t   Sign In User  ";
    B:
        cout << "\n\n\t\tEnter Your IC No.: ";
        cin >> u_IC;
        if (u_IC.length() != 12)
        {
            cout << "\n\t\tInvalid IC Number";
            char choice;
            cout << "\n\n\t\tEnter Y To Retype IC No. : ";
            cin >> choice;
            if (choice == 'y' || choice == 'Y')
            {
                goto B;
            }
            else
            {
                cin.clear();
                fflush(stdin); // clear input buffer
                user();
            }
        }
    C:
        cout << "\n\t\tEnter Your Password: ";
        cin >> u_pass;
        fname = u_IC + ".txt";
        filei.open(fname.c_str());
        if (!filei.is_open() && filei.fail())
        {
            cout << "\n\t\tYou are not registered, please register before sign in.\n";
            filei.close();
            getch();
            user_password();
        }
        getline(filei, usern);
        getline(filei, userp);
        if (u_pass == userp)
        {
            user_IC = u_IC;
            user_name = usern;
            cout << "\n\t\tYou are successfully sign in";
            cout << "\n\n\t\tPress Any Key To Continue..";
            getch();
        }
        else if (u_pass != userp)
        {
            cout << "\n\t\tWrong Password";
            char choice2;
            cout << "\n\n\t\tEnter Y To Retype Password : ";
            cin >> choice2;
            if (choice2 == 'y' || choice2 == 'Y')
            {
                goto C;
            }
            else
            {
                cout << "\n\n\t\tPress Any Key To Continue ";
                getch();
                cin.clear();
                fflush(stdin);
                cout.flush();
                user_password();
            }
        }
    }
    else if (u_option == 3)
    {
        system("cls");
        string u_IC, u_pass;
        title();
        cout << "\n\n\t\t   Change Password  ";
    D:
        cout << "\n\n\t\tEnter Your IC No.: ";
        cin >> u_IC;
        if (u_IC.length() != 12)
        {
            cout << "\n\t\tInvalid IC Number";
            char choice;
            cout << "\n\n\t\tEnter Y To Retype IC No. : ";
            cin >> choice;
            if (choice == 'y' || choice == 'Y')
            {
                goto D;
            }
            else
            {
                cin.clear();
                fflush(stdin); // clear input buffer
                user();
            }
        }
        fname = u_IC + ".txt";
        filei.open(fname.c_str());
        if (!filei.is_open() && filei.fail())
        {
            cout << "\n\t\tYou are not registered, please register before changing password.\n";
            filei.close();
            getch();
            user_password();
        }
        getline(filei, usern);
        getline(filei, userp);
        filei.close();
        cout << "\n\t\tEnter Your old Password: ";
        cin >> u_pass;
        if (u_pass == userp)
        {
            string newPassword;
            cout << "\n\t\tEnter a new password: ";
            cin >> newPassword;
            ofstream fileo;
            fileo.open(fname.c_str());
            fileo << usern << endl
                  << newPassword;
            fileo.close();
            cout << "\n\n\t\tYou have change Your Password";
            cout << "\n\n\t\tPress Any Key To Continue..";
            getch();
            system("cls");
            cin.clear();
            fflush(stdin);
            cout.flush();
            user_password();
        }
        else if (u_pass != userp)
        {
            cout << "\n\t\tWrong Password";
            cout << "\n\n\t\tPress Any Key To Continue ";
            getch();
            cin.clear();
            fflush(stdin);
            cout.flush();
            user_password();
        }
    }
    else if (u_option == 4)
    {
        system("cls");
        string u_IC, u_pass;
        title();
        cout << "\n\n\t\t   Delete account  ";
    E:
        cout << "\n\n\t\tEnter Your IC No.: ";
        cin >> u_IC;
        if (u_IC.length() != 12)
        {
            cout << "\n\t\tInvalid IC Number";
            char choice;
            cout << "\n\n\t\tEnter Y To Retype IC No. : ";
            cin >> choice;
            if (choice == 'y' || choice == 'Y')
            {
                goto E;
            }
            else
            {
                cin.clear();
                fflush(stdin); // clear input buffer
                user();
            }
        }
        fname = u_IC + ".txt";
        filei.open(fname.c_str());
        if (!filei.is_open() && filei.fail())
        {
            cout << "\n\t\tAccount not exitst.\n";
            filei.close();
            getch();
            user_password();
        }
        getline(filei, usern);
        getline(filei, userp);
        filei.close();
        cout << "\n\t\tEnter Your Password: ";
        cin >> u_pass;
        if (u_pass == userp)
        {
            int result = remove(fname.c_str());
            if (result == 0)
            {
                cout << "\n\t\tAccount Deleted Successfully!";
                cout << "\n\n\t\tPress Any Key To Continue ";
                getch();
                cin.clear();
                fflush(stdin);
                cout.flush();
                menu();
            }
            else
            {
                cout << "\n\t\tError Occurred!";
                cout << "\n\n\t\tPress Any Key To Continue ";
                getch();
                cin.clear();
                fflush(stdin);
                cout.flush();
                user_password();
            }
        }
    }
    else if (u_option == 5)
    {
        menu();
    }
    else
    {
        retypeOpt();
        user_password();
    }
}

void covid_vaccination::valid(string str) // Check Username exist
{
    string dir, user;
    ifstream file;
    dir = str + ".txt";
    file.open(dir.c_str());             // converts a string to an array of characters with a null character at the end.
    if (!file.is_open() && file.fail()) // f
    {
        return;
    }
    else
    {
        counter++;
        if (counter >= 3)
        {
            cout << "\n\t\tThis IC Already Registered\n\t\tPlease Try Again..";
            file.close();
            return;
        }
        cout << "\n\t\tYou have already registered!";
    B:
        cout << "\n\n\t\tPlease Retype your IC No.: ";
        cin >> IC;
        if (IC.length() != 12)
        {
            cout << "\n\t\tInvalid IC Number";
            char choice;
            cout << "\n\n\t\tEnter Y To Retype IC No. : ";
            cin >> choice;
            if (choice == 'y' || choice == 'Y')
            {
                goto B;
            }
            else
            {
                cin.clear();
                fflush(stdin); // clear input buffer
                user_password();
            }
        }
        valid(IC);
    }
}

// admin func
void covid_vaccination::add_vaccine_stock()
{
A:
    int option;
    fstream file;
    system("cls");
    title();
    cout << "\n\n\t\t  Add Vaccine To Center  ";
    cout << "\n\n\t\t1. " << VacCenter;
    cout << "\n\n\t\t2. Back";
    cout << "\n\n\t\tEnter Option: ";
    cin >> option;
    switch (option)
    {
    case 1:
    {
        int x, add;
        file.open("vac_center.txt", ios::in);
        if (!file)
        {
            cout << "File not found" << endl;
            cout << "\n\n\n\t\tPress Any Key To Continue..";
            getch();
            break;
        }
        file >> x;
        file.close();
        cout << "\n\n\t\tVaccine In Center: " << x;
        cout << "\n\t\tEnter Number Of Vaccines You Want To Add: ";
        while (!(cin >> add))
        {
            cout << "\n\t\tInvalid Input! Enter A Numeric Value: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
        x = x + add;
        file.open("vac_center.txt", ios::out);
        file << x;
        file.close();
        cout << "\n\t\tVaccine In Center: " << x;
        cout << "\n\n\t\t" << add << " Vaccine Added";
        cout << "\n\n\n\t\tPress Any Key To Continue..";
        getch();
        break;
    }
    case 2:
        break;
    default:
        retypeOpt();
        break;
    }
}

void covid_vaccination::display_vaccine_stock()
{
    system("cls");
    vac_data data;
    ifstream ind;
    fstream file;
    int a;
    title();
    cout << "\n\n\t\t  Available Vaccine Stock ";
    int i = 0;
    file.open("vac_center.txt");
    file >> a;
    ind.open("Vaccination_Records.bin", ios::binary | ios::in); // read data from the file
    ind.seekg(0, ios::beg);                                     // Set the input file's position to the beginning of the file
    while (ind.read((char *)&data, sizeof(data)))               // Read records from the input file until the end is reached
    {
        i++; // Increment the record counter
    }
    ind.close();
    int s = a - i;
    file.close();
    cout << "\n\n\t\t  " << VacCenter << "  ";
    cout << "\n\t\tTotal Vaccine: " << a;
    cout << "\n\n\t\tAssigned Vaccine Person: " << i;
    cout << "\n\n\t\tAvailable Number Of Vaccines are: " << s;
    cout << "\n\n\t\tPress Any Key To Continue..";
    getch();
}

void covid_vaccination::vaccination_record()
{
    vac_data Data;
    system("cls");
    title();
    cout << "\n\n\t\t  Assigned Vaccine Person  \n\n\t\t";
    ifstream file("Vaccination_Records.bin", ios::binary);
    if (!file.is_open())
    {
        cerr << "Failed to open file";
    }
    // Get the size of the file
    file.seekg(0, ios::end);
    streamoff fileSize = file.tellg();
    file.seekg(0, ios::beg);

    // Allocate memory for the buffer
    char *buffer = new char[fileSize];

    // Read contents of file into buffer
    file.read(buffer, fileSize);

    // Calculate the number of data structures in the buffer
    int dataCount = fileSize / sizeof(Data);

    // Determine maximum length for each column
    int maxLength[5] = {0, 0, 0, 0, 0};
    for (int i = 0; i < dataCount; ++i)
    {
        vac_data d;
        memcpy(&d, &buffer[i * sizeof(Data)], sizeof(Data));
        maxLength[0] = max(maxLength[0], (int)string(d.uIC).length()) + 1;
        maxLength[1] = max(maxLength[1], (int)string(d.uname).length() + 4);
        maxLength[2] = max(maxLength[2], 5);
        maxLength[3] = max(maxLength[3], 11);
        maxLength[4] = max(maxLength[4], 16);
    }

    // Print table header
    cout << left << setw(maxLength[0]) << "IC No."
         << left << setw(maxLength[1]) << "Name"
         << left << setw(maxLength[2]) << "Dose"
         << left << setw(maxLength[3]) << "Date"
         << left << setw(maxLength[4]) << "Manufacturer" << endl;

    // Print contents of data as a table
    for (int i = 0; i < dataCount; ++i)
    {
        vac_data d;
        memcpy(&d, &buffer[i * sizeof(Data)], sizeof(Data));
        cout << "\t\t";
        cout << left << setw(maxLength[0]) << d.uIC
             << left << setw(maxLength[1]) << d.uname
             << left << setw(maxLength[2]) << d.dose
             << left << setw(maxLength[3]) << d.udate
             << left << setw(maxLength[4]) << d.manufacturer << endl;
    }
    delete[] buffer;
    cout << "\n\n\t\tPress Any Key To Continue..";
    getch();
}

// user func
void covid_vaccination::apply_vaccine()
{
    vac_data data;
    vac_data datas;
    vac_data datac;
    fstream file;
    ifstream files;
    int length;
    int day, month, year;
    int result;
    char choice;
    int count = 0;

    system("cls");
    title();
    cout << "\n\n\t\t  Apply Vaccine  ";
A:
    cout << "\n\n\t\tEnter IC No.: ";
    fflush(stdin);
    cin >> data.uIC;
    if (strlen(data.uIC) != 12)
    {
        cout << "\n\t\tInvalid IC Number";
        char choice;
        cout << "\n\n\t\tEnter Y To Retype IC No. : ";
        cin >> choice;
        if (choice == 'y' || choice == 'Y')
        {
            goto A;
        }
        else
        {
            cin.clear();
            fflush(stdin); // clear input buffer
            goto D;
        }
    }
    file.open("Vaccination_Records.bin", ios::in | ios::binary);
    while (file.read((char *)&datac, sizeof(datac)))
    {
        if (strcmp(data.uIC, datac.uIC) == 0)
        {
            count++;
        }
    }
    file.close();
    files.open("Vaccination_Records.bin", ios::in | ios::binary);
    if (!files)
    {
        data.dose = 49;
        cout << "\n\t\tDose1 " << data.dose << ": ";
    }
    while (files.read((char *)&datas, sizeof(datas)))
    {
        if (strcmp(data.uIC, datas.uIC) == 0) // check IC exist before or not
        {
            cout << "\n\t\tYou Have Already Apply Dose " << count;
            data.dose = (char)(count + 49);
            cout << ". You Are Applying";
            cout << "\n\t\tDose " << data.dose << ": ";
            strcpy(data.uname, datas.uname);
            cout << "\n\n\t\tName: " << data.uname << "\n";
            goto B;
        }
        else
        {
            data.dose = 49;
            cout << "\n\t\tDose " << data.dose << ": ";
            goto Z;
        }
    }
Z:
    files.close();
    cout << "\n\t\tEnter Name: ";
    cin >> data.uname;
B:
    cout << "\n\t\tEnter date (DD/MM/YYYY): ";
    cin >> data.udate;
    result = sscanf(data.udate, "%d/%d/%d", &day, &month, &year);
    if (result != 3)
    {
        cout << "\t\tInvalid Date format.";
        cout << "\n\n\t\tEnter Y To Retype Date : ";
        cin >> choice;
        if (choice == 'y' || choice == 'Y')
        {
            goto B;
        }
        else
        {
            cin.clear();
            fflush(stdin); // clear input buffer
            goto D;
        }
    }
C:
    cout << "\n\t\tEnter Vaccine Manufacture \n\t\t(Pfizer-BioNTech/AstraZeneca/Sinovac): ";
    cin >> data.manufacturer;
    length = strlen(data.manufacturer);
    for (int i = 0; i < length; ++i)
    {
        data.manufacturer[i] = tolower(data.manufacturer[i]);
    }
    if (strcmp(data.manufacturer, "pfizer-biontech") == 0)
    {
        strcpy(data.manufacturer, "Pfizer-BioNTech");
    }
    else if (strcmp(data.manufacturer, "astrazeneca") == 0)
    {
        strcpy(data.manufacturer, "AstraZeneca");
    }
    else if (strcmp(data.manufacturer, "sinovac") == 0)
    {
        strcpy(data.manufacturer, "Sinovac");
    }
    else
    {
        cout << "\n\t\tInvalid manufacturer";
        char choice;
        cout << "\n\n\t\tEnter Y To Retype Manufacturer : ";
        cin >> choice;
        if (choice == 'y' || choice == 'Y')
        {
            goto C;
        }
        else
        {
            cin.clear();
            fflush(stdin); // clear input buffer
            goto D;
        }
    }
    cout << "\n\n\t\tPlease Double-Check All Information \n\t\tFor Accuracy And Completeness Before Submitting.";
    cout << "\n\n\t\tEnter Y To Confirm : ";
    cin >> choice;
    if (choice == 'y' || choice == 'Y')
    {
        file.open("Vaccination_Records.bin", ios::app | ios::binary);
        file.write((char *)&data, sizeof(data));
        cout << "\n\n\t\tYou Have Made An Vaccination Record";
    }
    else
    {
        cin.clear();
        fflush(stdin); // clear input buffer
        cout << "\n\n\t\tVaccination Record Canceled";
    }
D:
    file.close();
    cout << "\n\n\t\tPress Any Key To Continue.." << endl;
    getch();
}

void covid_vaccination::view_vaccination()
{
    vac_data datac;
    int count = 0;
    char bIC[13];
    char bname[100];
    fstream file;
    system("cls");
    title();
    cout << "\n\n\t\t  Check Vaccination Record  ";
    file.open("Vaccination_Records.bin", ios::binary | ios::in);
    if (!file) // check file open
    {
        cout << "\n\t\tThere Are No User Appointed";
        goto D;
    }
A:
    cout << "\n\n\t\tEnter IC No.: ";
    cin >> bIC;
    if (strlen(bIC) != 12)
    {
        cout << "\n\t\tInvalid IC Number";
        char choice;
        cout << "\n\n\t\tEnter Y To Retype IC No. : ";
        cin >> choice;
        if (choice == 'y' || choice == 'Y')
        {
            goto A;
        }
        else
        {
            cin.clear();
            fflush(stdin); // clear input buffer
            goto D;
        }
    }
    cout << "\n\t\tName: ";
    cin >> bname;
    while (file.read((char *)&datac, sizeof(datac)))
    {
        if (strcmp(bIC, datac.uIC) == 0 && strcmp(bname, datac.uname) == 0)
        {
            count++;
            {
                cout << endl
                     << "\t\tDose " << datac.dose << ": ";

                cout.setf(ios::left, ios::adjustfield);
                cout.width(20);
                cout << endl
                     << "\t\tDate: ";
                cout.setf(ios::right, ios::adjustfield);
                cout.width(25);
                cout << setfill(' ') << datac.udate;
                ;

                cout.setf(ios::left, ios::adjustfield);
                cout.width(20);
                cout << endl
                     << "\t\tManufacturer: ";
                cout.setf(ios::right, ios::adjustfield);
                cout.width(25);
                cout << setfill(' ') << datac.manufacturer;
            }
        }
    }
    if (count == 0)
    {
        cout << "\n\t\tRecord Not Found!";
    }
    file.close();
D:
    cout << "\n\n\t\tPress Any Key To Continue..";
    getch();
}

void covid_vaccination::delete_vaccination()
{
    vac_data datac;
    int count = 0;
    char bIC[13];
    char bname[100];
    fstream file;
    system("cls");
    title();
    cout << "\n\n\t\t  Delete Vaccination Record  ";
    file.open("Vaccination_Records.bin", ios::binary | ios::in);
    if (!file) // check file open
    {
        cout << "\n\t\tThere Are No User Appointed";
        goto D;
    }
    else
    {
        goto A;
    }
A:
    cout << "\n\n\t\tEnter IC No.: ";
    cin >> bIC;
    if (strlen(bIC) != 12)
    {
        cout << "\n\t\tInvalid IC Number";
        char choice;
        cout << "\n\n\t\tEnter Y To Retype IC No. : ";
        cin >> choice;
        if (choice == 'y' || choice == 'Y')
        {
            goto A;
        }
        else
        {
            cin.clear();
            fflush(stdin); // clear input buffer
            goto D;
        }
    }
    cout << "\n\t\tName: ";
    cin >> bname;
    while (file.read((char *)&datac, sizeof(datac)))
    {
        if (strcmp(bIC, datac.uIC) == 0 && strcmp(bname, datac.uname) == 0)
        {
            count++;
            {
                cout << endl
                     << "\t\tDose " << datac.dose << ": ";

                cout.setf(ios::left, ios::adjustfield);
                cout.width(20);
                cout << endl
                     << "\t\tDate: ";
                cout.setf(ios::right, ios::adjustfield);
                cout.width(25);
                cout << setfill(' ') << datac.udate;
                ;

                cout.setf(ios::left, ios::adjustfield);
                cout.width(20);
                cout << endl
                     << "\t\tManufacturer: ";
                cout.setf(ios::right, ios::adjustfield);
                cout.width(25);
                cout << setfill(' ') << datac.manufacturer;
            }
        }
    }
    file.close();
    if (count == 0)
    {
        cout << "\n\t\tRecord Not Found!";
        goto D;
    }
    cout << "\n\n\t\tEnter Y To Delete Vaccination Record : ";
    char choice;
    cin >> choice;
    if (choice == 'y' || choice == 'Y')
    {
        ifstream binaryFile("Vaccination_Records.bin", ios::binary);
        if (!binaryFile)
        {
            cerr << "Error Opening Vaccination Record File";
        }
        ofstream updatedBinaryFile("Vaccination_Records_temp.bin", ios::binary | ios::trunc);
        if (!updatedBinaryFile)
        {
            cerr << "Error Opening Vaccination Record Temp File";
            binaryFile.close();
        }
        while (binaryFile.read((char *)&datac, sizeof(datac)))
        {
            if (strcmp(datac.uIC, bIC) != 0)
            {
                updatedBinaryFile.write((const char *)&datac, sizeof(datac));
            }
        }
        binaryFile.close();
        updatedBinaryFile.close();
        remove("Vaccination_Records.bin");
        rename("Vaccination_Records_temp.bin", "Vaccination_Records.bin");
        cout << "\n\n\t\tYou Have Delete The Vaccination Record";
    }
    else
    {
        cin.clear();
        fflush(stdin); // clear input buffer
        cout << "\n\n\t\tYou Have Cancel Delete Vaccination Record";
        goto D;
    }
D:
    cout << "\n\n\t\tPress Any Key To Continue..";
    getch();
}

// both func

int main()
{
    covid_vaccination system;
    system.vac_center();
    system.menu();
}
