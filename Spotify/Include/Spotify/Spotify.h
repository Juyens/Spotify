#pragma once

#include "MenuManager.h"
#include "AuthManager.h"
#include "SongManager.h"
#include "Intro.h"

#define SIZE { 121, 41 }

class Spotify
{
private:
	UserManager* _userManager;
	AuthManager* _authManager;
	DataManager* _dataManager;
	SongManager* _songManager;
	MenuManager _menuManager;
	bool _isRunning;

	// ----------------- //
	void configureConsole();
	void setupPrevLogin();
	void setupPosLogin();

public:
	Spotify();
	~Spotify();

	void authenticate();
	void update();
	void render();

	void run();
};