#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <limits>
#include <cstdio>

using namespace std;

class Payments
{
public:
	void MakePayment(string*);
	void AddAccount();
	void DeleteAccount();
	float balance = 0.0f;

private:
	string receiver;
	int newAccountNo;
	int newSortcode;
	float amount;
};
