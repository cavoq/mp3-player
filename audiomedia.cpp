#include "audiomedia.h"

AudioMedia::AudioMedia(const QUrl &contentUrl, QString titel, QString artist,
                       QString album, QString length, QString genre): QMediaContent(contentUrl), titel(titel),
    artist(artist), album(album), length(length), genre(genre) {}

void AudioMedia::setMetaData(QString titel, QString artist, QString album, QString length, QString genre)
{
    this->titel = titel;
    this->artist = artist;
    this->album = album;
    this->length = length;
    this->genre = genre;
}
