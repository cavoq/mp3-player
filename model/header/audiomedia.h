/**
 *  Declaration of the AudioMedia class, defines the structure of a audio media.
 */

#ifndef AUDIOMEDIA_H
#define AUDIOMEDIA_H

#include <QMediaContent>
#include <QMediaMetaData>

class AudioMedia : public QMediaContent
{

public:

    /**
     * Constructs a AudioMedia object.
     *
     * @param contentUrl @see QUrl of the audio media.
     * @param titel Titel of the audio media.
     * @param artist Artist of the audio media.
     * @param album Album of the audio media.
     * @param length Length of the audio media.
     * @param genre Genre of the audio media.
     */
    AudioMedia(const QUrl &contentUrl = QUrl(), QString titel = QString(), QString artist = QString(),
               QString album = QString(), QString length = QString(), QString genre = QString());

    /// Titel of the audio media.
    QString titel;

    /// Artist of the audio media.
    QString artist;

    /// Album of the audio media.
    QString album;

    /// Length of the audio media.
    QString length;

    /// Genre of the audio media.
    QString genre;
};

#endif // AUDIOMEDIA_H
