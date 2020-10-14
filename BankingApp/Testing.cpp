#pragma once

#include <iostream>
#include <string>
#include "testing.h"

using namespace std;

void Test::ValidateInt(int i)
{
	while (1)
	{
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Wrong input" << endl;
		}
		if (!cin.fail())
			break;
	}
}

void Test::ValidateFloat(float f)
{
	while (1)
	{
		if (cin.fail())
		{
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			cout << "Wrong input" << endl;
		}
		if (!cin.fail())
			break;
	}
}