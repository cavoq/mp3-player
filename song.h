#ifndef SONG_H
#define SONG_H

#include <QString>

class Song
{

public:
    Song();
    Song(QString titel, QString artist, QString album, QString length, QString path);
    QString titel;
    QString artist;
    QString album;
    QString length;
    QString path;
};

#endif // SONG_H
