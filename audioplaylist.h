#ifndef AUDIOPLAYLIST_H
#define AUDIOPLAYLIST_H

#include "audiomedia.h"
#include <QMediaPlaylist>

class AudioPlaylist : public QMediaPlaylist
{
public:
    explicit AudioPlaylist(QObject *parent = nullptr);
    bool addMedia(const AudioMedia &audioContent);
    AudioMedia media(int index) const;
    QList<AudioMedia> &getMediaContent();

private:
    QList<AudioMedia> mediaContent = QList<AudioMedia>();
};

#endif // AUDIOPLAYLIST_H
