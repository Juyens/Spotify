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
    List<Song*>* _allSongs;
    Queue<Song*>* _playQueue;
    Stack<Song*>* _history;

public:
    SongManager(List<Song*>* _allSongs);
    ~SongManager();

    void show();
    void keyboard();

    void play(Album* album);
    void play(Playlist * album);
    void play(Song* song);

    void enqueue(Song* song);
    Song* next();

    Stack<Song*>* getHistory();
    Queue<Song*>* getPlayQueue();
};
