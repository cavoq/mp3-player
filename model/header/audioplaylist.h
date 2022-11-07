#ifndef AUDIOPLAYLIST_H
#define AUDIOPLAYLIST_H

#include "model/header/audiomedia.h"
#include <QMediaPlaylist>

class AudioPlaylist : public QMediaPlaylist
{
public:
    explicit AudioPlaylist(QObject *parent = nullptr);
    bool addMedia(AudioMedia audioContent);
    AudioMedia media(int index) const;
    AudioMedia currentAudio();
    int mediaCount() const;
    QList<AudioMedia> &getAudioContent();

private:
    QList<AudioMedia> audioContent;
};

#endif // AUDIOPLAYLIST_H
