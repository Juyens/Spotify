#pragma once

#include "List.h"
#include "Playlist.h"
#include "Artist.h"
#include "Album.h"
#include "Song.h"
#include "Utils.h"
#include "DataManager.h"

#include <string>
#include <typeinfo>

class Library
{
private:
	List<Artist*>* _artist;
	List<Album*>* _albums;
	List<Playlist*>* _playlists;
	std::string _email;
	enum Section { NONE, ARTISTS, ALBUMS, PLAYLIST };

public:
	Library(const std::string& email);
	Library(const std::string& email, DataManager* dataManager);
	~Library();

	List<Artist*>* getArtists();
	List<Album*>* getAlbums();
	List<Playlist*>* getPlaylists();

	void setEmail(const std::string& email);

    void add(Artist* artist);
    void add(Album* album);
    void add(Song* song, const std::string& playlistName = "Unnamed");

	void addPlaylist(const std::string& name);
	void addSongToPlaylist(const std::string& name, Song* song);

	void createPlaylist();

	void loadFromFile(const std::string& email, DataManager* dataManager);
	void recursiveLoad(std::ifstream& file, std::string& line, Section& section, Playlist*& currentPlaylist, DataManager* dataManager);
	void saveToFile(const std::string& email);
};