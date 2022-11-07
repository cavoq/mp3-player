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
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    QModelIndexList getIndexesOfRow(int row);
    AudioPlaylist *getPlaylist() const;
    const int columnSize = 5;

private:
    AudioPlaylist *playlist;
};

#endif // PLAYLISTTABLEMODEL_H
