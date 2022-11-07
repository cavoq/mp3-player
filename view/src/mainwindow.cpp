#include "view/header/mainwindow.h"
#include "model/header/audiomedia.h"
#include "ui_mainwindow.h"
#include <random>

#include <QFileDialog>
#include <QMediaMetaData>
#include <QAudioOutput>
#include <QTime>
#include <QShortcut>

#include <taglib/taglib.h>
#include <taglib/fileref.h>

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

qint64 FORWARD_STEP = 15000;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setIcons();
    player = new QMediaPlayer(this);
    filterProxyModel = new QSortFilterProxyModel(this);
    connectSignals();
    createShortcuts();
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

void MainWindow::connectSignals()
{
    connect(ui->loadPlaylistButton, SIGNAL(clicked()), this, SLOT(loadPlaylist()));
    connect(ui->playStopButton, SIGNAL(toggled(bool)), this, SLOT(switchPlaying(bool)));
    connect(ui->muteButton, SIGNAL(toggled(bool)), this, SLOT(switchMute(bool)));
    connect(ui->fastForwardButton, SIGNAL(clicked()), this, SLOT(fastForward()));
    connect(ui->rewindButton, SIGNAL(clicked()), this, SLOT(rewind()));
    connect(ui->stopButton, SIGNAL(clicked()), this, SLOT(stopSong()));
    connect(ui->songSlider, SIGNAL(sliderPressed()), player, SLOT(pause()));
    connect(ui->songSlider, SIGNAL(sliderReleased()), this, SLOT(onSongSliderReleased()));
    connect(ui->soundVolumeSlider, SIGNAL(sliderMoved(int)), player, SLOT(setVolume(int)));
    connect(ui->songSearchLineEdit, SIGNAL(textChanged(QString)), this, SLOT(searchSong(QString)));
    connect(player, SIGNAL(currentMediaChanged(QMediaContent)), this, SLOT(onCurrentMediaChanged(QMediaContent)));
    connect(player, SIGNAL(volumeChanged(int)), this, SLOT(onVolumeChanged(int)));
    connect(player, SIGNAL(durationChanged(qint64)), this,  SLOT(onDurationChanged(qint64)));
    connect(player, SIGNAL(positionChanged(qint64)), this, SLOT(onPositionChanged(qint64)));
}

void MainWindow::createShortcuts()
{
    QList<QShortcut*> shortcuts;
    shortcuts.append(new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_O), this, SLOT(loadPlaylist())));
    shortcuts.append(new QShortcut(QKeySequence(Qt::Key_Space), this, SLOT(switchPlaying())));
    shortcuts.append(new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_N), this, SLOT(nextSong())));
    shortcuts.append(new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_L), this, SLOT(previousSong())));
    shortcuts.append(new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Right), this, SLOT(fastForward())));
    shortcuts.append(new QShortcut(QKeySequence(Qt::CTRL + Qt::Key_Left), this, SLOT(rewind())));
    for (int i = 0; i < shortcuts.count() - 2; ++i) {
        shortcuts[i]->setAutoRepeat(false);
    }
}

void MainWindow::switchPlaying()
{
    ui->playStopButton->setChecked(!ui->playStopButton->isChecked());
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

void MainWindow::onCurrentSelectionChanged(const QItemSelection &current, const QItemSelection &previous)
{
    if (current.indexes().isDetached() || current.indexes().isEmpty()) {
        return;
    }
    int row = current.indexes().at(0).row();
    player->playlist()->setCurrentIndex(row);
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

void MainWindow::onCurrentMediaChanged(QMediaContent currentMedia)
{
    int currentIndex = player->playlist()->currentIndex();
    ui->playlistTableView->selectRow(currentIndex);
    ui->songNameLabel->setText(playlistTableModel->getPlaylist()->currentAudio().titel);
    ui->interpretLabel->setText(playlistTableModel->getPlaylist()->currentAudio().artist);
    player->play();
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
    if (songUrls.empty()) {
        return;
    }
    AudioPlaylist *playlist = new AudioPlaylist();
    playlistTableModel = new PlaylistTableModel(playlist, this);
    for (int i = 0; i < songUrls.count(); ++i) {
        playlist->addMedia(AudioMedia(songUrls[i]));
        playlistTableModel->setRowData(playlistTableModel->getIndexesOfRow(i), getMetaData(songUrls[i]));
    };
    filterProxyModel->setSourceModel(playlistTableModel);
    ui->playlistTableView->setModel(filterProxyModel);
    player->setPlaylist(playlist);
    connect(ui->nextSongButton, SIGNAL(clicked()), this, SLOT(nextSong()));
    connect(ui->lastSongButton, SIGNAL(clicked()), this, SLOT(previousSong()));
    connect(ui->randomSongButton, SIGNAL(clicked()), this, SLOT(randomSong()));
    connect(ui->playlistTableView->selectionModel(), SIGNAL(selectionChanged(QItemSelection,QItemSelection)),
            this, SLOT(onCurrentSelectionChanged(QItemSelection,QItemSelection)));
}

void MainWindow::stopSong()
{
    player->stop();
    ui->playStopButton->setChecked(false);
}

void MainWindow::searchSong(QString titel)
{
    filterProxyModel->setFilterKeyColumn(0);
    filterProxyModel->setFilterFixedString(titel);
    filterProxyModel->filterKeyColumn();
}

void MainWindow::randomSong()
{
    std::random_device randomHardwareNumber;
    std::mt19937 seedGenerator(randomHardwareNumber());
    std::uniform_int_distribution<> distribution(0,  player->playlist()->mediaCount() - 1);
    player->playlist()->setCurrentIndex(distribution(seedGenerator));
}

void MainWindow::nextSong()
{
    int currentIndex = player->playlist()->currentIndex();
    if (currentIndex >= player->playlist()->mediaCount() - 1) {
        return;
    }
    player->playlist()->setCurrentIndex(currentIndex + 1);
}

void MainWindow::previousSong()
{
    int currentIndex = player->playlist()->currentIndex();
    if (currentIndex <= 0) {
        return;
    }
    player->playlist()->setCurrentIndex(currentIndex - 1);
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
