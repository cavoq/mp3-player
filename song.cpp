#include "song.h"
#include <QString>

Song::Song() {}

Song::Song(QString titel, QString artist, QString album, QString length, QString path)
{
    this->titel = titel;
    this->artist = artist;
    this->album = album;
    this->length = length;
    this->path = path;
}
