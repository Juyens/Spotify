#pragma once

#include "List.h"
#include "Artist.h"

#include <fstream>
#include <string>
#include <sstream>
#include <iostream>

class DataManager
{
private:
	std::string _fileName{ "Data\\DataArtists.txt" };
	List<Artist*>* _artist;

	// -------------------- //
	void loadDataFromFile();
	void recursiveData(std::ifstream& file, int previousLevel, Artist* currentArtist, Album* currentAlbum, Song* currentSong, Credits* currentCredits);
	int countTabs(const std::string& line);
	List<std::string>* split(const std::string& input, char delimiter);

public:
	DataManager();
	~DataManager();


	Artist* searchArtist();
	Album* searchAlbum();
	Song* searchSong();

	List<Artist*>* getArtists();
	void printData();
	List<Song*>* getSongsByArtist(const std::string& artistName);
	List<Song*>* getSongsByAlbum(const std::string& albumName);

	List<Album*>* getAllAlbums();
	List<Song*>* getAllSongs();

	List<Song*>* getSongsSortedByDurationBubbleSort(bool ascending = true);
	List<Song*>* getSongsSortedByReproductions(bool ascending = true);

	Artist* findArtistByName(const std::string& name);
	Album* findAlbumByName(const std::string& name);
	Song* findSongByName(const std::string& name);
};