#ifndef SONGTABLEMODEL_H
#define SONGTABLEMODEL_H

#include <QAbstractTableModel>
#include "song.h"

class SongTableModel : public QAbstractTableModel
{

public:
    explicit SongTableModel(QList<Song> &songList, QObject *parent = nullptr);
    QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const override;
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;
    bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex()) override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    const QList<Song>& getSongs() const;
    const unsigned int columnSize = 4;


private:
    QList<Song> &songs;
};

#endif // SONGTABLEMODEL_H
