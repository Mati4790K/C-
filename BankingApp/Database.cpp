#pragma once

#include "database.h"
#include <iostream>
#include <string>
#include <fstream>

#include "user.h"
#include "testing.h"

using namespace std;

void Database::ChangePassword(string* login)
{
	string enteredPassword;
	string filename;
	bool passwordCorrcet = true;
	filename = *login + ".txt";
	ifstream bfile(filename);

	bfile >> *login;
	bfile >> password;

	//checks if the password is correct
	while (passwordCorrcet)
	{
		cout << "Enter old password" << endl;
		cin >> enteredPassword;

		if (enteredPassword != password)
		{
			cout << "Wrong password" << endl;
		}
		else
		{

			cout << "Enter new password" << endl;
			cin >> changePassword;
			bfile.close();
			ifstream bfile(filename);
			string stringToReplace = password;
			string newString = changePassword;
			ofstream cfile("cfile.txt"); //Temporary file
			if (!bfile || !cfile)
			{
				cout << "Error opening files!" << endl;
			}

			string tempStr;
			while (bfile >> tempStr)
			{
				if (tempStr == stringToReplace) 
				{
					tempStr = newString;
				}
				cfile << tempStr << '\n';
			}
			bfile.close();
			cfile.close();

			//convert filename to char, so remove can work
			char* file = new char[filename.length() + 1];
			//strcpy_s means that it's secured and number 40 specifies how many characters are allowed to prevent buffer overflow
			strcpy_s(file, 40, filename.c_str());

			//delete file
			if (remove(file) != 0)
			{
				perror("Deletion not possible \n");		
			}
			else
			{
				char oldname[] = "cfile.txt";

				if (rename(oldname, file) != 0)
				{
					perror("Error renaming file");
				}
				else
				{
					cout << "Password changed successfully";
				}	
			}
			passwordCorrcet = false;
		}
	}
}

void Database::AddAccount()
{
	bool finished = true;
	string filename;

	while (finished)
	{
		//creates a text file with name from the username
		cout << "Enter your new login" << endl;
		cin >> newLogin;
		filename = newLogin + ".txt";
		ifstream bfile(filename);

		//checks if this username exists
		if (bfile.fail())
		{
			cout << "Enter your new password" << endl;
			cin >> newPassword;

			//saves username and password to the file
			ofstream afile(filename);
			afile << newLogin << endl;
			afile << newPassword << endl;
			afile << "0";
			afile.close();
			finished = false;
		}
		else
		{
			cout << "This username already exists" << endl;
			bfile.close();
		}
	}
	cout << "Account created successfuly" << endl;
	system("pause");
}

void Database::Menu()
{
	Test t;

	int input;
	bool stay = true;

	while (stay)
	{
		cout << "Press 1 to Log in" << endl;
		cout << "Press 2 to Create new account" << endl;
		cout << "Press 3 to Quit" << endl;
		cin >> input;

		t.ValidateInt(input);

		if (input == 1)
		{
			LogIn();
			system("cls");
		}
		else if (input == 2)
		{
			AddAccount();
			system("cls");
		}
		else if (input == 3)
		{
			stay = false;
		}
		else
		{
			cout << "Wrong number" << endl;
		}
	}
}

void Database::LogIn()
{

	string enteredPassword;
	string filename;
	bool finished = true;
	bool passwordCorrcet = true;

	while (finished)
	{
		//checks if the username exists before user enters the password
		cout << "Enter your login" << endl;
		cin >> login;
		filename = login + ".txt";
		ifstream bfile(filename);
		if (bfile.fail())
		{
			cout << "Wrong username" << endl;
		}
		else
		{
			bfile >> login;
			bfile >> password;

			//checks if the password is correct
			while (passwordCorrcet)
			{
				cout << "Hello " << login << " , enter your password" << endl;
				cin >> enteredPassword;

				if (enteredPassword != password)
				{
					cout << "Wrong password" << endl;
				}
				else
				{
					bfile.close();
					finished = false;
					passwordCorrcet = false;
				}
			}
		}
	}
	//Logs in the user to their account
	User u;
	u.MainMenu(&filename, &login);

}
