/**
 * Implementation of the AudioMedia class, defines the structure of a audio media.
 */

#include "model/header/audiomedia.h"

AudioMedia::AudioMedia(const QUrl &contentUrl, QString titel, QString artist,
                       QString album, QString length, QString genre): QMediaContent(contentUrl), titel(titel),
    artist(artist), album(album), length(length), genre(genre) {}
