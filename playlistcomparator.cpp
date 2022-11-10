/**
 *  Implementation of the PlaylistComparator class, used to compare audios in the @see PlaylistTableView.
 */

#include "playlistcomparator.h"

PlaylistComparator::PlaylistComparator(const int column, const Qt::SortOrder order): column(column), order(order) {}

bool PlaylistComparator::operator()(const AudioMedia &audio1, const AudioMedia &audio2) const
{
    return PlaylistComparator::compareAudios(audio1, audio2, column, order);
}

bool PlaylistComparator::compareAudios(const AudioMedia &audio1, const AudioMedia &audio2, const int column, const Qt::SortOrder order) const
{
    switch (column) {
        case 0:
            return order == Qt::SortOrder::AscendingOrder ? audio1.titel > audio2.titel : audio1.titel < audio2.titel;
        case 1:
            return order == Qt::SortOrder::AscendingOrder  ? audio1.artist > audio2.artist : audio1.artist < audio2.artist;
        case 2:
            return order == Qt::SortOrder::AscendingOrder  ? audio1.album > audio2.album : audio1.album < audio2.album;
        case 3:
            return order == Qt::SortOrder::AscendingOrder  ? audio1.length > audio2.length : audio1.length < audio2.length;
        case 4:
            return order == Qt::SortOrder::AscendingOrder  ? audio1.genre > audio2.genre : audio1.genre < audio2.genre;
        default:
            return -1;
    }
}
