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

AudioMedia AudioPlaylist::media(int index) const
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


