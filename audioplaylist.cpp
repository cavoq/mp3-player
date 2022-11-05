#include "audioplaylist.h"

AudioPlaylist::AudioPlaylist(QObject *parent): QMediaPlaylist{parent} {}

bool AudioPlaylist::addMedia(const AudioMedia &audioContent)
{
    this->mediaContent.append(audioContent);
    if (!QMediaPlaylist::addMedia(audioContent)) {
        return false;
    }
    return true;
}

AudioMedia AudioPlaylist::media(int index) const
{
    return this->mediaContent.at(index);
}

QList<AudioMedia> &AudioPlaylist::getMediaContent()
{
    return this->mediaContent;
}
