#pragma once

#include <iostream>
#include <string>
#include <fstream>
#include <string>

using namespace std;

class Database
{
public:
	void ChangePassword(string*);
	void AddAccount();
	void LogIn();
	void Menu();
	string login;

private:
	string password;
	string savedAccount;
	
	string newLogin;
	string newPassword;
	string changePassword;
};
