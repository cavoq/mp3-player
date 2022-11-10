/**
 *  Declaration of the PlaylistComparator class, used to compare audios in the @see PlaylistTableView.
 */

#ifndef PLAYLISTCOMPARATOR_H
#define PLAYLISTCOMPARATOR_H

#include <QString>
#include "model/header/audiomedia.h"

class PlaylistComparator
{

public:

    /**
     * Constructs a PlaylistSorter object.
     *
     * @param column Column in a @see PlaylistTableModel.
     * @param order Order to sort.
     */
    PlaylistComparator(const int column, const Qt::SortOrder order);

    /**
     * Overrides the operator () to pass additional parameters to the comparator.
     *
     * @param audio1 First audio to compare.
     * @param audio2 Second audio to compare to.
     * @return Returns true or false, depending on the  {@link #order}.
     */
    bool operator()(const AudioMedia &audio1, const AudioMedia &audio2) const;

    /**
     * Compares two audios.
     *
     * @param audio1 First audio to compare.
     * @param audio2 Second audio to compare to.
     * @param column Column in a @see PlaylistTableModel.
     * @param order Order to sort.
     * @return If the order is ascending, returns true if the attribute of the first audio in the column is
     * greater than the attribute of the second audio in the column.
     * If the order is descending, returns true if the attribute of the first audio in the column is
     * less than the attribute of the second audio in the column.
     */
    bool compareAudios(const AudioMedia &audio1, const AudioMedia &audio2, const int column, const Qt::SortOrder order) const;

private:

    /**
     * Column of a @see PlaylistTableModel.
     */
    const int column;

    /**
     * Sort order @see Qt::SortOrder.
     */
    const Qt::SortOrder order;
};

#endif // PLAYLISTCOMPARATOR_H
