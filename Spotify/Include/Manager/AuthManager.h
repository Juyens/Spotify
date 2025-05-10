#pragma once

#include "Input.h"
#include "List.h"
#include "User.h"
#include "UserManager.h"

#include <iostream>
#include <fstream>
#include <sstream>

class AuthManager
{
private:
	bool _isSessionActive;
	bool _approved;

public:
	AuthManager();

	void signIn(UserManager* userManager);
	void signUp(UserManager* userManager);
	void logout();

	bool isSessionActive();
	bool approved();
	void toggleApproval();
};