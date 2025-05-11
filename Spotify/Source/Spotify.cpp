#include "Spotify.h"
#include "Console.h"
#include "KeyboardInput.h"

void Spotify::configureConsole()
{
	Console::hideCursor();
	Console::resizeConsole(SIZE);
}

void Spotify::setupPrevLogin()
{
	_menuManager.setupAuthMenu(_authManager, _userManager);

	Library* library = _userManager->getCurrentUser()->getLibrary();
	_menuManager.setupMainMenu(_authManager, _songManager, library);
}

void Spotify::setupPosLogin()
{
	_menuManager.initialize();

	_menuManager.setupProfileMenu(_userManager);

	Library* library = _userManager->getCurrentUser()->getLibrary();
	_menuManager.setupExploreMenu(_dataManager, library, _songManager);
	_menuManager.setupSearchMenu(_dataManager, library, _songManager);
	_menuManager.setupLibraryMenu(library, _songManager);
}

// ----------------------------------------------------- //

Spotify::Spotify()
	: _isRunning(true), _userManager(nullptr), _authManager(new AuthManager()), _dataManager(new DataManager()),
	_songManager(new SongManager())
{
	_userManager = new UserManager(_dataManager);
	// -------------------------------------------- //

	configureConsole();
	setupPrevLogin();
}

Spotify::~Spotify()
{
	delete _authManager;
	delete _userManager;
	delete _dataManager;
}

void Spotify::authenticate()
{
	if (!_authManager->isSessionActive())
	{
		_menuManager.switchToAuthMenu();
	}

	if (_authManager->approved())
	{
		setupPosLogin();

		_menuManager.switchToMainMenu();
		_authManager->toggleApproval();
	}
}

void Spotify::update()
{
	KeyboardInput::update();
	_menuManager.selectOption();
	_songManager->keyboard();
}

void Spotify::render()
{
	_menuManager.display();
	_songManager->show();
}

void Spotify::run()
{
	//Intro::showIntro(SIZE);

	while (_isRunning)
	{
		authenticate();
		// -------------- //

		update();
		render();
	}
}