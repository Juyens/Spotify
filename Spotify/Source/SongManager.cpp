#include "SongManager.h"
#include "Console.h"
#include "KeyboardInput.h"

SongManager::SongManager()
    : _playQueue(new Queue<Song*>()), _history(new Stack<Song*>()), _currentSong(nullptr)
{
}

SongManager::~SongManager()
{
    delete _playQueue;
    delete _history;
}

void SongManager::show()
{
    if (!_playQueue->isEmpty() && _currentSong)
    {
        auto consoleSize = Console::getSize();

        int width = 50;
        int height = 4;

        int x = consoleSize.width - width;
        int y = 0;

        drawBox(x, y, width, height);

        Console::writeAt(x + 2, y + 1, "Se esta reproduciendo...", FG::White | BG::Black);
        Console::writeAt(x + 2, y + 2, "-> " + _currentSong->getName() + " - " + _currentSong->getCredits()->getAuthor()->getFirst(), FG::White | BG::Black);
    }
}


void SongManager::clearBox(int x, int y, int width, int height)
{
    auto consoleSize = Console::getSize();

    Console::writeAt(x, y, std::string(width, ' '), FG::White | BG::Black);

    for (int i = 1; i < height - 1; ++i)
    {
        Console::writeAt(x, y + i, std::string(width, ' '), FG::White | BG::Black);
    }

    Console::writeAt(x, y + height - 1, std::string(width, ' '), FG::White | BG::Black);
}

void SongManager::drawBox(int x, int y, int width, int height)
{
    auto consoleSize = Console::getSize();

    Console::writeAt(x, y, char(218) + std::string(width - 2, char(196)) + char(191), FG::White | BG::Black);

    for (int i = 1; i < height - 1; ++i)
    {
        Console::writeAt(x, y + i, std::string(1, char(179)), FG::White | BG::Black);
        Console::writeAt(consoleSize.width - 1, y + i, std::string(1, char(179)), FG::White | BG::Black);
    }

    Console::writeAt(x, y + height - 1, char(192) + std::string(width - 2, char(196)) + char(217), FG::White | BG::Black);
}


void SongManager::keyboard()
{
    if (KeyboardInput::isKeyJustPressed(Key::RIGHT))
    {
        auto consoleSize = Console::getSize();

        int width = 50;
        int height = 4;

        int x = consoleSize.width - width;
        int y = 0;

        clearBox(x, y, width, height);

        next();
    }
}

void SongManager::play(Album* album)
{
    _playQueue->clear();

    for (uint i = 0; i < album->getSongs()->size(); i++)
    {
        auto song = album->getSongs()->getAtPosition(i);
        _playQueue->enqueue(song);
    }

    if (!_playQueue->isEmpty())
    {
        _currentSong = _playQueue->peek();
    }
}

void SongManager::play(Playlist* playlist)
{
    _playQueue->clear();

    for (uint i = 0; i < playlist->getSongs()->size(); i++)
    {
        auto song = playlist->getSongs()->getAtPosition(i);
        _playQueue->enqueue(song);
    }

    if (!_playQueue->isEmpty())
    {
        _currentSong = _playQueue->peek();
    }
}

void SongManager::play(Song* song)
{
    _playQueue->clear();
    _playQueue->enqueue(song);

    _currentSong = song;
}

void SongManager::enqueue(Song* song)
{
    _playQueue->enqueue(song);
}

void SongManager::next()
{
    if (!_playQueue->isEmpty() && _currentSong)
    {
        _history->push(_currentSong);
        _currentSong = _playQueue->dequeue();

        if (!_playQueue->isEmpty())
        {
            _currentSong = _playQueue->peek();
        }
    }
}

Stack<Song*>* SongManager::getHistory()
{
    return _history;
}

Queue<Song*>* SongManager::getPlayQueue()
{
    return _playQueue;
}
