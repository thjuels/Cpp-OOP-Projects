#include "manager.h"
#include <iostream>

MusicManager::MusicManager(int user_max, int singers_max, int songs_max)
    : user_capacity(user_max), singers_capacity(singers_max),
      songs_capacity(songs_max), num_of_singers(0), num_of_songs(0),
      num_of_user(0) {
  // TODO 1: MusicManager constructor.
  cout << "MusicManager constructor" << endl;
  user_list = new PlayList *[user_max];
  singer_list = new Singer *[singers_max];
  song_list = new Song *[songs_max];
}

MusicManager::~MusicManager() {
  // TODO 6: Build the destructors.
  cout << "MusicManager destructor" << endl;
  for (int i = 0; i < num_of_user; i++) {
    delete user_list[i];
  }
  delete[] user_list;
  for (int i = 0; i < num_of_singers; i++) {
    delete singer_list[i];
  }
  delete[] singer_list;
  for (int i = 0; i < num_of_songs; i++) {
    delete song_list[i];
  }
  delete[] song_list;
}

void MusicManager::createSinger(const string &name, const string &nationality) {
  singer_list[num_of_singers++] = new Singer(name, nationality);
}

void MusicManager::createSong(const string &name, const string &singer_name) {
  // TODO 2: Add a song into the MusicManager.

  // Ask question, what to do in the case that the singer does not exist in
  // singer_list??, as not enough data passed into
  //  function in order to create a Singer object??
  //  I think assume singer already exists, or only return error if the singer
  //  isn't found
  bool check_singer = false;
  Singer *singer;
  for (int i = 0; i < num_of_singers; i++) {
    if (singer_list[i] &&
        singer_list[i]->getName() ==
            singer_name) { // does == operator work for string comparing
      singer = singer_list[i];
      check_singer = true;
    }
  }
  if (check_singer) {
    song_list[num_of_songs++] = new Song{name, singer};
  } else {
    cout << "Singer not found in list" << endl;
  }
}

void MusicManager::createPlaylist(const string &user_name) {
  user_list[num_of_user++] = new PlayList(user_name, MAX_SIZE);
  cout << "[Creation] Playlist of " << user_name << endl;
  // Add a new user with the given name to your data structure
  // (You can assume that the name is unique and the user list is not full.
}

void MusicManager::createPlaylistFromOther(const string &des_user_name,
                                           const string &src_user_name) {
  // TODO 5: Copy the playlist from your friend.
  cout << "[CopyCreation] Playlist of " << des_user_name
       << " (From:" << src_user_name << ")." << endl;
  // get loc of other user
  PlayList *src;
  PlayList *dest;
  for (int i = 0; i < num_of_user; i++) {
    if (user_list[i]->getUsername() == src_user_name) {
      src = user_list[i];
    }
  }
  dest = new PlayList{des_user_name, *src};
  user_list[num_of_user++] = dest;
  return;
}

void MusicManager::displayPlaylist(const string &user_name) const {
  for (int i = 0; i < num_of_user; i++) {
    if (user_list[i]->getUsername() == user_name) {
      user_list[i]->display();
      return;
    }
  }
}

void MusicManager::addSongToPlaylist(const string &user_name,
                                     const string &song_name) {
  for (int i = 0; i < num_of_user; i++) {
    if (user_list[i]->getUsername() == user_name) {
      for (int j = 0; j < num_of_songs; j++) {
        if (song_list[j]->getName() == song_name) {
          user_list[i]->addSong(song_list[j]);
          cout << "[Add] Song " << song_list[j]->getName() << " to playlist of "
               << user_list[i]->getUsername() << endl;
          return;
        }
      }
    }
  }
}

void MusicManager::removeSongFromPlaylist(const string &user_name,
                                          const string &song_name) {
  for (int i = 0; i < num_of_user; i++) {
    if (user_list[i]->getUsername() == user_name) {
      user_list[i]->removeSong(song_name);
      cout << "[Remove] Song " << song_name << " from playlist of "
           << user_list[i]->getUsername() << endl;
      return;
    }
  }
}
