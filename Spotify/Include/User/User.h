#pragma once

#include <iostream>
#include <string>
#include "Library.h"

using namespace std;

class User
{
private:
	string _name;
	string _email;
	string _password;
	string _plan;
	Library* _library;

public:
	User();
	User(string name, string email, string password, string plan, Library* library = nullptr);

	string getName() const;
	void setName(const string& name);

	string getEmail() const;
	void setEmail(const string& email);

	string getPassword() const;
	void setPassword(const string& password);

	string getPlan() const;
	void setPlan(const string& plan);

	Library* getLibrary();
	void setLibrary(Library* library);

	void saveData();
};