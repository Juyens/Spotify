#pragma once

#include "User.h"
#include "List.h"
#include "Input.h"
#include "DataManager.h"

#include <string>
#include <fstream>
#include <sstream>
#include <optional>
#include <filesystem>

namespace fs = std::filesystem;

class UserManager
{
private:
	std::string _fileName{ "Data\\DataUsers.txt" };
	List<User*>* _users;
	int _currentUser;
	
	void readUsersFromFile(DataManager* dataManager);
	void saveUsersToFile();

public:
	UserManager(DataManager* dataManager);
	~UserManager();

	void addUser(User* user);
	bool updateUser(const std::string& emailToUpdate, User* newUserInfo);
	bool deleteUser(const std::string& emailToDelete);
	bool userIsRegistered(const std::string& email, const std::string& password);
	bool userExists(const std::string& userName, const std::string& email);
	void showUserInfo();

	void changePassword();
	void changeUsername();
	void changeEmail();
	void upgradePlan();

	List<User*>* getAllUsers();

	User* getCurrentUser();
};