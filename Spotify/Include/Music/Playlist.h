#pragma once

#include "List.h"
#include "Song.h"

#include <string>

class Playlist
{
private:
	std::string _name;
	List<Song*>* _songs;

public:
	Playlist(const std::string& name = "Unnamed");
	~Playlist();

	List<Song*>* getSongs();

	std::string getName();
	void setName(const std::string& name);

	void addSong(Song* song);
};