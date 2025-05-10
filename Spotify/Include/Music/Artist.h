#pragma once

#include "List.h"
#include "Album.h"

#include <string>

class Artist
{
private:
	std::string _name;
	List<Album*>* _albums;

public:
	Artist(const std::string& name = "unnamed");
	Artist(List<Album*>* albums, const std::string& name);
	~Artist();

	void addAlbum(Album* album);
	List<Album*>* getAlbums();
	List<Song*>* getSongs();

	std::string getName();
	void setName(const std::string& name);
};