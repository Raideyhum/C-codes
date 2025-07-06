#include <iostream>
#include <fstream>
#include "Header.h"
using namespace std;

void login() {
    system("cls");
    string uname, pass, role, line1, line2;
    User* ptr = NULL;
    bool found = false;

    cout << "\nENTER LOGIN DETAILS:" << endl;
    cout << "Username: ";
    cin >> uname;
    cout << "Password: ";
    cin >> pass;

    ifstream myfile("credentials.txt");
    if (!myfile.is_open()) {
        cout << "ERROR: Could not open credentials.txt" << endl;
        return;
    }

    while (myfile >> line1 >> line2 >> role) {

        if (uname == line1 && pass == line2) {
            found = true;

            if (role == "Admin")
                ptr = new Admin(uname, pass);
            else if (role == "Chef")
                ptr = new Chef(uname, pass);
            else if (role == "Manager")
                ptr = new Manager(uname, pass);
            else if (role == "Sales")
                ptr = new Sales(uname, pass);

            ptr->Menu();
            delete ptr;
            break;
        }
    }

    if (!found) {
        cout << "Invalid Username or Password!" << endl;
        system("pause");
    }
}


int main() {
    bool exit = false;
    int option;
    while (!exit) {
        system("cls");
        cout << endl << "-------------Welcome to FAST FOODIES-------------" << endl;
        cout << "1. Login" << endl;
        cout << "2. Exit" << endl;
        cout << endl << "Option: ";
        cin >> option;
        while (option > 2 || option < 1) {
            cout << "Enter a Valid option!: ";
            cin >> option;
        }

        if (option == 1) {
            login();
        }
        else {
            exit = true;
        }
    }
    return 0;
}