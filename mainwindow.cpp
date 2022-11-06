#include "mainwindow.h"
#include "audiomedia.h"
#include "ui_mainwindow.h"
#include <chrono>
#include <thread>

#include <QFileDialog>
#include <QMediaMetaData>
#include <QAudioOutput>
#include <QTime>
#include <taglib/taglib.h>
#include <taglib/fileref.h>

qint64 FORWARD_STEP = 15000;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setIcons();
    player = new QMediaPlayer(this);
    connect(ui->loadPlaylistButton, SIGNAL(clicked()), this, SLOT(loadPlaylist()));
    connect(ui->playStopButton, SIGNAL(toggled(bool)), this, SLOT(switchPlaying(bool)));
    connect(ui->muteButton, SIGNAL(toggled(bool)), this, SLOT(switchMute(bool)));
    connect(ui->fastForwardButton, SIGNAL(clicked()), this, SLOT(fastForward()));
    connect(ui->rewindButton, SIGNAL(clicked()), this, SLOT(rewind()));
    connect(ui->stopButton, SIGNAL(clicked()), player, SLOT(stop()));
    connect(ui->songSlider, SIGNAL(sliderPressed()), player, SLOT(pause()));
    connect(ui->songSlider, SIGNAL(sliderReleased()), this, SLOT(onSongSliderReleased()));
    connect(ui->soundVolumeSlider, SIGNAL(sliderMoved(int)), player, SLOT(setVolume(int)));
    connect(player, SIGNAL(volumeChanged(int)), this, SLOT(onVolumeChanged(int)));
    connect(player, SIGNAL(durationChanged(qint64)), this,  SLOT(onDurationChanged(qint64)));
    connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(onPositionChanged(qint64)));
    connect(player, SIGNAL(mediaStatusChanged(QMediaPlayer::MediaStatus)), this, SLOT(onMediaStatusChanged(QMediaPlayer::MediaStatus)));
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
    ui->muteButton->setIcon(QIcon(":/icons/sound.png"));
    ui->stopButton->setIcon(QIcon(":/icons/stop.png"));
    ui->playStopButton->setIcon(QIcon(":/icons/resumePlaying.png"));
}

void MainWindow::fastForward()
{
    qint64 currentPosition = player->position();
    setPosition(currentPosition + FORWARD_STEP);
}

void MainWindow::rewind()
{
    qint64 currentPosition = player->position();
    player->setPosition(currentPosition - FORWARD_STEP);
}

void MainWindow::onSongSliderReleased()
{
    setPosition(ui->songSlider->sliderPosition());
    player->play();
}

void MainWindow::setPosition(qint64 position)
{
    if (position < 0) {
        position = 0;
    }
    if (position > player->duration()) {
        position = player->duration();
    }
    player->setPosition(position);
}

void MainWindow::onVolumeChanged(int volume)
{
    if (volume < 0 || volume > 100) {
        return;
    }
    ui->soundVolumeSlider->setSliderPosition(volume);
}

void MainWindow::onDurationChanged(qint64 duration)
{
    setTimeLabel(ui->durationLabel, duration);
    ui->songSlider->setMaximum(duration);
}

void MainWindow::onPositionChanged(qint64 position)
{
    setTimeLabel(ui->positionLabel, position);
    ui->songSlider->setSliderPosition(position);
}

void MainWindow::setTimeLabel(QLabel *label, qint64 timeInMs)
{
    QString timeAsString = QDateTime::fromTime_t(long (timeInMs / 1000)).toUTC().toString("m:ss");
    label->setText(timeAsString);
}

void MainWindow::switchMute(bool muted)
{
    if (!muted) {
        switchButton(ui->muteButton, QIcon(":/icons/sound"), "Stummschaltung aufheben");
        player->setMuted(false);
        return;
    }
    switchButton(ui->muteButton, QIcon(":/icons/mute"), "Stummschalten");
    player->setMuted(true);
}

void MainWindow::switchPlaying(bool playing)
{
    if (!playing) {
        switchButton(ui->playStopButton, QIcon(":/icons/resumePlaying"), "Song wiedergeben");
        player->pause();
        return;
    }
    switchButton(ui->playStopButton, QIcon(":/icons/playing"), "Wiedergabe stoppen");
    player->play();
}

void MainWindow::switchButton(QToolButton *button, QIcon icon, QString tooltip)
{
    button->setIcon(icon);
    button->setToolTip(tooltip);
}

void MainWindow::loadPlaylist()
{
    QList<QUrl> songUrls = getSongUrlsFromDialog();
    AudioPlaylist *playlist = new AudioPlaylist();
    for (int i = 0; i < songUrls.count(); ++i) {
        playlist->addMedia(AudioMedia(songUrls[i]));
    }
    playlistTableModel = new PlaylistTableModel(playlist, this);
    ui->playlistTableView->setModel(playlistTableModel);
    for (int i = 0; i < songUrls.count(); ++i) {
        playlistTableModel->setRowData(playlistTableModel->getIndexesOfRow(i), getMetaData(songUrls[i]));
    }
}

QList<QUrl> MainWindow::getSongUrlsFromDialog()
{
    const QList<QUrl> songUrls = QFileDialog::getOpenFileUrls(this, tr("Wähle songs aus"), tr("Mp3 files (*.mp3)"));
    return songUrls;
}

QVariantList MainWindow::getMetaData(QUrl songUrl)
{
    TagLib::FileRef file = TagLib::FileRef(songUrl.path().toStdString().c_str());
    QVariantList metaData;
    const QVariant title = QVariant(file.tag()->title().toCString());
    const QVariant artist = QVariant(file.tag()->artist().toCString());
    const QVariant album = QVariant(file.tag()->album().toCString());
    const QVariant length = QDateTime::fromTime_t(long (file.audioProperties()->lengthInMilliseconds() / 1000)).toUTC().toString("m:ss");
    const QVariant genre = QVariant(file.tag()->genre().toCString());
    metaData << title << artist << album << length << genre;
    return metaData;
}

void MainWindow::onMediaStatusChanged(QMediaPlayer::MediaStatus status)
{
    if (status == QMediaPlayer::MediaStatus::LoadedMedia) {

    }
}

void MainWindow::onMetaDataChanged()
{
}
