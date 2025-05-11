#include "UserManager.h"
#include "Utils.h"

#include <iostream>
#include <algorithm>

UserManager::UserManager(DataManager* dataManager)
	: _currentUser(-1), _users(new List<User*>())
{
	readUsersFromFile(dataManager);
}

UserManager::~UserManager()
{
	for (uint i = 0; i < _users->size(); i++)
	{
		_users->getAtPosition(i)->saveData();
		delete _users->getAtPosition(i);
	}
	delete _users;
}

void UserManager::readUsersFromFile(DataManager* dataManager)
{
	std::ifstream file(_fileName);

	if (!file.is_open())
	{
		std::cerr << "Warning: Unable to open the file " << _fileName << " for reading." << std::endl;
		return;
	}

	std::string line;
	while (getline(file, line))
	{
		std::stringstream ss(line);
		std::string name, email, password, plan;
		if (getline(ss, name, ',') &&
			getline(ss, email, ',') &&
			getline(ss, password, ',') &&
			getline(ss, plan, ','))
		{
			_users->addLast(new User(name, email, password, plan, new Library(email, dataManager)));
		}
		else
		{
			std::cerr << "Warning: Skipping invalid user data line: " << line << std::endl;
		}
	}
	file.close();
}

void UserManager::saveUsersToFile()
{
	std::ofstream file(_fileName);

	if (!file.is_open())
	{
		throw std::runtime_error("Unable to open the file " + _fileName + " for writing.");
	}

	for (uint i = 0; i < _users->size(); ++i)
	{
		auto user = _users->getAtPosition(i);
		file << user->getName() << "," << user->getEmail() << "," << user->getPassword() << "," << user->getPlan() << "\n";
	}
	file.close();
}

void UserManager::addUser(User* user)
{
	_users->addLast(user);
	user->saveData();
	saveUsersToFile();
}

bool UserManager::updateUser(const std::string& emailToUpdate, User* newUserInfo)
{
	for (uint i = 0; i < _users->size(); ++i)
	{
		if (_users->getAtPosition(i)->getEmail() == emailToUpdate)
		{
			_users->updateAtPosition(newUserInfo, i);
			saveUsersToFile();
			return true;
		}
	}
	return false;
}

bool UserManager::deleteUser(const std::string& emailToDelete)
{
	for (uint i = 0; i < _users->size(); ++i)
	{
		if (_users->getAtPosition(i)->getEmail() == emailToDelete)
		{
			_users->removeAtPosition(i);
			saveUsersToFile();
			return true;
		}
	}
	return false;
}

bool UserManager::userIsRegistered(const std::string& email, const std::string& password)
{
	for (uint i = 0; i < _users->size(); ++i)
	{
		if (_users->getAtPosition(i)->getEmail() == email && _users->getAtPosition(i)->getPassword() == password)
		{
			_currentUser = i;
			return true;
		}
	}
	return false;
}

bool UserManager::userExists(const std::string& userName, const std::string& email)
{
	for (uint i = 0; i < _users->size(); ++i)
	{
		if (_users->getAtPosition(i)->getName() == userName || _users->getAtPosition(i)->getEmail() == email)
		{
			return true;
		}
	}
	return false;
}

void UserManager::showUserInfo()
{
	if (_currentUser != -1)
	{
		auto user = _users->getAtPosition(_currentUser);
		std::cout << "Mostrando informacion del usuario..." << '\n';
		std::cout << "Usuario: " << user->getName() << '\n';
		std::cout << "Email: " << user->getEmail() << '\n';
		std::cout << "Clave: " << user->getPassword() << '\n';
		std::cout << "Plan: " << user->getPlan() << "\n\n";
		PAUSE;
	}
	else
	{
		MSG(":: No hay usuario logueado para mostrar la informacion.\n\n");
	}
}

void UserManager::changePassword()
{
	if (_currentUser != -1)
	{
		auto newPassword = validatedInput<std::string>("Nueva clave: ", "\n:: Clave no valida, intentelo nuevamente.\n\n");
		User* currentUserData = _users->getAtPosition(_currentUser);
		User* updatedUserData = new User(currentUserData->getName(), currentUserData->getEmail(), newPassword, currentUserData->getPlan(), currentUserData->getLibrary());
		_users->updateAtPosition(updatedUserData, _currentUser);
		saveUsersToFile();
		MSG("\n:: Clave actualizada exitosamente.\n\n");
	}
	else
	{
		MSG(":: Debe iniciar sesion para cambiar su clave.\n\n");
	}
}

void UserManager::changeUsername()
{
	if (_currentUser != -1)
	{
		auto exists = [this](const std::string& user)
		{
			return !userExists(user, "");
		};

		auto newUsername = validatedInput<std::string>("Nuevo usuario: ", "\n:: Usuario no valido, intentelo nuevamente.\n\n", exists);

		User* currentUserData = _users->getAtPosition(_currentUser);
		User* updatedUserData = new User(newUsername, currentUserData->getEmail(), currentUserData->getPassword(), currentUserData->getPlan(), currentUserData->getLibrary());
		_users->updateAtPosition(updatedUserData, _currentUser);
		saveUsersToFile();

		MSG("\n:: Nombre de usuario actualizado exitosamente.\n\n");
	}
	else
	{
		MSG(":: Debe iniciar sesion para cambiar su nombre de usuario.\n\n");
	}
}

void UserManager::changeEmail()
{
	if (_currentUser != -1)
	{
		auto conditionEmail = [this](string email)
		{
			return email.find("@hotmail.com") != std::string::npos || email.find("@gmail.com") != std::string::npos || !userExists("", email);
		};

		auto newEmail = validatedInput<std::string>("Nuevo email: ", "\n:: Email no valido, intentelo nuevamente.\n\n", conditionEmail);

		User* currentUserData = _users->getAtPosition(_currentUser);
		currentUserData->setEmail(newEmail);

		User* updatedUserData = new User(currentUserData->getName(), newEmail, currentUserData->getPassword(), currentUserData->getPlan(), currentUserData->getLibrary());
		_users->updateAtPosition(updatedUserData, _currentUser);

		saveUsersToFile();

		std::string oldPath = "Data/Libraries/" + currentUserData->getEmail() + "_library.txt";
		std::string newPath = "Data/Libraries/" + newEmail + "_library.txt";

		if (fs::exists(oldPath))
		{
			try
			{
				fs::rename(oldPath, newPath);
				MSG("\n:: Email actualizado exitosamente.\n\n");
			}
			catch (const std::exception& e)
			{
				std::cerr << ":: Error al renombrar el archivo: " << e.what() << '\n';
			}
		}
		else
		{
			std::cerr << ":: No se pudo renombrar el archivo. No existe: " << oldPath << '\n';
			return;
		}

		MSG("\n:: Email actualizado exitosamente.\n\n");
	}
	else
	{
		MSG(":: Debe iniciar sesion para cambiar su email.\n\n");
	}
}

void UserManager::upgradePlan()
{
	if (_currentUser != -1)
	{
		std::cout << "Planes disponibles:\n";
		std::cout << "1. Free\n";
		std::cout << "2. Premium\n";
		std::cout << "3. Family\n";
		std::cout << "4. Student\n";

		auto contitionPlan = [](int plan)
		{
			return (plan >= 1 && plan <= 4);
		};

		auto planChoice = validatedInput<int>("Elija el nuevo plan: ", "\n:: Plan no valido, intentelo nuevamente.\n\n", contitionPlan);

		std::string newPlan;
		switch (planChoice)
		{
		case 1: newPlan = "Free"; break;
		case 2: newPlan = "Premium"; break;
		case 3: newPlan = "Family"; break;
		case 4: newPlan = "Student"; break;
		}

		User* currentUserData = _users->getAtPosition(_currentUser);
		User* updatedUserData = new User(currentUserData->getName(), currentUserData->getEmail(), currentUserData->getPassword(), newPlan, currentUserData->getLibrary());
		_users->updateAtPosition(updatedUserData, _currentUser);
		saveUsersToFile();

		MSG("\n:: Plan actualizado a " + newPlan + " exitosamente.\n\n");
	}
	else
	{
		MSG(":: Debe iniciar sesion para cambiar su plan.\n\n");
	}
}

List<User*>* UserManager::getAllUsers()
{
	return _users;
}

User* UserManager::getCurrentUser()
{
	if (_currentUser != -1)
	{
		return _users->getAtPosition(_currentUser);
	}

	return _users->getAtPosition(0);
}
