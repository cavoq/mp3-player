#include "songtablemodel.h"

SongTableModel::SongTableModel(QList<Song> &songs, QObject *parent) : QAbstractTableModel{parent}, songs(songs) {}

QVariant SongTableModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    if (role != Qt::DisplayRole)
            return QVariant();

    if (orientation == Qt::Horizontal) {
        switch (section) {
            case 0:
                return tr("Titel");
            case 1:
                return tr("Künstler");
            case 2:
                return tr("Album");
            case 3:
                return tr("Länge");
            default:
                break;
        }
    }
    return QVariant();
}

int SongTableModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : this->songs.size();
}

int SongTableModel::columnCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : this->columnSize;
}

bool SongTableModel::removeRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginRemoveRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row)
        songs.removeAt(position);

    endRemoveRows();
    return true;
}

bool SongTableModel::insertRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginInsertRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row)
        songs.insert(position, Song());

    endInsertRows();
    return true;
}

QVariant SongTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= this->songs.size() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole) {
        const auto &song = this->songs.at(index.row());
        switch (index.column()) {
            case 0:
                return song.titel;
            case 1:
                return song.artist;
            case 2:
                return song.album;
            case 3:
                return song.length;
            default:
                break;
        }
    }
    return QVariant();
}

bool SongTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        const int row = index.row();
        auto song = this->songs.value(row);

        switch (index.column()) {
            case 0:
                song.titel = value.toString();
                break;
            case 1:
                song.artist = value.toString();
                break;
            case 2:
                song.album = value.toString();
                break;
            case 3:
                song.length = value.toString();
                break;
            default:
                return false;
        }
        this->songs.replace(row, song);
        emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});

        return true;
    }

    return false;
}

const QList<Song>& SongTableModel::getSongs() const
{
    return this->songs;
}
