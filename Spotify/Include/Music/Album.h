#pragma once

#include "List.h"
#include "Song.h"

#include <string>

class Album
{
private:
	std::string _name;
	List<Song*>* _songs;

public:
	Album(const std::string& name = "unnamed");
	Album(List<Song*>* songs, const std::string& name);
	~Album();

	void addSong(Song* song);
	List<Song*>* getSongs();
	std::string getName();
	void setName(const std::string& name);
};