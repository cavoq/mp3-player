/**
 *  Declaration of the PlaylistTableModel class, which contains all data @see MainWindow communicates.
 */

#ifndef PLAYLISTTABLEMODEL_H
#define PLAYLISTTABLEMODEL_H

#include <QAbstractTableModel>
#include <QMediaPlaylist>
#include "model/header/audioplaylist.h"

class PlaylistTableModel : public QAbstractTableModel
{

public:

    /**
     * Constructs a PlaylistTableModel object.
     *
     * @param playlist AudioPlaylist that contains the data of the model.
     * @param parent Parent object.
     */
    explicit PlaylistTableModel(AudioPlaylist *playlist = nullptr, QObject *parent = nullptr);

    /**
     * Returns the header data of a section.
     *
     * @param section Section index.
     * @param orientation Orientation of the table.
     * @param role Role of the variant.
     * @return Returns the header data as a @see QVariant.
     */
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;

    /**
     * Sets the data of a row.
     *
     * @param indexes Corresponding model indexes of the row.
     * @param values Corresponding values the data will be set to.
     * @param role Role of the model indexes in the row.
     * @return Returns true if size of the indexes and values have the same size
     * and the row data was set successfully.
     */
    bool setRowData(const QModelIndexList &indexes, const QVariantList &values, int role = Qt::EditRole);

    /**
     * Get mime data on drag.
     *
     * @param indexes Indexes to get mime data from.
     * @return Returns mime data.
     */
    QMimeData *mimeData(const QModelIndexList &indexes) const override;

    /**
     * Sets the data if a item.
     *
     * @param index Index of the item.
     * @param roles Roles of the item.
     * @return Returns true if data could be set.
     */
    bool setItemData(const QModelIndex &index, const QMap<int, QVariant> &roles) override;

    /**
     * Get item flags.
     *
     * @param index Index to get the item flags from.
     * @return Returns the item flags of the corresponding index.
     */
    Qt::ItemFlags flags(const QModelIndex &index) const override;

    /**
     * Get supported drop actions.
     *
     * @return Returns the supported drop actions.
     */
    Qt::DropActions supportedDropActions() const override;

    /**
     * Drop data on a drag and drop operation.
     *
     * @param data Mime data to be dropped.
     * @param action Drop action used.
     * @param row Row to be dropped to.
     * @param column Column to be dropped to.
     * @param parent Parent index.
     * @return Returns false due to internal recursion.
     */
    bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) override;

    /**
     * Get row count.
     *
     * @param parent Parent object.
     * @return Returns the row count of the playlist table model.
     */
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;

    /**
     * Get the column count.
     *
     * @param parent Parent object.
     * @return Returns the column count of the playlist table model.
     */
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;

    /**
     * Inserts new empty rows.
     *
     * @param postion Index where the rows will be inserted.
     * @param rows Number of rows to be inserted.
     * @param index Unused parameter (needed for overriding).
     * @return Returns true if inserting was successful.
     */
    bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;

    /**
     * Remove rows.
     *
     * @param postion Index where the rows will be removed from.
     * @param rows Number of rows to be removed.
     * @param index Unused parameter (needed for overriding).
     * @return Returns true if removing was successful.
     */
    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;

    /**
     * Sets the data of a single entry of the playlist table model.
     *
     * @param index QModelIndex of the entry.
     * @param value QVariant containing the data.
     * @param role  Role of the entry.
     * @return Returns true if the index exists and the entry could be set to th data.
     */
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

    /**
     * Returns data of the playlist table model.
     *
     * @param index QModelIndex data will be returned from.
     * @param role Role of the data.
     * @return Returns the data as a QVariant.
     */
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

    /**
     * Get the model indexes of a row.
     *
     * @param row Index of row.
     * @return Returns all corresponding model indexes of the row as a QModelIndexList.
     */
    QModelIndexList getIndexesOfRow(int row);

    /**
     * Get the playlist.
     * @return Returns the playlist @see AudioPlaylist of the playlist table model.
     */
    AudioPlaylist *getPlaylist() const;

    /**
     * Sorts the playlist table model.
     * @param column Column to be sorted by.
     * @param order Order to sort the column by.
     */
    void sort(int column, Qt::SortOrder order = Qt::AscendingOrder) override;

    /// Column count of the table model.
    const int columnSize = 5;

private:

    /// AudioPlaylist containing the data of the model.
    AudioPlaylist *playlist;

    /// Last dragged row index.
    mutable int draggedRow;
};

#endif // PLAYLISTTABLEMODEL_H
