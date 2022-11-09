#ifndef PLAYLISTSORTER_H
#define PLAYLISTSORTER_H

#include <QString>
#include "model/header/audiomedia.h"

class PlaylistSorter
{

public:
    PlaylistSorter(const int column, const Qt::SortOrder order);
    bool operator()(const AudioMedia &audio1, const AudioMedia &audio2) const;
    bool compareAudios(const AudioMedia &audio1, const AudioMedia &audio2, const int column, const Qt::SortOrder order) const;

private:
    const int column;
    const Qt::SortOrder order;
};

#endif // PLAYLISTSORTER_H
