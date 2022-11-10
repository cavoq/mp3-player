/**
 *  Implementation of the PlaylistTableModel class, which contains all data @see MainWindow communicates.
 */

#include "model/header/playlisttablemodel.h"
#include "model/header/audiomedia.h"
#include "playlistcomparator.h"

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

PlaylistTableModel::PlaylistTableModel(AudioPlaylist *playlist, QObject *parent) : QAbstractTableModel{parent}, playlist(playlist) {}

QVariant PlaylistTableModel::headerData(int section, Qt::Orientation orientation, int role) const
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
            case 4:
                return tr("Genre");
            default:
                break;
        }
    }
    return QVariant();
}

int PlaylistTableModel::rowCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : this->playlist->mediaCount();
}

int PlaylistTableModel::columnCount(const QModelIndex &parent) const
{
    return parent.isValid() ? 0 : this->columnSize;
}

bool PlaylistTableModel::removeRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginRemoveRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row)
        playlist->removeMedia(row);

    endRemoveRows();
    return true;
}

bool PlaylistTableModel::insertRows(int position, int rows, const QModelIndex &index)
{
    Q_UNUSED(index);
    beginInsertRows(QModelIndex(), position, position + rows - 1);

    for (int row = 0; row < rows; ++row)
        playlist->insertMedia(position, AudioMedia());

    endInsertRows();
    return true;
}

bool PlaylistTableModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if (index.isValid() && role == Qt::EditRole) {
        const int row = index.row();
        AudioMedia song = this->playlist->audioMedia(row);

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
            case 4:
                song.genre = value.toString();
                break;
            default:
                return false;
        }

        this->playlist->getAudioContent().replace(row, song);
        emit dataChanged(index, index, {Qt::DisplayRole, Qt::EditRole});
        return true;
    }

    return false;
}

bool PlaylistTableModel::setRowData(const QModelIndexList &indexes, const QVariantList &values, int role)
{
    if (indexes.count() != values.count()) {
        return false;
    }
    for (int i = 0; i < values.count(); ++i) {
        if (!setData(indexes[i], values[i], role)) {
            return false;
        }
    }
    return true;
}

QVariant PlaylistTableModel::data(const QModelIndex &index, int role) const
{
    if (!index.isValid())
        return QVariant();

    if (index.row() >= this->playlist->mediaCount() || index.row() < 0)
        return QVariant();

    if (role == Qt::DisplayRole) {
        AudioMedia song = this->playlist->audioMedia(index.row());

        switch (index.column()) {
            case 0:
                return song.titel;
            case 1:
                return song.artist;
            case 2:
                return song.album;
            case 3:
                return song.length;
            case 4:
                return song.genre;
            default:
                break;
        }
    }

    return QVariant();
}

QModelIndexList PlaylistTableModel::getIndexesOfRow(int row)
{
    QModelIndexList indexes;
    for (int column = 0; column < columnSize; ++column) {
        indexes.append(index(row, column));
    }
    return indexes;
}

Qt::ItemFlags PlaylistTableModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags = Qt::ItemIsEnabled | Qt::ItemIsSelectable | Qt::ItemIsDragEnabled;

        if(!index.isValid()) {
            flags |= Qt::ItemIsDropEnabled;
        }

        return flags;
}

Qt::DropActions PlaylistTableModel::supportedDropActions() const
{
    return Qt::MoveAction | Qt::CopyAction;
}

bool PlaylistTableModel::setItemData(const QModelIndex &index, const QMap<int, QVariant> &roles)
{
    if(!roles.contains(Qt::EditRole) && !roles.contains(Qt::DisplayRole)) {
        return false;
    }

    setData(index, roles[Qt::DisplayRole]);
    return true;
}

QMimeData *PlaylistTableModel::mimeData(const QModelIndexList &indexes) const
{
    draggedRow = indexes.at(0).row();
    return QAbstractTableModel::mimeData(indexes);
}

bool PlaylistTableModel::dropMimeData(const QMimeData *data, Qt::DropAction action, int row, int column, const QModelIndex &parent)
{
    Q_UNUSED(parent);
    Q_UNUSED(column);

    QList<AudioMedia> &audioList = playlist->getAudioContent();

    if(row == -1) {
        row = rowCount();
    }

    AudioMedia replacedSong = audioList.at(row - 1);
    AudioMedia draggedSong = audioList.at(draggedRow);

    audioList.replace(row - 1, draggedSong);
    audioList.replace(draggedRow, replacedSong);

    emit dataChanged(this->index(0, 0), this->index(this->rowCount() - 1, this->columnCount() - 1));
    return false;
}

AudioPlaylist *PlaylistTableModel::getPlaylist() const
{
    return this->playlist;
}

void PlaylistTableModel::sort(int column, Qt::SortOrder order)
{
    QList<AudioMedia> &audioList = playlist->getAudioContent();
    std::sort(audioList.begin(), audioList.end(), PlaylistComparator(column, order));

    emit dataChanged(this->index(0, 0), this->index(this->rowCount() - 1, this->columnCount() - 1));
}

