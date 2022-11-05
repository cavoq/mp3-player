#include "mainwindow.h"
#include "audiomedia.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QMediaMetaData>
#include <QAudioOutput>

int LOAD_INDEX = 0;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setIcons();
    player = new QMediaPlayer(this);
    connect(ui->loadPlaylistButton, SIGNAL(clicked()), this, SLOT(loadPlaylist()));
    connect(player, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), this, SLOT(onMediaStatusChanged(QMediaPlayer::MediaStatus)));
    connect(player, SIGNAL(metaDataChanged()), this, SLOT(onMetaDataChanged()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setIcons()
{
    ui->rewindButton->setIcon(QIcon(":/icons/rewind.png"));
    ui->fastForwardButton->setIcon(QIcon(":/icons/fastForward.png"));
    ui->lastSongButton->setIcon(QIcon(":/icons/last.png"));
    ui->nextSongButton->setIcon(QIcon(":/icons/next.png"));
    ui->muteButton->setIcon(QIcon(":/icons/mute.png"));
    ui->stopButton->setIcon(QIcon(":/icons/stop.png"));
    ui->playStopButton->setIcon(QIcon(":/icons/resumePlaying.png"));
}

void MainWindow::loadPlaylist()
{
    QList<QUrl> songUrls = getSongUrlsFromDialog();
    AudioPlaylist *playlist = new AudioPlaylist();
    for (int i = 0; i < songUrls.count(); ++i) {
        playlist->addMedia(AudioMedia(songUrls[i]));
    }
    playlistTableModel = new PlaylistTableModel(playlist, this);
    ui->tableView->setModel(playlistTableModel);
    setMetaData(playlist->getMediaContent());
}

QList<QUrl> MainWindow::getSongUrlsFromDialog()
{
    const QList<QUrl> songUrls = QFileDialog::getOpenFileUrls(this, tr("Wähle songs aus"), tr("Mp3 files (*.mp3)"));
    return songUrls;
}

void MainWindow::setMetaData(QList<AudioMedia> &songs)
{
    for (int i = 0; i < songs.count(); ++i) {
        player->setMedia(songs[i]);
        player->setPlaylist(playlistTableModel->getPlaylist());
        player->play();
    }
}

void MainWindow::onMediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    if (status == QMediaPlayer::MediaStatus::LoadedMedia) {
        QVariantList metaData;
        const QVariant title = player->metaData(QMediaMetaData::Title);
        const QVariant artist = player->metaData(QMediaMetaData::ContributingArtist);
        const QVariant album = player->metaData(QMediaMetaData::AlbumTitle);
        const QVariant length = player->metaData(QMediaMetaData::Duration);
        const QVariant genre = player->metaData(QMediaMetaData::Genre);
        metaData << title << artist << album << length << genre;
        qInfo()<<metaData;
        playlistTableModel->setRowData(playlistTableModel->getIndexesOfRow(LOAD_INDEX), metaData);
        LOAD_INDEX += 1;
    }
}

void MainWindow::onMetaDataChanged()
{
    qInfo()<<player->availableMetaData();
    qInfo()<<player->metaData(QMediaMetaData::Duration);
}
