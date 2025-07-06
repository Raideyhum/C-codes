#pragma once

#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
using namespace std;

class User {
protected:
	string username, password, role;
public:
	User() {
		username = "";
		password = "";
		role = "";
	}
	User(string name, string pass, string rol) {
		username = name;
		password = pass;
		role = rol;
	}
	virtual void Menu() = 0;
};

class Admin : public User {
public:
	Admin(string name, string pass) : User(name, pass, "Admin") {}

	void Menu() override {
		int option;
		system("cls");
		do {
			cout << "\n-----Admin Menu-----\n";
			cout << "Choose from options below : " << endl;
			cout << "1. Add Employee \n2. View Credentials \n3. View Logs \n4.Exit" << endl;
			cout << "Enter option: ";
			cin >> option;
			while (option > 4 || option < 1) {
				cout << "Invalid option! Enter again: ";
				cin >> option;
			}
			if (option == 1) {
				addEmployee();
			}
			else if (option == 2) {
				viewcreds();
			}
			else if (option == 3) {
				viewlog();
			}
		} while (option != 4);
	}

	void addEmployee() {
		string name, pass, role;
		cout << "Enter username : ";
		cin >> name;
		cout << "Enter password : ";
		cin >> pass;
		cout << "Enter role (Manager / Chef / Sales) : ";
		cin >> role;

		while (role != "Manager" && role != "Chef" && role != "Sales") {
			if (role == "Admin") {
				cout << "There can only be 1 admin choose an other option: ";
				cin >> role;
			}
			else {
				cout << "Invalid Option! Please choose again: ";
				cin >> role;
			}
		}

		ofstream myfile;
		myfile.open("credentials.txt", ios::app);
		if (!myfile) {
			cout << "Error opening file!" << endl;
		}
		else {
			myfile << endl;
			myfile << name << "\t" << pass << "\t" << role;
			myfile.close();
			newadd(name);
			cout << "Employee added successfully!" << endl;
		}
	}

	void newadd(string name) {
		ofstream myfile;
		myfile.open("log.txt", ios::app);
		if (!myfile) {
			cout << "Error opening file!" << endl;
		}
		else {
			myfile << "New Employee : " << name << endl;
		}
		myfile.close();
	}

	void viewcreds() {
		ifstream myfile;
		myfile.open("credentials.txt");
		if (!myfile) {
			cout << "Error opening file!" << endl;
		}
		else {
			string line;
			while (getline(myfile, line)) {
				cout << line << endl;
			}
		}
		myfile.close();
	}

	void viewlog() {
		ifstream myfile;
		myfile.open("log.txt");
		if (!myfile) {
			cout << "Error opening file!" << endl;
		}
		else {
			string line;
			while (getline(myfile, line)) {
				cout << line << endl;
			}
		}
		myfile.close();
	}
};

class Chef : public User {
public:

	Chef(string name, string pass) : User(name, pass, "Chef") {}

	void Menu()override {
		int option;
		system("cls");
		do {
			cout << "\n-----Chef Menu-----\n";
			cout << "Choose from options below : " << endl;
			cout << "1. Add Recipe \n2. Edit Recipe \n3. Display Items \n4. Exit" << endl;
			cout << "Enter option: ";
			cin >> option;
			while (option > 4 || option < 1) {
				cout << "Invalid option! Enter again: ";
				cin >> option;
			}

			if (option == 1) {
				addrecipe();
			}
			else if (option == 2) {
				editrecipe();
			}
			else if (option == 3) {
				display();
			}
		} while (option != 4);
	}

	void addrecipe() {
		string line, name, recipe, ingredients, type, price, qty;
		ifstream infile("requests.txt");
		while (getline(infile, line)) {
			cout << line << endl;
		}
		infile.close();
		cout << "Enter name of product(for recipe): ";
		cin.ignore();
		getline(cin, name);
		cout << "Enter full ingredients : ";
		getline(cin, ingredients);
		cout << "Enter full steps: ";
		getline(cin, recipe);
		ofstream outfile("recipes.txt", ios::app);
		outfile << endl;
		outfile << endl << name << endl;
		outfile << "Ingredients: " << ingredients << endl;
		outfile << "Steps: " << recipe;
		ofstream ofile("menu.txt", ios::app);
		ifstream intfile("requests.txt");
		while (intfile >> line) {
			if (line == name) {
				ofile << name << endl;
				intfile >> type >> price >> qty;
				intfile.ignore();
				ofile << type << " " << price << " " << qty << endl;
			}
		}
		intfile.close();
		ofstream out("temp.txt");
		string a, b, c, d;
		ifstream inttfile("requests.txt");
		while (inttfile >> a >> b >> c >> d) {
			inttfile.ignore();
			if (a != name) {
				out << a << "\t" << b << "\t" << c << "\t" << d << endl;
			}
		}
		ifstream in("temp.txt");
		ofstream ouch("requests.txt");
		string line33;
		while (getline(in, line33)) {
			ouch << line33 << endl;
		}
		inttfile.close();
		outfile.close();
		ofile.close();
		out.close();
		in.close();
		ouch.close();
	}

	void editrecipe() {
		ifstream infile("recipes.txt");
		string line1, line2, line3, line4;
		while (getline(infile, line1)) {
			cout << line1 << endl;
		}
		infile.close();
		string option, steps, ingredients;
		ifstream getfile("recipes.txt");
		cout << "Enter recipe name: ";
		cin.ignore();
		getline(cin, option);
		cout << "Enter new ingredients: ";
		getline(cin, ingredients);
		cout << "Enter new steps: ";
		getline(cin, steps);
		ofstream outtemp("temp.txt");
		while (getline(getfile, line1)) {
			getline(getfile, line2);
			getline(getfile, line3);
			getline(getfile, line4);
			if (line1 == option) {
				outtemp << line1 << endl;
				outtemp << "Ingredients: " << ingredients << endl;
				outtemp << "Steps: " << steps << endl;
				outtemp << line4 << endl;
			}
			else {
				outtemp << line1 << endl << line2 << endl << line3 << endl;
				outtemp << line4 << endl;
			}
		}
		getfile.close();
		outtemp.close();
		ifstream intemp("temp.txt");
		ofstream getreal("recipes.txt");
		while (getline(intemp, line1)) {
			getreal << line1 << endl;
		}
		intemp.close();
		getreal.close();
	}

	void display() {
		ifstream infile1("recipes.txt");
		ifstream infile2("menu.txt");
		string l1, l2, l3, l4, l5, l6, l7, l8;
		while (getline(infile2, l1)) {//menu l1 = name 
			infile2 >> l2 >> l3 >> l4;//l2 = type l3 = price l4 = qty
			infile2.ignore();
			getline(infile1, l5);//name
			getline(infile1, l6);//ingredients
			getline(infile1, l7);//steps
			getline(infile1, l8);//empty line
			cout << endl;
			cout << l1 << " : " << endl;
			cout << "Quantity: " << l4 << endl;
			cout << l6 << endl << l7 << endl;


		}
		infile1.close();
		infile2.close();
	}
};

class Manager : public User {
public:
	Manager(string name, string pass) : User(name, pass, "Manager") {}

	void Menu()override {
		system("cls");
		int option;

		ifstream infile("menu.txt");
		string a, b;
		int c, d;
		while (getline(infile, a) && infile >> b >> c >> d) {
			infile.ignore();
			if (d < 10) {
				cout << endl << endl;
				cout << a << " is low in stock!!!" << endl;
			}

		}

		do {
			cout << "\n-----Manager Menu-----\n";
			cout << "Choose from options below : " << endl;
			cout << "1. Add New Food Item \n2. Restock Item \n3. View Sales Report \n4. Exit" << endl;
			cout << "Enter option: ";
			cin >> option;
			while (option > 4 || option < 1) {
				cout << "Invalid option! Enter again: ";
				cin >> option;
			}

			if (option == 1) {
				addfood();
			}
			else if (option == 2) {
				Restock();
			}
			else if (option == 3) {
				salesreport();
			}
		} while (option != 4);
	}

	void addfood() {
		string name, type;
		int price, quantity;

		cout << "Enter the food item : ";
		cin.ignore();
		getline(cin, name);
		cout << "Enter type (Meal / Desert / Drink) : ";
		cin >> type;
		cout << "Enter price : ";
		cin >> price;
		cout << "Enter quantity : ";
		cin >> quantity;

		ofstream rfile;
		rfile.open("requests.txt", ios::app);
		if (!rfile) {
			cout << "Error opening request file!" << endl;
		}
		else {
			rfile << name << "\t" << type << "\t" << price << "\t" << quantity << endl;
		}
		rfile.close();
	}

	void Restock() {
		cout << endl << endl;
		bool found = false;
		int qty, price, quantity;
		string product, line, category;

		ifstream infile73("menu.txt");
		while (getline(infile73, line)) {
			cout << "Product: " << line << endl;
			infile73 >> line >> line >> line;
			cout << "In Stock: " << line << endl;
			infile73.ignore();
		}
		cout << endl;
		cout << "Enter the name of the product: ";
		cin.ignore();
		getline(cin, product);

		ifstream infile("menu.txt");

		while (getline(infile, line)) {
			if (line == product) {
				found = true;
				break;
			}
		}
		infile.close();

		if (found) {
			cout << "Enter the amount you want to add: ";
			cin >> qty;

			ifstream infile("menu.txt");
			ofstream outfile("temp.txt");

			while (getline(infile, line)) {
				outfile << line << endl;
				if (line == product) {
					infile >> category >> price >> quantity;
					infile.ignore();
					quantity += qty;
					outfile << category << "\t" << price << "\t" << quantity << endl;
				}
				else {
					infile >> category >> price >> quantity;
					infile.ignore();
					outfile << category << "\t" << price << "\t" << quantity << endl;
				}
			}

			infile.close();
			outfile.close();

			ifstream fin("temp.txt");
			ofstream fout("menu.txt");
			while (getline(fin, line)) {
				fout << line << endl;
			}
			fin.close();
			fout.close();

			cout << "Quantity updated successfully!" << endl;
		}
		else {
			cout << "Product not found!!" << endl;
		}
	}

	void salesreport() {
		ifstream infile("sales.txt");
		int num1, num2;
		string waste;
		int amount = 0, revenue = 0;
		while (getline(infile, waste) && infile >> waste >> waste >> num1 >> waste >> waste >> num2) {
			infile.ignore();
			amount = amount + num1;
			revenue = revenue + num2;
		}
		cout << "Total items sold: " << amount << endl;
		cout << "Total revenue made: PKR " << revenue << endl;
	}
};

class Sales : public User {
public:
	Sales(string name, string pass) : User(name, pass, "Sales") {}

	void Menu()override {
		system("cls");
		int option;
		do {
			cout << "\n-----Sales Menu-----\n";
			cout << "Choose from option below : " << endl;
			cout << "1. Take Order \n2. Exit" << endl;
			cout << "Enter option: ";
			cin >> option;
			while (option > 2 || option < 1) {
				cout << "Invalid option! Enter again: ";
				cin >> option;
			}
			if (option == 1) {
				TakeOrder();
			}
		} while (option != 2);
	}

	void TakeOrder() {
		int items, count = 0;
		string type, line1, line2;
		int line3, line4, qty;
		string option;
		cout << "Please enter number of Items you wish to buy : ";
		cin >> items;

		ofstream trip("INVOICE.txt", ios::trunc);
		trip.close();


		for (int i = 0; i < items; i++) {
			cout << "Enter the item category (Meal / Dessert / Drink) : ";
			cin >> type;
			while (type != "Meal" && type != "Dessert" && type != "Drink") {
				cout << "Enter a valid option: ";
				cin >> type;
			}

			ifstream infile("menu.txt");
			cout << "\n+----+----------------+--------+----------+" << endl;
			cout << "| ID | Item Name      | Price  | In Stock |" << endl;
			cout << "+----+----------------+--------+----------+" << endl;

			while (getline(infile, line1) && infile >> line2 >> line3 >> line4) {
				infile.ignore();
				if (type == line2) {
					count++;
					if (count < 10) {
						cout << "| 0" << count << " |";
					}
					else {
						cout << "| " << count << " |";
					}
					cout << " " << line1;
					for (int i = 0; i < 15 - line1.length(); i++) {
						cout << " ";
					}
					cout << "|";
					cout << " PKR" << line3 << " |" << "   " << line4;
					if (line4 < 10) {
						for (int i = 0; i < 6; i++) {
							cout << " ";
						}
					}
					else {
						for (int i = 0; i < 5; i++) {
							cout << " ";
						}
					}
					cout << "|" << endl;
				}
			}
			cout << "+----+----------------+--------+----------+" << endl;
			infile.close();
			cout << "Enter name of product: ";
			cin.ignore();
			getline(cin, option);
			cout << "Enter the amount of product: ";
			cin >> qty;
			bool REAL = true;
			bool found = false;
			ifstream infile2("menu.txt");
			while (REAL && getline(infile2, line1)) {
				infile2 >> line2 >> line3 >> line4;
				infile2.ignore();
				if (line1 == option && line4 == 0) {
					found = true;
					cout << endl << "Product not in stock!" << endl;
					i = i - 1;
					break;
				}
				if (line1 == option && line4 < qty) {
					REAL = true;
					cout << "Stock is low!! Enter a value within stock: ";

					cin >> qty;

				}
				else {
					REAL = false;
				}
			}
			if (found) {
				continue;
			}
			infile2.close();

			ofstream tout("INVOICE.txt", ios::app);

			ofstream opensales("sales.txt", ios::app);
			opensales << "Name of product: " << option << endl;
			tout << option << endl;
			opensales << "Quantity purchased: " << qty << endl;
			tout << qty << endl;
			ifstream infile1("menu.txt");
			ofstream temp("temp.txt");
			while (getline(infile1, line1) && infile1 >> line2 >> line3 >> line4) {
				infile1.ignore();
				if (option == line1) {
					temp << line1 << endl;
					temp << line2 << "\t" << line3 << "\t";
					temp << line4 - qty << endl;
					opensales << "Price: PKR " << qty * line3 << endl;

					tout << qty * line3 << endl;


				}
				else {
					temp << line1 << endl << line2 << "\t" << line3 << "\t" << line4 << endl;
				}
			}
			infile1.close();
			temp.close();

			ifstream temp1("temp.txt");
			ofstream outfile("menu.txt");
			while (getline(temp1, line1)) {
				outfile << line1 << endl;
			}
			temp1.close();
			outfile.close();
			tout.close();


		}
		int total = 0;
		system("cls");
		ifstream inv("INVOICE.txt");
		time_t now = time(0);
		char dt[26];
		ctime_s(dt, sizeof(dt), &now);
		cout << endl;
		cout << "============================================" << endl;
		cout << "               FAST FOODIES" << endl;
		cout << "                  INVOICE" << endl;
		cout << "============================================" << endl;
		cout << dt;
		cout << "============================================" << endl;
		cout << "Item Name          Quantity     Price (PKR) " << endl;
		cout << "--------------------------------------------" << endl;
		while (getline(inv, line1) && inv >> line3 >> line4) {
			inv.ignore();
			cout << line1;
			for (int i = 0; i < 22 - line1.length(); i++) {
				cout << " ";
			}
			cout << line3;
			int num;
			if (line3 < 10) {
				num = 1;
			}
			else {
				num = 2;
			}
			for (int i = 0; i < 14 - num; i++) {
				cout << " ";
			}
			total += line4;
			cout << line4;
			int num2;
			if (line4 < 1000) {
				num2 = 3;
			}
			else {
				num2 = 4;
			}
			for (int i = 0; i < 8 - num2; i++) {
				cout << " ";
			}
			cout << endl;
		}
		cout << "--------------------------------------------" << endl;
		cout << "Grand Total                     PKR " << total << endl;
		cout << "============================================" << endl;
		cout << endl;
		cout << "Thank you for your purchase." << endl;

		inv.close();

	}
};