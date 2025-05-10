#include "Playlist.h"

Playlist::Playlist(const std::string& name)
	: _name(name), _songs(new List<Song*>())
{

}

Playlist::~Playlist()
{
	for (uint i = 0; i < _songs->size(); i++)
	{
		delete _songs->getAtPosition(i);
	}
	delete _songs;
}

List<Song*>* Playlist::getSongs()
{
	return _songs;
}

std::string Playlist::getName()
{
	return _name;
}

void Playlist::setName(const std::string& name)
{
	_name = name;
}

void Playlist::addSong(Song* song)
{
	_songs->addLast(song);
}
