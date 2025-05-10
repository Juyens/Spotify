#include "Album.h"

Album::Album(const std::string& name)
	: _songs(new List<Song*>())
{
}

Album::Album(List<Song*>* songs, const std::string& name)
	: _songs(songs), _name(name)
{
}

Album::~Album()
{
	for (uint i = 0; i < _songs->size(); i++)
	{
		delete _songs->getAtPosition(i);
	}
	delete _songs;
}

void Album::addSong(Song* song)
{
	_songs->addLast(song);
}

List<Song*>* Album::getSongs()
{
	return _songs;
}

std::string Album::getName()
{
	return _name;
}

void Album::setName(const std::string& name)
{
	_name = name;
}
