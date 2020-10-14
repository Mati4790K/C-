#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <cstdio>

#include "payments.h"
#include "testing.h"

using namespace std;

void Payments::MakePayment(string* login)
{
	Test t;

	bool finished = true;
	while (finished)
	{
		cout << "Enter recipient name" << endl;
		cin >> receiver;

		string filename = receiver + "Pay.txt";

		//checks if recipient exists
		ifstream bfile(filename);
		if (bfile.fail())
		{
			cout << "Recipient doesn't exist" << endl;
		}
		else
		{
			bool balanceOK = true;
			while (balanceOK)
			{
				cout << "Enter the amount you want to pay to " << receiver << endl;
				cin >> amount;

				bool fail = false;
				while (1)
				{
					if (cin.fail() || amount <= 0.0f)
					{
						cin.clear();
						cin.ignore(numeric_limits<streamsize>::max(), '\n');
						cout << "Wrong input" << endl;
						fail = true;
					}
					if (!cin.fail())
					{
						break;
					}
				}
				if (fail)
				{
					break;
				}

				//checks if user has enough money
				float tempBalance;
				tempBalance = balance - amount;
				if (tempBalance < 0)
				{
					cout << "You don't have enough money" << endl;
				}
				else
				{
					//writes to the file how much user transferred
					filename = *login + ".txt";
					ofstream cfile(filename, ios::app);
					cfile << "\n" + to_string(-amount);
					cout << "Payment successful" << endl;

					//transfers money to the receiver
					filename = receiver + ".txt";
					ofstream afile(filename, ios::app);
					afile << "\n" + to_string(amount);
					balanceOK = false;
					finished = false;
					bfile.close();
					afile.close();
				}
			}
		}
	}
}

void Payments::AddAccount()
{
	bool fail = false;
	bool finished = true;
	while (finished)
	{
		cout << "Enter name of the receiver" << endl;
		cin >> receiver;

		string filename;
		filename = receiver + "Pay.txt";

		//tries to find a file
		ifstream bfile(filename);
		//creates a file if it doesn't exist already
		if (bfile.fail())
		{
			cout << "Enter Account Number" << endl;
			cin >> newAccountNo;

			while (1)
			{
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Wrong input" << endl;
					fail = true;
				}
				if (!cin.fail())
				{
					break;
				}
			}
			if (fail)
			{
				break;
			}

			cout << "Enter Sortcode" << endl;
			cin >> newSortcode;

			while (1)
			{
				if (cin.fail())
				{
					cin.clear();
					cin.ignore(numeric_limits<streamsize>::max(), '\n');
					cout << "Wrong input" << endl;
					fail = true;
				}
				if (!cin.fail())
				{
					break;
				}
			}
			if (fail)
			{
				break;
			}

			//saves recipient info to the file
			ofstream afile(filename);
			afile << receiver << endl;
			afile << newAccountNo << endl;
			afile << newSortcode << endl;
			afile.close();
			finished = false;
		}
		else
		{
			cout << "You already have this account saved" << endl;
			bfile.close();
		}
	}
	if (fail == true)
	{
		cout << "Recipient not added" << endl;
	}
	else
	{
		cout << "Recipient added successfuly" << endl;
	}
}


void Payments::DeleteAccount()
{
	bool finished = true;
	while (finished)
	{
		cout << "Enter name of the receiver you want to delete" << endl;
		cin >> receiver;

		string filename;
		filename = receiver + "Pay.txt";

		//convert filename to char, so remove can work
		char* file = new char[filename.length() + 1];
		strcpy_s(file, 40, filename.c_str());

		//delete file
		if (remove(file) != 0)
		{
			perror("Recipient deletion failed - doesn't exist \n");
		}
		else
		{
			cout << "Recipient deleted successfully" << endl;
		}
		finished = false;
	}
}