#pragma once

#include "Menu.h"
#include "AuthManager.h"
#include "UserManager.h"
#include "DataManager.h"
#include "SongManager.h"
#include "Artist.h"

class MenuManager
{
private:
	Menu* _currentMenu;

	Menu* _authMenu;
	Menu* _profileMenu;
	Menu* _exploreMenu;
	Menu* _searchMenu;
	Menu* _libraryMenu;
	Menu* _mainMenu;

public:
	MenuManager();
	~MenuManager();

	void initialize();

	void setupAuthMenu(AuthManager* authManager, UserManager* userManager);
	void setupProfileMenu(UserManager* userManager);
	void setupExploreMenu(DataManager* dataManager, Library* library, SongManager* songManager);
	void setupSearchMenu(DataManager* dataManager, Library* library, SongManager* songManager);
	void setupLibraryMenu(Library* library, SongManager* songManager);
	void setupMainMenu(AuthManager* authManager, SongManager* songManager, Library* library);
	void createHistoryMenu(SongManager* songManager, Library* library);

	void createArtistSubMenu(Artist* artist, Menu* previousMenu, Library* library, SongManager* songManager, bool add);
	void createAlbumSubMenu(Album* album, Menu* previousMenu, Library* library, SongManager* songManager, bool add);
	void createSongSubMenu(DataManager* dataManager, Menu* previousMenu, Library* library, SongManager* songManager);

	void createSearchArtistSubMenu(DataManager* dataManager, Menu* previousMenu, Library* library, SongManager* songManager);
	void createSearchAlbumSubMenu(DataManager* dataManager, Menu* previousMenu, Library* library, SongManager* songManager);
	void createSearchSongSubMenu(DataManager* dataManager, Menu* previousMenu, Library* library, SongManager* songManager);

	void createListArtistSubMenu(const std::string& name, List<Artist*>* artists, Menu* previousMenu, Library* library, SongManager* songManager, bool add);
	void createListAlbumSubMenu(const std::string& name, List<Album*>* albums, Menu* previousMenu, Library* library, SongManager* songManager, bool add);
	void createListSongSubMenu(const std::string& name, List<Song*>* songs, Menu* previousMenu, Library* library, SongManager* songManager);
	void createListPlaylistSubMenu(const std::string& name, List<Playlist*>* playlists, Menu* previousMenu, SongManager* songManager);

	void createHistorySubMenu(Menu* previousMenu, SongManager* songManager, Library* library);

	template<class T>
	void createAddToPlayListSubMenu(T object, Library* library, Menu* previousMenu);

	void createSubMenuLibrarySong(const std::string& name, Song* song, Menu* previousMenu, Library* library, SongManager* songManager);

	void changeMenu(Menu* menu);

	void switchToAuthMenu();
	void switchToMainMenu();

	void display();
	void selectOption();
};

template<class T>
inline void MenuManager::createAddToPlayListSubMenu(T object, Library* library, Menu* previousMenu)
{
	Menu* listMenu = new Menu("Mis PlayLists");

	auto playlists = library->getPlaylists();
	for (uint i = 0; i < playlists->size(); i++)
	{
		auto playlist = playlists->getAtPosition(i);
		listMenu->addOption(playlist->getName(), [this, library, playlist, object, previousMenu]
		{
			library->add(object, playlist->getName()); changeMenu(previousMenu);
		});
	}
	listMenu->addOptionBack("Volver", [this, previousMenu] { changeMenu(previousMenu); });

	changeMenu(listMenu);
}