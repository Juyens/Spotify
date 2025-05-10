#include "User.h"

#include "User.h"

User::User()
    : _name(""), _email(""), _password(""), _plan(""), _library(nullptr)
{
}

User::User(string name, string email, string password, string plan, Library* library)
    : _name(name), _email(email), _password(password), _plan(plan), _library(library)
{
}

string User::getName() const
{
    return _name;
}

string User::getEmail() const
{
    return _email;
}

string User::getPassword() const
{
    return _password;
}

string User::getPlan() const
{
    return _plan;
}

void User::setName(const string& name)
{
    _name = name;
}

void User::setEmail(const string& email)
{
    _email = email;
}

void User::setPassword(const string& password)
{
    _password = password;
}

void User::setPlan(const string& plan)
{
    _plan = plan;
}

Library* User::getLibrary()
{
    return _library;
}

void User::setLibrary(Library* library)
{
    _library = library;
}

void User::saveData()
{
    _library->saveToFile(_email);
}
