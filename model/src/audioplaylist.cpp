#include "model/header/audioplaylist.h"

AudioPlaylist::AudioPlaylist(QObject *parent): QMediaPlaylist(parent) {}

bool AudioPlaylist::addMedia(AudioMedia audioContent)
{
    this->audioContent.append(audioContent);
    if (!QMediaPlaylist::addMedia(audioContent)) {
        return false;
    }
    return true;
}

AudioMedia AudioPlaylist::audioMedia(int index) const
{
    return this->audioContent.at(index);
}

QList<AudioMedia> &AudioPlaylist::getAudioContent()
{
    return this->audioContent;
}

int AudioPlaylist::mediaCount() const
{
    return this->audioContent.count();
}

AudioMedia AudioPlaylist::currentAudio()
{
    int currentIndex = QMediaPlaylist::currentIndex();
    return this->audioContent.at(currentIndex);
}

bool AudioPlaylist::removeMedia(int position)
{
    if (!QMediaPlaylist::removeMedia(position)) {
        return false;
    }
    if (position > audioContent.size()) {
        return false;
    }
    audioContent.removeAt(position);
    return true;
}

bool AudioPlaylist::insertMedia(int position, const AudioMedia &audioMedia)
{
    if (!QMediaPlaylist::insertMedia(position, audioMedia)) {
        return false;
    }
    if (position > audioContent.size()) {
        return false;
    }
    audioContent.insert(position, audioMedia);
    return true;
}
