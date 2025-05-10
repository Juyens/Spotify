#include "AuthManager.h"
#include "Utils.h"

AuthManager::AuthManager()
	: _isSessionActive(false), _approved(false)
{
}

void AuthManager::signIn(UserManager* userManager)
{
	auto condition = [](string email)
	{
		return email.find('@') != std::string::npos;
	};

	cout << "Autenticando credenciales... " << '\n';

	auto email = validatedInput<string>(
		"Email: ",
		"\n:: Email no valido, intentelo nuevamente.\n\n",
		condition);

	auto password = validatedInput<string>(
		"Password: ",
		"\n:: Clave no valida, intentelo nuevamente.\n\n");

	bool found = userManager->userIsRegistered(email, password);

	if (found)
	{
		MSG("\n:: Ingreso exitoso.\n\n");
		_isSessionActive = true;
		_approved = true;
	}
	else
	{
		MSG("\n:: Fallo en el inicio de sesion. Verifique las credenciales.\n\n")
	}
}

void AuthManager::signUp(UserManager* userManager)
{
	auto conditionEmail = [](string email)
	{
		return email.find("@hotmail.com") != std::string::npos || email.find("@gmail.com") != std::string::npos;
	};

	auto contitionPlan = [](int plan)
	{
		return (plan >= 1 && plan <= 4);
	};

	cout << "Iniciando proceso de registro... " << '\n';

	auto userName = validatedInput<string>(
		"Usuario: ",
		"\n:: Usuario no valido, intentelo nuevamente.\n\n");

	auto email = validatedInput<string>(
		"Email: ",
		"\n:: Email no valido, intentelo nuevamente.\n\n",
		conditionEmail);

	auto password = validatedInput<string>(
		"Password: ",
		"\n:: Clave no valida, intentelo nuevamente.\n\n");

	bool found = userManager->userExists(userName, email);

	if (found)
	{
		MSG("\n:: Usuario o email ya registrados.\n\n")
		return;
	}

	cout << "\nElije tu plan..." << '\n';
	cout << "1. Plan Free" << '\n';
	cout << "2. Plan Premium" << '\n';
	cout << "3. Plan Family" << '\n';
	cout << "4. Plan Student" << '\n';

	auto planChoice = validatedInput<int>("Plan: ", "\n:: Plan no valido, intentelo nuevamente.\n\n", contitionPlan);

	string plan;
	switch (planChoice)
	{
	case 1: plan = "Free";
		break;
	case 2: plan = "Premium";
		break;
	case 3: plan = "Family";
		break;
	case 4: plan = "Student";
		break;
	}

	User* newUser = new User(userName, email, password, plan, new Library(email));
	userManager->addUser(newUser);

	MSG("\n:: Registro exitoso.\n\n")
}

void AuthManager::logout()
{
	_isSessionActive = false;
}

bool AuthManager::isSessionActive()
{
	return _isSessionActive;
}

void AuthManager::toggleApproval()
{
	_approved = !_approved;
}

bool AuthManager::approved()
{
	return _approved;
}
