#ifndef PLAYLISTTABLEMODEL_H
#define PLAYLISTTABLEMODEL_H

#include <QAbstractTableModel>
#include <QMediaPlaylist>
#include "model/header/audioplaylist.h"

class PlaylistTableModel : public QAbstractTableModel
{

public:
    explicit PlaylistTableModel(AudioPlaylist *playlist = nullptr, QObject *parent = nullptr);
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    bool setRowData(const QModelIndexList &indexes, const QVariantList &values, int role = Qt::EditRole);
    QMimeData *mimeData(const QModelIndexList &indexes) const override;
    bool setItemData(const QModelIndex &index, const QMap<int, QVariant> &roles) override;
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    Qt::DropActions supportedDropActions() const override;
    bool dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent) override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QModelIndexList getIndexesOfRow(int row);
    AudioPlaylist *getPlaylist() const;
    void sort(int column, Qt::SortOrder order = Qt::AscendingOrder) override;
    const int columnSize = 5;

private:
    AudioPlaylist *playlist;
    mutable int draggedRow;
};

#endif // PLAYLISTTABLEMODEL_H
