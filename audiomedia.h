#ifndef AUDIOMEDIA_H
#define AUDIOMEDIA_H

#include <QMediaContent>
#include <QMediaMetaData>

class AudioMedia : public QMediaContent
{

public:
    AudioMedia(const QUrl &contentUrl = QUrl(), QString titel = QString(), QString artist = QString(),
               QString album = QString(), QString length = QString(), QString genre = QString());
    QString titel;
    QString artist;
    QString album;
    QString length;
    QString genre;
};

#endif // AUDIOMEDIA_H
