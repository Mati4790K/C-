#pragma once

#include "user.h"
#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <cstdio>

#include "payments.h"
#include "database.h"
#include "testing.h"


using namespace std;

void User::MainMenu(string* filename, string* login)
{
	Payments p;
	Database d;
	Test t;

	string str;
	
	system("cls");
	bool quit = true;
	while (quit)
	{
		fstream bfile(*filename);

		p.balance = 0.0f;
		//starts reading file from line 3
		GotoLine(bfile, 3);

		//calculates the account balance
		while (!bfile.eof())
		{
			bfile >> str;
			float strFloat = stof(str);
			p.balance += strFloat;
		}

		cout << "Welcome " << *login << ", your current balance is: ";
		cout << p.balance << endl;

		int input;

		cout << "Press 1 to Make a payment" << endl;
		cout << "Press 2 to Add new recipient" << endl;
		cout << "Press 3 to Delete a recipient" << endl;
		cout << "Press 4 to Check your transaction history" << endl;
		cout << "Press 5 to Change password" << endl;
		cout << "Press 6 to Log out" << endl;
		cin >> input;

		t.ValidateInt(input);

		if (input == 1)
		{
			string log = *login;
			p.MakePayment(&log);
		}
		else if (input == 2)
		{
			p.AddAccount();
		}
		else if (input == 3)
		{
			p.DeleteAccount();
		}
		else if (input == 4)
		{
			bfile.close();
			fstream bfile(*filename);
			//start reading file from line 3
			GotoLine(bfile, 3);

			cout << "Transaction history:" << endl;

			while (!bfile.eof())
			{
				bfile >> str;
				cout << str << endl;
			}

			cout << endl;
		}
		else if (input == 5)
		{
			string log = *login;
			bfile.close();
			d.ChangePassword(&log);
		}
		else if (input == 6)
		{
			quit = false;
		}
		else
		{
			cout << "Wrong number" << endl;
		}
	}


}

//allows to start reading from specified line in the text file
inline fstream& User::GotoLine(fstream& file, unsigned int num)
{
	file.seekg(ios::beg);
	for (int i = 0; i < num - 1; ++i) 
	{
		file.ignore(numeric_limits<streamsize>::max(), '\n');
	}
	return file;
}
