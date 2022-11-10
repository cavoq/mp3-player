/**
 *  Declaration of the AudioPlaylist class, which contains @see AudioMedia.
 */

#ifndef AUDIOPLAYLIST_H
#define AUDIOPLAYLIST_H

#include "model/header/audiomedia.h"
#include <QMediaPlaylist>

class AudioPlaylist : public QMediaPlaylist
{

public:

    /**
     * Constructs a AudioPlaylist object.
     *
     * @param parent Parent object.
     */
    explicit AudioPlaylist(QObject *parent = nullptr);

    /**
     * Adds media to the playlist.
     *
     * @param audioContent @see AudioContent to add.
     * @return Returns true if the audio content was successfully added.
     */
    bool addMedia(AudioMedia audioContent);

    /**
     * Get the audio media by index.
     *
     * @param index Index of the media to retrieve.
     * @return Returns the audio media in the index, if it exists.
     */
    AudioMedia audioMedia(int index) const;

    /**
     * Get the current audio.
     *
     * @return Returns the current audio.
     */
    AudioMedia currentAudio();

    /**
     * Get the current media count.
     *
     * @return Returns the media count.
     */
    int mediaCount() const;

    /**
     * Removes a media.
     *
     * @param position Position to remove the media from.
     * @return Returns true if removing was successful.
     */
    bool removeMedia(int position);

    /**
     * Inserts a media.
     *
     * @param position Position to insert the media in.
     * @param audioMedia AudioMedia to be inserted.
     * @return Returns true if inserting was successful.
     */
    bool insertMedia(int position, const AudioMedia &audioMedia);

    /**
     * Get the audio content.
     *
     * @return Returns the audio medias as a list.
     */
    QList<AudioMedia> &getAudioContent();

private:

    /// List of audio medias.
    QList<AudioMedia> audioContent;
};

#endif // AUDIOPLAYLIST_H
