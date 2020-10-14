#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <cstdio>

using namespace std;

class User
{
public:
	void MainMenu(string*, string*);
	fstream& GotoLine(fstream&, unsigned int);

private:
	string name;
	int accountNo;
	int sortCode;
};
