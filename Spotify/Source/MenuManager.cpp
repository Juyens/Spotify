#include "MenuManager.h"
#include "Console.h"

MenuManager::MenuManager()
	: _authMenu(new Menu("Spotify - Login")), _profileMenu(nullptr), _exploreMenu(nullptr),
	_searchMenu(nullptr), _libraryMenu(nullptr), _mainMenu(new Menu("Spotify")), _currentMenu(nullptr)
{
}

MenuManager::~MenuManager()
{
	delete _currentMenu;
	delete _authMenu;
	delete _profileMenu;
	delete _exploreMenu;
	delete _searchMenu;
	delete _libraryMenu;
	delete _mainMenu;
}

void MenuManager::initialize()
{
	_profileMenu = new Menu("Spotify - Perfil");
	_exploreMenu = new Menu("Spotify - Explorar");
	_libraryMenu = new Menu("Spotify - Biblioteca");
	_searchMenu = new Menu("Spotify - Buscar");
}

void MenuManager::setupAuthMenu(AuthManager* authManager, UserManager* userManager)
{
	_authMenu->addOption("Iniciar sesion", [authManager, userManager] { authManager->signIn(userManager); });
	_authMenu->addOption("Registrarse", [authManager, userManager] { authManager->signUp(userManager); });
	_authMenu->addOptionBack("Salir", [] { Console::clearScreen(); exit(0); });
}

void MenuManager::setupProfileMenu(UserManager* userManager)
{
	_profileMenu->addOption("Ver informacion general", [userManager] { userManager->showUserInfo(); });
	_profileMenu->addOption("Cambiar usuario", [userManager] { userManager->changeUsername(); });
	//_profileMenu->addOption("Cambiar email", [userManager] { userManager->changeEmail(); });
	_profileMenu->addOption("Cambiar clave", [userManager] { userManager->changePassword(); });
	_profileMenu->addOption("Actualizar plan", [userManager] { userManager->upgradePlan(); });
	_profileMenu->addOptionBack("Volver", [this] { changeMenu(_mainMenu); });
}

void MenuManager::setupExploreMenu(DataManager* dataManager, Library* library)
{
	_exploreMenu->addOptionBack("Volver", [this] { changeMenu(_mainMenu); });
}

void MenuManager::setupSearchMenu(DataManager* dataManager, Library* library)
{
	_searchMenu->addOption("Buscar Artista", [this, dataManager, library] { createSearchArtistSubMenu(dataManager, _searchMenu, library); });
	_searchMenu->addOption("Buscar Album", [this, dataManager, library] { createSearchAlbumSubMenu(dataManager, _searchMenu, library); });
	_searchMenu->addOption("Buscar Cancion", [this, dataManager, library] { dataManager->searchSong()->printInfo(); });
	_searchMenu->addOption("Listar Artistas", [this, dataManager, library] { createListArtistSubMenu("Spotify -> Artistas", dataManager->getArtists(), _searchMenu, library, true); });
	_searchMenu->addOption("Listar Albumes", [this, dataManager, library] { createListAlbumSubMenu("Spotify -> Albums", dataManager->getAllAlbums(), _searchMenu, library, true); });
	_searchMenu->addOption("Listar Canciones", [this, dataManager, library] { createSongSubMenu(dataManager, _searchMenu, library); });

	_searchMenu->addOptionBack("Volver", [this] { changeMenu(_mainMenu); });
}

void MenuManager::setupLibraryMenu(Library* library)
{
	_libraryMenu->addOption("Mis Artistas", [this, library] { createListArtistSubMenu("Mis Artistas", library->getArtists(), _libraryMenu, library, false); });
	_libraryMenu->addOption("Mis Albumes", [this, library] { createListAlbumSubMenu("Mis Albums", library->getAlbums(), _libraryMenu, library, false); });
	_libraryMenu->addOption("Mis Paylist", [this, library] { createListPlaylistSubMenu("Mis Playlist", library->getPlaylists(), _libraryMenu); });
	_libraryMenu->addOption("Agregar Playlist", [library] { library->createPlaylist(); });

	_libraryMenu->addOptionBack("Volver", [this] { changeMenu(_mainMenu); });
}

void MenuManager::setupMainMenu(AuthManager* authManager)
{
	_mainMenu->addOption("Perfil", [this] { changeMenu(_profileMenu); });
	_mainMenu->addOption("Explorar", [this] { changeMenu(_exploreMenu); });
	_mainMenu->addOption("Buscar", [this] { changeMenu(_searchMenu); });
	_mainMenu->addOption("Biblioteca", [this] { changeMenu(_libraryMenu); });
	_mainMenu->addOption("Historial", nullptr );
	_mainMenu->addOptionBack("Cerrar sesion", [authManager] { authManager->logout(); });
}

void MenuManager::createArtistSubMenu(Artist* artist, Menu* previousMenu, Library* library, bool add)
{
	Menu* subMenu = new Menu(artist->getName());

	subMenu->addOption("Listar Albums",
							 [this, artist, subMenu, library, add]
	{
		createListAlbumSubMenu(artist->getName() + " -> Albums", artist->getAlbums(), subMenu, library, true);
	});

	subMenu->addOption("Listar Canciones",
							 [this, artist, subMenu, library]
	{
		createListSongSubMenu(artist->getName() + " -> Canciones", artist->getSongs(), subMenu, library);
	});

	if (add)
		subMenu->addOption("Agregar a la biblioteca", [this, artist, library, previousMenu] { library->add(artist); changeMenu(previousMenu); });

	subMenu->addOptionBack("Volver", [this, previousMenu] { changeMenu(previousMenu); });

	changeMenu(subMenu);
}

void MenuManager::createAlbumSubMenu(Album* album, Menu* previousMenu, Library* library, bool add)
{
	Menu* subMenu = new Menu(album->getName());

	subMenu->addOption("Listar Canciones",
							 [this, album, subMenu, library]
	{
		createListSongSubMenu(album->getName() + " -> Canciones", album->getSongs(), subMenu, library);
	});

	if (add)
		subMenu->addOption("Agregar a la biblioteca", [this, album, library, previousMenu] { library->add(album); changeMenu(previousMenu); });

	subMenu->addOptionBack("Volver", [this, previousMenu] { changeMenu(previousMenu); });

	changeMenu(subMenu);
}

void MenuManager::createSongSubMenu(DataManager* dataManager, Menu* previousMenu, Library* library)
{
	Menu* songSubMenu = new Menu("Spotify -> Canciones");

	songSubMenu->addOption("Mayor reproducciones", [this, dataManager, songSubMenu, library] { createListSongSubMenu("Mayor reproducciones", dataManager->getSongsSortedByReproductions(true), songSubMenu, library); });
	songSubMenu->addOption("Menor reproducciones", [this, dataManager, songSubMenu, library] { createListSongSubMenu("Menor reproducciones", dataManager->getSongsSortedByReproductions(false), songSubMenu, library); });
	songSubMenu->addOption("Mayor duracion", [this, dataManager, songSubMenu, library] { createListSongSubMenu("Mayor duracion", dataManager->getSongsSortedByDurationBubbleSort(true), songSubMenu, library); });
	songSubMenu->addOption("Menor duracion", [this, dataManager, songSubMenu, library] { createListSongSubMenu("Menor duracion", dataManager->getSongsSortedByDurationBubbleSort(false), songSubMenu, library); });
	songSubMenu->addOption("Mostrar todas", [this, dataManager, songSubMenu, library] { createListSongSubMenu("Spotify -> Canciones", dataManager->getAllSongs(), songSubMenu, library); });
	songSubMenu->addOptionBack("Volver", [this, previousMenu] { changeMenu(previousMenu); });

	changeMenu(songSubMenu);
}

void MenuManager::createSearchArtistSubMenu(DataManager* dataManager, Menu* previousMenu, Library* library)
{
	auto artist = dataManager->searchArtist();

	if (!artist)
		return;

	createArtistSubMenu(artist, previousMenu, library, true);
}

void MenuManager::createSearchAlbumSubMenu(DataManager* dataManager, Menu* previousMenu, Library* library)
{
	auto album = dataManager->searchAlbum();

	if (!album)
		return;

	createAlbumSubMenu(album, previousMenu, library, true);
}

void MenuManager::createListArtistSubMenu(const std::string& name, List<Artist*>* artists, Menu* previousMenu, Library* library, bool add)
{
	Menu* listArtistSubMenu = new Menu(name);

	for (uint i = 0; i < artists->size(); i++)
	{
		auto artist = artists->getAtPosition(i);
		listArtistSubMenu->addOption(artist->getName(),
									[this, artist, listArtistSubMenu, library, add]
		{
			createArtistSubMenu(artist, listArtistSubMenu, library, add);
		});
	}

	listArtistSubMenu->addOptionBack("Volver", [this, previousMenu] { changeMenu(previousMenu); });

	changeMenu(listArtistSubMenu);
}

void MenuManager::createListAlbumSubMenu(const std::string& name, List<Album*>* albums, Menu* previousMenu, Library* library, bool add)
{
	Menu* listAlbumSubMenu = new Menu(name);

	for (uint i = 0; i < albums->size(); i++)
	{
		auto album = albums->getAtPosition(i);
		listAlbumSubMenu->addOption(album->getName(), 
									[this, albums, album, name, listAlbumSubMenu, library, add]
		{ 
			createAlbumSubMenu(album, listAlbumSubMenu, library, add);
		});
	}

	listAlbumSubMenu->addOptionBack("Volver", [this, previousMenu] { changeMenu(previousMenu); });

	changeMenu(listAlbumSubMenu);
}

void MenuManager::createListSongSubMenu(const std::string& name, List<Song*>* songs, Menu* previousMenu, Library* library)
{
	Menu* listSongsSubMenu = new Menu(name);

	for (uint i = 0; i < songs->size(); i++)
	{
		auto song = songs->getAtPosition(i);
		listSongsSubMenu->addOption(song->getName(), [this, song, listSongsSubMenu, library] { createSubMenuLibrarySong(song->getName(), song, listSongsSubMenu, library); });
	}

	listSongsSubMenu->addOptionBack("Volver", [this, previousMenu] { changeMenu(previousMenu); });

	changeMenu(listSongsSubMenu);
}

void MenuManager::createListPlaylistSubMenu(const std::string& name, List<Playlist*>* playlists, Menu* previousMenu)
{
	Menu* listPlaylistSubMenu = new Menu(name);

	for (uint i = 0; i < playlists->size(); i++)
	{
		auto playlist = playlists->getAtPosition(i);
		listPlaylistSubMenu->addOption(playlist->getName(), [this, playlist, previousMenu] { createListSongSubMenu(playlist->getName() + " -> Canciones", playlist->getSongs(), previousMenu, nullptr); });
	}

	listPlaylistSubMenu->addOptionBack("Volver", [this, previousMenu] { changeMenu(previousMenu); });

	changeMenu(listPlaylistSubMenu);
}

void MenuManager::createSubMenuLibrarySong(const std::string& name, Song* song, Menu* previousMenu, Library* library)
{
	Menu* subMenu = new Menu(name);

	subMenu->addOption("Reproducir", nullptr);
	
	if (library)
		subMenu->addOption("Agregar a la biblioteca", [this, song, library, subMenu] { createAddToPlayListSubMenu(song, library, subMenu); });

	subMenu->addOption("Mostrar informacion", [song] { song->printInfo(); });

	subMenu->addOptionBack("Volver", [this, previousMenu] { changeMenu(previousMenu); });

	changeMenu(subMenu);
}

void MenuManager::changeMenu(Menu* menu)
{
	Console::clearScreen();

	_currentMenu = menu;
	
	if (_currentMenu != _mainMenu)
		_currentMenu->restoreSelectionTracker();
}

void MenuManager::switchToAuthMenu()
{
	if (_currentMenu != _authMenu)
		changeMenu(_authMenu);
}

void MenuManager::switchToMainMenu()
{
	if (_currentMenu != _mainMenu)
		changeMenu(_mainMenu);
}

void MenuManager::display()
{
	if (_currentMenu == nullptr)
		return;

	_currentMenu->display();
}

void MenuManager::selectOption()
{
	if (_currentMenu == nullptr)
		return;

	_currentMenu->selectOption();
}
