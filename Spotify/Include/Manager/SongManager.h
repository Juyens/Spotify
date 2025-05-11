#pragma once

#include "List.h"
#include "Stack.h"
#include "Queue.h"
#include "Artist.h"
#include "Song.h"
#include "Album.h"
#include "Playlist.h"
#include "Utils.h"

#include <string>
#include <iostream>

class SongManager
{
private:
    Queue<Song*>* _playQueue;
    Stack<Song*>* _history;

    Song* _currentSong;

public:
    SongManager();
    ~SongManager();

    void show();

    void clearBox(int x, int y, int width, int height);
    void drawBox(int x, int y, int width, int height);

    void keyboard();

    void play(Album* album);
    void play(Playlist * playlist);
    void play(Song* song);

    void enqueue(Song* song);
    void next();

    Stack<Song*>* getHistory();
    Queue<Song*>* getPlayQueue();
};
