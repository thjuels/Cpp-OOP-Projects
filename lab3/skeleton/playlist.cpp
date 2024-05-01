#include "playlist.h"
#include <iostream>

PlayList::PlayList(const string& username, int capacity): username(username), capacity(capacity) {
    songs = new const Song*[capacity];  // assuming a maximum of 100 songs
    for (int i = 0; i < capacity; i++) {
        songs[i] = nullptr;
    }
}

PlayList::PlayList(const string& username, const PlayList& playlist, int capacity): username(username),capacity(capacity) {
    // TODO 3: PlayList constructor.
    if (playlist.capacity < capacity){ //need to create playlist with larger capacity
        songs = new const Song*[capacity];//create new array
        int i = 0;
        for (; i < playlist.capacity; i++){
            songs[i] = playlist.songs[i];
        }
        for (; i < this->capacity; i++){
            songs[i] = nullptr;
        }
    } 
    else if (playlist.capacity == this->capacity){
        songs = new const Song*[capacity];
        for (int i = 0; i < playlist.capacity; i++){
            songs[i] = playlist.songs[i];
        }
    }
}

PlayList::~PlayList() {
    // TODO 6: Build the destructors.
    // for (int i = 0; i < capacity; i++){
    //     delete songs[i];
    // }
    delete [] songs;
}

void PlayList::addSong(const Song* song) {
    // TODO 4: Add and Remove Songs of a Playlist.
    //need to check if number of songs is at capacity
    int count = 0;
    for (int i = 0; i < capacity; i++){
        if (songs[i]){
            count++;
        }
        else
            break;
    }
    if (count <= capacity){
           songs[count] = song;
    }
}

void PlayList::removeSong(const string& name) {
    // TODO 4: Add and Remove Songs of a Playlist.
    int i = 0;
    for (; i < this->capacity; i++){
        if (songs[i] && songs[i]->getName() == name){//if valid mem and name is same
            for (; i < this->capacity - 1; i++) {
                songs[i] = songs[i + 1];
            }
            break;
        }
    }
}

string PlayList::getUsername() const {
    return username;
}

void PlayList::display() const {
    cout << "========================================" << endl; 
    cout << "Playlist of " << username << endl;
    for (int i = 0; i < capacity; i++) {
        if (songs[i] != nullptr) {
            cout << i << ". " << songs[i]->getName() << " - " << songs[i]->getSinger()->getName() << endl;
        }
    }
    cout << "========================================" << endl;
}

