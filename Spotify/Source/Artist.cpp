#include "Artist.h"

Artist::Artist(const std::string& name)
	: _albums(new List<Album*>())
{
}

Artist::Artist(List<Album*>* albums, const std::string& name)
	: _albums(albums), _name(name)
{
}

Artist::~Artist()
{
	for (uint i = 0; i < _albums->size(); i++)
	{
		delete _albums->getAtPosition(i);
	}
	delete _albums;
}

void Artist::addAlbum(Album* album)
{
	_albums->addLast(album);
}

List<Album*>* Artist::getAlbums()
{
	return _albums;
}

List<Song*>* Artist::getSongs()
{
    List<Song*>* allSongs = new List<Song*>();

    for (uint j = 0; j < _albums->size(); ++j)
    {
        Album* album = _albums->getAtPosition(j);
        List<Song*>* songs = album->getSongs();
        for (uint k = 0; k < songs->size(); ++k)
        {
            allSongs->addLast(songs->getAtPosition(k));
        }
    }
    return allSongs;
}

std::string Artist::getName()
{
	return _name;
}

void Artist::setName(const std::string& name)
{
	_name = name;
}
