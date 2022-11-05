#ifndef SONGREADER_H
#define SONGREADER_H

#include "song.h"
#include <QStringList>

class SongReader
{

public:
    SongReader();
    QList<Song> &read(QStringList &songs);
};

#endif // SONGREADER_H
