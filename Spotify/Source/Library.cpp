#include "Library.h"
#include "Input.h"

Library::Library(const std::string& email)
    : _playlists(new List<Playlist*>()), _artist(new List<Artist*>()), _albums(new List<Album*>()), _email(email)
{
}

Library::Library(const std::string& email, DataManager* dataManager)
	: _playlists(new List<Playlist*>()), _artist(new List<Artist*>()), _albums(new List<Album*>()), _email(email)
{
    loadFromFile(email, dataManager);
}

Library::~Library()
{
	for (uint i = 0; i < _playlists->size(); i++)
	{
		delete _playlists->getAtPosition(i);
	}
	delete _playlists;
}

List<Artist*>* Library::getArtists()
{
	return _artist;
}

List<Album*>* Library::getAlbums()
{
	return _albums;
}

List<Playlist*>* Library::getPlaylists()
{
	return _playlists;
}

void Library::setEmail(const std::string& email)
{
    _email = email;
}

void Library::add(Artist* artist)
{
	_artist->addLast(artist);
    saveToFile(_email);
}

void Library::add(Album* album)
{
	_albums->addLast(album);
    saveToFile(_email);
}

void Library::add(Song* song, const std::string& playlistName)
{
    if (playlistName != "Unamed")
    {
        for (uint i = 0; i < _playlists->size(); i++)
        {
            auto playlist = _playlists->getAtPosition(i);
            if (playlist->getName().find(playlistName) != std::string::npos)
            {
                playlist->addSong(song);
                saveToFile(_email);
				break;
            }
        }
    }
}

void Library::addPlaylist(const std::string& name)
{
	_playlists->addLast(new Playlist(name));
    saveToFile(_email);
}

void Library::addSongToPlaylist(const std::string& name, Song* song)
{
	for (uint i = 0; i < _playlists->size(); i++)
	{
		auto playlist = _playlists->getAtPosition(i);
		if (playlist->getName().find(name) != std::string::npos)
		{
			playlist->addSong(song);
            saveToFile(_email);
		}
	}
}

void Library::createPlaylist()
{
	std::cout << "Agregando playlist..." << '\n';
	
	auto playlistName = validatedInput<std::string>(
		"Nombre de la playList: ",
		"\n:: Nombre no valido\n\n"
	);

	addPlaylist(playlistName);

	MSG("\n:: Playlist agregada con exito.");
}

void Library::loadFromFile(const std::string& email, DataManager* dataManager)
{
    std::ifstream file("Data/Libraries/" + email + "_library.txt");
    if (!file.is_open())
    {
        std::ofstream create("Data/Libraries/" + email + "_library.txt");
        return;
    }

    std::string line;
    Section section = NONE;
    Playlist* currentPlaylist = nullptr;

	recursiveLoad(file, line, section, currentPlaylist, dataManager);
}
void Library::recursiveLoad(std::ifstream& file, std::string& line, Section& section, Playlist*& currentPlaylist, DataManager* dataManager)
{
    if (!std::getline(file, line)) return;

    if (line == "Artists:")
    {
        section = ARTISTS;
    }
    else if (line == "Albums:")
    {
        section = ALBUMS;
    }
    else if (line.rfind("Playlist: ", 0) == 0)
    {
        section = PLAYLIST;
        std::string playlistName = line.substr(10);
        currentPlaylist = new Playlist(playlistName);
        _playlists->addLast(currentPlaylist);
    }
    else if (!line.empty())
    {
        switch (section)
        {
        case ARTISTS:
        {
            Artist* artist = dataManager->findArtistByName(line);
            if (artist) _artist->addLast(artist);
            break;
        }
        case ALBUMS:
        {
            Album* album = dataManager->findAlbumByName(line);
            if (album) _albums->addLast(album);
            break;
        }
        case PLAYLIST:
        {
            Song* song = dataManager->findSongByName(line);
            if (song && currentPlaylist) currentPlaylist->addSong(song);
            break;
        }
        default: break;
        }
    }
	recursiveLoad(file, line, section, currentPlaylist, dataManager);
}

void Library::saveToFile(const std::string& email)
{
    std::ofstream file("Data/Libraries/" + email + "_library.txt");
    file << "Artists:\n";
    for (uint i = 0; i < _artist->size(); ++i)
        file << _artist->getAtPosition(i)->getName() << "\n";

    file << "\nAlbums:\n";
    for (uint i = 0; i < _albums->size(); ++i)
        file << _albums->getAtPosition(i)->getName() << "\n";

    for (uint i = 0; i < _playlists->size(); ++i)
    {
        auto playlist = _playlists->getAtPosition(i);
        file << "\nPlaylist: " << playlist->getName() << "\n";
        for (uint j = 0; j < playlist->getSongs()->size(); ++j)
            file << playlist->getSongs()->getAtPosition(j)->getName() << "\n";
    }
}
