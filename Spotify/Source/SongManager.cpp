#include "SongManager.h"

SongManager::SongManager(List<Song*>* songs)
    : _allSongs(songs), _playQueue(new Queue<Song*>()), _history(new Stack<Song*>())
{
}

SongManager::~SongManager()
{
    delete _playQueue;
    delete _history;
}

void SongManager::show()
{

}

void SongManager::keyboard()
{

}

void SongManager::play(Album* album)
{

}

void SongManager::play(Playlist* album)
{

}

void SongManager::play(Song* song)
{
    _history->push(song);
}

void SongManager::enqueue(Song* song)
{
    _playQueue->enqueue(song);
}

Song* SongManager::next()
{
    if (!_playQueue->isEmpty())
    {
        Song* song = _playQueue->dequeue();
        play(song);
        return song;
    }
    return nullptr;
}

Stack<Song*>* SongManager::getHistory()
{
    return _history;
}

Queue<Song*>* SongManager::getPlayQueue()
{
    return _playQueue;
}
